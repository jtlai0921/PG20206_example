/*
 * server.c
 *
 * [how to compile]
 *   # gcc -o server server.c
 *
 */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
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
		printf("Can't nslookup hostname(%s)\n", hostname);
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
	int sock, cl_sock;
	int ret;
	struct sockaddr_in skaddr, cl_addr;
	int size;
	char buf[4096];

	int port;
	struct in_addr ipaddr;
	char *hostname;

	if (argc != 3) {
		printf("help: server hostname|IP address port\n");
		exit(1);
	}
	hostname = argv[1];
	port = atoi(argv[2]);

	nslookup(hostname, &ipaddr);
	printf("%s(%08x)\n", inet_ntoa(ipaddr), ipaddr.s_addr);

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1) {
		printf("Can't create socket\n");
		exit(1);
	}

	skaddr.sin_family = AF_INET;
	skaddr.sin_port = htons(port);
	skaddr.sin_addr = ipaddr;
	ret = bind(sock, (struct sockaddr *)&skaddr, sizeof(skaddr));
	if (ret == -1) {
		printf("bind error\n");
		goto error;
	}

	ret = listen(sock, SOMAXCONN);
	if (ret == -1) {
		printf("listen error\n");
		goto error;
	}

	printf("Wait client connection...\n");
	cl_sock = accept(sock, NULL, NULL);

	for (;;) {
		size = recv(cl_sock, buf, sizeof(buf), 0);
		if (size == 0 || size == -1) {
			break;
		}

		if (size > 0) {
			printf(">%s\n", buf);
			send(cl_sock, "OK", 2, 0);
		}
	} 

	shutdown(cl_sock, SHUT_RDWR);
	close(cl_sock);

error:;
	close(sock);

	return 0;
}


