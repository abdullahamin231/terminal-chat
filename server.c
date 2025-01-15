#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main(int argc, char *argv[])
{
	// Create server socket
	int server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_fd == -1)
	{
		perror("Socket creation failed");
		exit(EXIT_FAILURE);
	}

	// Bind the socket to a port
	struct sockaddr_in sa;
	sa.sin_family = AF_INET;
	sa.sin_port = htons(PORT);
	sa.sin_addr.s_addr = INADDR_ANY;

	if (bind(server_fd, (struct sockaddr *)&sa, sizeof(sa)) == -1)
	{
		perror("Bind failed");
		close(server_fd);
		exit(EXIT_FAILURE);
	}

	// Listen for incoming connections
	if (listen(server_fd, 5) == -1)
	{
		perror("Listen failed");
		close(server_fd);
		exit(EXIT_FAILURE);
	}

	printf("Server is listening on port %d\n", PORT);

	// Accept incoming connections
	int client_fd;
	struct sockaddr_in client_sa;
	socklen_t ca_len = sizeof(client_sa);

	while (1)
	{
		client_fd = accept(server_fd, (struct sockaddr *)&client_sa, &ca_len);
		if (client_fd == -1)
		{
			perror("Accept failed.");
			continue;
		}

		printf("Connection established with client: %s:%d\n",
					 inet_ntoa(client_sa.sin_addr), ntohs(client_sa.sin_port));

		char buffer[BUFFER_SIZE];
		int bytes_recieved = recv(client_fd, buffer, BUFFER_SIZE - 1, 0);
		if (bytes_recieved > 0)
		{
			buffer[bytes_recieved] = '\0';
			printf("Client: %s\n", buffer);

			if (send(client_fd, "Hello from server!", 18, 0) == -1)
			{
				perror("Send failed.");
			}
		}
		else if (bytes_recieved == 0)
		{
			printf("Client disconnected.\n");
		}
		else
		{
			perror("Recieved failed.");
		}
	}

	// Close the sockets
	close(server_fd);
	close(client_fd);

	return 0;
}
