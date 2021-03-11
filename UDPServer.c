#include <winsock2.h>
#include <stdio.h>
#include <string.h>

#pragma comment (lib, "Ws2_32.lib")

#define port 8080
#define max_receive 1024
#define ip_type AF_INET
#define socket_type SOCK_DGRAM
#define protocol IPPROTO_UDP
#define address INADDR_ANY

int main() {
	WSADATA initialize_data;
	SOCKADDR_IN server, client;
	SOCKET receiver;
	char buffer[max_receive];
	int length;

	WSAStartup(MAKEWORD(2,2), &initialize_data);
	receiver = socket(ip_type, socket_type, protocol);
	server.sin_family = ip_type;
	server.sin_port = htons(port);
	server.sin_addr.s_addr = htonl(address);
	bind(receiver, &server, sizeof(server));
	getsockname(receiver, &server, sizeof(server));
	length = sizeof(client);
	while (1) {
		recvfrom(receiver, buffer, max_receive, 0, &client, &length);
		printf("%s\n", buffer);
	}
	return 0;
}
