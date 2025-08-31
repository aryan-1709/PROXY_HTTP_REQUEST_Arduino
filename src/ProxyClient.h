#ifndef  PROXY_CLIENT_H
#define PROXY_CLIENT_H

#include<Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
// #include <string>

using namespace std;

class PROXY_CLIENT : public WiFiClient{
private:
    String network_ssid;
    String network_password;
    String proxy_host;
    uint16_t proxy_port;
    String proxy_username;
    String proxy_password;

    PROXY_CLIENT(){}

    PROXY_CLIENT(
                String network_ssid,
                String network_password,
                String proxy_host,
                uint16_t proxy_port,
                String proxy_username,
                String proxy_password){
        this->network_ssid=network_ssid;
        this->network_password=network_password;
        this->proxy_host=proxy_host;
        this->proxy_port=proxy_port;
        this->proxy_username=proxy_username;
        this->proxy_password=proxy_password;
    }

    static PROXY_CLIENT* instance;
public:
    static PROXY_CLIENT* getInstance(){
        // if(!instance)
        //     instance=new PROXY_CLIENT();
        // if (!instance->connect(instance->proxy_host, instance->proxy_port)) {
        //     Serial.println("Connection to proxy failed!");
        //     return nullptr;
        // }
        // Serial.println("Connected to proxy!");
        return instance;
    }
    static PROXY_CLIENT* init_and_get_instance(
            String network_ssid,
            String network_password,
            String proxy_host,
            uint16_t proxy_port,
            String proxy_username,
            String proxy_password) {
        if(!instance)
            instance=new PROXY_CLIENT();
        instance->network_ssid=network_ssid;
        instance->network_password=network_password;
        instance->proxy_host=proxy_host;
        instance->proxy_port=proxy_port;
        instance->proxy_username=proxy_username;    
        instance->proxy_password=proxy_password;
        
        if (!instance->connect(instance->proxy_host.c_str(), instance->proxy_port)) {
            Serial.println("Connection to proxy failed!");
            return nullptr;
        }
        Serial.println("Connected to proxy!");
        return instance;
    }

    String get_proxy_host(){
        return proxy_host;
    }
    uint16_t get_proxy_port(){
        return proxy_port;
    }
    String get_proxy_username(){
        return proxy_username;
    }
    String get_proxy_password(){
        return proxy_password;
    }
};

PROXY_CLIENT* PROXY_CLIENT::instance = nullptr;

#endif