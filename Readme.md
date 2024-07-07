# ESP8266 Pastebin

This project allows you to create a simple pastebin using an ESP8266 module. Users can connect to the ESP8266, submit text, and receive a unique URL to access their paste. The paste data is stored in EEPROM, and the blue LED on the ESP8266 flashes whenever the EEPROM is accessed.

## Features

* WiFi network selection via serial input
* Stores WiFi credentials in EEPROM
* Simple web interface to submit and view pastes
* Generates a unique URL for each paste
* Flashes the blue LED when accessing EEPROM
* Customizable EEPROM size for larger storage

## Requirements

* ESP8266 module
* Arduino IDE
* Required Libraries:

  - ESP8266WiFi
  - EEPROM
  - ESP8266WebServer

## Setup Instructions

1. **Download or Clone the Repository**
`git clone https://github.com/yourusername/ESP8266-Pastebin.git
`cd ESP8266-Pastebin`

3. **Open the Project in Arduino IDE**

Open the `ESP8266_Pastebin.ino` file in the Arduino IDE.

3. **Install Required Libraries**

Ensure you have the necessary libraries installed in your Arduino IDE. You can install them via the Library Manager:

  - ESP8266WiFi
  - EEPROM
  - ESP8266WebServer


4. **Upload the Code to Your ESP8266**

Connect your ESP8266 to your computer, select the correct board and port in the Arduino IDE, and upload the code.

5. **Set Up WiFi Connection**

Open the Serial Monitor (set baud rate to 9600).

Follow the prompts to select a WiFi network and enter the password.

The ESP8266 will save these credentials and restart to connect to the network.

6. **Access the Web Interface**

Once connected to WiFi, the Serial Monitor will display the IP address of the ESP8266.

Open a web browser and navigate to `http://<ESP_IP>/` to access the pastebin interface.

7. **Submit a Paste**

Fill in the paste name and text, then submit the form.

The server will generate a unique URL where you can access your paste.

8. **View Your Paste**

Navigate to the generated URL to view your saved paste.

## Example

1. **Serial Monitor Output:**

```
Connecting to YourNetwork
...
WiFi connected
Server started
Use this URL to connect: http://192.168.1.100/
```

2. **Web Interface:**

  - Navigate to `http://192.168.1.100/`.
  - Fill out the form with a name and text for your paste.
  - Submit the form to receive a unique URL for your paste.


## LED Indication

The blue LED on the ESP8266 will flash whenever the EEPROM is accessed for reading or writing data.

## Files

* [ESP8266_Pastebin.ino](ESP8266-Pastebin.ino): Main Arduino sketch file.
* [ESP8266_Pastebin.bin](ESP8266-Pastebin.bin): Precompiled binary file for direct upload.

### Precompiled Binary

You can directly upload the precompiled binary file to your ESP8266 using the Arduino IDE or any other tool that supports binary uploads.

1. Download the [ESP8266_Pastebin.bin](ESP8266-Pastebin.bin) file.
2. Use the ESP8266 Flash Download Tool or the Arduino IDE to upload the binary file to your ESP826

### Arduino Project Files

The main Arduino project file is `ESP8266_Pastebin.ino`. Open this file in the Arduino IDE to upload the code to your ESP8266.

## Questions and Support

For any questions or support, feel free to open an issue on the [GitHub repository](https://github.com/yourusername/ESP8266-Pastebin/issues).

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
