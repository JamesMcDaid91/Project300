#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;     
#include <TouchScreen.h>
#include <HardwareSerial.h>
#include "TicTacToe.h"
char *name = "TTTCMR";  
const int XP=6,XM=A2,YP=A1,YM=7; //320x480 ID=0x9486
const int TS_LEFT=927,TS_RT=115,TS_TOP=954,TS_BOT=114;

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
TSPoint tp;

#define MINPRESSURE 100
#define MAXPRESSURE 1000

int16_t BOXSIZE;
int16_t OTHERBOXSIZE;
uint16_t ID, oldPOS, currentPOS;
uint8_t Orientation = 0;    //PORTRAIT


#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF


void setup(void){
    uint16_t tmp;

    tft.reset();
    ID = tft.readID();
    tft.begin(ID);
    Serial.begin(9600);
    Serial.print("   test");
    tft.setRotation(Orientation);
    tft.fillScreen(BLACK);


    //TicTacToe.mainGameSetup(tft);

    //tft.fillScreen(YELLOW);
}

void loop(){
  TicTacToe.mainGameLoop(tft);
}
