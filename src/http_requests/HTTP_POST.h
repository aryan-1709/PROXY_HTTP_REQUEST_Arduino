#ifndef HTTP_POST_REQUEST_H
#define HTTP_POST_REQUEST_H

// #include<string>
#include<Arduino.h>
#include<http_requests/HTTP_Request.h>
#include <ProxyClient.h>
#include<utility/Base64.h>

using namespace std;

class http_post_request : public http_request {
private:
    String jsonData="";
public:
    http_post_request(String jsonData, String  target_host, String target_path) : http_request(target_host, target_path){
        this->jsonData=jsonData;
    }

    String get_jsonData(){
        if(this->jsonData=="")    return "No json data provided";
        return this->jsonData;
    }

    String get_request() override {
        PROXY_CLIENT* proxy_client = PROXY_CLIENT::getInstance();
        String proxy_auth=encodeBasicAuth(proxy_client->get_proxy_username(), proxy_client->get_proxy_password());
        String request = "POST https://" + String(get_target_host()) + String(get_target_path()) + " HTTP/1.1\r\n";
        request += "Host: " + String(get_target_host()) + "\r\n";
        request += "Proxy-Authorization: " + String(proxy_auth) + "\r\n";
        request += "Content-Type: application/json\r\n";
        request += "Content-Length: " + String(this->jsonData.length()) + "\r\n";
        request += "Connection: close\r\n\r\n";
        request += this->jsonData;
        return request;
    }
};

#endif