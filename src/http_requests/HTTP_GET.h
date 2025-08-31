#ifndef HTTP_GET_H
#define HTTP_GET_H

#include<Arduino.h>
#include<HTTP_Request.h>
#include<../ProxyClient.h>
#include<utility/Base64.h>

using namespace std;

class http_post_request : public http_request {
private:
public:
    http_post_request(String  target_host, String target_path) : http_request(target_host, target_path){
        //Do Nothing
    }

    String get_request() override {
        PROXY_CLIENT* proxy_client = PROXY_CLIENT::getInstance();
        String proxy_auth=encodeBasicAuth(proxy_client->get_proxy_username(), proxy_client->get_proxy_password());
        String request = "GET https://" + String(get_target_host()) + String(get_target_path()) + " HTTP/1.1\r\n";
        request += "Host: " + String(get_target_host()) + "\r\n";
        request += "Proxy-Authorization: " + String(proxy_auth) + "\r\n";
        request += "Connection: close\r\n\r\n";
        return request;
    }
};

#endif