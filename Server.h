//* Author: 318509700 Peleg
//*         207984956 Nadav

#ifndef SERVER_H_
#define SERVER_H_


#include <thread>
#include "CLI.h"

using namespace std;

// edit your ClientHandler interface here:
class ClientHandler {
public:
    virtual void handle(int clientID) = 0;
};


// edit your AnomalyDetectionHandler class here
class AnomalyDetectionHandler : public ClientHandler {
public:
    virtual void handle(int clientID) {
        SocketIO sockIO(clientID);
        CLI handlerAPI(&sockIO);
        handlerAPI.start();
    }
};


// implement on Server.cpp
class Server {
    bool shouldStop;
    int clientLimit;
    int port;

protected:
    thread *t; // the thread to run the start() method in
    int server_fd;
    struct sockaddr_in serverAddress;
    struct sockaddr_in clientAddress;

    // you may add data members

public:
    explicit Server(int port) ;

    virtual ~Server();

    virtual void start(ClientHandler &ch) ;

    virtual void stop();

    void initServer(int portGiven, int *serverFileDesc, struct sockaddr_in *address);
};

class ThreadedServer : public Server {
    int port;
    int clientID;
public:
    explicit ThreadedServer(int port, int clientID);

    void start(ClientHandler &ch) ;

    virtual ~ThreadedServer();

    void stop();
};

#endif /* SERVER_H_ */
