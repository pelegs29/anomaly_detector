//* Author: 318509700 Peleg
//*         207984956 Nadav

#ifndef SERVER_H_
#define SERVER_H_


#include <thread>

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

    }
};


// implement on Server.cpp
class Server {
    thread *t; // the thread to run the start() method in

    // you may add data members

public:
    Server(int port) throw(const char *);

    virtual ~Server();

    virtual void start(ClientHandler &ch) throw(const char *);

    virtual void stop();
};

class ThreadedServer : public Server {
public:
    ThreadedServer(int port) : Server(port) {

    }

    void start(ClientHandler &ch) throw(const char *);

    void ~ThreadedServer();

    void stop();
};

#endif /* SERVER_H_ */
