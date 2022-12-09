#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;     
#include <TouchScreen.h>
#include <TrueRandom.h>
#include <HardwareSerial.h>
#include "ttcMasterGame.h"
#include "ttcGUI.h"
#include "MP3_Player.h"
#include "FiniteStateMachine.h"
#include <stdio.h>
#include "Binary_Clock.h"




//declaring various states to be in such as main menu, tic tac toe etc.

//misc
State mainMenuGUI(mainGUI);
State voidState(voidMethod);
State voidTrueState(voidMethod);
FSM GUI = FSM(mainMenuGUI);

//tic tac toe
State tictacIntroScreen(ttFrontPage); 
State tictacGridScreen(ttGridPage);
FSM TTC = FSM(voidState);

//music
State musicGUI(musicDashboard);
FSM MUSIC = FSM(voidState);

//clock
State clockLoop(clockVoidLoop);
State clockGUI(clockDashboard);
FSM CLOCK = FSM(voidState);

//settings
State settingsGUI(settingsDashboard);





char *name = "TTTCMR";  
const int XP=6,XM=A2,YP=A1,YM=7; //320x480 ID=0x9486
const int TS_LEFT=929,TS_RT=180,TS_TOP=963,TS_BOT=186;
int counter = 1;
bool firstRunTicTac = false;
bool ticTacFinished = false;

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 150);
TSPoint tp;


#define MINPRESSURE 200
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
  Serial.println("right before mp3 setup");

  Serial.println("from setup method");
  mp3Player.mp3Setup();

  ///////////////////////////////////////////////////////////////////////////////////////////////
  //                             SETS UP SERIAL, SCREEN AND CLOCK                              //
  ///////////////////////////////////////////////////////////////////////////////////////////////
  
  Serial.begin(9600);
  Serial.flush();
  Serial.println("Beginning Setup...");
  
  tft.reset();
  ID = tft.readID();
  tft.begin(ID);
  Serial.println("Setting up TFT Screen...   ");

  tft.setRotation(Orientation);
  Serial.println("Orientation Set...");

  bClock.bClockSetup();      
       
  Serial.println("Setting up Binary Clock...   ");

  BOXSIZE = (tft.width()+1)/ 3;
  OTHERBOXSIZE = tft.width() / 5.33;
  Serial.println("Declaring boxed regions...  ");

  mainGUI();
  Serial.println("Main GUI displayed... ");
  Serial.println("Setup Complete... ");
  
  //Serial.println("Playing Song");
}


void loop(){
  CLOCK.update();
  MUSIC.update();
  
  ///////////////////////////////////////////////////////////////////////////////////////////////
  //                                 MAP DETECTED TS TOUCH POINTS                              //
  ///////////////////////////////////////////////////////////////////////////////////////////////

  uint16_t xpos, ypos;  //screen coordinates
  findXposYpos(xpos, ypos);
  
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);

  ///////////////////////////////////////////////////////////////////////////////////////////////
  //                       DETECT IF MAIN MENU BUTTON AREA TOUCHED                             //
  ///////////////////////////////////////////////////////////////////////////////////////////////

  if (tp.z < MINPRESSURE || tp.z > MAXPRESSURE) return; //checks if has been pressed
  if (tp.x > 0 && tp.x > TS_LEFT/2  && tp.y > 0 && tp.y > TS_TOP/2){ //TOP RIGHT || TIC TAC TOE
    if (GUI.isInState(mainMenuGUI)){
      GUI.transitionTo(tictacIntroScreen);
    }
  }

  else if (tp.x > 0 && tp.x < TS_LEFT/2  && tp.y > 0 && tp.y < TS_TOP/2){ //BOTTOM LEFT || MUSIC
    if (GUI.isInState(mainMenuGUI)){
      GUI.transitionTo(musicGUI);
      MUSIC.transitionTo(voidTrueState);
      MUSIC.update();
      counter = 1;
    }

    else if (GUI.isInState(musicGUI)){ // WHEN IN PREVIOUS/NEXT IN MUSIC CONTROLS

      if (counter <= 0){
        counter = 1;
      }
      else if (counter == 1){
        musicClearTextArea();
        tft.print("Song : ");
        tft.print(counter);        
        mp3Player.playSelectedSong(counter);
      }
      else if (counter <= mp3Player.fileCount()){
        counter--;
        musicClearTextArea();
        tft.print("Song : ");
        tft.print(counter);
        mp3Player.playSelectedSong(counter);
      }
    }
  }

  else if (tp.x > 0 && tp.x > TS_LEFT/2  && tp.y > 0 && tp.y < TS_TOP/2){ //TOP LEFT || CLOCK
    if (GUI.isInState(mainMenuGUI)){
      GUI.transitionTo(clockGUI);
    }
  }
  
  else if(tp.x > 0 && tp.x < TS_LEFT/2  && tp.y > 0 && tp.y > TS_TOP/2){ //BOTTOM RIGHT || SETTINGS
    if (GUI.isInState(mainMenuGUI)){
      GUI.transitionTo(settingsGUI);
    }

    if (GUI.isInState(musicGUI)){ // WHEN IN PREVIOUS/NEXT IN MUSIC CONTROLS
      if (tp.x < TS_LEFT && tp.x > (TS_LEFT - BOXSIZE)){
        GUI.transitionTo(mainMenuGUI);
      }

      if (counter == 0){
        counter = 1;
      }
      
      else if (counter == mp3Player.fileCount()){
        counter = 1;
        musicClearTextArea();
        tft.print("Song : ");
        tft.print(counter);
        mp3Player.playSelectedSong(counter);
      }

      else if (counter > 1){
        counter++;
        musicClearTextArea();
        tft.print("Song : ");
        tft.print(counter);
        mp3Player.playSelectedSong(counter);
      }

      else if (counter == 1){
        musicClearTextArea();
        counter++;
        tft.print("Song : ");
        tft.print(counter);
        mp3Player.playSelectedSong(counter);
      }
      delay(500);
    }
  } 

  ///////////////////////////////////////////////////////////////////////////////////////////////
  //                            DETECT IF NEEDED TO EXIT ANY GUI                               //
  ///////////////////////////////////////////////////////////////////////////////////////////////


  if(tp.x > 0 && tp.x < TS_LEFT && tp.y > 0 && tp.y < TS_TOP && (GUI.isInState(clockGUI) || GUI.isInState(settingsGUI) || ticTacFinished)){ //SETTINGS AND CLOCK EXIT
    GUI.transitionTo(mainMenuGUI);
  }
  
  else if (tp.x < TS_LEFT && tp.x > (TS_LEFT - BOXSIZE) && GUI.isInState(musicGUI)){
    GUI.transitionTo(mainMenuGUI);
    MUSIC.transitionTo(voidState);
    MUSIC.update();
  }
  
  if (GUI.isInState(mainMenuGUI) || GUI.isInState(clockGUI) || GUI.isInState(settingsGUI) || (GUI.isInState(musicGUI) && MUSIC.isInState(voidState)) || ticTacFinished){
    if (ticTacFinished) ticTacFinished = false;
    ticTacFinished = false;
    GUI.update();   //update GUI to selected state if it gets this far.
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////
  //                               TIC TAC TOE MAIN RUNNING GAME                               //
  //                       HAS TO BE IN HERE DUE TO HOW THE STATES WORK                        //
  ///////////////////////////////////////////////////////////////////////////////////////////////

  if (tp.x > 0 && tp.x < TS_LEFT && tp.y > 0 && tp.y < TS_TOP && (GUI.isInState(tictacIntroScreen) || GUI.isInState(tictacGridScreen))){
    //START OF TIC TAC TOE GAME
    if (GUI.isInState(tictacIntroScreen)){ 
      GUI.transitionTo(tictacGridScreen);
      TTC.transitionTo(voidTrueState);
      TTC.update();
      GUI.update();
      ticTacFinished = false;
      firstRunTicTac = true;
    }


    //LOOP FOR MAIN GAME
    if (GUI.isInState(tictacGridScreen)){
      int pos = 0;
      if (firstRunTicTac == true){
        pos = tictacGUI.getTouchedPosition(tft, firstRunTicTac);
        firstRunTicTac = false;
        return;
      }
      else {
        pos = tictacGUI.getTouchedPosition(tft, firstRunTicTac);
      }
      

      //ttcMasterGame(gridRow, gridCol);
      int gridRow, gridCol;
      switch(pos){
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

      //return int value from player turn, have 0 = continue, 1 = ai go etc. if (end screen num) endscreen(), go back to main menu state.
      int result = ttcMasterGame.PlayerTurn(gridRow, gridCol);
      Serial.println("RESULT FROM GAME");
      Serial.print(result);
      switch(result){
        case 0: 
          tictacGUI.EndScreen(0); 
          ticTacFinished = true;
          break;
        case 1:
          tictacGUI.EndScreen(1);
          ticTacFinished = true;
          break;
        case 2:
          tictacGUI.EndScreen(2);
          ticTacFinished = true;   
          break;
        case 3:
          break;
      }
    }
    CLOCK.update();
    delay(500);
  }

  CLOCK.update(); //update clock to current time.
  
}

void mainGUI(){
  ///////////////////////////////////////////////////////////////////////////////////////////////
  //                                 DRAW GUI ELEMENTS                                         //
  ///////////////////////////////////////////////////////////////////////////////////////////////

  //box 1, tic tac toe
  tft.setRotation(0);
  tft.fillScreen(BLACK);
  tft.fillRect(OTHERBOXSIZE/2, OTHERBOXSIZE/2, OTHERBOXSIZE*2, 3*OTHERBOXSIZE, MAGENTA);
  tft.setCursor(BOXSIZE*2.75, OTHERBOXSIZE*1.4);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.setRotation(3);
  tft.print("TIC TAC TOE");
  tft.setRotation(0);

  //box 2, tbd (settings etc)
  tft.fillRect(OTHERBOXSIZE*3, OTHERBOXSIZE/2, OTHERBOXSIZE*2, 3*OTHERBOXSIZE, MAGENTA);
  tft.setCursor(BOXSIZE*2.7, OTHERBOXSIZE*3.8);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.setRotation(3);
  tft.print("SETTINGS");
  tft.setRotation(0);

  //box 3. //clock
  tft.fillRect(OTHERBOXSIZE/2, OTHERBOXSIZE*4.5, OTHERBOXSIZE*2, 3*OTHERBOXSIZE, MAGENTA);
  tft.setCursor(OTHERBOXSIZE*1.2, OTHERBOXSIZE*1.3);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.setRotation(3);
  tft.print("CLOCK");
  tft.setRotation(0);

  //box 4 //music
  tft.fillRect(OTHERBOXSIZE*3, OTHERBOXSIZE*4.5, OTHERBOXSIZE*2, 3*OTHERBOXSIZE, MAGENTA);
  tft.setCursor(OTHERBOXSIZE*1.2, OTHERBOXSIZE*3.8);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.setRotation(3);
  tft.print("MUSIC");
  tft.setRotation(0);  
}

void musicDashboard(){
  ///////////////////////////////////////////////////////////////////////////////////////////////
  //                METHOD IS ONLY FOR DRAWING GUI ELEMENTS AND STATE FUNCTIONS                //
  ///////////////////////////////////////////////////////////////////////////////////////////////

  tft.fillScreen(BLACK);
  tft.setRotation(0);
  
  //previous track button for music
  tft.fillRect(OTHERBOXSIZE*3, OTHERBOXSIZE*4.5, OTHERBOXSIZE*2, 3*OTHERBOXSIZE, MAGENTA);
  tft.setCursor(OTHERBOXSIZE, OTHERBOXSIZE*3.8);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.setRotation(3);
  tft.print("PREVIOUS");
  tft.setRotation(0);  

  //next track button for music
  tft.fillRect(OTHERBOXSIZE*3, OTHERBOXSIZE/2, OTHERBOXSIZE*2, 3*OTHERBOXSIZE, MAGENTA);
  tft.setCursor(BOXSIZE*3, OTHERBOXSIZE*3.8);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.setRotation(3);
  tft.print("NEXT");

  //exit at top of screen
  tft.fillRect(0, 0, tft.width(), OTHERBOXSIZE, MAGENTA);
  tft.setCursor(OTHERBOXSIZE/2, OTHERBOXSIZE/2);
  tft.print("PRESS HERE TO EXIT");

  ///////////////////////////////////////////////////////////////////////////////////////////////
  //             DETECT IF PRESSED, GET COUNT OF SONGS AND ITERATE AS REQUIRED                 //
  //                           AS OF 06/12/22 EVERYTHING WORKS HERE                            //
  //                                                                                           //
  //            ALL DETECTION IS DONE IN THE METHODS FOR MAIN MENU DETECTION TOO               //                                                                                         //
  //                                                                                           //
  //                         EXIT SEQUENCE IS DONE IN MAIN MENU DETECTION                      //
  ///////////////////////////////////////////////////////////////////////////////////////////////
  
}

void clockDashboard(){
  //FILLS SCREEN TO RESET GUI, LETS USER KNOW CLOCK IS STARTED AND EXITS UPON TOUCH
  tft.setRotation(3);
  tft.setTextSize(4);
  tft.setCursor(0, BOXSIZE);
  tft.setTextColor(BLACK);
  tft.fillScreen(GREEN);
  tft.println("Started clock app!");
  tft.println("Press anywhere to return to main menu");
  tft.setRotation(0);
  tft.setTextColor(WHITE);

  CLOCK.transitionTo(clockLoop); // ONLY IMPORTANT THING HERE, STARTS THE CLOCK
}

void settingsDashboard(){
  //CURRENTLY TBD BUT PROBABLY SOMETHING ALONG THE LINES OF ALL SETTINGS, IE. CLOCK, VOLUME ETC.
  tft.setRotation(3);
  tft.setTextSize(4);
  tft.setCursor(0, BOXSIZE);
  tft.setTextColor(BLACK);
  tft.fillScreen(BLUE);
  tft.println("Started settings!");
  tft.println("Press anywhere to continue");
  tft.setRotation(0);
  tft.setTextColor(WHITE);

  // volume up/down method mp3Player.changeVolume(int (1/0)) ...WANT TO IMPLEMENT BUT NOT PRIORITY...
}

void findXposYpos(uint16_t xpos, uint16_t ypos){ //calibrates xpos and ypos every time its called
  tp = ts.getPoint();   //tp.x, tp.y are ADC values
  
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
}

void musicClearTextArea(){
  //AREA WHERE SONG NO. IS DISPLAYED, NEEDS TO BE WIPED TO ALLOW FOR NEW TEXT
  tft.fillRect(0, OTHERBOXSIZE,tft.width(), tft.height()/3, BLACK);
  tft.setCursor(BOXSIZE, BOXSIZE);
  tft.setTextSize(4);
}

void tictacEndScreen(int winner){
  tictacGUI.EndScreen(winner); //display end screen
}

void clockVoidLoop(){bClock.bClockLoop();} //CLOCK VOID LOOP, STATES DIDN'T LIKE IT BEING A METHOD FROM A HEADER

void voidMethod(){} //VOID METHOD FOR ANY TIME STATES NEED TO BE STAGNANT

void ttFrontPage(){tictacGUI.drawFrontPage(tft);} //FRONT PAGE FOR STATE

void ttGridPage(){tictacGUI.drawGrid(tft);} //GRID PAGE FOR STATE
