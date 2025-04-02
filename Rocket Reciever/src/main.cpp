#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>

// Updated structure to receive data from the sender
typedef struct struct_message {
  char a[32];
  double lat;
  double longi;
  float pitch;
  float roll;
  float yaw;
} struct_message;

// Create a struct_message instance called myData
struct_message myData;

// Callback function executed when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t* incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.print("Bytes received: ");
  Serial.println(len);

  // Send all struct items in one message
  Serial.printf("Data received - Message: %s, Latitude: %.6f, Longitude: %.6f, Pitch: %.2f, Roll: %.2f, Yaw: %.2f\n",
                myData.a, myData.lat, myData.longi, myData.pitch, myData.roll, myData.yaw);
}

void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
  delay(1000); // Give time for Serial to initialize
  Serial.println("ESP-NOW Receiver");

  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Initialize ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  } else {
    Serial.println("ESP-NOW initialized successfully");
  }

  // Register the receive callback function
  esp_now_register_recv_cb(esp_now_recv_cb_t(OnDataRecv));
}

void loop() {
  // Nothing to do here
}