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
  int wellknownpipe = mkfifo(well_known_pipe,0644);
  char *secret_pipe_PID;
  int fromChild = open(well_known_pipe,O_RDONLY);
  read(fromChild,secret_pipe_PID,8);

  printf("The pid of the client is %s\n",secret_pipe_PID);

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
  int wellknownpipe = mkfifo(well_known_pipe,0644);

  char * pid_pointer;
  int pid = getpid();
  char pointer = (char)pid;
  strcpy(pid_pointer,&pointer);
  int toServer = open(well_known_pipe,O_WRONLY);
  write(toServer,pid_pointer,strlen(pid_pointer));

 //int private_pipe = mkfifo(pointer,0644);

  //mkfifo(pid,0644);
  return from_server;
}
