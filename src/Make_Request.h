#ifndef MAKE_REQUEST_H
#define MAKE_REQUEST_H

// #include<string>

#include<Arduino.h>
#include<HTTP_POST.h>
#include<HTTP_Request.h>
#include<ProxyClient.h>

using namespace std;

class make_http_request{
private:
    PROXY_CLIENT* proxy_client;
    http_request* http_request_;
public:
    make_http_request(PROXY_CLIENT* proxy_client, http_request* http_request_){
        this->proxy_client=proxy_client;
        this->http_request_=http_request_;
    }
// ----------------------------------------------------------------------
    // void make_request(){
    //     if(proxy_client==nullptr || http_request_==nullptr)  return;
    //     Serial.println(http_request_->get_request());
    //     proxy_client->print(http_request_->get_request());
    //     Serial.println("POST request sent. Awaiting response...\n");

    //     while (proxy_client->connected()) {
    //         while (proxy_client->available()) {
    //             String line = proxy_client->readStringUntil('\n');
    //             Serial.println(line);
    //         }
    //     }

    //     Serial.println("Connection closed.");
    //     return;
    // }
// ----------------------------------------------------------------------

    void make_request() {
        if (!proxy_client || !http_request_) return;

        proxy_client->setTimeout(10000);
        proxy_client->print(http_request_->get_request());
        Serial.println("POST request sent. Awaiting response...\n");

        const unsigned long overallDeadline = millis() + 15000;
        while (millis() < overallDeadline) {
            while (proxy_client->available()) {
                String line = proxy_client->readStringUntil('\n'); 
                Serial.println(line);
                yield();                                           
            }
            if (!proxy_client->connected()) break;
            delay(10);
        }
        proxy_client->stop(); 
        Serial.println("Connection closed.");
    }

};

#endif