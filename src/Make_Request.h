#ifndef NEW_MAKE_REQUEST_H
#define NEW_MAKE_REQUEST_H

#include<Arduino.h>
#include<http_requests/HTTP_Request.h>
#include<Client/Client.h>
#include<structures/Response.h>

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

    Response make_request(http_request* http_request_) {
        Response response;
        if (!client || !http_request_){
            response.first=false;
            response.second="Something went Wrong!";
            return response;
        } 
        
        if(!client->_connect_()){
            response.first=false;
            response.second="Connection failed!";
            return response;
        }    
        
        String request=http_request_->get_request(this->username, this->password);
        
        response=client->_print_(request);

        return response;
    }
};

#endif