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
	struct sockaddr_in client_sa;
	socklen_t client_len = sizeof(client_sa);

	// Blocks the program until a client connects
	int client_fd = accept(server_fd, (struct sockaddr *)&client_sa, &client_len);
	if (client_fd == -1)
	{
		perror("Accept failed");
		close(server_fd);
		exit(EXIT_FAILURE);
	}

	printf("Connected to client.\n");

	// Now we can communicate with the client
	char buffer[BUFFER_SIZE];
	int bytes_received = recv(client_fd, buffer, BUFFER_SIZE, 0);
	if (bytes_received == -1)
	{
		perror("Receive failed");
		close(client_fd);
		close(server_fd);
		exit(EXIT_FAILURE);
	}

	buffer[bytes_received] = '\0'; // Null-terminate the received message
	printf("Client: %s\n", buffer);

	// Send a response to the client
	const char *response = "Hello from server!";
	if (send(client_fd, response, strlen(response), 0) == -1)
	{
		perror("Send failed");
		close(client_fd);
		close(server_fd);
		exit(EXIT_FAILURE);
	}

	printf("Response sent to client.\n");

	// Close the sockets
	close(client_fd);
	close(server_fd);

	return 0;
}
