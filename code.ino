#include <ESP8266WiFi.h>
#include <PubSubClient.h>

//  Wifi network SSID (name)
const char* ssid = "XXX";  
// Wifi WPA2 PSK 
const char* password = "XXXXXXX";
const char* mqtt_server = "mqtt.local";
const int switch_pump = 14;
const int switch_valve_1 = 12;
const int switch_valve_2 = 13;
const int switch_valve_3 = 15;

int value;

WiFiClient espClient;
PubSubClient client(espClient);

void callback(char* topic, byte* payload, unsigned int length) {

Serial.print("Message arrived in topic: ");
  Serial.print(topic);
 
  Serial.print(" Message:");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    value = (char)payload[i] - '0';
  }
 
  Serial.println();

 if (!strcmp(topic,"switch/pump"))  { 
     if (value == 1) { 
      digitalWrite(switch_pump, LOW);
      client.publish("switch/pump/state","1");
     }
     if (value == 0) { 
      digitalWrite(switch_pump, HIGH);
      client.publish("switch/pump/state","0");
     }
 }
 
 if (!strcmp(topic,"switch/valve1")) {
    if (value == 1) { 
      digitalWrite(switch_valve_2, HIGH);
      client.publish("switch/valve2/state","0");
      digitalWrite(switch_valve_3, HIGH);
       client.publish("switch/valve3/state","0");
      digitalWrite(switch_valve_1, LOW);
       client.publish("switch/valve1/state","1");
     }
     if (value == 0) { 
      digitalWrite(switch_valve_1, HIGH);
       client.publish("switch/valve1/state","0");
     }
 }
 if (!strcmp(topic,"switch/valve2")) {
     if (value == 1) { 
      digitalWrite(switch_valve_1, HIGH);
       client.publish("switch/valve1/state","0");
      digitalWrite(switch_valve_3, HIGH);
       client.publish("switch/valve3/state","0");
      digitalWrite(switch_valve_2, LOW);
       client.publish("switch/valve2/state","1");
     }
     if (value == 0) { 
      digitalWrite(switch_valve_2, HIGH);
       client.publish("switch/valve2/state","0");
     }
 }
 if (!strcmp(topic,"switch/valve3")) {
     if (value == 1) { 
      digitalWrite(switch_valve_1, HIGH);
      client.publish("switch/valve1/state","0");
      digitalWrite(switch_valve_2, HIGH);
      client.publish("switch/valve2/state","0");
      digitalWrite(switch_valve_3, LOW);
      client.publish("switch/valve3/state","1");
     }
     if (value == 0) { 
      digitalWrite(switch_valve_3, HIGH);
      client.publish("switch/valve3/state","0");
     }
 } 
}

void reconnect() {
 // Loop until we're reconnected
 Serial.println("");
 while (!client.connected()) {
 Serial.print("Attempting MQTT connection...");
 // Attempt to connect
 if (client.connect("ESP8266 Client","peak-load", "password")) {
  Serial.println("");
  Serial.println("MQTT connected");
  Serial.println("");
  // ... and subscribe to topic
  client.subscribe("switch/pump");
  client.subscribe("switch/valve1");
  client.subscribe("switch/valve2");
  client.subscribe("switch/valve3");
 } else {
  Serial.print("failed, rc=");
  Serial.print(client.state());
  Serial.println(" try again in 5 seconds");
  // Wait 5 seconds before retrying
  delay(5000);
  }
 }
}

void setup()
{
  pinMode(14, OUTPUT); 
  pinMode(15, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);   
  
  Serial.begin(115200);
  // We start by connecting to a WiFi network
  Serial.print("Connecting to Wifi ");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(200);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("WiFi connected! ");  
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  delay(1000);
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback); 

}

void loop()
{  
 if (!client.connected()) {
  reconnect();
 }
 client.loop();
}
