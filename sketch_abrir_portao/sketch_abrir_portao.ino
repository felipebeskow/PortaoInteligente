
#include <SPI.h> 
#include <UIPEthernet.h>
 
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; 
byte ip[] = { 192, 168, 2, 175 };
EthernetServer server(80); 

String readString = String(30);
int status = 0;
 
int RelayPin = 6;

void setup() {
    Ethernet.begin(mac, ip); 
    server.begin();
    pinMode(RelayPin, OUTPUT);
    digitalWrite(RelayPin, HIGH);
    Serial.begin(9600);
}


void abrirPortao(){
    digitalWrite(RelayPin, LOW);
    Serial.print("LOW\n");
    delay(1000);

    digitalWrite(RelayPin, HIGH);
    Serial.print("HIGH\n");
}


void loop() {
    EthernetClient client = server.available(); 
    if (client) {
        while (client.connected()) {
            if (client.available()) { 
                char c = client.read(); 
                if (readString.length() < 100) 
                {
                    readString += c; 
                }  
                if (c == '\n') { 
                    if (readString.indexOf("?") <0){ 
                    }
                    else
                    if(readString.indexOf("abrir=SENHA-PARA-ABRIR") >0){ 
                        abrirPortao();
                    }
                    client.println("HTTP/1.1 200 OK");
                    client.println("Content-Type: text/html");
                    client.println();
                    client.println("<body><html>");
                    client.println("<center><form method=get name=LED><input type=hidden name=abrir value=\"SENHA-PARA-ABRIR\" /><input type=submit value=Abrir Portão></form></center>");
                    client.println("</body></html>");
                    readString=""; 
                    client.stop(); 
                }
            }
        }
    }
}
