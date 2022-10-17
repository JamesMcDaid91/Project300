#include <MCUFRIEND_kbv.h>

#include <TouchScreen.h>  

class ttc{
  private:  
const int XP=6,XM=A2,YP=A1,YM=7; //320x480 ID=0x9486
const int TS_LEFT=927,TS_RT=115,TS_TOP=954,TS_BOT=114;

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
TSPoint tp;

//MCUFRIEND_kbv tft;    

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


  public:

void test(){
  Serial.print("fromTicTacToe_Method");
  }
  
void mainGameSetup(MCUFRIEND_kbv tft){
    tft.setTextColor(RED);
    tft.setTextSize(4);
    tft.print("WELCOME TO   TIC.TAC.TOE");
    tft.setCursor(0, 120);   
    tft.print("PRESS ANYWHERE TO CONTINUE");
    while (1) {
        tp = ts.getPoint();
        pinMode(XM, OUTPUT);
        pinMode(YP, OUTPUT);
        if (tp.z < MINPRESSURE || tp.z > MAXPRESSURE) continue;
        if (tp.x > 0 && tp.x < TS_LEFT  && tp.y > 0 && tp.y < TS_TOP) break; // GOES INTO LOOP
    }
    BOXSIZE = (tft.width()+1)/ 3;
    OTHERBOXSIZE = tft.width() / 5.33;
    tft.fillScreen(WHITE);

    tft.fillRect(0, (OTHERBOXSIZE * 3)-3, tft.height(), 5, BLACK); //left line
    tft.fillRect(0, (OTHERBOXSIZE * 5)-3, tft.height(), 5, BLACK); //right line
    tft.fillRect(BOXSIZE-2, OTHERBOXSIZE, 5, OTHERBOXSIZE*6, BLACK); //middle top  
    tft.fillRect((BOXSIZE * 2)-2, OTHERBOXSIZE, 5, OTHERBOXSIZE*6, BLACK); //middle bottom
    delay(1000);
}

void mainGameLoop(MCUFRIEND_kbv tft){
  //mainGameSetup();
   while(BOXSIZE==NULL){
     mainGameSetup(tft);   
   }
  uint16_t xpos, ypos;  //screen coordinates
    tp = ts.getPoint();   //tp.x, tp.y are ADC values

    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);

    if (tp.z > MINPRESSURE && tp.z < MAXPRESSURE) {
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

        // //BREAKOUT CODE
        // if (ypos < OTHERBOXSIZE || ypos > (OTHERBOXSIZE * 5 + BOXSIZE)){
        //   break;
        // }


        //split into 3 ypos, top, middle and bottom. if you are within the boxsize height portion of each designated one. 
        //first 3 positions, if you are within the boxsize height portion of the top 3 boxes.
        if (ypos > OTHERBOXSIZE && ypos < (OTHERBOXSIZE + BOXSIZE)) {               
            oldPOS = currentPOS;
            //width of all boxes are BOXSIZE, this finds out which based on the xpos
            if (xpos < BOXSIZE) { 
                currentPOS = 1;
                Cross_1();
                //Circle_1();                
            } else if (xpos < BOXSIZE * 2) { 
                currentPOS = 2;
                Cross_2();
                //Circle_2();
            } else if (xpos < BOXSIZE * 3) {
                currentPOS = 3;
                Cross_3();
                //Circle_3();
            }
       }

       if (ypos > OTHERBOXSIZE * 3 && ypos < (OTHERBOXSIZE * 3 + BOXSIZE)){
         oldPOS = currentPOS;

            if (xpos < BOXSIZE) {
                currentPOS = 4;
                Cross_4();
                //Circle_4();                
            } else if (xpos < BOXSIZE * 2) {
                currentPOS = 5;
                Cross_5();
                //Circle_5();
            } else if (xpos < BOXSIZE * 3) {
                currentPOS = 6;
                Cross_6();          
                //Circle_6();
            }
       }

       if (ypos > OTHERBOXSIZE * 5 && ypos < (OTHERBOXSIZE * 5 + BOXSIZE)){
          oldPOS = currentPOS;

            if (xpos < BOXSIZE) {
                currentPOS = 7;
                Cross_7();
                //Circle_7();                
            } else if (xpos < BOXSIZE * 2) {
                currentPOS = 8;
                Cross_8();
                //Circle_8();
            } else if (xpos < BOXSIZE * 3) {
                currentPOS = 9;
                Cross_9();
                //Circle_9();
            }
       }
    }    

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
  tft.drawCircle(BOXSIZE/2, BOXSIZE, OTHERBOXSIZE/1.5, RED);
  tft.drawCircle(BOXSIZE/2, BOXSIZE, (OTHERBOXSIZE/1.5) + 1, RED);
  tft.drawCircle(BOXSIZE/2, BOXSIZE, (OTHERBOXSIZE/1.5) + 2, RED);
  tft.drawCircle(BOXSIZE/2, BOXSIZE, (OTHERBOXSIZE/1.5) + 3, RED);
}

void Circle_2(){
  tft.drawCircle(tft.width()/2, BOXSIZE, OTHERBOXSIZE/1.5, RED);
  tft.drawCircle(tft.width()/2, BOXSIZE, (OTHERBOXSIZE/1.5) + 1, RED);
  tft.drawCircle(tft.width()/2, BOXSIZE, (OTHERBOXSIZE/1.5) + 2, RED);
  tft.drawCircle(tft.width()/2, BOXSIZE, (OTHERBOXSIZE/1.5) + 3, RED);
}

void Circle_3(){
  tft.drawCircle((BOXSIZE*3)-(BOXSIZE/2), BOXSIZE, OTHERBOXSIZE/1.5, RED);
  tft.drawCircle((BOXSIZE*3)-(BOXSIZE/2), BOXSIZE, (OTHERBOXSIZE/1.5) + 1, RED);
  tft.drawCircle((BOXSIZE*3)-(BOXSIZE/2), BOXSIZE, (OTHERBOXSIZE/1.5) + 2, RED);
  tft.drawCircle((BOXSIZE*3)-(BOXSIZE/2), BOXSIZE, (OTHERBOXSIZE/1.5) + 3, RED);
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
  
};


ttc TicTacToe;  
