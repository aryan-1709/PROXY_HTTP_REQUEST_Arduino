#ifndef MAKE_REQUEST_H
#define MAKE_REQUEST_H

#include<Arduino.h>
#include<http_requests/HTTP_Request.h>
#include<ProxyClient.h>

using namespace std;

class make_http_request{
private:
    PROXY_CLIENT* proxy_client;
    http_request* http_request_;
public:
    make_http_request(PROXY_CLIENT* proxy_client){
        this->proxy_client=proxy_client;
    }

    bool make_request(http_request* http_request_) {
        if (!proxy_client || !http_request_) return false;

        // Set a timeout for individual read operations (good practice)
        proxy_client->setTimeout(10000);

        // Send the HTTP request
        proxy_client->print(http_request_->get_request());
        Serial.print("Request sent. Awaiting response");

        bool responseReceived = false;
        unsigned long startTime = millis();
        unsigned long lastDotTime = startTime;
        const unsigned long timeoutDuration = 30000; // 30-second overall timeout

        // Loop until timeout or until the full response is likely received
        while (millis() - startTime < timeoutDuration) {
            // Check for incoming data from the server
            if (proxy_client->available()) {
                if (!responseReceived) {
                    Serial.println(); // Move to the next line once response starts
                    responseReceived = true;
                }
                // Read and print all available lines
                while (proxy_client->available()) {
                    String line = proxy_client->readStringUntil('\n');
                    Serial.println(line);
                }
            }

            // If we've received a response and the server closes the connection, we are done.
            if (responseReceived && !proxy_client->connected()) {
                break;
            }

            // --- NEW: Print a dot every second while waiting ---
            if (!responseReceived && (millis() - lastDotTime >= 1000)) {
                Serial.print(".");
                lastDotTime = millis();
            }

            yield(); // Allow background processes to run (important for ESP boards)
            delay(10); // Small delay to prevent the loop from overwhelming the CPU
        }

        // --- NEW: Check for timeout after the loop finishes ---
        if (!responseReceived) {
            Serial.println(); // Add a newline after the final dot
            Serial.println("Timeout: Can't reach the server or no response received in 30 seconds.");
            return false;
        }

        // Clean up the connection
        if (proxy_client->connected()) {
            proxy_client->stop();
        }
        Serial.println("Connection closed.");
        return true;
    }
};

#endif