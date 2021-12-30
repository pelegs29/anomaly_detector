//* Author: 318509700 Peleg
//*         207984956 Nadav

#include <netinet/in.h>
#include <unistd.h>
#include <csignal>
#include <sys/types.h>
#include <ctime>
#include <cstdio>
#include "Server.h"
#include "commands.h"


void Server::initServer(int portGiven, int *serverFileDesc, struct sockaddr_in *address) {
    // Creating socket file descriptor
    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if ((*serverFileDesc = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    address->sin_family = AF_INET;
    address->sin_addr.s_addr = INADDR_ANY;
    address->sin_port = htons(portGiven);

    // Forcefully attaching socket to the portGiven 8080
    if (bind(*serverFileDesc, (struct sockaddr *) address, sizeof(*address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(*serverFileDesc, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
}

void sigalarm_handler(int) {
    cout << "alarm fired" << endl;
}

Server::Server(int port) {
    this->shouldStop = false;
    this->port = port;
    this->clientLimit = 5; //TODO : check for real value 😃
    initServer(port, &this->server_fd, &this->serverAddress);
}

void Server::start(ClientHandler &ch) {
    this->t = new thread([&ch, this]() {
        signal(SIGALRM, sigalarm_handler);
        while (!this->shouldStop) {
            int addrlen = sizeof(this->serverAddress);
            alarm(3);
            int clientID = accept(this->server_fd, (struct sockaddr *) &this->serverAddress,
                                  (socklen_t *) &addrlen);
            if (clientID > 0) {
                ThreadedServer newThread(++this->port, clientID);
                newThread.start(ch);
            } else {
                perror("accept");
                exit(EXIT_FAILURE);
            }
            alarm(0);
        }
        close(this->server_fd);
    });
}

void Server::stop() {
    this->shouldStop = true;
    t->join(); // do not delete this!
}

Server::~Server() {
}

ThreadedServer::ThreadedServer(int port, int clientID) : Server(port) {
    this->port = port;
    this->clientID = clientID;
    //initServer(port, &this->server_fd, &this->serverAddress);
}

void ThreadedServer::start(ClientHandler &ch) {
    this->t = new thread([&ch, this]() {
                             ch.handle(this->clientID);
                             close(this->clientID);
                         }
    );
}

void ThreadedServer::stop() {
    this->t->join();
}

ThreadedServer::~ThreadedServer() {
};

