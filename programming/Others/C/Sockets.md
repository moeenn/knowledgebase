```c
#include <arpa/inet.h>  // inet_ntoa,
#include <netinet/in.h> // sockaddr_in
#include <stdio.h>
#include <stdlib.h>     // atoi,
#include <string.h>     // memset,
#include <sys/socket.h> // socket, AF_INET, SOCK_STREAM

int main(int argc, char *argv[]) 
{
  if (argc < 2) {
    fprintf(stderr, "Usage %s <port>", argv[0]);
    return 1;
  }

  const int port = atoi(argv[1]);

  /**
   *  step 1: create the socket
   *  AF_INET:
   *  SOCK_STREAM: socket type is TCP
   *  0: Protocol: Zero means use the default protocol for TCP
   */
  int sock = socket(AF_INET, SOCK_STREAM, 0);

  /**
   *  step 2: bind the socket
   *  htons: host to network short: different systems might store the bytes in
   *  different order, this function will normalize them
   */
  struct sockaddr_in address;
  memset(&address, 0, sizeof(address));

  address.sin_family = AF_INET;
  address.sin_port = htons(port);

  int bind_value = bind(sock, (struct sockaddr *)&address, sizeof(address));
  if (bind_value < 0) {
    perror("[error] Failed to bind to port");
    return 1;
  }

  /**
   *  step 3: start listening
   *
   */
  int listen_value = listen(sock, 1);
  if (listen_value < 0) {
    perror("[error] Failed to listen on port");
    return 1;
  }

  /**
   *  step 4: accept new connections
   *
   */
  struct sockaddr_in remote_address;
  memset(&remote_address, 0, sizeof(remote_address));
  socklen_t remote_addlen = sizeof(remote_address);

  printf("-- waiting for connections --\n");
  int client_socket =
      accept(sock, (struct sockaddr *)&remote_address, &remote_addlen);
  if (client_socket < 0) {
    perror("[error] Could not accept client connection");
    return 1;
  }

  char *client_ip = inet_ntoa(remote_address.sin_addr);
  int remote_port = ntohs(remote_address.sin_port);
  printf("[connection] Client connected @ %s:%d\n", client_ip, remote_port);

  /**
   *  step 5: receive data from client
   *
   */
  int BUFFLEN = 1024;
  char buffer[BUFFLEN];

  while (1) {
    memset(buffer, 0, BUFFLEN);

    int bytes_received = recv(client_socket, buffer, BUFFLEN - 1, 0);

    if (bytes_received < 0) {
      perror("[error] Failed to receive data");
      continue;
    }

    if (bytes_received == 0) {
      printf("[disconnect] client @ %s:%d\n", client_ip, remote_port);
      break;
    }

    printf("[message] %s", buffer);

    /* echo message back to client */
    int bytes_sent = send(client_socket, buffer, sizeof(buffer), 0);
    if (bytes_sent < 0) {
      perror("[error] Failed to send response");
      continue;
    }
  }

  printf("-- closing socket --\n");
  shutdown(client_socket, SHUT_RDWR);

  return 0;
}
```