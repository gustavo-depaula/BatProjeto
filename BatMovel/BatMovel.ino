#include <SPI.h>
#include <WiFi.h>
#include <WiFiUdp.h>

char ssid[] = "raul-wifi-network";
char pass[] = "w1f1p@$$w0rd";

int  CAR_PORT = 55056;

char packetBuffer[255];

WiFiUDP Udp;

void setup() {
  Serial.begin(9600);
  conectToWifi();
  
  Serial.println("\nWaiting..");
  Udp.begin(CAR_PORT);
}

void loop() {
  int packetSize = Udp.parsePacket();
  if (packetSize){
    Serial.print("****************************************\nPacote recebido\nTamanho: ");
    Serial.println(packetSize);
    Serial.print("IP de origem: ");
    IPAddress remoteIp = Udp.remoteIP();
    Serial.println(remoteIp);
    Serial.println("Porta: ");
    Serial.println(CAR_PORT);

    //Tratando pacote recebido
    int len = Udp.read(packetBuffer, 255);
    if (len > 0) packetBuffer[len] = 0;
    Serial.print("Conteudo: ");
    Serial.println(packetBuffer);
    Serial.println("****************************************");
 
  }
}

void conectToWifi(){
  int status = WL_IDLE_STATUS;

  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("Wifi shield nao conectado ao arduino!");
    while (true);
  }

  while ( status != WL_CONNECTED) {
    Serial.print("Tentando se conectar a rede: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid,pass);
    delay(10000);
  }
  Serial.println("Conectado a rede!");
  printWifiStatus();

}

//void checkMessage(char packetBuffer[255]){
//    char ReplyBuffer[10];
//    if(strcmp(packetBuffer,"LIGAM1A")==0){
//      strcpy(ReplyBuffer,"M1A-ON");
//      Udp.write(ReplyBuffer);
//      Serial.println("Enviado: M1A-ON");
//      digitalWrite(m1a,LOW);
//      digitalWrite(m1b,HIGH);      
//    }
//    else if(strcmp(packetBuffer,"LIGAM1B")==0){
//      strcpy(ReplyBuffer,"M1B-ON");
//      Udp.write(ReplyBuffer);
//      Serial.println("Enviado: M1B-ON");
//      digitalWrite(m1a,HIGH);
//      digitalWrite(m1b,LOW);      
//    }
//    else if(strcmp(packetBuffer,"DESLIGAM1")==0){
//      strcpy(ReplyBuffer,"M1-OFF");
//      Udp.write(ReplyBuffer);
//      Serial.println("Enviado: M1-OFF");
//      digitalWrite(m1a,HIGH);
//      digitalWrite(m1b,HIGH);      
//    }
//    else if(strcmp(packetBuffer,"LIGAM2A")==0){
//      strcpy(ReplyBuffer,"M2A-ON");
//      Udp.write(ReplyBuffer);
//      Serial.println("Enviado: M2A-ON");
//      digitalWrite(m2a,LOW);
//      digitalWrite(m2b,HIGH);      
//    }
//    else if(strcmp(packetBuffer,"LIGAM2B")==0){
//      strcpy(ReplyBuffer,"M2B-ON");
//      Udp.write(ReplyBuffer);
//      Serial.println("Enviado: M2B-ON");
//      digitalWrite(m2a,HIGH);
//      digitalWrite(m2b,LOW);      
//    }
//    else if(strcmp(packetBuffer,"DESLIGAM2")==0){
//      strcpy(ReplyBuffer,"M2-OFF");
//      Udp.write(ReplyBuffer);
//      Serial.println("Enviado: M2-OFF");
//      digitalWrite(m2a,HIGH);
//      digitalWrite(m2b,HIGH);      
//    }
//    else if(strcmp(packetBuffer,"LIGAM3A")==0){
//      strcpy(ReplyBuffer,"M3A-ON");
//      Udp.write(ReplyBuffer);
//      Serial.println("Enviado: M3A-ON");
//      digitalWrite(m3a,LOW);
//      digitalWrite(m3b,HIGH);      
//    }
//    else if(strcmp(packetBuffer,"LIGAM3B")==0){
//      strcpy(ReplyBuffer,"M3B-ON");
//      Udp.write(ReplyBuffer);
//      Serial.println("Enviado: M3B-ON");
//      digitalWrite(m3a,HIGH);
//      digitalWrite(m3b,LOW);      
//    }
//    else if(strcmp(packetBuffer,"DESLIGAM3")==0){
//      strcpy(ReplyBuffer,"M3-OFF");
//      Udp.write(ReplyBuffer);
//      Serial.println("Enviado: M3-OFF");
//      digitalWrite(m3a,HIGH);
//      digitalWrite(m3b,HIGH);      
//    }    else if(strcmp(packetBuffer,"LIGAM4A")==0){
//      strcpy(ReplyBuffer,"M4A-ON");
//      Udp.write(ReplyBuffer);
//      Serial.println("Enviado: M4A-ON");
//      digitalWrite(m4a,LOW);
//      digitalWrite(m4b,HIGH);      
//    }
//    else if(strcmp(packetBuffer,"LIGAM4B")==0){
//      strcpy(ReplyBuffer,"M4B-ON");
//      Udp.write(ReplyBuffer);
//      Serial.println("Enviado: M4B-ON");
//      digitalWrite(m4a,HIGH);
//      digitalWrite(m4b,LOW);      
//    }
//    else if(strcmp(packetBuffer,"DESLIGAM4")==0){
//      strcpy(ReplyBuffer,"M4-OFF");
//      Udp.write(ReplyBuffer);
//      Serial.println("Enviado: M4-OFF");
//      digitalWrite(m4a,HIGH);
//      digitalWrite(m4b,HIGH);      
//    }    else if(strcmp(packetBuffer,"LIGAM5A")==0){
//      strcpy(ReplyBuffer,"M5A-ON");
//      Udp.write(ReplyBuffer);
//      Serial.println("Enviado: M5A-ON");
//      digitalWrite(m5a,LOW);
//      digitalWrite(m5b,HIGH);      
//    }
//    else if(strcmp(packetBuffer,"LIGAM5B")==0){
//      strcpy(ReplyBuffer,"M5B-ON");
//      Udp.write(ReplyBuffer);
//      Serial.println("Enviado: M5B-ON");
//      digitalWrite(m5a,HIGH);
//      digitalWrite(m5b,LOW);      
//    }
//    else if(strcmp(packetBuffer,"DESLIGAM5")==0){
//      strcpy(ReplyBuffer,"M5-OFF");
//      Udp.write(ReplyBuffer);
//      Serial.println("Enviado: M5-OFF");
//      digitalWrite(m5a,HIGH);
//      digitalWrite(m5b,HIGH);      
//    }
//    else if(strcmp(packetBuffer,"LIGALED")==0){
//      strcpy(ReplyBuffer,"LED-ON");
//      Udp.write(ReplyBuffer);
//      Serial.println("Enviado: LED-ON");
//      analogWrite(led,1024);
//    }
//    else if(strcmp(packetBuffer,"DESLIGALED")==0){
//      strcpy(ReplyBuffer,"LED-OFF");
//      Udp.write(ReplyBuffer);
//      Serial.println("Enviado: LED-OFF");
//      analogWrite(led,0);
//    }
//    else if(strcmp(packetBuffer,"TESTEON")==0){
//      strcpy(ReplyBuffer,"T-ON");
//      Udp.write(ReplyBuffer);
//      Serial.println("Enviado: T-ON");
//      analogWrite(A5,1024);
//    }
//    else if(strcmp(packetBuffer,"TESTEOFF")==0){
//      strcpy(ReplyBuffer,"T-OFF");
//      Udp.write(ReplyBuffer);
//      Serial.println("Enviado: T-OFF");
//      analogWrite(A5,0);
//    }
//
//    
//    Udp.beginPacket(Udp.remoteIP(),CAR_PORT);
//    Udp.write(ReplyBuffer);
//    Udp.endPacket();
//}

void printWifiStatus() {
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  IPAddress ip = WiFi.localIP();
  Serial.print("Endereco IP: ");
  Serial.println(ip);
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
