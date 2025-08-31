#ifndef PROXY_HTTP_REQUEST
#define PROXY_HTTP_REQUEST

// #include<string>
#include<Arduino.h>
#include<http_requests/HTTP_POST.h>
#include<http_requests/HTTP_Request.h>
#include<Make_Request.h>
#include<ProxyClient.h>

using namespace std;

class proxy_http_request{
private:
    String network_ssid;
    String network_password;
    String proxy_host;
    uint16_t proxy_port;
    String proxy_username;
    String proxy_password;
    String target_host="";
    String target_path="";
    String jsonData="";

    PROXY_CLIENT* proxy_client;
    http_request* http_request_;
    make_http_request* make_http_request_;
public:
    proxy_http_request( String network_ssid,
                        String network_password,
                        String proxy_host,
                        uint16_t proxy_port,
                        String proxy_username,
                        String proxy_password,
                        String target_host="",
                        String target_path="",
                        String jsonData=""){
        this->network_ssid=network_ssid;
        this->network_password=network_password;
        this->proxy_host=proxy_host;
        this->proxy_port=proxy_port;
        this->proxy_username=proxy_username;
        this->proxy_password=proxy_password;
        this->target_host=target_host;
        this->target_path=target_path;
        this->jsonData=jsonData;
    }

    void init(){
        proxy_client = PROXY_CLIENT::init_and_get_instance(
            this->network_ssid,
            this->network_password,
            this->proxy_host,
            this->proxy_port,
            this->proxy_username,
            this->proxy_password
        );
        http_request_=new http_post_request(this->jsonData, this->target_host, this->target_path);
        make_http_request_=new make_http_request(proxy_client, http_request_);
        return;
    }
    void make_request(){
        if(!proxy_client || !http_request_){
            Serial.out.println("Error finding proxy_client/http_request_ please follow the original order!");
            return;
        }
        make_http_request_->make_request();
        return ;
    }
    
    public static class proxy_http_request_builder{
    private:
        String network_ssid;
        String network_password;
        String proxy_host;
        uint16_t proxy_port;
        String proxy_username;
        String proxy_password;
        String target_host="";
        String target_path="";
        String jsonData="";
    public:
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
        proxy_http_request_builder* set_target_host(String target_host){
            this->target_host=target_host;
            return this;
        }
        proxy_http_request_builder* set_target_path(String target_path){
            this->target_path=target_path;
            return this;
        }
        proxy_http_request_builder* set_jsonData(String jsonData){
            this->jsonData=jsonData;
            return this;
        }
    };
    
};

#endif