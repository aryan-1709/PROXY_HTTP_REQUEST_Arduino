# PROXY\_HTTP\_REQUEST\_Arduino

A lightweight Arduino library to send HTTP requests through proxy networks or mobile hotspots using `WiFiClient` and `WiFiClientSecure`. This library supports both unsecured and secured client connections, enabling flexible network configurations for your IoT projects.

---

## Features

* Send HTTP requests via proxy servers.
* Support for both WiFiClient (insecure) and WiFiClientSecure (TLS/SSL).
* Compatible with proxy networks as well as mobile hotspots.
* Easy to integrate with Arduino projects.

---

## Requirements

* Arduino IDE (version 1.8.13 or later recommended)
* Compatible hardware with WiFi capabilities (e.g., ESP8266, ESP32)
* `WiFiClient` and `WiFiClientSecure` libraries (usually included with board packages)

---

## Installation

### Using Arduino Library Manager

1. Open the Arduino IDE.
2. Navigate to **Sketch** > **Include Library** > **Manage Libraries...**
3. In the Library Manager search bar, type `PROXY_HTTP_REQUEST_Arduino`.
4. Find the library and click **Install**.

### Manual Installation

1. Download the latest release or clone the repository:

   ```bash
   git clone https://github.com/aryan-1709/PROXY_HTTP_REQUEST_Arduino.git
   ```

2. Copy the `PROXY_HTTP_REQUEST_Arduino` folder into your Arduino libraries folder:

   * Windows: `Documents/Arduino/libraries/`
   * macOS: `~/Documents/Arduino/libraries/`
   * Linux: `~/Arduino/libraries/`

3. Restart the Arduino IDE to recognize the new library.

---


## Contributions

Contributions, issues, and feature requests are welcome! Feel free to check [issues page](https://github.com/aryan-1709/PROXY_HTTP_REQUEST_Arduino/issues).

---
