#include "pipe_networking.h"


/*=========================
  server_handshake
  args: int * to_client
  Performs the client side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe.
  returns the file descriptor for the upstream pipe.
  =========================*/
int server_handshake(int *to_client) {

    //0
    int well_known_pipe = mkfifo(WKP, 0644);


    //4
    int from_client = open(WKP, O_RDONLY);
    char clientPID[HANDSHAKE_BUFFER_SIZE];
    int readforSecretPipe = read(from_client, clientPID, HANDSHAKE_BUFFER_SIZE);
    remove(WKP);

    //5
    *to_client = open(clientPID, O_WRONLY);
    int writeAcknowledgement = write(*to_client, ACK, sizeof(ACK));

    int checkAcknowledgement = read(from_client, clientPID, sizeof(clientPID));

    if (strcmp(clientPID, ACK) == 0){
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

    char clientPID[1000];
    sprintf(clientPID, "%d", getpid());

    //1
    mkfifo(clientPID, 0644);

    //2
    *to_server = open(WKP, O_WRONLY);
    int send_secret_pipe_to_server = write(*to_server, clientPID, HANDSHAKE_BUFFER_SIZE);

    //3
    int from_server = open(clientPID, O_RDONLY);

    //6
    char acknowledgement[HANDSHAKE_BUFFER_SIZE];
    int receiveAcknowledgement = read(from_server, acknowledgement, HANDSHAKE_BUFFER_SIZE);
    remove(clientPID);

    int returnAcknowledgement = write(*to_server, ACK, sizeof(ACK));

}
