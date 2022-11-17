// Client side C/C++ program to demonstrate Socket
// programming
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string>
#include <iostream>
#define PORT 1234

int main(int argc, char const* argv[])
{
	int sock = 0, valread, client_fd, opt = 1;
	socklen_t optt;
	struct sockaddr_in serv_addr;
	//char* hello = "Hello from client";
	std::string greeting = "Hello from gopi";
	const char* hello = greeting.c_str();
	char buffer[1024] = { 0 };
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("\n Socket creation error \n");
		return -1;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	// Convert IPv4 and IPv6 addresses from text to binary
	// form
	if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)
		<= 0) {
		printf(
			"\nInvalid address/ Address not supported \n");
		return -1;
	}

	if ((client_fd
		= connect(sock, (struct sockaddr*)&serv_addr,
				sizeof(serv_addr)))
		< 0) {
		printf("\nConnection Failed \n");
		return -1;
	}
	int i = 0;
    while(1)
    {
		if(getsockopt(sock,SOL_SOCKET,SO_REUSEADDR | SO_REUSEPORT, &opt,&optt))
		{
			send(sock, hello, strlen(hello), 0);
			printf("Hello message sent\n");
			sleep(2);
			greeting = greeting + std::to_string(i++);
			hello = greeting.c_str();
        }
		else
			break;
		// valread = read(sock, buffer, 1024);
        // printf("%s\n", buffer);
    }
	// closing the connected socket
	close(client_fd);
	return 0;
}
