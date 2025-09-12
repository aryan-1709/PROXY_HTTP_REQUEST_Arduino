#ifndef CLIENT_H
#define CLIENT_H 

#include<Arduino.h>
#include<structures/Response.h>

class http_client{
protected:
    String host;
    uint16_t port;
public:
    http_client(String host, uint16_t port){
        this->host=host;
        this->port=port;
    }

    virtual bool _connect_()=0;

    virtual Response _print_(String request)=0;
};

#endif