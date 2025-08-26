#ifndef BASE64_UTILS_H
#define BASE64_UTILS_H

#include <string>
#include "mbedtls/base64.h"

using namespace std;

inline string encodeBasicAuth(const string& username, const string& password) {
    string credentials = username + ":" + password;

    // Output buffer for base64 (max size ~ 4/3 input + padding)
    size_t outputLength = 0;
    unsigned char encoded[256]; // adjust size if needed

    // Encode with mbedtls
    int res = mbedtls_base64_encode(
        encoded, sizeof(encoded), &outputLength,
        reinterpret_cast<const unsigned char*>(credentials.c_str()), credentials.length()
    );

    if (res != 0) {
        return ""; // encoding failed
    }

    // Build "Basic ..." string
    string proxyAuth = "Basic ";
    proxyAuth.append(reinterpret_cast<char*>(encoded), outputLength);

    return proxyAuth;
}

#endif