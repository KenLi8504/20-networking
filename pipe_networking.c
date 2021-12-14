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

  //(0)
  char *well_known_pipe = "Hey I'm Famous";
  int wellknownpipe = mkfifo(well_known_pipe,0644);

  //(4)
  char *secret_pipe_PID;
  int fromChild = open(well_known_pipe,O_RDONLY);
  read(fromChild,secret_pipe_PID,8);
  //printf("The pid of the client is %s\n",secret_pipe_PID);
  remove(well_known_pipe);

  //(5)
  *to_client = open(secret_pipe_PID,O_WRONLY);
  write(*to_client,ACK,sizeof(ACK));

  read(fromChild,secret_pipe_PID,strlen(secret_pipe_PID));
  if (strcmp(secret_pipe_PID,ACK) == 0){
    printf("There are no errors POG :)\n");
  }
  else{
    printf("RUH ROH!\n");
  }

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

  //(1)
  char pid_pointer[1000];
  sprintf(pid_pointer, "%d", getpid());
  mkfifo(pid_pointer, 0644);

  //(2 and 3)
  *to_server = open(well_known_pipe,O_WRONLY);
  write(*to_server,pid_pointer,strlen(pid_pointer));


  //(6)
  int fromServer = open(pid_pointer, O_RDONLY);
  char * clientMessage;
  read(fromServer,clientMessage,8);
  remove(pid_pointer);

  //(7)
  write(*to_server,ACK,sizeof(ACK));
  return from_server;
}
