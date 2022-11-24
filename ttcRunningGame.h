#include "ttcGUI.h"
#include "ttcMasterGame.h"
#include <MCUFRIEND_kbv.h>
#include <TrueRandom.h>
#include <TouchScreen.h>  


class runningGame{
  private :

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

  void mainGameLoop(MCUFRIEND_kbv tft){
    int gridRow, gridCol;
    tft.setTextColor(RED);
    tft.setTextSize(4);    
    tft.print(tictacGUI.mainGameLoop(tft));
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

  
};

runningGame ttcRunningGame;