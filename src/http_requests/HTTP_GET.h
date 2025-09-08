#ifndef HTTP_GET_H
#define HTTP_GET_H

#include<Arduino.h>
#include<http_requests/HTTP_Request.h>
#include<utility/Base64.h>

using namespace std;

class http_get_request : public http_request {
private:
public:
    http_get_request(String  target_host, String target_path) : http_request(target_host, target_path){
        //Do Nothing
    }

    String get_request(String username, String password) override {
        String proxy_auth="";
        if(username != "")  proxy_auth=encodeBasicAuth(username, password);
        String request = "GET https://" + String(get_target_host()) + String(get_target_path()) + " HTTP/1.1\r\n";
        request += "Host: " + String(get_target_host()) + "\r\n";
        if(proxy_auth != "")
            request += "Proxy-Authorization: " + String(proxy_auth) + "\r\n";
        request += "Connection: close\r\n\r\n";
        return request;
    }
};

#endif