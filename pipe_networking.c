#include "pipe_networking.h"


/*=========================
  server_handshake
  args: int * to_client
  Performs the client side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe.
  returns the file descriptor for the upstream pipe.
  =========================*/
int server_handshake(int *to_client) {
  int from_client = 0;
  char *well_known_pipe = "Hey I'm Famous";
  int pipeto = open(well_known_pipe,O_RDONLY);
  int *client_PID;
  read(pipeto,client_PID,8);
  printf("The PID of the client is %d",*client_PID);
  //remove(well_known_pipe);
  return from_client;
}


/*=========================
  client_handshake
  args: int * to_server
  Performs the client side pipe 3 way handshake.
  Sets *to_server to the file descriptor for the upstream pipe.
  returns the file descriptor for the downstream pipe.
  =========================*/
int client_handshake(int *to_server) {
  int from_server = 0;
  char *well_known_pipe = "Hey I'm Famous";
  int pipeto = open(well_known_pipe,O_WRONLY);
  write(pipeto,to_server,sizeof(to_server));
  return from_server;
}
