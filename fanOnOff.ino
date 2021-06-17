#include <SPI.h>
#include <Ethernet.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

// Put The LOW/HIGH Pins Here //
const int greenPin  = 8;
const int redPin    = 7;
const int fanPin    = 5;

IPAddress ip(192, 168, 199, 123);
EthernetServer server(24);

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Ethernet.begin(mac, ip);
  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    Serial.println("Ethernet Module Not Found.");
  }
  if (Ethernet.linkStatus() == LinkOFF) {
    Serial.println("Ethernet Cable Is Not Connected");
  }

  server.begin();
  Serial.print("Server iS at: ");
  Serial.println(Ethernet.localIP());

  // Set Pin As Output Pin //
  //pinMode(ledPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(fanPin, OUTPUT);
  pinMode(2, OUTPUT); // The Pin For The Raindrop Sensor //

  //digitalWrite(ledPin, LOW);
  digitalWrite(greenPin, LOW);
  digitalWrite(redPin, LOW);
  digitalWrite(fanPin, LOW);
}

void loop() {
  EthernetClient client = server.available();

  if (client) {
    Serial.println("New Connection");

    while (client.connected()) {
      if (client.available()) {
        char c = client.read();

        // Green Led //
        if (c == 'z') {
          client.println("turning on led");
          digitalWrite(greenPin, HIGH); // Pin 8 //
        }
        else if (c == 'x') {
          client.println("turning off led");
          digitalWrite(greenPin, LOW); // Pin 8 //
        }

        // Red Led //
        else if (c == 'n') {
          client.println("turning on led");
          digitalWrite(redPin, HIGH); // Pin 7 //
        }
        else if (c == 'm') {
          client.println("turning off led");
          digitalWrite(redPin, LOW); // Pin 7 //
        }
        
        // Fan Control //
        else if (c == 'k') {
          client.println("turning on fan");
          digitalWrite(fanPin, HIGH); // Pin 5 //
        }
        else if (c == 'j') {
          client.println("turning off fan");
          digitalWrite(fanPin, LOW); // Pin 5 //
        }

        // ! -- This Is For The Raindrop Sensor -- ! //
        int result = analogRead(0);
        Serial.println(result);
  
        if (analogRead(0) < 500) {
          Serial.println("Moderate Rain");
          server.write("a");
        }
        else {
          Serial.println("No Rain");
        }
        delay(1000);
      }
    }

    delay(1);

    client.stop();
    Serial.println("Connection Closed");
  }
}
