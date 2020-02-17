/*
 * server.c
 *
 * [how to compile]
 *   >cl server.c ws2_32.lib
 *
 */
#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>


void nslookup(char *hostname, struct in_addr *ipaddr)
{
	struct in_addr iaHost, *alist;
	struct hostent *lpHostEntry;
	int i;

	/* convert string to IP-address(u_long) */
	iaHost.s_addr = inet_addr(hostname);
	if (iaHost.s_addr != INADDR_NONE) {  /* IP-address */
		*ipaddr = iaHost;
		return;
	} 

	/* lookup DNS; hostname -> IP-address */
	lpHostEntry = gethostbyname(hostname);
	if (lpHostEntry == NULL) {  /* DNS error? */
		printf("Can't nslookup hostname(%s) %d\n", hostname, WSAGetLastError());
		exit(1);
	}

	for (i = 0 ; ; i++) {
		alist = (struct in_addr *)lpHostEntry->h_addr_list[i];
		if (alist == NULL)
			break;
		printf("%s\n", inet_ntoa(*alist));
		*ipaddr = *alist;
	}

	if (i == 0) {
		printf("Can't get IP-address\n");
		exit(1);
	}
}


int main(int argc, char **argv)
{
	WSADATA wsaData;
	WORD version = MAKEWORD(2, 2);

	SOCKET sock, cl_sock;
	int ret;
	SOCKADDR_IN skaddr, cl_addr;
	int size;
	char buf[4096];

	int port;
	IN_ADDR ipaddr;
	char *hostname;

	if (argc != 3) {
		printf("help: server hostname|IP address port\n");
		exit(1);
	}
	hostname = argv[1];
	port = atoi(argv[2]);

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

	nslookup(hostname, &ipaddr);
	printf("%s(%08x)\n", inet_ntoa(ipaddr), ipaddr.s_addr);

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) {
		printf("Can't create socket\n");
		exit(1);
	}

	skaddr.sin_family = AF_INET;
	skaddr.sin_port = htons(port);
	skaddr.sin_addr = ipaddr;
	ret = bind(sock, (struct sockaddr *)&skaddr, sizeof(skaddr));
	if (ret == SOCKET_ERROR) {
		printf("bind error\n");
		goto error;
	}

	ret = listen(sock, SOMAXCONN);
	if (ret == SOCKET_ERROR) {
		printf("listen error\n");
		goto error;
	}

	printf("Wait client connection...\n");
	cl_sock = accept(sock, NULL, NULL);

	for (;;) {
		size = recv(cl_sock, buf, sizeof(buf), 0);
		if (size == 0 || size == SOCKET_ERROR) {
			break;
		}

		if (size > 0) {
			printf(">%s\n", buf);
			send(cl_sock, "OK", 2, 0);
		}
	} 

	shutdown(cl_sock, SD_BOTH);
	closesocket(cl_sock);

error:;
	closesocket(sock);
	WSACleanup();

	return 0;
}


