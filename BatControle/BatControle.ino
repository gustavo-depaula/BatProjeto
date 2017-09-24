#include <SPI.h>
#include <WiFi.h>
#include <WiFiUdp.h>

#define AXIS_X_PIN A0
#define AXIS_Y_PIN A1
#define BTN_PIN    A2
#define LED_WIFI_CONNECTED 13

int status = WL_IDLE_STATUS;
char ssid[] = "raul-wifi-network";
char pass[] = "w1f1p@$$w0rd";

char CAR_IP[] = "192.168.0.17";
int  CAR_PORT = 55056;
int UDP_SEND_RATE = 500;

WiFiUDP Udp;

void setup() {
  Serial.begin(9600);
  pinMode(LED_WIFI_CONNECTED,OUTPUT);
  digitalWrite(LED_WIFI_CONNECTED,LOW);

  conectToWifi();
}


void loop() {
  Udp.beginPacket(CAR_IP,CAR_PORT);
  String data;
  data = getControlData();
  Serial.print("Packet Sent:");
  Serial.println(data);
  Udp.print(data);
  Udp.endPacket();
  delay(UDP_SEND_RATE);
}

String getControlData(){
  /* data ordering meaning:
    analog0 -> axis x
    analog1 -> axis y
    analog2 -> btn
  */
  String data;
  int analog0 = analogRead(AXIS_X_PIN);
  int analog1 = analogRead(AXIS_Y_PIN);
  int analog2 = analogRead(BTN_PIN);
  data = String(analog0);
  data.concat(";");
  data.concat(String(analog1));
  data.concat(";");
  data.concat(String(analog2));
  //.concat(String(analog1)).concat(String(analog2));

  return data;
}

void conectToWifi(){
  int status = WL_IDLE_STATUS;
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    while (true);
  }

  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid,pass);
    delay(10000);
  }
  Serial.println("Conectado a rede!");
  digitalWrite(LED_WIFI_CONNECTED,HIGH);
  printWifiStatus();
}

void printWifiStatus(){
  Serial.println("Connected to wifi");
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

