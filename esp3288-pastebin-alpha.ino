#include <ESP8266WiFi.h>
#include <EEPROM.h>
#include <ESP8266WebServer.h>

// Define EEPROM size
#define EEPROM_SIZE 2048 // Increase the size for storing larger text

// Define the LED pin
#define LED_PIN 2

// Create an instance of the ESP8266WebServer class on port 80
ESP8266WebServer server(80);

char ssid[32];
char password[64];
String storedText;

void setup() {
  // Start the Serial communication
  Serial.begin(9600);
  delay(10);

  // Initialize EEPROM
  EEPROM.begin(EEPROM_SIZE);
  loadCredentials();
  
  // Initialize LED pin
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH); // Turn off LED initially

  // Check if SSID is not empty
  if (strlen(ssid) > 0) {
    // Attempt to connect to Wi-Fi
    WiFi.begin(ssid, password);
    Serial.print("Connecting to ");
    Serial.println(ssid);

    // Wait for connection
    int timeout = 0;
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
      timeout++;
      if (timeout > 20) {
        Serial.println("Failed to connect. Starting Wi-Fi scan...");
        scanNetworks();
        return;
      }
    }

    Serial.println("");
    Serial.println("WiFi connected");

    // Start the server
    server.on("/", handleRoot); // Define the route for displaying the form
    server.on("/submit", handleSubmit); // Define the route for handling form submission
    server.begin(); // Start the server
    Serial.println("Server started");

    // Print the IP address
    Serial.print("Use this URL to connect: ");
    Serial.print("http://");
    Serial.print(WiFi.localIP());
    Serial.println("/");
  } else {
    scanNetworks();
  }
}

void loop() {
  server.handleClient(); // Handle client requests
}

void handleRoot() {
  String html = "<html><body>"
                "<h1>ESP8266 Pastebin</h1>"
                "<form action='/submit' method='POST'>"
                "<textarea name='content' rows='10' cols='30'></textarea><br>"
                "<input type='submit' value='Submit'>"
                "</form>"
                "<h2>Stored Text:</h2>"
                "<pre>" + storedText + "</pre>"
                "</body></html>";

  server.send(200, "text/html", html);
}

void handleSubmit() {
  if (server.hasArg("content")) {
    storedText = server.arg("content");
    saveText(storedText);
  }
  server.sendHeader("Location", "/");
  server.send(303);
}

void scanNetworks() {
  int n = WiFi.scanNetworks();
  Serial.println();
  if (n == 0) {
    Serial.println("No networks found");
  } else {
    Serial.println("Networks found:");
    for (int i = 0; i < n; ++i) {
      Serial.print(i);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.println(")");
    }
  }
  Serial.println("Select network by number: ");
  while (!Serial.available());
  int networkIndex = Serial.parseInt();
  Serial.print("Selected network: ");
  Serial.println(WiFi.SSID(networkIndex));
  Serial.println("Enter password: ");

  // Wait for the user to enter the password
  while (!Serial.available());
  int len = Serial.readBytesUntil('\n', password, sizeof(password) - 1);
  password[len] = '\0';

  // Save credentials to EEPROM
  saveCredentials(WiFi.SSID(networkIndex).c_str(), password);

  // Restart to connect with new credentials
  ESP.restart();
}

void saveCredentials(const char* ssid, const char* password) {
  flashLED(); // Flash LED when accessing EEPROM
  
  // Clear previous data
  for (int i = 0; i < EEPROM_SIZE; i++) {
    EEPROM.write(i, 0);
  }
  
  // Save SSID
  for (int i = 0; i < 32; i++) {
    EEPROM.write(i, ssid[i]);
    if (ssid[i] == '\0') break;
  }

  // Save password
  for (int i = 0; i < 64; i++) {
    EEPROM.write(32 + i, password[i]);
    if (password[i] == '\0') break;
  }

  EEPROM.commit();
  flashLED(); // Flash LED when EEPROM write is completed
}

void loadCredentials() {
  flashLED(); // Flash LED when accessing EEPROM
  
  // Load SSID
  for (int i = 0; i < 32; i++) {
    ssid[i] = EEPROM.read(i);
  }
  ssid[31] = '\0';

  // Load password
  for (int i = 0; i < 64; i++) {
    password[i] = EEPROM.read(32 + i);
  }
  password[63] = '\0';

  flashLED(); // Flash LED when EEPROM read is completed
}

void saveText(String text) {
  flashLED(); // Flash LED when accessing EEPROM
  
  for (int i = 0; i < EEPROM_SIZE; i++) {
    EEPROM.write(i, 0);
  }
  for (int i = 0; i < text.length(); i++) {
    EEPROM.write(i, text[i]);
  }
  EEPROM.commit();
  
  flashLED(); // Flash LED when EEPROM write is completed
}

void loadText() {
  flashLED(); // Flash LED when accessing EEPROM
  
  storedText = "";
  for (int i = 0; i < EEPROM_SIZE; i++) {
    char c = EEPROM.read(i);
    if (c == 0) break;
    storedText += c;
  }

  flashLED(); // Flash LED when EEPROM read is completed
}

void flashLED() {
  digitalWrite(LED_PIN, LOW); // Turn on the LED
  delay(100); // Wait for 100 milliseconds
  digitalWrite(LED_PIN, HIGH); // Turn off the LED
}
