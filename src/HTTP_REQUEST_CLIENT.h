#ifndef PROXY_HTTP_REQUEST
#define PROXY_HTTP_REQUEST

#include<Arduino.h>
#include<http_requests/HTTP_POST.h>
#include<http_requests/HTTP_GET.h>
#include<http_requests/HTTP_Request.h>
#include<Make_Request.h>
#include<Client/Client.h>
#include<Client/HTTP_NormalClient.h>
#include<Client/HTTP_ProxyClient.h>

using namespace std;

class HTTP_REQUEST_CLIENT_BUILDER{
public:
    String proxy_host="";
    uint16_t proxy_port=0;
    String proxy_username="";
    String proxy_password="";
    HTTP_REQUEST_CLIENT_BUILDER* set_proxy_host(String proxy_host){
        this->proxy_host=proxy_host;
        return this;
    }
    HTTP_REQUEST_CLIENT_BUILDER* set_proxy_port(uint16_t proxy_port){
        this->proxy_port=proxy_port;
        return this;
    }
    HTTP_REQUEST_CLIENT_BUILDER* set_proxy_username(String proxy_username){
        this->proxy_username=proxy_username;
        return this;
    }
    HTTP_REQUEST_CLIENT_BUILDER* set_proxy_password(String proxy_password){
        this->proxy_password=proxy_password;
        return this;    
    }
};

class HTTP_REQUEST_CLIENT{
private:
    String proxy_host="";
    uint16_t proxy_port=0;
    String proxy_username="";
    String proxy_password="";
    String target_host="";
    String target_path="";
    String jsonData="";

    http_client* client;
    http_request* http_request_;
    make_http_request* make_http_request_;
public:
    HTTP_REQUEST_CLIENT(HTTP_REQUEST_CLIENT_BUILDER* builder){
        this->proxy_host=builder->proxy_host;
        this->proxy_port=builder->proxy_port;
        this->proxy_username=builder->proxy_username;
        this->proxy_password=builder->proxy_password;
    }

    void init(){
        if(this->proxy_username == ""){
            client = new NormalClient(
                this->proxy_host,
                this->proxy_port
            );
        }
        else{
            client = new Proxy_Client(
                this->proxy_host,
                this->proxy_port,
                this->proxy_username,
                this->proxy_password
            );
        }
        make_http_request_ = new make_http_request(client, proxy_username, proxy_password);
        return;
    }
    String make_request(String target_host, String target_path, String jsonData){
        this->target_host=target_host;
        this->target_path=target_path;
        this->jsonData=jsonData;
        if(jsonData!="")
            http_request_=new http_post_request(this->jsonData, this->target_host, this->target_path);
        else    http_request_=new http_get_request(this->target_host, this->target_path);
        if(!client || !http_request_){
            Serial.println("Error finding proxy_client/http_request_ please follow the original order!");
            return "Something went wrong!";
        }
        String response = make_http_request_->make_request(http_request_);
        Serial.print("Response received request sent!");
        Serial.print(response);
        this->jsonData="";
        return response;
    }
};

#endif