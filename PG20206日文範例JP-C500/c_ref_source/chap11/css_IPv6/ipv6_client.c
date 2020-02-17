/*
 * ipv6_client.c
 *
 * [how to compile]
 *   >cl ipv6_client.c ws2_32.lib
 *
 */
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	WSADATA wsaData;
	WORD version = MAKEWORD(2, 2);

	SOCKET sock;
	int ret;
	SOCKADDR_IN skaddr;
	int size;
	char buf[4096];

	char *port;
	IN_ADDR ipaddr;
	char *hostname;
	char *msg;

	struct addrinfo hints, *reslist, *res;

	if (argc != 3) {
		printf("help: ipv6_client hostname|IP address port\n");
		exit(1);
	}
	hostname = argv[1];
	port = argv[2];   /* not convert numeric value */

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

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = PF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	ret = getaddrinfo(hostname, port, &hints, &reslist);
	if (ret != 0) {
		printf("getaddrinfo error\n");
		exit(1);
	}

	for (res = reslist ; res ; res = res->ai_next) {
		sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
		if (sock == INVALID_SOCKET) {
			printf("Can't create socket\n");
			exit(1);
		}

		ret = connect(sock, res->ai_addr, res->ai_addrlen);
		if (ret == SOCKET_ERROR) {
			printf("connect error\n");
			goto error;
		}

		printf("Connect to server\n");

		msg = "hello!";
		send(sock, msg, strlen(msg), 0);
		memset(buf, 0, sizeof(buf));
		size = recv(sock, buf, sizeof(buf), 0);
		if (size > 0) {
			printf(">%s\n", buf);
		}

		shutdown(sock, SD_BOTH);
		closesocket(sock);
	}
	freeaddrinfo(reslist);  /* free linked-list */

error:;
	WSACleanup();

	return 0;
}


