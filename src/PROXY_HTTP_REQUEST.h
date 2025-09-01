#ifndef PROXY_HTTP_REQUEST
#define PROXY_HTTP_REQUEST

#include<Arduino.h>
#include<http_requests/HTTP_POST.h>
#include<http_requests/HTTP_GET.h>
#include<http_requests/HTTP_Request.h>
#include<Make_Request.h>
#include<ProxyClient.h>

using namespace std;

class proxy_http_request_builder{
public:
    String network_ssid;
    String network_password;
    String proxy_host;
    uint16_t proxy_port;
    String proxy_username;
    String proxy_password;
    proxy_http_request_builder* set_network_ssid(String network_ssid){
        this->network_ssid=network_ssid;
        return this;
    }
    proxy_http_request_builder* set_network_password(String network_password){
        this->network_password=network_password;
        return this;
    }
    proxy_http_request_builder* set_proxy_host(String proxy_host){
        this->proxy_host=proxy_host;
        return this;
    }
    proxy_http_request_builder* set_proxy_port(uint16_t proxy_port){
        this->proxy_port=proxy_port;
        return this;
    }
    proxy_http_request_builder* set_proxy_username(String proxy_username){
        this->proxy_username=proxy_username;
        return this;
    }
    proxy_http_request_builder* set_proxy_password(String proxy_password){
        this->proxy_password=proxy_password;
        return this;
    }
};

class proxy_http_request{
private:
    String network_ssid="";
    String network_password="";
    String proxy_host="";
    uint16_t proxy_port=0;
    String proxy_username="";
    String proxy_password="";
    String target_host="";
    String target_path="";
    String jsonData="";

    PROXY_CLIENT* proxy_client;
    http_request* http_request_;
    make_http_request* make_http_request_;
public:
    proxy_http_request(proxy_http_request_builder* builder){
        this->network_ssid=builder->network_ssid;
        this->network_password=builder->network_password;
        this->proxy_host=builder->proxy_host;
        this->proxy_port=builder->proxy_port;
        this->proxy_username=builder->proxy_username;
        this->proxy_password=builder->proxy_password;
    }

    void init(){
        if( this->network_ssid=="" ||
            this->network_password=="" ||
            this->proxy_host=="" ||
            this->proxy_port==0 ||
            this->proxy_username=="" ||
            this->proxy_password == ""){
                Serial.println(this->network_ssid);
                Serial.println(this->network_password);
                Serial.println(this->proxy_host);
                Serial.println(this->proxy_port);
                Serial.println(this->proxy_username);
                Serial.println("Given data is missing please check!!");
                return;
            }
        proxy_client = PROXY_CLIENT::init_and_get_instance(
            this->network_ssid,
            this->network_password,
            this->proxy_host,
            this->proxy_port,
            this->proxy_username,
            this->proxy_password
        );
        make_http_request_=new make_http_request(proxy_client);
        return;
    }
    void make_request(String target_host, String target_path, String jsonData){
        this->target_host=target_host;
        this->target_path=target_path;
        this->jsonData=jsonData;
        if(jsonData!="")
            http_request_=new http_post_request(this->jsonData, this->target_host, this->target_path);
        else    http_request_=new http_get_request(this->target_host, this->target_path);
        if(!proxy_client || !http_request_){
            Serial.println("Error finding proxy_client/http_request_ please follow the original order!");
            return;
        }
        bool repsonse = make_http_request_->make_request(http_request_);
        if(repsonse == false)   Serial.println("Something went wrong!");
        else Serial.println("Response received request sent!");
        this->jsonData="";
        return;
    }
};

#endif