#include <Bounce2.h>

#include <ESP8266WiFi.h>

#define WIFI_SSID       "yourssid"
#define WIFI_PASSWORD   "yourpassword"

#define LED_PIN 14
#define BUTTON_PIN 12

// Instantiate a Bounce object
Bounce debouncer = Bounce(); 

void setup() {
  Serial.begin(74880);
  Serial.println(WiFi.localIP());
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

  pinMode(15, OUTPUT);
  digitalWrite(15, 1);

  // Setup the first button with an internal pull-up :
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  // After setting up the button, setup the Bounce instance :
  debouncer.attach(BUTTON_PIN);
  debouncer.interval(5); // interval in ms
  
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  debouncer.update();
  
  // Get the updated value :
  int value = debouncer.read();

  // Turn on the LED if either button is pressed :
  if ( value == LOW) {
    digitalWrite(LED_PIN, HIGH);
  } else {
    digitalWrite(LED_PIN, LOW);
  }  
}
