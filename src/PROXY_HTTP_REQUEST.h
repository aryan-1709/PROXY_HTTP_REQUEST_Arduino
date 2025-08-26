#ifndef PROXY_HTTP_REQUEST
#define PROXY_HTTP_REQUEST

#include<string>
#include<HTTP_POST.h>
#include<HTTP_Request.h>
#include<Make_Request.h>
#include<ProxyClient.h>

using namespace std;

class proxy_http_request{
private:
    string network_ssid;
    string network_password;
    string proxy_host;
    uint16_t proxy_port;
    string proxy_username;
    string proxy_password;
    string target_host="";
    string target_path="";
    string jsonData="";

    PROXY_CLIENT* proxy_client;
    http_request* http_request;
    make_http_request* make_http_request;
public:
    proxy_http_request( string network_ssid,
                        string network_password,
                        string proxy_host,
                        uint16_t proxy_port,
                        string proxy_username,
                        string proxy_password,
                        string target_host="",
                        string target_path="",
                        string jsonData=""){
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
        //create a proxy client
        proxy_client = PROXY_CLIENT::init_and_get_instance(
            this->network_ssid,
            this->network_password,
            this->proxy_host,
            this->proxy_port,
            this->proxy_username,
            this->proxy_password
        );
        http_request=new http_post_request(this->jsonData, this->target_host, this->target_path);
        make_http_request=new make_http_request(proxy_client, http_request);
        return;
    }
    void make_request(){
        make_http_request->make_request();
        return ;
    }
    
};

#endif