#ifndef __C_EASE_SOCKET_H_
#define __C_EASE_SOCKET_H_

#include <winsock2.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct {
  SOCKET socket;
  struct sockaddr_in address;
} socket_t;

// SOCK_STREAM

void socket_cleanup(){
    WSACleanup();
	puts("Cleaned Up WSA");
}

socket_t socket_create(size_t port, int type){

    WSADATA wsa;
	SOCKET sock ;
	struct sockaddr_in server;

	if (WSAStartup(MAKEWORD(2,2), &wsa) != 0)
	{
		printf("Failed. Error Code : %d", WSAGetLastError());
        exit(1);
	}
	
	//Create a socket
	if((sock = socket(AF_INET , type , 0 )) == INVALID_SOCKET)
	{
		printf("Could not create socket : %d" , WSAGetLastError());
        exit(1);
	}

	printf("Socket created.\n");
	
	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons( port );

    atexit(socket_cleanup);

	socket_t client_socket =  {sock, server};
    return client_socket; 
} 

socket_t socket_create_tcp(size_t port){
    return socket_create(port, SOCK_STREAM);
}

void socket_listen(socket_t* s, int backlog){
    listen(s->socket , backlog);
}

void socket_bind(socket_t* s){
    	//Bind
	if( bind(s->socket ,(struct sockaddr *)&s->address , sizeof(s->address)) == SOCKET_ERROR)
	{
		printf("Bind failed with error code : %d" , WSAGetLastError());
		exit(EXIT_FAILURE);
	}
}

bool socket_is_valid(socket_t* s){
    return s->socket != INVALID_SOCKET;
}


int socket_recv(socket_t* s, char* buf, int length, int flags){
    return recv(s->socket, buf, length, flags);
} 

int socket_send(socket_t* s, char* buf, int length, int flags){
    return send(s->socket , buf, length , flags);
} 


socket_t socket_accept(socket_t* s){
	SOCKET new_socket;
    int address_len;
	struct sockaddr_in client;

    new_socket = accept(s->socket, (struct sockaddr *)&client, &address_len);

	socket_t client_socket =  {new_socket, client};
    return client_socket;
}

void socket_close(socket_t* s){
    closesocket(s->socket);
}


#endif