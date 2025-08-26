#ifndef HTTP_POST_REQUEST_HPP
#define HTTP_POST_REQUEST_HPP

#include<string>
#include<HTTP_Request.h>
#include<ProxyClient.h>
#include<utility/Base64.h>

using namespace std;

class http_post_request : public http_request {
private:
    string jsonData="";
public:
    http_post_request(string jsonData, string  target_host, string target_path) : http_request(target_host, target_path){
        this->jsonData=jsonData;
    }

    string get_jsonData(){
        if(this->jsonData=="")    return "No json data provided";
        return this->jsonData;
    }

    string get_request() override {
        PROXY_CLIENT* proxy_client = PROXY_CLIENT::getInstance();
        string proxy_auth=encodeBasicAuth(proxy_client->get_proxy_username, proxy_client->get_proxy_password);
        // Prepare the HTTP POST request
        string request = "POST https://" + string(proxy_client->target_host) + string(proxy_client->target_path) + " HTTP/1.1\r\n";
        request += "Host: " + string(proxy_client->target_host) + "\r\n";
        request += "Proxy-Authorization: " + string(proxy_auth) + "\r\n";
        request += "Content-Type: application/json\r\n";
        request += "Content-Length: " + string(this->jsonData.length()) + "\r\n";
        request += "Connection: close\r\n\r\n";
        request += this->jsonData;
    }
};

#endif