#ifndef BASE64_UTILS_H
#define BASE64_UTILS_H

#include <Arduino.h>

// Base64 character set
const String base64_chars =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789+/";

// Custom Base64 encoding for Arduino String
inline String base64_encode(const String& input) {
    String encoded_string = "";
    int i = 0, j = 0;
    unsigned char char_array_3[3];
    unsigned char char_array_4[4];

    size_t in_len = input.length();
    const unsigned char* bytes_to_encode = (const unsigned char*)input.c_str();

    while (in_len--) {
        char_array_3[i++] = *(bytes_to_encode++);
        if (i == 3) {
            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
            char_array_4[3] = char_array_3[2] & 0x3f;

            for (i = 0; (i < 4); i++) {
                encoded_string += base64_chars.charAt(char_array_4[i]);
            }
            i = 0;
        }
    }

    // Handle padding
    if (i) {
        for (j = i; j < 3; j++) {
            char_array_3[j] = '\0';
        }

        char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
        char_array_4[3] = char_array_3[2] & 0x3f;

        for (j = 0; (j < i + 1); j++) {
            encoded_string += base64_chars.charAt(char_array_4[j]);
        }

        while ((i++ < 3)) {
            encoded_string += '=';
        }
    }

    return encoded_string;
}

// Generate "Basic <Base64(username:password)>"
inline String encodeBasicAuth(const String& username, const String& password) {
    String credentials = username + ":" + password;
    return "Basic " + base64_encode(credentials);
}

#endif
