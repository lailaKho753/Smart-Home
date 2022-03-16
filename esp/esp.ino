#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "UGM-Hotspot";
const char* password =  "";
const char* mqttServer = "10.33.109.37";
const int mqttPort =  1883;
const char* mqttUser = "";
const char* mqttPassword = "";
WiFiClient espClient;
PubSubClient client(espClient);
char angka[50];
int databaca;
void setup() {
  pinMode (13, OUTPUT);
  pinMode (12, OUTPUT);
  pinMode (14, OUTPUT);
  pinMode (4, OUTPUT);
  pinMode (5, OUTPUT);
  Serial.begin(115200);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    //    Serial.println("Connecting to WiFi..");
  }
  //  Serial.println("Connected to the WiFi network");

  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);

  while (!client.connected()) {
    //    Serial.println("Connecting to MQTT...");

    if (client.connect("ESP8266Client", mqttUser, mqttPassword )) {

      //      Serial.println("connected");

    } else {

      //      Serial.print("failed with state ");
      //      Serial.print(client.state());
      delay(2000);

    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {

  //  Serial.print("Message arrived in topic: ");
  //  Serial.println(topic);
  //  Serial.print("Message:");
  String payloadmsg;

  for (int i = 0; i < length; i++) {
    //    Serial.print((char)payload[i]);
    payloadmsg += (char)payload[i];
  }
  /* if (payload [0] = '1') {
     client.subscribe("/coba1");
     Serial.print("1");
    }*/
  //  Serial.println();
  //  Serial.println("-----------------------");
  if (strcmp(topic, "LED/1") == 0) {
    if (payloadmsg == "OFF") {
      //Serial.println("ON");
      digitalWrite(13, HIGH);
        Serial.println("m0,1,1");
      //Serial.print("m0" + "," + String(1) + "," + String(1) + "\r\n");
    }
    else if (payloadmsg == "ON") {
      //Serial.println("OFF");
      digitalWrite (13, LOW);
        Serial.println("m0,1,0");
      //Serial.print("m0" + "," + String(1) + "," + String(0) + "\r\n");
    }
  }
  if (strcmp(topic, "LED/2") == 0) {
    if (payloadmsg == "OFF") {
      //Serial.println("ON");
      digitalWrite(12, HIGH);
        Serial.println("m0,2,1");
      //Serial.print("m0" + "," + String(2) + "," + String(1) + "\r\n");
    }
    else if (payloadmsg == "ON") {
      //Serial.println("OFF");
      digitalWrite (12, LOW);
        Serial.println("m0,2,0");
      //Serial.print("m0" + "," + String(2) + "," + String(0) + "\r\n");
    }
  }
  if (strcmp(topic, "LED/3") == 0) {
    if (payloadmsg == "OFF") {
      //Serial.println("ON");
      digitalWrite(14, HIGH);
        Serial.println("m0,3,1");
      //Serial.print("m0" + "," + String(3) + "," + String(1) + "\r\n");
    }
    else if (payloadmsg == "ON") {
      //Serial.println("OFF");
      digitalWrite (14, LOW);
        Serial.println("m0,3,0");
      //Serial.print("m0" + "," + String(3) + "," + String(0) + "\r\n");
    }
  }
  if (strcmp(topic, "LED/4") == 0) {
    if (payloadmsg == "OFF") {
      //Serial.println("ON");
      digitalWrite(4, HIGH);
        Serial.println("m0,4,1");
      //Serial.print("m0" + "," + String(4) + "," + String(1) + "\r\n");
    }
    else if (payloadmsg == "ON") {
      //Serial.println("OFF");
      digitalWrite (4, LOW);
      Serial.println("m0,4,0");
      //Serial.print("m0" + "," + String(4) + "," + String(0) + "\r\n");
    }
  }
//

}

void loop() {
  if (!client.connected()) {
    /*reconnect();*/
  }

  client.subscribe("LED/1");
  client.loop();
  client.subscribe("LED/2");
  client.loop();
  client.subscribe("LED/3");
  client.loop();
  client.subscribe("LED/4");
  client.loop();
  client.subscribe("LED/5");
  client.loop();
  /*int bacadata = Serial.read();
    if(bacadata == 1){
     digitalWrite (13,HIGH);
    }
    if(bacadata == 0){
     digitalWrite (13,LOW);
    }*/

}
/*void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
      // Subscribe
      client.subscribe("LED/1");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
  }*/

/*int angka (){
  int i=1;
  for(i=0;i<=10;i++){
  Serial.println(i);
  }
  }*/
