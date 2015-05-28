//We always have to include the library
#include <SoftwareSerial.h>// import the serial library
#include "string.h"
#include "font.h"
#include "LedControl.h"

/*
 Now we need a LedControl to work with.
 ***** These pin numbers will probably not work with your hardware *****
 pin 12 is connected to the DataIn
 pin 11 is connected to the CLK
 pin 10 is connected to LOAD
 We have only a single MAX72XX.
 */
LedControl lc = LedControl(12, 11, 10, 2);
int index = 0;
byte text[512];
byte byteRead;
int scroll = 0; //0 = left, 1 = right

/* we always wait a bit between updates of the display */
unsigned long delaytime = 200;

SoftwareSerial Genotronex(0, 1); // RX, TX
byte BluetoothData; // the data given from Computer
String content = "";
String temp = "";
char character;

// settup devices run one
void setup() {
  /*
   The MAX72XX is in power-saving mode on startup,
   we have to do a wakeup call
   */
  lc.shutdown(0, false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0, 8);
  /* and clear the display */
  lc.clearDisplay(0);

  lc.shutdown(1, false);
  /* Set the brightness to a medium values */
  lc.setIntensity(1, 8);
  /* and clear the display */
  lc.clearDisplay(1);

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
    if (content.equals("m01"))
    {
      scroll = 0; //set to scroll left mode
      content = temp;
    }
    if (content.equals("m02"))
    {
      scroll = 1; //set to scroll right mode
      content = temp;
    }
    temp = content;
    buffer(content);
    if (scroll == 0)
    {
      scrollLeft();
    } else
    {
      scrollRight();
    }
  }
}

void copyChar2Buffer(char ch)
{
  long tchr = ch;
  for (int i = index; i < index + 5; i++)
  {
    text[i] = pgm_read_byte(&font7x5[((tchr) * 5) + i - index]);
  }
  index += 5;
}


void buffer(String message)
{
  //Set Start SPACE
  for (int i = 0; i < 16; i++) text[i] = B00000000;
  index = 16;
  //Copy character hex
  for (int i = 0; i < message.length(); i++)
  {
    copyChar2Buffer(message[i]);
    text[index] = B00000000;
    index++;
  }
  //Set end SPACE
  for (int i = index; i < index + 16; i++) text[i] = B00000000;
  index += 16;

}

void scrollLeft()
{
  for (int co = 0; co < index - 16; co ++)
  {
    if (Genotronex.available() > 0)
      break;

    lc.setRow(1, 7, text[co + 7]);
    lc.setRow(1, 6, text[co + 6]);
    lc.setRow(1, 5, text[co + 5]);
    lc.setRow(1, 4, text[co + 4]);
    lc.setRow(1, 3, text[co + 3]);
    lc.setRow(1, 2, text[co + 2]);
    lc.setRow(1, 1, text[co + 1]);
    lc.setRow(1, 0, text[co + 0]);

    lc.setRow(0, 7, text[co + 15]);
    lc.setRow(0, 6, text[co + 14]);
    lc.setRow(0, 5, text[co + 13]);
    lc.setRow(0, 4, text[co + 12]);
    lc.setRow(0, 3, text[co + 11]);
    lc.setRow(0, 2, text[co + 10]);
    lc.setRow(0, 1, text[co + 9]);
    lc.setRow(0, 0, text[co + 8]);
    delay(delaytime);
  }
}

void scrollRight()
{
  for (int co = index; co >= 15; co--)
  {
    if (Genotronex.available() > 0) break;

    lc.setRow(1, 7, text[co - 8]);
    lc.setRow(1, 6, text[co - 9]);
    lc.setRow(1, 5, text[co - 10]);
    lc.setRow(1, 4, text[co - 11]);
    lc.setRow(1, 3, text[co - 12]);
    lc.setRow(1, 2, text[co - 13]);
    lc.setRow(1, 1, text[co - 14]);
    lc.setRow(1, 0, text[co - 15]);

    lc.setRow(0, 7, text[co - 0]);
    lc.setRow(0, 6, text[co - 1]);
    lc.setRow(0, 5, text[co - 2]);
    lc.setRow(0, 4, text[co - 3]);
    lc.setRow(0, 3, text[co - 4]);
    lc.setRow(0, 2, text[co - 5]);
    lc.setRow(0, 1, text[co - 6]);
    lc.setRow(0, 0, text[co - 7]);
    delay(delaytime);
  }
}



