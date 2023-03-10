#include <MCUFRIEND_kbv.h>
#include <TrueRandom.h>
#include <TouchScreen.h>
#include "FiniteStateMachine.h"
#include <stdio.h>


// PLAYER 1 = X
// PLAYER 2 = O
// 
//

#ifndef ttcGUI_h
#define ttcGUI_h

class ttcGUI{
  private:  
    bool player1 = true, player2 = false, pos1, pos2, pos3, pos4, pos5, pos6, pos7, pos8, pos9;
    const int XP=6,XM=A2,YP=A1,YM=7; //320x480 ID=0x9486
    const int TS_LEFT=929,TS_RT=180,TS_TOP=963,TS_BOT=186;

    TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
    TSPoint tp;

    //MCUFRIEND_kbv tft;    

    #define MINPRESSURE 200
    #define MAXPRESSURE 1000

    int16_t BOXSIZE;
    int16_t OTHERBOXSIZE;
    
    uint8_t Orientation = 0;    //PORTRAIT

    #define BLACK   0x0000
    #define BLUE    0x001F
    #define RED     0xF800
    #define GREEN   0x07E0
    #define CYAN    0x07FF
    #define MAGENTA 0xF81F
    #define YELLOW  0xFFE0
    #define WHITE   0xFFFF


  public:
    uint16_t ID, currentPOS;

    void allPosReset(){
      pos1 = false, pos2 = false, pos3 = false, pos4 = false, pos5 = false, pos6 = false, pos7 = false, pos8 = false, pos9 = false;
    }

    void EndScreen(int winner){
      allPosReset();
      tft.fillScreen(GREEN);
      tft.setRotation(3);
      tft.setTextColor(BLACK);
      tft.setTextSize(4);
      tft.setCursor(0, OTHERBOXSIZE);
      switch(winner){
        case 0:
          tft.print("Draw! ");
          break;
        case 1:
          tft.print("Player 1 Wins! ");
          break;
        case 2: 
          tft.print("AI Wins! ");
          break;
        case 3: 
          tft.print("Player 2 Wins! ");
        case 4:
        break;
        default:
          tft.print("Error in calculating winner");      
          break;
      }

      tft.println("press anywhere to return to main menu");
      tft.setRotation(0);
    }
      
    void drawFrontPage(MCUFRIEND_kbv tft){}

    void drawGrid(MCUFRIEND_kbv tft){
      BOXSIZE = (tft.width()+1)/ 3;
      OTHERBOXSIZE = tft.width() / 5.33;
      tft.fillScreen(BLACK);

      tft.fillRect(0, (OTHERBOXSIZE * 3)-3, tft.height(), 5, WHITE); //left line
      tft.fillRect(0, (OTHERBOXSIZE * 5)-3, tft.height(), 5, WHITE); //right line
      tft.fillRect(BOXSIZE-2, OTHERBOXSIZE, 5, OTHERBOXSIZE*6, WHITE); //middle top  
      tft.fillRect((BOXSIZE * 2)-2, OTHERBOXSIZE, 5, OTHERBOXSIZE*6, WHITE); //middle bottom
      delay(250);
    }

    int getTouchedPosition(MCUFRIEND_kbv tft, bool firstRun){
      
      uint16_t xpos = 0, ypos = 0;  //screen coordinates
      tp = ts.getPoint();   //tp.x, tp.y are ADC values

      pinMode(XM, OUTPUT);
      pinMode(YP, OUTPUT);

      if (firstRun == true) return 0;
      

      switch (Orientation) {
        case 0:
            xpos = map(tp.x, TS_LEFT, TS_RT, 0, tft.width());
            ypos = map(tp.y, TS_TOP, TS_BOT, 0, tft.height());
            break;
        case 1:
            xpos = map(tp.y, TS_TOP, TS_BOT, 0, tft.width());
            ypos = map(tp.x, TS_RT, TS_LEFT, 0, tft.height());
            break;
        case 2:
            xpos = map(tp.x, TS_RT, TS_LEFT, 0, tft.width());
            ypos = map(tp.y, TS_BOT, TS_TOP, 0, tft.height());
            break;
        case 3:
            xpos = map(tp.y, TS_BOT, TS_TOP, 0, tft.width());
            ypos = map(tp.x, TS_LEFT, TS_RT, 0, tft.height());
            break;
      }

      ///////////////////////////////////////////////////////////////////////////////////////////////
      //                       split into 3 ypos, top, middle and bottom.                          //
      //                                                                                           //
      //       if you are within the boxsize height portion of each designated one.                //
      //                                                                                           //
      //       first 3 positions, if you are within the boxsize height portion of the top 3 boxes. //                                                                                         //
      //                                                                                           //
      //        width of all boxes are BOXSIZE, this finds out which based on the xpos             //
      ///////////////////////////////////////////////////////////////////////////////////////////////
      
      
      if (ypos > OTHERBOXSIZE && ypos < (OTHERBOXSIZE + BOXSIZE)) {             
        if (xpos < BOXSIZE && pos1 == false) { 
            currentPOS = 1;
            pos1 = true;                            
        } else if (xpos < BOXSIZE * 2 && pos2 == false) { 
            currentPOS = 2;
            pos2 = true;
        } else if (xpos < BOXSIZE * 3 && pos3 == false) {
            currentPOS = 3;
            pos3 = true;
        }
      }

      if (ypos > OTHERBOXSIZE * 3 && ypos < (OTHERBOXSIZE * 3 + BOXSIZE)){
        if (xpos < BOXSIZE && pos4 == false) {
            currentPOS = 4;
            pos4 = true;          
        } else if (xpos < BOXSIZE * 2 && pos5 == false) {
            currentPOS = 5;
            pos5 = true;              
        } else if (xpos < BOXSIZE * 3 && pos6 == false) {
            currentPOS = 6;
            pos6 = true;                 
        }
      }

      if (ypos > OTHERBOXSIZE * 5 && ypos < (OTHERBOXSIZE * 5 + BOXSIZE)){
        if (xpos < BOXSIZE && pos7 == false) {
            currentPOS = 7;
            pos7 = true;           
        } else if (xpos < BOXSIZE * 2 && pos8 == false) {
            currentPOS = 8;
            pos8 = true;
        } else if (xpos < BOXSIZE * 3 && pos9 == false) {
            currentPOS = 9;
            pos9 = true;
        }
      }
      return currentPOS;
    }

    void Cross_1(){
      tft.drawLine(OTHERBOXSIZE / 4, OTHERBOXSIZE * 1.25, BOXSIZE - (OTHERBOXSIZE / 4), (OTHERBOXSIZE * 2.75), BLUE);
      tft.drawLine(OTHERBOXSIZE / 4 + 1, OTHERBOXSIZE * 1.25, BOXSIZE - (OTHERBOXSIZE / 4 - 1), (OTHERBOXSIZE * 2.75), BLUE);
      tft.drawLine(OTHERBOXSIZE / 4 + 2, OTHERBOXSIZE * 1.25, BOXSIZE - (OTHERBOXSIZE / 4 - 2), (OTHERBOXSIZE * 2.75), BLUE);
      tft.drawLine(OTHERBOXSIZE / 4 + 3, OTHERBOXSIZE * 1.25, BOXSIZE - (OTHERBOXSIZE / 4 - 3), (OTHERBOXSIZE * 2.75), BLUE);

      tft.drawLine(BOXSIZE - (OTHERBOXSIZE / 4), OTHERBOXSIZE * 1.25, OTHERBOXSIZE / 4, (OTHERBOXSIZE * 2.75), BLUE);
      tft.drawLine(BOXSIZE - (OTHERBOXSIZE / 4 - 1), OTHERBOXSIZE * 1.25, OTHERBOXSIZE / 4 + 1, (OTHERBOXSIZE * 2.75), BLUE);
      tft.drawLine(BOXSIZE - (OTHERBOXSIZE / 4 - 2), OTHERBOXSIZE * 1.25, OTHERBOXSIZE / 4 + 2, (OTHERBOXSIZE * 2.75), BLUE);
      tft.drawLine(BOXSIZE - (OTHERBOXSIZE / 4 - 3), OTHERBOXSIZE * 1.25, OTHERBOXSIZE / 4 + 3, (OTHERBOXSIZE * 2.75), BLUE);
    }

    void Cross_2(){
      tft.drawLine(BOXSIZE + OTHERBOXSIZE / 4, OTHERBOXSIZE * 1.25, BOXSIZE * 2 - (OTHERBOXSIZE / 4), (OTHERBOXSIZE * 2.75), BLUE);
      tft.drawLine(BOXSIZE + OTHERBOXSIZE / 4 + 1, OTHERBOXSIZE * 1.25, BOXSIZE * 2 - (OTHERBOXSIZE / 4 - 1), (OTHERBOXSIZE * 2.75), BLUE);
      tft.drawLine(BOXSIZE + OTHERBOXSIZE / 4 + 2, OTHERBOXSIZE * 1.25, BOXSIZE * 2 - (OTHERBOXSIZE / 4 - 2), (OTHERBOXSIZE * 2.75), BLUE);
      tft.drawLine(BOXSIZE + OTHERBOXSIZE / 4 + 3, OTHERBOXSIZE * 1.25, BOXSIZE * 2 - (OTHERBOXSIZE / 4 - 3), (OTHERBOXSIZE * 2.75), BLUE);

      tft.drawLine(BOXSIZE * 2 - (OTHERBOXSIZE / 4), OTHERBOXSIZE * 1.25, BOXSIZE + OTHERBOXSIZE / 4, (OTHERBOXSIZE * 2.75), BLUE);
      tft.drawLine(BOXSIZE * 2 - (OTHERBOXSIZE / 4 - 1), OTHERBOXSIZE * 1.25, BOXSIZE + OTHERBOXSIZE / 4 + 1, (OTHERBOXSIZE * 2.75), BLUE);
      tft.drawLine(BOXSIZE * 2 - (OTHERBOXSIZE / 4 - 2), OTHERBOXSIZE * 1.25, BOXSIZE + OTHERBOXSIZE / 4 + 2, (OTHERBOXSIZE * 2.75), BLUE);
      tft.drawLine(BOXSIZE * 2 - (OTHERBOXSIZE / 4 - 3), OTHERBOXSIZE * 1.25, BOXSIZE + OTHERBOXSIZE / 4 + 3, (OTHERBOXSIZE * 2.75), BLUE);
    }

    void Cross_3(){
      tft.drawLine(BOXSIZE * 2 + OTHERBOXSIZE / 4, OTHERBOXSIZE * 1.25, BOXSIZE * 3 - (OTHERBOXSIZE / 4), (OTHERBOXSIZE * 2.75), BLUE);
      tft.drawLine(BOXSIZE * 2 + OTHERBOXSIZE / 4 + 1, OTHERBOXSIZE * 1.25, BOXSIZE * 3 - (OTHERBOXSIZE / 4 - 1), (OTHERBOXSIZE * 2.75), BLUE);
      tft.drawLine(BOXSIZE * 2 + OTHERBOXSIZE / 4 + 2, OTHERBOXSIZE * 1.25, BOXSIZE * 3 - (OTHERBOXSIZE / 4 - 2), (OTHERBOXSIZE * 2.75), BLUE);
      tft.drawLine(BOXSIZE * 2 + OTHERBOXSIZE / 4 + 3, OTHERBOXSIZE * 1.25, BOXSIZE * 3 - (OTHERBOXSIZE / 4 - 3), (OTHERBOXSIZE * 2.75), BLUE);

      tft.drawLine(BOXSIZE * 3 - (OTHERBOXSIZE / 4), OTHERBOXSIZE * 1.25, BOXSIZE * 2 + OTHERBOXSIZE / 4, (OTHERBOXSIZE * 2.75), BLUE);
      tft.drawLine(BOXSIZE * 3 - (OTHERBOXSIZE / 4 - 1), OTHERBOXSIZE * 1.25, BOXSIZE * 2 + OTHERBOXSIZE / 4 + 1, (OTHERBOXSIZE * 2.75), BLUE);
      tft.drawLine(BOXSIZE * 3 - (OTHERBOXSIZE / 4 - 2), OTHERBOXSIZE * 1.25, BOXSIZE * 2 + OTHERBOXSIZE / 4 + 2, (OTHERBOXSIZE * 2.75), BLUE);
      tft.drawLine(BOXSIZE * 3 - (OTHERBOXSIZE / 4 - 3), OTHERBOXSIZE * 1.25, BOXSIZE * 2 + OTHERBOXSIZE / 4 + 3, (OTHERBOXSIZE * 2.75), BLUE);
    }

    void Cross_4(){
      tft.drawLine(OTHERBOXSIZE / 4, OTHERBOXSIZE * 3.25, BOXSIZE - (OTHERBOXSIZE / 4), (OTHERBOXSIZE * 4.75), BLUE);
      tft.drawLine(OTHERBOXSIZE / 4 + 1, OTHERBOXSIZE * 3.25, BOXSIZE - (OTHERBOXSIZE / 4 - 1), (OTHERBOXSIZE * 4.75), BLUE);
      tft.drawLine(OTHERBOXSIZE / 4 + 2, OTHERBOXSIZE * 3.25, BOXSIZE - (OTHERBOXSIZE / 4 - 2), (OTHERBOXSIZE * 4.75), BLUE);
      tft.drawLine(OTHERBOXSIZE / 4 + 3, OTHERBOXSIZE * 3.25, BOXSIZE - (OTHERBOXSIZE / 4 - 3), (OTHERBOXSIZE * 4.75), BLUE);

      tft.drawLine(BOXSIZE - (OTHERBOXSIZE / 4), OTHERBOXSIZE * 3.25, OTHERBOXSIZE / 4, (OTHERBOXSIZE * 4.75), BLUE);
      tft.drawLine(BOXSIZE - (OTHERBOXSIZE / 4 - 1), OTHERBOXSIZE * 3.25, OTHERBOXSIZE / 4 + 1, (OTHERBOXSIZE * 4.75), BLUE);
      tft.drawLine(BOXSIZE - (OTHERBOXSIZE / 4 - 2), OTHERBOXSIZE * 3.25, OTHERBOXSIZE / 4 + 2, (OTHERBOXSIZE * 4.75), BLUE);
      tft.drawLine(BOXSIZE - (OTHERBOXSIZE / 4 - 3), OTHERBOXSIZE * 3.25, OTHERBOXSIZE / 4 + 3, (OTHERBOXSIZE * 4.75), BLUE);
    }

    void Cross_5(){
      tft.drawLine(BOXSIZE + OTHERBOXSIZE / 4, OTHERBOXSIZE * 3.25, BOXSIZE * 2 - (OTHERBOXSIZE / 4), (OTHERBOXSIZE * 4.75), BLUE);
      tft.drawLine(BOXSIZE + OTHERBOXSIZE / 4 + 1, OTHERBOXSIZE * 3.25, BOXSIZE * 2 - (OTHERBOXSIZE / 4 - 1), (OTHERBOXSIZE * 4.75), BLUE);
      tft.drawLine(BOXSIZE + OTHERBOXSIZE / 4 + 2, OTHERBOXSIZE * 3.25, BOXSIZE * 2 - (OTHERBOXSIZE / 4 - 2), (OTHERBOXSIZE * 4.75), BLUE);
      tft.drawLine(BOXSIZE + OTHERBOXSIZE / 4 + 3, OTHERBOXSIZE * 3.25, BOXSIZE * 2 - (OTHERBOXSIZE / 4 - 3), (OTHERBOXSIZE * 4.75), BLUE);

      tft.drawLine(BOXSIZE * 2 - (OTHERBOXSIZE / 4), OTHERBOXSIZE * 3.25, BOXSIZE + OTHERBOXSIZE / 4, (OTHERBOXSIZE * 4.75), BLUE);
      tft.drawLine(BOXSIZE * 2 - (OTHERBOXSIZE / 4 - 1), OTHERBOXSIZE * 3.25, BOXSIZE + OTHERBOXSIZE / 4 + 1, (OTHERBOXSIZE * 4.75), BLUE);
      tft.drawLine(BOXSIZE * 2 - (OTHERBOXSIZE / 4 - 2), OTHERBOXSIZE * 3.25, BOXSIZE + OTHERBOXSIZE / 4 + 2, (OTHERBOXSIZE * 4.75), BLUE);
      tft.drawLine(BOXSIZE * 2 - (OTHERBOXSIZE / 4 - 3), OTHERBOXSIZE * 3.25, BOXSIZE + OTHERBOXSIZE / 4 + 3, (OTHERBOXSIZE * 4.75), BLUE);
    }

    void Cross_6(){
      tft.drawLine(BOXSIZE * 2 + OTHERBOXSIZE / 4, OTHERBOXSIZE * 3.25, BOXSIZE * 3 - (OTHERBOXSIZE / 4), (OTHERBOXSIZE * 4.75), BLUE);
      tft.drawLine(BOXSIZE * 2 + OTHERBOXSIZE / 4 + 1, OTHERBOXSIZE * 3.25, BOXSIZE * 3 - (OTHERBOXSIZE / 4 - 1), (OTHERBOXSIZE * 4.75), BLUE);
      tft.drawLine(BOXSIZE * 2 + OTHERBOXSIZE / 4 + 2, OTHERBOXSIZE * 3.25, BOXSIZE * 3 - (OTHERBOXSIZE / 4 - 2), (OTHERBOXSIZE * 4.75), BLUE);
      tft.drawLine(BOXSIZE * 2 + OTHERBOXSIZE / 4 + 3, OTHERBOXSIZE * 3.25, BOXSIZE * 3 - (OTHERBOXSIZE / 4 - 3), (OTHERBOXSIZE * 4.75), BLUE);

      tft.drawLine(BOXSIZE * 3 - (OTHERBOXSIZE / 4), OTHERBOXSIZE * 3.25, BOXSIZE * 2 + OTHERBOXSIZE / 4, (OTHERBOXSIZE * 4.75), BLUE);
      tft.drawLine(BOXSIZE * 3 - (OTHERBOXSIZE / 4 - 1), OTHERBOXSIZE * 3.25, BOXSIZE * 2 + OTHERBOXSIZE / 4 + 1, (OTHERBOXSIZE * 4.75), BLUE);
      tft.drawLine(BOXSIZE * 3 - (OTHERBOXSIZE / 4 - 2), OTHERBOXSIZE * 3.25, BOXSIZE * 2 + OTHERBOXSIZE / 4 + 2, (OTHERBOXSIZE * 4.75), BLUE);
      tft.drawLine(BOXSIZE * 3 - (OTHERBOXSIZE / 4 - 3), OTHERBOXSIZE * 3.25, BOXSIZE * 2 + OTHERBOXSIZE / 4 + 3, (OTHERBOXSIZE * 4.75), BLUE);
    }

    void Cross_7(){
      tft.drawLine(OTHERBOXSIZE / 4, OTHERBOXSIZE * 5.25, BOXSIZE - (OTHERBOXSIZE / 4), (OTHERBOXSIZE * 6.75), BLUE);
      tft.drawLine(OTHERBOXSIZE / 4 + 1, OTHERBOXSIZE * 5.25, BOXSIZE - (OTHERBOXSIZE / 4 - 1), (OTHERBOXSIZE * 6.75), BLUE);
      tft.drawLine(OTHERBOXSIZE / 4 + 2, OTHERBOXSIZE * 5.25, BOXSIZE - (OTHERBOXSIZE / 4 - 2), (OTHERBOXSIZE * 6.75), BLUE);
      tft.drawLine(OTHERBOXSIZE / 4 + 3, OTHERBOXSIZE * 5.25, BOXSIZE - (OTHERBOXSIZE / 4 - 3), (OTHERBOXSIZE * 6.75), BLUE);

      tft.drawLine(BOXSIZE - (OTHERBOXSIZE / 4), OTHERBOXSIZE * 5.25, OTHERBOXSIZE / 4, (OTHERBOXSIZE * 6.75), BLUE);
      tft.drawLine(BOXSIZE - (OTHERBOXSIZE / 4 - 1), OTHERBOXSIZE * 5.25, OTHERBOXSIZE / 4 + 1, (OTHERBOXSIZE * 6.75), BLUE);
      tft.drawLine(BOXSIZE - (OTHERBOXSIZE / 4 - 2), OTHERBOXSIZE * 5.25, OTHERBOXSIZE / 4 + 2, (OTHERBOXSIZE * 6.75), BLUE);
      tft.drawLine(BOXSIZE - (OTHERBOXSIZE / 4 - 3), OTHERBOXSIZE * 5.25, OTHERBOXSIZE / 4 + 3, (OTHERBOXSIZE * 6.75), BLUE);
    }

    void Cross_8(){
      tft.drawLine(BOXSIZE + OTHERBOXSIZE / 4, OTHERBOXSIZE * 5.25, BOXSIZE * 2 - (OTHERBOXSIZE / 4), (OTHERBOXSIZE * 6.75), BLUE);
      tft.drawLine(BOXSIZE + OTHERBOXSIZE / 4 + 1, OTHERBOXSIZE * 5.25, BOXSIZE * 2 - (OTHERBOXSIZE / 4 - 1), (OTHERBOXSIZE * 6.75), BLUE);
      tft.drawLine(BOXSIZE + OTHERBOXSIZE / 4 + 2, OTHERBOXSIZE * 5.25, BOXSIZE * 2 - (OTHERBOXSIZE / 4 - 2), (OTHERBOXSIZE * 6.75), BLUE);
      tft.drawLine(BOXSIZE + OTHERBOXSIZE / 4 + 3, OTHERBOXSIZE * 5.25, BOXSIZE * 2 - (OTHERBOXSIZE / 4 - 3), (OTHERBOXSIZE * 6.75), BLUE);

      tft.drawLine(BOXSIZE * 2 - (OTHERBOXSIZE / 4), OTHERBOXSIZE * 5.25, BOXSIZE + OTHERBOXSIZE / 4, (OTHERBOXSIZE * 6.75), BLUE);
      tft.drawLine(BOXSIZE * 2 - (OTHERBOXSIZE / 4 - 1), OTHERBOXSIZE * 5.25, BOXSIZE + OTHERBOXSIZE / 4 + 1, (OTHERBOXSIZE * 6.75), BLUE);
      tft.drawLine(BOXSIZE * 2 - (OTHERBOXSIZE / 4 - 2), OTHERBOXSIZE * 5.25, BOXSIZE + OTHERBOXSIZE / 4 + 2, (OTHERBOXSIZE * 6.75), BLUE);
      tft.drawLine(BOXSIZE * 2 - (OTHERBOXSIZE / 4 - 3), OTHERBOXSIZE * 5.25, BOXSIZE + OTHERBOXSIZE / 4 + 3, (OTHERBOXSIZE * 6.75), BLUE);
    }

    void Cross_9(){
      tft.drawLine(BOXSIZE * 2 + OTHERBOXSIZE / 4, OTHERBOXSIZE * 5.25, BOXSIZE * 3 - (OTHERBOXSIZE / 4), (OTHERBOXSIZE * 6.75), BLUE);
      tft.drawLine(BOXSIZE * 2 + OTHERBOXSIZE / 4 + 1, OTHERBOXSIZE * 5.25, BOXSIZE * 3 - (OTHERBOXSIZE / 4 - 1), (OTHERBOXSIZE * 6.75), BLUE);
      tft.drawLine(BOXSIZE * 2 + OTHERBOXSIZE / 4 + 2, OTHERBOXSIZE * 5.25, BOXSIZE * 3 - (OTHERBOXSIZE / 4 - 2), (OTHERBOXSIZE * 6.75), BLUE);
      tft.drawLine(BOXSIZE * 2 + OTHERBOXSIZE / 4 + 3, OTHERBOXSIZE * 5.25, BOXSIZE * 3 - (OTHERBOXSIZE / 4 - 3), (OTHERBOXSIZE * 6.75), BLUE);

      tft.drawLine(BOXSIZE * 3 - (OTHERBOXSIZE / 4), OTHERBOXSIZE * 5.25, BOXSIZE * 2 + OTHERBOXSIZE / 4, (OTHERBOXSIZE * 6.75), BLUE);
      tft.drawLine(BOXSIZE * 3 - (OTHERBOXSIZE / 4 - 1), OTHERBOXSIZE * 5.25, BOXSIZE * 2 + OTHERBOXSIZE / 4 + 1, (OTHERBOXSIZE * 6.75), BLUE);
      tft.drawLine(BOXSIZE * 3 - (OTHERBOXSIZE / 4 - 2), OTHERBOXSIZE * 5.25, BOXSIZE * 2 + OTHERBOXSIZE / 4 + 2, (OTHERBOXSIZE * 6.75), BLUE);
      tft.drawLine(BOXSIZE * 3 - (OTHERBOXSIZE / 4 - 3), OTHERBOXSIZE * 5.25, BOXSIZE * 2 + OTHERBOXSIZE / 4 + 3, (OTHERBOXSIZE * 6.75), BLUE);
    }

    void Circle_1(){
      tft.drawCircle(BOXSIZE/2, OTHERBOXSIZE * 2, OTHERBOXSIZE/1.5, RED);
      tft.drawCircle(BOXSIZE/2, OTHERBOXSIZE * 2, (OTHERBOXSIZE/1.5) + 1, RED);
      tft.drawCircle(BOXSIZE/2, OTHERBOXSIZE * 2, (OTHERBOXSIZE/1.5) + 2, RED);
      tft.drawCircle(BOXSIZE/2, OTHERBOXSIZE * 2, (OTHERBOXSIZE/1.5) + 3, RED);
    }

    void Circle_2(){
      tft.drawCircle(tft.width()/2, OTHERBOXSIZE * 2, OTHERBOXSIZE/1.5, RED);
      tft.drawCircle(tft.width()/2, OTHERBOXSIZE * 2, (OTHERBOXSIZE/1.5) + 1, RED);
      tft.drawCircle(tft.width()/2, OTHERBOXSIZE * 2, (OTHERBOXSIZE/1.5) + 2, RED);
      tft.drawCircle(tft.width()/2, OTHERBOXSIZE * 2, (OTHERBOXSIZE/1.5) + 3, RED);
    }

    void Circle_3(){
      tft.drawCircle((BOXSIZE*3)-(BOXSIZE/2), OTHERBOXSIZE * 2, OTHERBOXSIZE/1.5, RED);
      tft.drawCircle((BOXSIZE*3)-(BOXSIZE/2), OTHERBOXSIZE * 2, (OTHERBOXSIZE/1.5) + 1, RED);
      tft.drawCircle((BOXSIZE*3)-(BOXSIZE/2), OTHERBOXSIZE * 2, (OTHERBOXSIZE/1.5) + 2, RED);
      tft.drawCircle((BOXSIZE*3)-(BOXSIZE/2), OTHERBOXSIZE * 2, (OTHERBOXSIZE/1.5) + 3, RED);
    }

    void Circle_4(){
      tft.drawCircle(BOXSIZE/2, OTHERBOXSIZE*4, OTHERBOXSIZE/1.5, RED);
      tft.drawCircle(BOXSIZE/2, OTHERBOXSIZE*4, (OTHERBOXSIZE/1.5) + 1, RED);
      tft.drawCircle(BOXSIZE/2, OTHERBOXSIZE*4, (OTHERBOXSIZE/1.5) + 2, RED);
      tft.drawCircle(BOXSIZE/2, OTHERBOXSIZE*4, (OTHERBOXSIZE/1.5) + 3, RED);
    }

    void Circle_5(){
      tft.drawCircle(tft.width()/2, OTHERBOXSIZE*4, OTHERBOXSIZE/1.5, RED);
      tft.drawCircle(tft.width()/2, OTHERBOXSIZE*4, (OTHERBOXSIZE/1.5) + 1, RED);
      tft.drawCircle(tft.width()/2, OTHERBOXSIZE*4, (OTHERBOXSIZE/1.5) + 2, RED);
      tft.drawCircle(tft.width()/2, OTHERBOXSIZE*4, (OTHERBOXSIZE/1.5) + 3, RED);
    }

    void Circle_6(){
      tft.drawCircle((BOXSIZE*3)-(BOXSIZE/2), OTHERBOXSIZE*4, OTHERBOXSIZE/1.5, RED);
      tft.drawCircle((BOXSIZE*3)-(BOXSIZE/2), OTHERBOXSIZE*4, (OTHERBOXSIZE/1.5) + 1, RED);
      tft.drawCircle((BOXSIZE*3)-(BOXSIZE/2), OTHERBOXSIZE*4, (OTHERBOXSIZE/1.5) + 2, RED);
      tft.drawCircle((BOXSIZE*3)-(BOXSIZE/2), OTHERBOXSIZE*4, (OTHERBOXSIZE/1.5) + 3, RED);
    }

    void Circle_7(){
      tft.drawCircle(BOXSIZE/2, OTHERBOXSIZE*6, OTHERBOXSIZE/1.5, RED);
      tft.drawCircle(BOXSIZE/2, OTHERBOXSIZE*6, (OTHERBOXSIZE/1.5) + 1, RED);
      tft.drawCircle(BOXSIZE/2, OTHERBOXSIZE*6, (OTHERBOXSIZE/1.5) + 2, RED);
      tft.drawCircle(BOXSIZE/2, OTHERBOXSIZE*6, (OTHERBOXSIZE/1.5) + 3, RED);
    }

    void Circle_8(){
      tft.drawCircle(tft.width()/2, OTHERBOXSIZE*6, OTHERBOXSIZE/1.5, RED);
      tft.drawCircle(tft.width()/2, OTHERBOXSIZE*6, (OTHERBOXSIZE/1.5) + 1, RED);
      tft.drawCircle(tft.width()/2, OTHERBOXSIZE*6, (OTHERBOXSIZE/1.5) + 2, RED);
      tft.drawCircle(tft.width()/2, OTHERBOXSIZE*6, (OTHERBOXSIZE/1.5) + 3, RED);
    }

    void Circle_9(){
      tft.drawCircle((BOXSIZE*3)-(BOXSIZE/2), OTHERBOXSIZE*6, OTHERBOXSIZE/1.5, RED);
      tft.drawCircle((BOXSIZE*3)-(BOXSIZE/2), OTHERBOXSIZE*6, (OTHERBOXSIZE/1.5) + 1, RED);
      tft.drawCircle((BOXSIZE*3)-(BOXSIZE/2), OTHERBOXSIZE*6, (OTHERBOXSIZE/1.5) + 2, RED);
      tft.drawCircle((BOXSIZE*3)-(BOXSIZE/2), OTHERBOXSIZE*6, (OTHERBOXSIZE/1.5) + 3, RED);
    }


}; ttcGUI tictacGUI;  
#endif