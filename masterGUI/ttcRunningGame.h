#include "ttcGUI.h"
#include "ttcMasterGame.h"
#include <MCUFRIEND_kbv.h>
#include <TrueRandom.h>
#include <TouchScreen.h>  
#include "FiniteStateMachine.h"

#define MINPRESSURE 150
#define MAXPRESSURE 1000




class runningGame{
  private :
  

  int16_t BOXSIZE;
  int16_t OTHERBOXSIZE;
  uint16_t ID, oldPOS, currentPOS;
  uint8_t Orientation = 0;    //PORTRAIT

  const int XP=6,XM=A2,YP=A1,YM=7; //320x480 ID=0x9486
  const int TS_LEFT=929,TS_RT=180,TS_TOP=963,TS_BOT=186;

  #define BLACK   0x0000
  #define BLUE    0x001F
  #define RED     0xF800
  #define GREEN   0x07E0
  #define CYAN    0x07FF
  #define MAGENTA 0xF81F
  #define YELLOW  0xFFE0
  #define WHITE   0xFFFF



  public :
  void mainSetup(MCUFRIEND_kbv tft){
    tictacGUI.mainGameSetup(tft);
  }

  void testLoop(MCUFRIEND_kbv tft){
    if (tictacGUI.mainGameLoop(tft) > 0 && tictacGUI.mainGameLoop(tft) < 10){
      int gridRow, gridCol;

      switch(tictacGUI.mainGameLoop(tft)){
        case 1:
          gridRow = 0;
          gridCol = 0;
          break;
        case 2:
          gridRow = 0;
          gridCol = 1;
          break;
        case 3:
          gridRow = 0;
          gridCol = 2;
          break;
        case 4:
          gridRow = 1;
          gridCol = 0;
          break;
        case 5:
          gridRow = 1;
          gridCol = 1;
          break;
        case 6:
          gridRow = 1;
          gridCol = 2;
          break;
        case 7:
          gridRow = 2;
          gridCol = 0;
          break;
        case 8:
          gridRow = 2;
          gridCol = 1;
          break;
        case 9:
          gridRow = 2;
          gridCol = 2;
          break;
      }

      ttcMasterGame.PlayerTurn(gridRow, gridCol);
    }
  }
  
};

runningGame ttcRunningGame;