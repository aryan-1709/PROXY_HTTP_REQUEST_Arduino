#ifndef HTTP_NORMAL_CLIENT_H
#define HTTP_NORMAL_CLIENT_H

#include<Client/Client.h>
#include <WiFiClientSecure.h>
#include<structures/Response.h>

class NormalClient : public http_client, public WiFiClientSecure {
public:
    NormalClient(String host, uint16_t port) : http_client(host, port){
        //do nothig
    }

    bool _connect_() override{
        this->setInsecure();
        if (!this->connected()) {
            // Serial.println("Not connected, connecting...");
            if (!this->connect(this->host.c_str(), this->port)) {
                Serial.println("Reconnection failed!");
                return false;                
            }
            // Serial.println("Reconnected to proxy!");
        }
        return true;
    }

    Response _print_(String request) override{
        this->setTimeout(10000);
        Response res;
        // Send the HTTP request
        this->print(request);
        Serial.print("Request sent.");

        bool responseStarted = false;
        bool InsideBody=false;
        unsigned long startTime = millis();
        unsigned long lastDotTime = startTime;
        const unsigned long timeoutDuration = 30000; // 30-second overall timeout
        String response="";

        while (millis() - startTime < timeoutDuration) {
            if (this->available()) {
                if (!responseStarted) {
                    Serial.println();
                    responseStarted = true;
                }
                while (this->available()) {
                    String line = this->readStringUntil('\n');
                    line.trim(); 

                    if (line.length() == 0) {
                        InsideBody = true;
                        continue;
                    }

                    if (InsideBody) {
                        if (line.length() <= 2 && isHexadecimalDigit(line[0])) {
                            continue;
                        }

                        response += line;
                    }
                }
            }

            if (responseStarted && !this->connected()) {
                break;
            }

            if (!responseStarted && (millis() - lastDotTime >= 1000)) {
                Serial.print(".");
                lastDotTime = millis();
            }

            yield(); 
            delay(10); 
        }

        if (!responseStarted) {
            Serial.println(); // Add a newline after the final dot
            // Serial.println("Timeout: Can't reach the server or no response received in 30 seconds.");
            res.first=false;
            res.second="No reponse received!";
            return res;
        }
        if (this->connected()) {
            this->stop();
        }
        // Serial.println("Connection closed.");
        res.first=true;
        res.second=response;
        return res;
    }
};

#endif