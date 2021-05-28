#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#include "config.h"
#include "Adafruit_Thermal.h"
#include "SoftwareSerial.h"

#define RX_PIN 5 // RX GPIO-Pin of your Microcontroller
#define TX_PIN 4 // TX GPIO-Pin of your Microcontroller 

#define MAX_TOPIC_LENGTH 50
#define MAX_PAYLOAD_LENGTH 10

char mqtt_id[24];
char mqtt_topic[50];

DeviceAddress device_address;
WiFiClient client;
PubSubClient mqtt(client);

SoftwareSerial mySerial(RX_PIN, TX_PIN); 
Adafruit_Thermal printer(&mySerial);

void callback(char* topic, byte* payload, unsigned int length) {

  // set textlineheight
if (strcmp(topic,mqtt_listen_topic_textlineheight)==0){
      //this topic expects integer!
      int payload_int = mqtt_row_spacing;
      for (int i=0;i<length;i++) {
        char c = payload[i];
        if (c >= '0' && c <= '9')
          payload_int = payload_int*10 + c - '0';  //encode to interger
        }
      printer.setLineHeight(payload_int);
  } 
  // set text size (S | M | L)
  if (strcmp(topic,mqtt_listen_topic_textsize)==0){
      char c = 'S';  
      for (int i=0;i<length;i++) {
        c = payload[i]; 
      }
      printer.setSize(c);
  } 
  // topic to inverse the text (0 | 1)
  if (strcmp(topic,mqtt_listen_topic_textinverse)==0){
      char c = '0';
      for (int i=0;i<length;i++) { 
       c = payload[i];   
      }
      if (c == '1') {
        printer.inverseOn();
      } else {
        printer.inverseOff();
      } 
  } 
  // topic to justify the text (L | C | R)
  if (strcmp(topic,mqtt_listen_topic_textjustify)==0){
      char c = 'L';
      for (int i=0;i<length;i++) { 
        c = payload[i];   
      }
      printer.justify(c);
  } 
  // topic to bold the text (0 | 1)
  if (strcmp(topic,mqtt_listen_topic_textbold)==0){
      char c = '0';
      for (int i=0;i<length;i++) { 
        c = payload[i];   
      }
      if (c == '1') {
        printer.boldOn();
      } else {
        printer.boldOff();
      } 
  } 
  // topic to underline the text (0 | 1)
  if (strcmp(topic,mqtt_listen_topic_textunderline)==0){
      char c = '0';
      for (int i=0;i<length;i++) { 
        c = payload[i];   
      }
      if (c == '1') {
        printer.underlineOn();
      } else {
        printer.underlineOff();
      } 
  } 

// topic to print text
 if (strcmp(topic,mqtt_listen_topic_textsize)==0){
    printer.print(F("Message arrived:\n"));
    for (int i=0;i<length;i++) {
      printer.print((char)payload[i]);
    }
    printer.print(F("\n"));
 }

} 

void setup() {

  mySerial.begin(baud);
  printer.begin();
  printer.setDefault();
  
  printer.setSize(mqtt_text_size);
  printer.setLineHeight(mqtt_row_spacing);
  printer.feed(1);
  printer.println(F("Printer starting"));
  
  wifi_station_set_hostname(my_id);
  printer.print(F("Hostname: "));
  printer.println(my_id);
  WiFi.mode(WIFI_STA);

  mqtt.setServer(mqtt_server, mqtt_port);
  mqtt.setCallback(callback);

}

void loop() {

  if (WiFi.status() != WL_CONNECTED) {
    printer.println(F("Connecting to WiFi..."));
    WiFi.begin(ssid, password);

    unsigned long begin_started = millis();
    while (WiFi.status() != WL_CONNECTED) {
      delay(10);
      if (millis() - begin_started > 60000) {
        ESP.restart();
      }
    }
    printer.println(F("WiFi connected!"));
  }

  if (!mqtt.connected()) {
    if (mqtt.connect(mqtt_id, mqtt_user, mqtt_pass)) {
      printer.println(F("MQTT connected"));
      printer.feed(1);
      mqtt.subscribe(mqtt_listen_topic_text2print);
      mqtt.subscribe(mqtt_listen_topic_textsize);
      mqtt.subscribe(mqtt_listen_topic_textlineheight);
      mqtt.subscribe(mqtt_listen_topic_textinverse);
      mqtt.subscribe(mqtt_listen_topic_textjustify);
      mqtt.subscribe(mqtt_listen_topic_textbold);
      mqtt.subscribe(mqtt_listen_topic_textunderline);
    } else {
      printer.println(F("MQTT connection failed"));
      printer.feed(1);
      delay(2000);
      return;
    }
  }

  mqtt.loop();
  
}

