#ifndef NEW_MAKE_REQUEST_H
#define NEW_MAKE_REQUEST_H

#include<Arduino.h>
#include<http_requests/HTTP_Request.h>
#include<Client/Client.h>

using namespace std;

class make_http_request{
private:
    http_client* client;
    http_request* http_request_;
    String username="";
    String password="";
public:
    make_http_request(http_client* client, String username, String password){
        this->client=client;
        this->username=username;
        this->password=password;
    }

    String make_request(http_request* http_request_) {
        if (!client || !http_request_) return "Something went Wrong!";

        client->_connect_();

        String request=http_request_->get_request(this->username, this->password);

        String response = client->_print_(request);

        return response;
    }
};

#endif