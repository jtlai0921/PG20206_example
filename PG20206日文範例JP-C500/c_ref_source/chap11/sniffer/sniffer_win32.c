/* 2003/7/20
 *
 * sniffer_win32.c - [Ethernet packet capture] for Windows
 * 
 * [how to compile]
 *   > cl sniffer_win32.c ws2_32.lib
 *
 * Presented by YUTAKA
 */

#ifdef _WIN32
#include <winsock2.h>
#include <MSTcpIP.h>  // for SIO_RCVALL
#include <WS2tcpip.h>  // for SIO_RCVALL
#include <stdio.h>
#include <stdlib.h>

#define RECVSIZE 4096

void disp_line(int addr, unsigned char *bytes, int byte_cnt)
{
	int i, c;

	printf("%08X : ", addr);

	for (i = 0; i < byte_cnt; i++) {
		if (i > 0 && i % 4 == 0)
			printf(" ");

		printf("%02X", bytes[i]);
	}

	printf("   %*s%*s", (16 - byte_cnt) * 2 + 1, " ",
		   (16 - byte_cnt + 3) / 4, " ");

	for (i = 0; i < byte_cnt; i++) {
		c = bytes[i];
		if (c >= 0x20 && c <= 0x7f) {
			printf("%c", c);
		} else {
			printf(".");
		}
	}

	printf("\n");
}

void dump_packet(unsigned char *buf, int size)
{
	int n;
	int addr;
	int byte_cnt;
	unsigned char bytes[16], *ptr;

	addr = byte_cnt = 0;
	ptr = bytes;

	for (n = 0; n < size; n++) {
		*ptr++ = buf[n];
		byte_cnt++;

		if (byte_cnt == 16) {
			disp_line(addr, bytes, byte_cnt);

			addr += 16;
			byte_cnt = 0;
			ptr = bytes;
		}
	}

	if (byte_cnt > 0) {
		disp_line(addr, bytes, byte_cnt);
	}
}

void analyze_packet(unsigned char *buf, int size)
{
	struct ethhdr *eth_header;
	struct ip *ip_header;
	struct tcphdr *tcp_header;
	unsigned char *ptr;
	int i, proto, ipaddr;
	short type, port;
	struct servent *entp;

	ptr = buf;

#ifdef _WIN32
	/* check packet size */
	if (size < 20 + 20) {
		printf("Can't analyze because packet size is too small!\n");
		return;
	}

#else
	/* check packet size */
	if (size - 14 < 20 + 20) {
		printf("Can't analyze because packet size is too small!\n");
		return;
	}

	/* MAC frame(DIX) */
	printf("DA=> %02X-%02X-%02X-%02X-%02X-%02X\n", ptr[0], ptr[1], ptr[2], ptr[3], ptr[4], ptr[5]);
	ptr += 6;
	printf("SA=> %02X-%02X-%02X-%02X-%02X-%02X\n", ptr[0], ptr[1], ptr[2], ptr[3], ptr[4], ptr[5]);
	ptr += 6;

	memcpy(&type, ptr, 2);
	type = ntohs(type);  /* convert big-endian to little-endian */
	printf("ULP type(%04x)=> ", type);
	switch (type) {
	case 0x0800:
		printf("IPv4\n");
		break;
	case 0x0806:
		printf("ARP\n");
		break;
	case 0x86DD:
		printf("IPv6\n");
		break;
	default:
		printf("unknown\n");
		break;
	}
	ptr += 2;

	/* IPv4 packet */
	if (type != 0x0800)
		return;
#endif

	ptr += (4 + 4 + 1);
	proto = *ptr;
	printf("ULP type(%x)=> ", proto);
	switch (proto) {
	case 1:
		printf("ICMP\n");
		break;
	case 6:
		printf("TCP\n");
		break;
	case 17:
		printf("UDP\n");
		break;
	default:
		printf("unknown\n");
		break;
	}

	ptr += 3;
	memcpy(&ipaddr, ptr, 4);
	printf("Source IP=> %d.%d.%d.%d (%08X)\n", ptr[0], ptr[1], ptr[2], ptr[3], ipaddr);

	ptr += 4;
	printf("Destination IP=> %d.%d.%d.%d (%08X)\n", ptr[0], ptr[1], ptr[2], ptr[3], ipaddr);
	ptr += 4;


	/* TCP packet */
	if (proto != 6)
		return;

	memcpy(&port, ptr, 2);
	port = ntohs(port);
	printf("Source port=> %d ", port);
	entp = getservbyport(htons(port), "tcp");  /* /etc/servies */
	if (entp != NULL) {
		printf("(%s)", entp->s_name);
	}
	printf("\n");
	ptr += 2;

	memcpy(&port, ptr, 2);
	port = ntohs(port);
	printf("Destination port=> %d ", port);
	entp = getservbyport(htons(port), "tcp");  /* /etc/servies */
	if (entp != NULL) {
		printf("(%s)", entp->s_name);
	}
	printf("\n");
	ptr += 2;
}

int main(void)
{
	WSADATA wsaData;
	WORD version = MAKEWORD(2, 2);
	SOCKET sock;
	char buf[4096];
	DWORD bytes;
	int ret, i;
	SOCKET_ADDRESS_LIST *niclist;
	SOCKADDR_IN *nicaddr, bindaddr;
	char *nicname;
	unsigned int optval;

	unsigned char recvbuf[RECVSIZE];
	int size;

	/* WinSock initialize */
	ret = WSAStartup(version, &wsaData);
	if (ret != 0) {
		printf("WinSock error\n");
		exit(1);
	}
	if (wsaData.wVersion != version) {
		printf("WinSock version not available\n");
		goto error;
	}

	/* create socket */
	sock = WSASocket(
			AF_INET, 
			SOCK_RAW, 
			IPPROTO_IP,
			NULL,
			0,
			WSA_FLAG_OVERLAPPED
			);
	if (sock == INVALID_SOCKET) {
		printf("Can't create socket\n");
		goto error;
	}
#if 0
	optval = 1;
	ret = setsockopt(sock, IPPROTO_IP, IP_HDRINCL, (char *)&optval, sizeof(optval));
	if (ret == SOCKET_ERROR) {
		printf("Can't set socket option\n");
	}
#endif


	/* query network card */
	ret = WSAIoctl(
			sock,
			SIO_ADDRESS_LIST_QUERY,
			NULL,
			0,
			buf, 
			sizeof(buf),
			&bytes,
			NULL,
			NULL
			);
	if (ret == SOCKET_ERROR) {
		printf("ioctl error\n");
		goto error2;
	}

	niclist = (SOCKET_ADDRESS_LIST *)buf;
	for (i = 0 ; i < niclist->iAddressCount ; i++) {
		nicaddr = (SOCKADDR_IN *)niclist->Address[i].lpSockaddr;
		nicname = inet_ntoa(nicaddr->sin_addr);  // IP address
		printf("%s\n", nicname);
	}

	/* bind */
	bindaddr.sin_addr.s_addr = nicaddr->sin_addr.s_addr;
	bindaddr.sin_family = AF_INET;
	bindaddr.sin_port = htons(0);
	ret = bind(sock, (SOCKADDR *)&bindaddr, sizeof(bindaddr));
	if (ret == SOCKET_ERROR) {
		printf("bind error\n");
		goto error2;
	}

	/* set promiscous mode */
	optval = 1;
	ret = WSAIoctl(
			sock,
			SIO_RCVALL,
			&optval,
			sizeof(optval),
			NULL,
			0,
			&bytes,
			NULL,
			NULL
			);
	if (ret == SOCKET_ERROR) {
		printf("ioctl error2\n");
		goto error2;
	}
	
	/* capture packet */
	for (;;) {
		size = recv(sock, recvbuf, sizeof(recvbuf), 0);
		if (size > 0) {
			analyze_packet(recvbuf, size);
			dump_packet(recvbuf, size);

			printf("\n---\n\n");
			fflush(stdout);
			break;
		}
	}

error2:;
	/* close socket */
	closesocket(sock);

error:;
	WSACleanup();

	return 0;
}

#else

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/select.h>
#include <linux/if.h>
#include <linux/if_ether.h>
#include <netdb.h>

#define NICNAME "eth0"
#define RECVSIZE 4096

void disp_line(int addr, unsigned char *bytes, int byte_cnt)
{
	int i, c;

	printf("%08X : ", addr);

	for (i = 0; i < byte_cnt; i++) {
		if (i > 0 && i % 4 == 0)
			printf(" ");

		printf("%02X", bytes[i]);
	}

	printf("   %*s%*s", (16 - byte_cnt) * 2 + 1, " ",
		   (16 - byte_cnt + 3) / 4, " ");

	for (i = 0; i < byte_cnt; i++) {
		c = bytes[i];
		if (c >= 0x20 && c <= 0x7f) {
			printf("%c", c);
		} else {
			printf(".");
		}
	}

	printf("\n");
}

void dump_packet(unsigned char *buf, int size)
{
	int n;
	int addr;
	int byte_cnt;
	unsigned char bytes[16], *ptr;

	addr = byte_cnt = 0;
	ptr = bytes;

	for (n = 0; n < size; n++) {
		*ptr++ = buf[n];
		byte_cnt++;

		if (byte_cnt == 16) {
			disp_line(addr, bytes, byte_cnt);

			addr += 16;
			byte_cnt = 0;
			ptr = bytes;
		}
	}

	if (byte_cnt > 0) {
		disp_line(addr, bytes, byte_cnt);
	}
}

void analyze_packet(unsigned char *buf, int size)
{
	struct ethhdr *eth_header;
	struct ip *ip_header;
	struct tcphdr *tcp_header;
	unsigned char *ptr;
	int i, proto, ipaddr;
	short type, port;
	struct servent *entp;

	/* check packet size */
	if (size - 14 < 20 + 20) {
		printf("Can't analyze because packet size is too small!\n");
		return;
	}

	/* MAC frame(DIX) */
	ptr = buf;
	printf("DA=> %02X-%02X-%02X-%02X-%02X-%02X\n", ptr[0], ptr[1], ptr[2], ptr[3], ptr[4], ptr[5]);
	ptr += 6;
	printf("SA=> %02X-%02X-%02X-%02X-%02X-%02X\n", ptr[0], ptr[1], ptr[2], ptr[3], ptr[4], ptr[5]);
	ptr += 6;

	memcpy(&type, ptr, 2);
	type = ntohs(type);  /* convert big-endian to little-endian */
	printf("ULP type(%04x)=> ", type);
	switch (type) {
	case 0x0800:
		printf("IPv4\n");
		break;
	case 0x0806:
		printf("ARP\n");
		break;
	case 0x86DD:
		printf("IPv6\n");
		break;
	default:
		printf("unknown\n");
		break;
	}
	ptr += 2;

	/* IPv4 packet */
	if (type != 0x0800)
		return;

	ptr += (4 + 4 + 1);
	proto = *ptr;
	printf("ULP type(%x)=> ", proto);
	switch (proto) {
	case 1:
		printf("ICMP\n");
		break;
	case 6:
		printf("TCP\n");
		break;
	case 17:
		printf("UDP\n");
		break;
	default:
		printf("unknown\n");
		break;
	}

	ptr += 3;
	memcpy(&ipaddr, ptr, 4);
	printf("Source IP=> %d.%d.%d.%d (%08X)\n", ptr[0], ptr[1], ptr[2], ptr[3], ipaddr);

	ptr += 4;
	printf("Destination IP=> %d.%d.%d.%d (%08X)\n", ptr[0], ptr[1], ptr[2], ptr[3], ipaddr);
	ptr += 4;


	/* TCP packet */
	if (proto != 6)
		return;

	memcpy(&port, ptr, 2);
	port = ntohs(port);
	printf("Source port=> %d ", port);
	entp = getservbyport(htons(port), "tcp");  /* /etc/servies */
	if (entp != NULL) {
		printf("(%s)", entp->s_name);
	}
	printf("\n");
	ptr += 2;

	memcpy(&port, ptr, 2);
	port = ntohs(port);
	printf("Destination port=> %d ", port);
	entp = getservbyport(htons(port), "tcp");  /* /etc/servies */
	if (entp != NULL) {
		printf("(%s)", entp->s_name);
	}
	printf("\n");
	ptr += 2;
}

int main(void)
{
	int sock;
	struct ifreq f;
	int ret;
	unsigned char recvbuf[RECVSIZE];
	ssize_t size;
	fd_set read_fd;
	struct timeval tv;

	/* open socket */
	sock = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
	if (sock == -1) {
		printf("Can't create socket\n");
		exit(1);
	}

	/* set promiscous mode */
	strcpy(f.ifr_name, NICNAME);
	/* Socket I/O Configuration Get I/F Flags */
	ret = ioctl(sock, SIOCGIFFLAGS, &f);
	if (ret == -1) {
		perror("ioctl error\n");
		goto error;
	}

	f.ifr_ifru.ifru_flags |= IFF_PROMISC;
	ret = ioctl(sock, SIOCSIFFLAGS, &f);
	if (ret == -1) {
		perror("ioctl error2\n");
		goto error;
	}

	/* capture packet */
	for (;;) {
		size = read(sock, recvbuf, sizeof(recvbuf));
		if (size > 0) {
			analyze_packet(recvbuf, size);
			dump_packet(recvbuf, size);

			printf("\n---\n\n");
			fflush(stdout);
		}
	}

  error:;
	close(sock);

	return 0;
}

#endif

