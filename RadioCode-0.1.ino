//Libraries Used
#include <Wire.h>
#include <TEA5767N.h>

//Variables
TEA5767N radio = TEA5767N();
float station[] = {94.7,102.5,103.0,105.0};
int i=0, numStations = *(&station+1)-station;
boolean radioOnOff = false, muteAudio = false;

//Pins 
int onOffButton = A1;
int changeFrequencyButton = A2;

void setup() {
  pinMode(onOffButton,INPUT); 
  pinMode(changeFrequencyButton,INPUT);
  radio.setStereoNoiseCancellingOn();
}

void loop() {
  if(radioOnOff == false)
  {
    radio.setStandByOn();    
  }
  //-------------------------------------------
  if(radioOnOff == true)
  {
    radio.setStandByOff();
    radio.mute();
  }
  while(radioOnOff)
  {
    if(digitalRead(changeFrequencyButton) == HIGH) changeStation();
    if(digitalRead(onOffButton) == HIGH) muteStatus();
  }
}

void changeStation() {
  radio.turnTheSoundBackOn();
  radio.selectFrequency(station[i]);
  i++;
  if(i == numStations) i = 0;
}

void muteStatus()
{
  delay(200);
  muteAudio = !muteAudio;
  if(muteAudio == true)
  {
    radio.mute();
  }
  else
  {
    radio.turnTheSoundBackOn();
  }
}
