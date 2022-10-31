#include <Conceptinetics.h>
#include <Rdm_Defines.h>
#include <Rdm_Uid.h>



DMX_Master dmx_master ( 16 , 2 );
int bit0Pin = 8;              // LED connected to digital pin 13
int bit1Pin = 9;              // LED connected to digital pin 13
int bit2Pin = 10;              // LED connected to digital pin 13
int bit3Pin = 11;              // LED connected to digital pin 13
int defaultValue=0;
// Channel 1 is brightness??
// Channel2 is red
// 3 Green
// 4 Blue
// 5 Stobe SPeed  - Strobes per second = (value/X).  The bigger the number the faster it is.  Maybe value/10???
// 6 Pattern????
// 7 // Nothin
byte BRIGHTNESS_CHANNEL = 1;
byte RED_CHANNEL = 2;
byte GREEN_CHANNEL = 3;
byte BLUE_CHANNEL = 4;
byte STROBE_CHANNEL = 5;

void setup() {
  pinMode(bit0Pin, OUTPUT);
  pinMode(bit1Pin, OUTPUT);
  pinMode(bit2Pin, OUTPUT);
  pinMode(bit3Pin, OUTPUT);
  digitalWrite(bit0Pin,HIGH);
  digitalWrite(bit1Pin,HIGH);
  digitalWrite(bit2Pin,HIGH);
  digitalWrite(bit3Pin,HIGH);
  dmx_master.setChannelRange ( 1, 7, defaultValue );
  //dmx_master.setChannelValue ( channel, byte_value );
  // put your setup code here, to run once:
  //dmx_master.enable ();
  

  
}
// Channel 1 is brightness??
// Channel2 is red
// 3 Green
// 4 Blue
// 5 Stobe SPeed  - Strobes per second = (value/X).  The bigger the number the faster it is.  Maybe value/10???
// 6 Pattern????
// 7 // Nothin


byte strobeValue=0;


void loop() {
  int channel, channelLoop;

  // put your main code here, to run repeatedly:
  //Clear all channels to 0.  Turn off everything.
  dmx_master.setChannelRange ( 1, 7, defaultValue );  //turn everything off
  dmx_master.enable ();
  dmx_master.setChannelValue ( BRIGHTNESS_CHANNEL, 255 ); //255 = max brightness, 0 = off.    0xFF = hex 0xFF =
  
  // Ramp each color in sequence
  for (channelLoop=2; channelLoop<=4; channelLoop++)
  {
    shmooChannel(channelLoop);
    dmx_master.setChannelRange ( 2, 4, defaultValue ); // ;; Turn off everything
  }

  dmx_master.setChannelRange ( 2, 4, 255 ); // ;; Turn on everything
  // Cause Strobe
  // Channel 5, Stobe SPeed  - Strobes per second = (value/X).  The bigger the number the faster it is.  Maybe value/10???
  dmx_master.setChannelValue ( STROBE_CHANNEL, strobeValue );    
  strobeValue = (strobeValue  + 20);  //0, 20,40, 60,...240,0,20,40
  delay(5000);   //delay 5 seconds
  dmx_master.disable ();
  delay(50);
}



//increase the brightness of each color
void shmooChannel(byte channelNumber)
{
byte brightness;
  displayChannel(channelNumber);
  for (brightness = 0; brightness< 150; brightness+=1)
  {
    dmx_master.setChannelValue ( channelNumber, brightness );    
    delay(20); //delay 20 milliseconds between each increase in brightness
  }
}


//for visuals on Arduino board
void displayChannel(byte channel)
{
  digitalWrite(bit0Pin,LOW);
  digitalWrite(bit1Pin,LOW);
  digitalWrite(bit2Pin,LOW);
  digitalWrite(bit3Pin,LOW);

  if (channel & 1) {digitalWrite(bit0Pin, HIGH);};
  if (channel & 2) {digitalWrite(bit1Pin, HIGH);};
  if (channel & 4) {digitalWrite(bit2Pin, HIGH);};
  if (channel & 8) {digitalWrite(bit3Pin, HIGH);};

}