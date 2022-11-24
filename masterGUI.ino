#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;     
#include <TouchScreen.h>
#include <TrueRandom.h>
//#include <HardwareSerial.h>
#include "ttcRunningGame.h"
#include "ttcMasterGame.h"
#include "ttcGUI.h"

char *name = "TTTCMR";  
const int XP=6,XM=A2,YP=A1,YM=7; //320x480 ID=0x9486
const int TS_LEFT=927,TS_RT=115,TS_TOP=954,TS_BOT=114;

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 150);
TSPoint tp;

#define MINPRESSURE 150
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

  BOXSIZE = (tft.width()+1)/ 3;
  OTHERBOXSIZE = tft.width() / 5.33;

  // if (tp.z > MINPRESSURE && tp.z < MAXPRESSURE){
    
  // } 
}

void loop(){
  tictactoe();

  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  //mainGUI();

  while(1){


    // uint16_t xpos, ypos;  //screen coordinates
    // tp = ts.getPoint();   //tp.x, tp.y are ADC values
    // //tft.fillScreen(WHITE);
    // switch (Orientation) {
    // case 0:
    //     xpos = map(tp.x, TS_LEFT, TS_RT, 0, tft.width());
    //     ypos = map(tp.y, TS_TOP, TS_BOT, 0, tft.height());
    //     break;
    // case 1:
    //     xpos = map(tp.y, TS_TOP, TS_BOT, 0, tft.width());
    //     ypos = map(tp.x, TS_RT, TS_LEFT, 0, tft.height());
    //     break;
    // case 2:
    //     xpos = map(tp.x, TS_RT, TS_LEFT, 0, tft.width());
    //     ypos = map(tp.y, TS_BOT, TS_TOP, 0, tft.height());
    //     break;
    // case 3:    
    //     xpos = map(tp.y, TS_BOT, TS_TOP, 0, tft.width());
    //     ypos = map(tp.x, TS_LEFT, TS_RT, 0, tft.height());
    //     break;
    // }
    // // if (xpos > OTHERBOXSIZE && xpos < OTHERBOXSIZE*2.5 && ypos > OTHERBOXSIZE && ypos < OTHERBOXSIZE*6){
    // //   tft.fillScreen(WHITE);
    // // }

    // if (tp.z > MINPRESSURE && tp.z < MAXPRESSURE){
    //   tft.fillScreen(WHITE);
    //   if (xpos > OTHERBOXSIZE && xpos < OTHERBOXSIZE*6){
    //         tft.fillScreen(GREEN);
    //       }
    // }
  }
}
  
void mainGUI(){
   //box 1, tic tac toe
  tft.fillRect(OTHERBOXSIZE, OTHERBOXSIZE, OTHERBOXSIZE*1.5, 6*OTHERBOXSIZE, RED);
  tft.setCursor(OTHERBOXSIZE*1.25, OTHERBOXSIZE*1.4);
  tft.setTextColor(WHITE);
  tft.setTextSize(5);
  tft.setRotation(3);
  tft.print("TIC TAC TOE");
  tft.setRotation(0);

  //box 2, tbd (settings etc)
  tft.fillRect(OTHERBOXSIZE*3, OTHERBOXSIZE, OTHERBOXSIZE*1.5, 6*OTHERBOXSIZE, GREEN);
  tft.setCursor(OTHERBOXSIZE*1.05, OTHERBOXSIZE*3.4);
  tft.setTextColor(WHITE);
  tft.setTextSize(5);
  tft.setRotation(3);
  tft.print("TBD/SETTINGS");
  tft.setRotation(0);
}

void tictactoe(){
 ttcRunningGame.mainSetup(tft);
 ttcRunningGame.mainGameLoop(tft);
}
