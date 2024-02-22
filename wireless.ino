#if defined(ESP32)
#include <WiFi.h>
#include <FirebaseESP32.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#endif

#include <addons/TokenHelper.h>
#include <addons/RTDBHelper.h>

/* 1. Define the WiFi credentials */
#define WIFI_SSID "Son of God"
#define WIFI_PASSWORD ""

/* 2. Define the API Key */
#define API_KEY "AIzaSyDhODCfRKvVbYeHQOruplcmfY0_f_PNaoc"

/* 3. Define the RTDB URL */
#define DATABASE_URL "oilleveldetector-default-rtdb.firebaseio.com"

/* 4. Define the user Email and password that already registered or added in your project */
#define USER_EMAIL "vincentbettoh@gmail.com"
#define USER_PASSWORD "123456"

// Define Firebase Data object
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

// Pin connected to the water level sensor
const int waterLevelSensorPin = D2;  // Change this to the actual pin you've connected the sensor to

unsigned long sendDataPrevMillis = 0;
unsigned long count = 0;
int h;

void setup() {
  Serial.begin(115200);

  // Connect to WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);

  // Configure Firebase
  config.api_key = API_KEY;
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;
  config.database_url = DATABASE_URL;
  config.token_status_callback = tokenStatusCallback; 

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
  Firebase.setDoubleDigits(5);
}

void loop() {
  while (Serial.available()) {
    h = Serial.read();
  }

  // Read water level from the sensor
  int waterLevel = digitalRead(waterLevelSensorPin);

  // Prepare Firebase JSON data
  FirebaseJson json1;
  json1.set("1/Status", F("1"));
  json1.set("1/OilLevel", F("taken"));
  json1.set("1/WaterLevel",1);

  // Send data to Firebase
  Serial.printf("Set json... %s\n", Firebase.set(fbdo, F("/OilLevels"), json1) ? "ok" : fbdo.errorReason().c_str());

  delay(1000);
}
