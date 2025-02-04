#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main()
{
  // Create the client socket
  int client_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (client_fd == -1)
  {
    perror("Client socket creation failed.");
    exit(EXIT_FAILURE);
  }

  // Define the server address
  struct sockaddr_in server_address;
  memset(&server_address, 0, sizeof(server_address)); // Zero out the structure
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(PORT);

  // Convert IP address from text to binary form
  if (inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr) <= 0)
  {
    perror("Invalid address or address not supported.");
    close(client_fd);
    exit(EXIT_FAILURE);
  }

  // Connect to the server
  if (connect(client_fd, (struct sockaddr *)&server_address, sizeof(server_address)) == -1)
  {
    perror("Connection to the server failed.");
    close(client_fd);
    exit(EXIT_FAILURE);
  }

  printf("Connected to the server.\n");

  while (1)
  {
    char message[BUFFER_SIZE];
    printf("Enter message (type 'quit' to exit): ");
    fgets(message, BUFFER_SIZE, stdin);
    message[strcspn(message, "\n")] = '\0'; // Remove newline

    if (strcmp(message, "quit") == 0)
      break;

    if (send(client_fd, message, strlen(message), 0) == -1)
    {
      perror("Send to server failed.");
      break;
    }

    printf("Message sent to server.\n");

    char buffer[BUFFER_SIZE];
    int bytes_received = recv(client_fd, buffer, BUFFER_SIZE - 1, 0);
    if (bytes_received == -1)
    {
      perror("Receive from server failed.");
      break;
    }

    buffer[bytes_received] = '\0';
    printf("Server: %s\n", buffer);
  }

  // Close the socket
  close(client_fd);

  return 0;
}
