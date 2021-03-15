#include <WiFi.h>

const char* ssid     = "LABORATÓRIO";
const char* password = "labo1234";
int tempoInicial = 0;
int lerEstadoPino = 0;      
int lerEstadoPinoT = 0;
int Pino = 4;
int count = 0;
int countAnterior = 0;

WiFiServer server(80);

void setup()
{
    Serial.begin(115200);       
    pinMode(Pino, INPUT_PULLUP);
    delay(10);
    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());    
    server.begin();

}

void loop() {  
  
 WiFiClient client = server.available();   // listen for incoming clients
 
  if (client) {  
  
    Serial.println("New Client.");           
    String currentLine = "";   
                 
    while (client.connected()) {   
              
      if (client.available()) {            
        char c = client.read();             
        Serial.write(c);    
                        
        if (c == '\n') {                   

          
          if (currentLine.length() == 0) {            
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.println(count); 
            client.println();            
            break;
          } else {    
            
            currentLine = "";
            
          }
          
        } else if (c != '\r') { 
          
          currentLine += c;  
              
        }
      }
    }
    
    client.stop();
    Serial.println("Client Disconnected.");
    
  }

  lerEstadoPino = digitalRead(Pino);

    if (lerEstadoPino == LOW && lerEstadoPinoT == 0) {
      
      lerEstadoPinoT = 1;
      
    } else if (lerEstadoPino == HIGH && lerEstadoPinoT == 1) {
      
      lerEstadoPinoT = 0;
      count++;
      Serial.println(count);
      
    }
    
    delay(5);

}
