//We always have to include the library
#include <SoftwareSerial.h>// import the serial library
SoftwareSerial Genotronex(0, 1); // RX, TX
byte BluetoothData; // the data given from Computer
String content = "";
String temp = "";
char character;

// settup devices run one
void setup() {

  pinMode(13, OUTPUT);
  
  // Turn the Serial Protocol ON
  // Serial.begin(9600);
  Genotronex.begin(9600);
}

// Loop
void loop()
{
  if (Genotronex.available() > 0) {
    content = Genotronex.readStringUntil('\n');
    Genotronex.println(content);
  }
  if (content != "")
  {
    if (content.equals("on"))
    {
      digitalWrite(13, HIGH);
    }
    if (content.equals("off"))
    {
      digitalWrite(13, LOW);
    }
  }
}
