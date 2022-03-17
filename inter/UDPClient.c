#include <winsock2.h>
#include <stdio.h>
#pragma comment (lib, "Ws2_32.lib")

#define port 8080
#define max_receive 3000
#define ip_type AF_INET
#define socket_type SOCK_DGRAM
#define protocol IPPROTO_UDP
#define address INADDR_ANY

int main() {

	WSADATA initialize_data;
	SOCKET receiver;
	SOCKADDR_IN server, SrcInfo;
	// append memory for identifier
	char *message[max_receive];

	WSAStartup(MAKEWORD(2,2), &initialize_data);

	receiver = socket(ip_type, socket_type, protocol);

	server.sin_family = ip_type;
	server.sin_port = htons(port);
	server.sin_addr.s_addr = inet_addr("127.0.0.1");

	while(1) {
		gets(message, sizeof(message));
		sendto(receiver, message, max_receive, 0, &server, sizeof(server));
	}

	return 0;
}
