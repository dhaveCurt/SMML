#include <WiFi.h>
#include <HTTPClient.h>
#include <stdlib.h>

const char* ssid = "Yahay";
const char* password = "erefresh";
const char* server = "http://192.168.211.91/insert_data.php";  // Replace [yourIP] with your server IP address
int node = 1;

void setup() {
  Serial.begin(115200);
  
  // Connect to WiFi
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(server);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    
    // Random sensor data for testing
    float randomTemperature = random(200, 350) / 10.0; // Random value between 20.0 and 35.0
    float randomMoisture = random(100, 800) / 10.0; // Random value between 10.0 and 80.0
    float randomEC = random(100, 200) / 10.0; // Random EC value for testing
    float randompH = random(50, 70) / 10.0; // Random pH value for testing
    float randomN = random(10, 50); // Random Nitrogen value for testing
    float randomP = random(10, 50); // Random Phosphorus value for testing
    float randomK = random(10, 50); // Random Potassium value for testing

    // Device ID (1 = Raspberry Pi, 2 = NPK Sensor, etc.)
    int deviceID = 1; // You can dynamically change it based on the device

    // Prepare the data to send
    String postData = "deviceID=" + String(deviceID) + 
                      "&phVal=" + String(randompH) + 
                      "&nVal=" + String(randomN) + 
                      "&pVal=" + String(randomP) + 
                      "&kVal=" + String(randomK) + 
                      "&tempVal=" + String(randomTemperature) + 
                      "&ecVal=" + String(randomEC) + 
                      "&moistVal=" + String(randomMoisture);

    // Send POST request
    int httpResponseCode = http.POST(postData);

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println(response);  // Server response
    } else {
      Serial.println("Error sending data");
    }

    http.end();
  }
  
  delay(3000); // Send data every 5 minutes (300000 ms)
}