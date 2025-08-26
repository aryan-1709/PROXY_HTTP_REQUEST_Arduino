#ifndef MAKE_REQUEST_H
#define MAKE_REQUEST_H

#include<string>

#include<HTTP_POST.h>
#include<HTTP_Request.h>
#include<ProxyClient.h>

using namespace std;

class make_http_request{
private:
    PROXY_CLIENT* proxy_client;
    http_request* http_request;
public:
    make_http_request(PROXY_CLIENT* proxy_client, http_request* http_request){
        this->proxy_client=proxy_client;
        this->http_request=http_request;
    }

    void make_request(){
        if(proxy_client==nullptr || http_request==nullptr)  return;
        proxy_client->print(http_request->get_request());
        Serial.println("POST request sent. Awaiting response...\n");

        while (proxy_client->connected() || proxy_client->available()) {
            string line = proxy_client->readStringUntil('\n');
            Serial.println(line);
        }

        Serial.println("Connection closed.");
        return;
    }
};

#endif