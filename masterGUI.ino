#include "bitmap_rgb.h"
#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;     
#include <TouchScreen.h>
#include <TrueRandom.h>
#include <HardwareSerial.h>
#include "ttcMasterGame.h"
#include "ttcNewMasterGame.h"
#include "ttcGUI.h"
#include "MP3_Player.h"
#include "FiniteStateMachine.h"
#include <stdio.h>
#include "Binary_Clock.h"
#include "bitmap_mono.h"





//declaring various states to be in such as main menu, tic tac toe etc.

//misc
State mainMenuGUI(mainGUI);
State voidState(voidMethod);
State voidTrueState(voidMethod);
FSM GUI = FSM(mainMenuGUI);

//tic tac toe
State tictacIntroScreen(ttFrontPage); 
State tictacGridScreen(ttGridPage);
State tictacPlayerChoice(ttcPlayerAmountChoice);
State tictacDifficultyChoice(ttcAiDifficultyChoice);
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

bool firstRunTicTac = false;
bool ticTacFinished = false;
bool songPaused = true;
bool songPlaying = false;
bool adjustingVolume = false;
bool timezoneSaved = false;

int currentSetting = 1;
int musicPlayerVolume = 12;
int ttcPlayerChoice = 1;
int totalSongFileCount = 0;
int timezone = 1;
int primaryColourNum = 1;
int secondaryColourNum = 3;
int counter = 1;





TouchScreen ts = TouchScreen(XP, YP, XM, YM, 150);
TSPoint tp;


#define MINPRESSURE 200
#define MAXPRESSURE 1000

int16_t BOXSIZE;
int16_t OTHERBOXSIZE;
uint16_t ID, oldPOS, currentPOS;
uint8_t Orientation = 0;    //PORTRAIT

#define BLACK   0x0000 // 1
#define BLUE    0x001F // 2
#define RED     0xF800 // 3
#define GREEN   0x07E0 // 4
#define DARKGREEN 0x0E69 // 5
#define CYAN    0x07FF  // 6
#define MAGENTA 0xF81F  // 7
#define YELLOW  0xFFE0  // 8
#define WHITE   0xFFFF //9
#define ORANGE  0xFCA0 //10

uint16_t primaryColour = BLACK;
uint16_t secondaryColour = RED;


void setup(void){  
  Serial.println("right before mp3 setup");

  Serial.println("from setup method");  
  mp3Player.mp3Setup(12);
  

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

  CLOCK.transitionTo(clockLoop); // STARTS THE CLOCK
  bClock.bClockSetup();      

  Serial.println("Setting up Binary Clock...   ");

  BOXSIZE = (tft.width()+1)/ 3;
  OTHERBOXSIZE = tft.width() / 5.33;
  Serial.println("Declaring boxed regions...  ");
  
  ///////////////////
  // PUT THIS BACK IN AT THE END

  startupSplash();
  ///////////////////

  clockVoidLoop(); 
  mainGUI();
  
  Serial.println("Main GUI displayed... ");
  Serial.println("Setup Complete... ");

  
  //Serial.println("Playing Song");
}


void loop(){
  //


  // while(1){
  //   tictacGUI.pickPlayerAmount(tft);
  //   delay(1000000000);
  // }

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
    if (GUI.isInState(tictacDifficultyChoice)){ // tic tac difficulty choice
      ttcPlayerChoice = 2; // medium
    }
  }

  else if (tp.x > 0 && tp.x < TS_LEFT/2  && tp.y > 0 && tp.y < TS_TOP/2){ //BOTTOM LEFT || MUSIC
    if (GUI.isInState(mainMenuGUI)){
      GUI.transitionTo(musicGUI);
      MUSIC.transitionTo(voidTrueState);
      MUSIC.update();
      // = 1;
    }

    else if (GUI.isInState(musicGUI)){ // PREVIOUS IN MUSIC CONTROLS
      if (tp.x > 0 && tp.x < TS_LEFT/2  && tp.y > 0 && tp.y < TS_TOP/3){ // LEFT - PREVIOUS - FIRST THIRD
        musicLogic(1);
        mp3Player.playSongNo(counter);
        //mp3Player.playSelectedSong(1);
        songPlaying = true;
        songPaused = false;
      }
      else if (tp.x > 0 && tp.x < TS_LEFT/2  && tp.y > TS_TOP/3 && tp.y < TS_TOP/2) { // PAUSE/PLAY
        if (songPlaying == false){
          mp3Player.playSongNo(counter);
          //mp3Player.playSelectedSong(2);
          songPlaying = true;
        }
        else if (songPaused == false){
          mp3Player.pausePlay(1);
          songPaused = true;
          musicPausePlayClear();
        } else if (songPaused = true){
          mp3Player.pausePlay(2);
          songPaused = false;
          musicPausePlayClear();
        }
        delay(500);
      }
      delay(500);
    }

    else if (GUI.isInState(clockGUI)){ // CLOCK
      if (timezone == 1){
          timezone = 1;
          CLOCK.update();
        }
        else{
          timezone--;
          CLOCK.update();
        }
        whichFlag();  
    }

    else if (GUI.isInState(settingsGUI)){ // SETTINGS
      if (tp.x > 0 && tp.x < TS_LEFT/2  && tp.y > 0 && tp.y < TS_TOP/3){ // LEFT OPTION OF CURRENT SETTING
        if (currentSetting == 1){
          settingsColourOptionsPrimary(1);
          settingsOptions(currentSetting);
        } else if (currentSetting == 2){
          settingsColourOptionsSecondary(1);
          settingsOptions(currentSetting);
        } else if (currentSetting == 3){
          
          adjustingVolume = true;
          volumeChangeOption(2);
          volumeDisplayLogic();
        }
      }
      else if (tp.x > 0 && tp.x < TS_LEFT/2  && tp.y > TS_TOP/3 && tp.y < TS_TOP/2) { // RIGHT OPTION OF CURRENT SETTING
        if (currentSetting == 1){
          settingsColourOptionsPrimary(2);
          settingsOptions(currentSetting);
          adjustingVolume = false;
        } else if (currentSetting == 2){
          settingsColourOptionsSecondary(2);
          settingsOptions(currentSetting);
          adjustingVolume = false;
        } else if (currentSetting == 3){
          
          adjustingVolume = true;
          volumeChangeOption(1);
          volumeDisplayLogic();          
        }
      }
      delay(200);
    }

    if (GUI.isInState(tictacDifficultyChoice)){ // tic tac difficulty choice
      ttcPlayerChoice = 3; // hard
    }
  }

  else if (tp.x > 0 && tp.x > TS_LEFT/2  && tp.y > 0 && tp.y < TS_TOP/2){ //TOP LEFT || CLOCK
    if (GUI.isInState(mainMenuGUI)){
      GUI.transitionTo(clockGUI);
      timezoneSaved = false;
    }
    if (GUI.isInState(tictacDifficultyChoice)){ // tic tac difficulty choice
      ttcPlayerChoice = 1; // easy
    }
  }
  
  else if(tp.x > 0 && tp.x < TS_LEFT/2  && tp.y > 0 && tp.y > TS_TOP/2){ //BOTTOM RIGHT || SETTINGS
    if (GUI.isInState(mainMenuGUI)){
      GUI.transitionTo(settingsGUI);
    }
    
    if (GUI.isInState(musicGUI)){ // NEXT IN MUSIC CONTROLS
      if (tp.x > 0 && tp.x < TS_LEFT/2  && tp.y > 0 && tp.y > TS_TOP - TS_TOP/3){
        musicLogic(2);
        mp3Player.playSongNo(counter);
        songPlaying = true;
        songPaused = false;
        musicPausePlayClear();
      }
      else if (tp.x > 0 && tp.x < TS_LEFT/2  && tp.y > TS_TOP/2 && tp.y < TS_TOP - TS_TOP/3){
        if (songPlaying == false){
          mp3Player.playSongNo(counter);
          songPlaying = true;
          songPaused = false;
          musicPausePlayClear();
        }
        else if (songPaused == false){
          mp3Player.pausePlay(1);
          songPaused = true;
          musicPausePlayClear();
        } else if (songPaused = true){
          mp3Player.pausePlay(2);
          songPaused = false;
          musicPausePlayClear();
        }
        delay(500);
      }
      delay(500);
    }

    if (GUI.isInState(clockGUI)){ // CLOCK
        if (timezone == 4){
          timezone = 1;
          CLOCK.update();
        }
        else{
          timezone++;
          CLOCK.update();
        }
        whichFlag();
    }

    if (GUI.isInState(settingsGUI)){ // SETTINGS
      if (tp.x > 0 && tp.x < TS_LEFT/2  && tp.y > 0 && tp.y > TS_TOP - TS_TOP/3){ // NEXT SETTING
        if (currentSetting < 3){
          currentSetting++;
        } else if (currentSetting >= 3){
          currentSetting = 1;
        }
      }
      else if (tp.x > 0 && tp.x < TS_LEFT/2  && tp.y > TS_TOP/2 && tp.y < TS_TOP - TS_TOP/3){ // RIGHT OPTION OF CURRENT SETTING
        if (currentSetting == 1){
          adjustingVolume = false;
          settingsColourOptionsPrimary(2);
          settingsOptions(currentSetting);
        } else if (currentSetting == 2){
          adjustingVolume = false;
          settingsColourOptionsSecondary(2);
          settingsOptions(currentSetting);
        } else if (currentSetting == 3){
          
          adjustingVolume = true;
          volumeChangeOption(1);
          volumeDisplayLogic();
        }
      }
      delay(200);
    }

    if (tp.x < TS_LEFT && tp.x > (TS_LEFT - BOXSIZE)){
      GUI.transitionTo(mainMenuGUI);
    }

    if (GUI.isInState(tictacDifficultyChoice)){ // tic tac difficulty choice
      ttcPlayerChoice = 4; // random
    }
  } 

  ///////////////////////////////////////////////////////////////////////////////////////////////
  //                            DETECT IF NEEDED TO EXIT ANY GUI                               //
  ///////////////////////////////////////////////////////////////////////////////////////////////


  if(tp.x > 0 && tp.x < TS_LEFT && tp.y > 0 && tp.y < TS_TOP && ticTacFinished){ //SETTINGS AND CLOCK EXIT
    GUI.transitionTo(mainMenuGUI);
  }
  
  else if (tp.x < TS_LEFT && tp.x > (TS_LEFT - BOXSIZE) && (GUI.isInState(musicGUI) || (GUI.isInState(settingsGUI) && adjustingVolume == true) || GUI.isInState(settingsGUI) || GUI.isInState(clockGUI))){
    GUI.transitionTo(mainMenuGUI);
    MUSIC.transitionTo(voidState);
    adjustingVolume = false;
    timezoneSaved = true;
    CLOCK.update();
    MUSIC.update();
  }
  
  if (GUI.isInState(mainMenuGUI) || (GUI.isInState(settingsGUI) && adjustingVolume == false) || (GUI.isInState(musicGUI) && MUSIC.isInState(voidState)) || (GUI.isInState(clockGUI) && timezoneSaved) || ticTacFinished){
    if (ticTacFinished) ticTacFinished = false;
    ticTacFinished = false;
    adjustingVolume = false;
    //if (timezoneSaved) GUI.transitionTo(mainMenuGUI);
    GUI.update();   //update GUI to selected state if it gets this far.
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////
  //                               TIC TAC TOE MAIN RUNNING GAME                               //
  //                       HAS TO BE IN HERE DUE TO HOW THE STATES WORK                        //
  ///////////////////////////////////////////////////////////////////////////////////////////////

  if (tp.x > 0 && tp.x < TS_LEFT && tp.y > 0 && tp.y < TS_TOP && (GUI.isInState(tictacIntroScreen) || GUI.isInState(tictacGridScreen) || GUI.isInState(tictacPlayerChoice) || GUI.isInState(tictacDifficultyChoice))){
    //START OF TIC TAC TOE GAME
    if (GUI.isInState(tictacIntroScreen)){ 
      GUI.transitionTo(tictacPlayerChoice);
      GUI.update();
    }

    else if (GUI.isInState(tictacPlayerChoice)){
      // 0 == 2 Players
      // > 0 == 1 Player with designated AI Difficulty
      if (tp.x > 0 && tp.x > TS_LEFT/2 && tp.y < TS_TOP){ // TOP
        ttcPlayerChoice = 1; // defaults to easy difficulty, will go through to ask which difficulty the player wants.
        GUI.transitionTo(tictacDifficultyChoice);
        GUI.update();
      }
      if (tp.x > 0 && tp.x < TS_LEFT/2 && tp.y < TS_TOP){ // BOTTOM
        ttcPlayerChoice = 0; // signifies to the backend that it is 2 player.
        GUI.transitionTo(tictacGridScreen);
        TTC.transitionTo(voidTrueState);
        TTC.update();
        GUI.update();
        ticTacFinished = false;
        firstRunTicTac = true;
        ttcNewMasterGame.TicTacToeSetup(ttcPlayerChoice);
      }
    }

    else if (GUI.isInState(tictacDifficultyChoice)){
      //detects which corner the screen is pressed earlier in the program, here we will transition the state and the difficulty to be sent off to the backend logic.
      GUI.transitionTo(tictacGridScreen);
      TTC.transitionTo(voidTrueState);
      TTC.update();
      GUI.update();
      ticTacFinished = false;
      firstRunTicTac = true;  
      ttcNewMasterGame.TicTacToeSetup(ttcPlayerChoice);    
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
      int result;

      
      

      // Serial.println("gamestate ");
      // Serial.println(ttcNewMasterGame.returnGameState(gridRow, gridCol));
      if (ttcNewMasterGame.returnGameState(gridCol, gridRow) == 0){
        Serial.println("turn ");
        Serial.println(ttcNewMasterGame.returnTurnCounter());
        Serial.println("gr = ");
        Serial.println(gridRow);
        Serial.println("gc = ");
        Serial.println(gridCol);
        if (ttcNewMasterGame.returnTurnCounter() % 2 == 0 && ttcNewMasterGame.returnSecondPlayer() == true){
          result = ttcNewMasterGame.Player2Turn(gridRow, gridCol);       
        }
        else{
          result = ttcNewMasterGame.PlayerTurn(gridRow, gridCol);
        }
        
        delay(200);
      }

      switch(result){
        case 4:
        break;
        case 0: 
          tictacGUI.EndScreen(0); 
          ticTacFinished = true;
          firstRunTicTac = true;
          if (!songPlaying){
            mp3Player.advertWithoutBackgroundMusic(2, counter);
          }else{
            mp3Player.playAdvertisement(2);
          }
          break;
        case 1:
          tictacGUI.EndScreen(1);
          ticTacFinished = true;
          firstRunTicTac = true;
          if (!songPlaying){
            mp3Player.advertWithoutBackgroundMusic(3, counter);
          }else{
            mp3Player.playAdvertisement(3);            
          }
          break;
        case 2:
          tictacGUI.EndScreen(2);
          ticTacFinished = true;   
          firstRunTicTac = true;
          if (!songPlaying){
            mp3Player.advertWithoutBackgroundMusic(5, counter);
          }else{
            mp3Player.playAdvertisement(5);
          }
          break;
        case 3:
          tictacGUI.EndScreen(3);
          ticTacFinished = true;  
          firstRunTicTac = true;
          if (!songPlaying){
            mp3Player.advertWithoutBackgroundMusic(3, counter);
          }else{
            mp3Player.playAdvertisement(3);
          }
          break;
        default:
          break;
      }
    }
    CLOCK.update();
  }

  CLOCK.update(); //update clock to current time.
  
}

void mainGUI(){
  ///////////////////////////////////////////////////////////////////////////////////////////////
  //                                 DRAW GUI ELEMENTS                                         //
  ///////////////////////////////////////////////////////////////////////////////////////////////

  
  tft.setRotation(0);
  tft.fillScreen(primaryColour);
  //CACTUS
  tft.setRotation(3);
  tft.drawBitmap(tft.width()-30,4, cactus_24x32, 24,32, GREEN);
  tft.setRotation(0);

  //box 1, tic tac toe
  tft.fillRect(OTHERBOXSIZE/2, OTHERBOXSIZE/2, OTHERBOXSIZE*2, 3*OTHERBOXSIZE, secondaryColour);
  tft.setRotation(3);
  tft.drawBitmap(OTHERBOXSIZE*5.2, OTHERBOXSIZE*.7, tictactoe_96x96, 96, 96, primaryColour);
  tft.setRotation(0);

  
  //box 2, tbd (settings etc)
  tft.fillRect(OTHERBOXSIZE*3, OTHERBOXSIZE/2, OTHERBOXSIZE*2, 3*OTHERBOXSIZE, secondaryColour);
  tft.setRotation(3);
  tft.drawBitmap(BOXSIZE*2.9, OTHERBOXSIZE*3.3, settings_96x96, 96, 96, primaryColour);
  tft.setRotation(0);

  //box 3. //clock
  tft.fillRect(OTHERBOXSIZE/2, OTHERBOXSIZE*4.5, OTHERBOXSIZE*2, 3*OTHERBOXSIZE, secondaryColour);
  tft.setRotation(3);
  tft.drawBitmap(OTHERBOXSIZE*1.2, OTHERBOXSIZE*.7, clock_96x96, 94, 90, primaryColour); // Bitmap Image of Clock
  tft.setRotation(0);

  //box 4 //music
  tft.fillRect(OTHERBOXSIZE*3, OTHERBOXSIZE*4.5, OTHERBOXSIZE*2, 3*OTHERBOXSIZE, secondaryColour);
  tft.setRotation(3);
  tft.drawBitmap(OTHERBOXSIZE*0.7, OTHERBOXSIZE*3.2, music_96x96, 96, 96, primaryColour);
  tft.drawBitmap(OTHERBOXSIZE*1.7, OTHERBOXSIZE*3.2, music_96x96, 96, 96, primaryColour);
  tft.setRotation(0);  
}

void ttcAiDifficultyChoice(){
  tft.fillScreen(primaryColour);

  //top right / medium
  tft.fillRect(OTHERBOXSIZE/2, OTHERBOXSIZE/2, OTHERBOXSIZE*2, 3*OTHERBOXSIZE, secondaryColour);
  //bottom right / random
  tft.fillRect(OTHERBOXSIZE*3, OTHERBOXSIZE/2, OTHERBOXSIZE*2, 3*OTHERBOXSIZE, secondaryColour);
  //top left / easy
  tft.fillRect(OTHERBOXSIZE/2, OTHERBOXSIZE*4.5, OTHERBOXSIZE*2, 3*OTHERBOXSIZE, secondaryColour);
  //bottom left / hard
  tft.fillRect(OTHERBOXSIZE*3, OTHERBOXSIZE*4.5, OTHERBOXSIZE*2, 3*OTHERBOXSIZE, secondaryColour);
  

  tft.setRotation(3);

  tft.drawBitmap(OTHERBOXSIZE*5.2, OTHERBOXSIZE, mediumDifficulty_96x64, 98, 64, primaryColour);
  tft.drawBitmap(OTHERBOXSIZE*5.2, OTHERBOXSIZE*3.5, randomDifficulty_96x64, 96, 64, primaryColour);
  tft.drawBitmap(OTHERBOXSIZE*1.2, OTHERBOXSIZE, easyDifficulty_96x64, 96, 64, primaryColour); 
  tft.drawBitmap(OTHERBOXSIZE*1.2, OTHERBOXSIZE*3.5, hardDifficulty_98x64, 96, 64, primaryColour);
  tft.drawBitmap(tft.width()-30,4, cactus_24x32, 24,32, GREEN);

  tft.setRotation(0);
}

void ttcPlayerAmountChoice(){
  tft.fillScreen(primaryColour);

  tft.setRotation(3);
  tft.drawBitmap(tft.width()-30,4, cactus_24x32, 24,32, GREEN);
  tft.setRotation(0);

  //top / 1 player
  tft.fillRect(OTHERBOXSIZE/2, OTHERBOXSIZE/2, OTHERBOXSIZE*2, 7*OTHERBOXSIZE, secondaryColour);
  tft.setRotation(3);
  tft.setCursor((tft.width()/4) * 1.25, tft.height()/4);
  tft.setTextSize(4);
  tft.print("1 PLAYER");
  tft.setRotation(0);

  //bottom / 2 player
  tft.fillRect(OTHERBOXSIZE*3, OTHERBOXSIZE/2, OTHERBOXSIZE*2, 7*OTHERBOXSIZE, secondaryColour);
  tft.setRotation(3);
  tft.setCursor((tft.width()/4) * 1.25, (tft.height()/4) * 2.85);
  tft.setTextSize(4);
  tft.print("2 PLAYER");
  tft.setRotation(0);
}

void musicDashboard(){
  ///////////////////////////////////////////////////////////////////////////////////////////////
  //                METHOD IS ONLY FOR DRAWING GUI ELEMENTS AND STATE FUNCTIONS                //
  ///////////////////////////////////////////////////////////////////////////////////////////////

  tft.fillScreen(primaryColour);
  tft.setRotation(0);
  tft.setCursor(0,0);
  tft.setTextSize(4);
  
  
  
  //previous track button for music
  tft.fillRect(OTHERBOXSIZE*3, OTHERBOXSIZE*5.5, OTHERBOXSIZE*2, 2*OTHERBOXSIZE, secondaryColour);
  tft.setRotation(3);
  tft.drawBitmap(OTHERBOXSIZE*.9,  OTHERBOXSIZE*3.5, backward_64x64, 64, 64, WHITE); // BACKWARD
  tft.setRotation(0);  

  //pause/play
  musicPausePlayClear();
  tft.setRotation(0);

  //next track button for music
  tft.fillRect(OTHERBOXSIZE*3, OTHERBOXSIZE/2, OTHERBOXSIZE*2, 2*OTHERBOXSIZE, secondaryColour);
  tft.setRotation(3);
  tft.drawBitmap(BOXSIZE*3.4,  OTHERBOXSIZE*3.5, forward_64x64, 64, 64, WHITE);

  //exit at top of screen
  tft.fillRect(0, 0, tft.width(), OTHERBOXSIZE, secondaryColour);
  tft.setCursor(OTHERBOXSIZE/2, OTHERBOXSIZE/2);
  tft.setTextColor(WHITE);
  tft.print("PRESS HERE TO EXIT");

  musicClearTextArea();
  tft.print("Song : ");
  musicSongName(counter);  
  tft.setRotation(3);
  tft.drawBitmap(tft.width()-30,4, cactus_24x32, 24,32, GREEN);

  ///////////////////////////////////////////////////////////////////////////////////////////////
  //             DETECT IF PRESSED, GET COUNT OF SONGS AND ITERATE AS REQUIRED                 //
  //                           AS OF 06/12/22 EVERYTHING WORKS HERE                            //
  //                                                                                           //
  //            ALL DETECTION IS DONE IN THE METHODS FOR MAIN MENU DETECTION TOO               //                                                                                         //
  //                                                                                           //
  //                         EXIT SEQUENCE IS DONE IN MAIN MENU DETECTION                      //
  ///////////////////////////////////////////////////////////////////////////////////////////////
  
}

void settingsDashboard(){

  tft.fillScreen(primaryColour);
  tft.setRotation(0);
  tft.setCursor(0,0);

  //left / adjust left on current setting
  tft.fillRect(OTHERBOXSIZE*3, OTHERBOXSIZE*5.5, OTHERBOXSIZE*2, 2*OTHERBOXSIZE, secondaryColour);
  tft.setRotation(3);
  tft.drawBitmap(OTHERBOXSIZE*.9,  OTHERBOXSIZE*3.5, backwardsPlay_64x64, 64, 64, WHITE); // BACKWARD
  tft.setRotation(0);  

  //right / adjust right on current setting
  tft.fillRect(OTHERBOXSIZE*3, OTHERBOXSIZE * 3, OTHERBOXSIZE*2, 2*OTHERBOXSIZE, secondaryColour);
  tft.setRotation(3);
  tft.drawBitmap(OTHERBOXSIZE * 3.5, OTHERBOXSIZE * 3.5, play_64x64, 64, 64, WHITE); // PLAY 
  tft.setRotation(0);

  //right / next setting
  tft.fillRect(OTHERBOXSIZE*3, OTHERBOXSIZE/2, OTHERBOXSIZE*2, 2*OTHERBOXSIZE, secondaryColour);
  tft.setRotation(3);
  tft.drawBitmap(BOXSIZE*3.4,  OTHERBOXSIZE*3.5, forward_64x64, 64, 64, WHITE);


  //exit at top of screen
  tft.fillRect(0, 0, tft.width(), OTHERBOXSIZE, secondaryColour);
  tft.setCursor(OTHERBOXSIZE/2, OTHERBOXSIZE/2);
  tft.setTextSize(4);
  tft.print("PRESS HERE TO EXIT");
  tft.setCursor(OTHERBOXSIZE/2, BOXSIZE);
  displayCurrentSetting(currentSetting);
  tft.setRotation(3);
  tft.drawBitmap(tft.width()-30,4, cactus_24x32, 24,32, GREEN);
  tft.setRotation(0);

  
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
  tft.fillRect(0, OTHERBOXSIZE + 10,tft.width(), tft.height()/3, primaryColour);
  tft.setCursor(OTHERBOXSIZE/2, BOXSIZE);
  tft.setTextColor(WHITE);
  tft.setTextSize(4);
}

void tictacEndScreen(int winner){
  tictacGUI.EndScreen(winner); //display end screen
}

void musicPausePlayClear(){
  //upate the display of pause/play symbol based on if it is playing or not.

  if (songPaused == true){ // DISPLAYS PLAY ICON
    tft.fillRect(OTHERBOXSIZE*3, OTHERBOXSIZE * 3, OTHERBOXSIZE*2, 2*OTHERBOXSIZE, secondaryColour);
    tft.setRotation(3);
    tft.drawBitmap(OTHERBOXSIZE * 3.5, OTHERBOXSIZE * 3.5, play_64x64, 64, 64, WHITE); // PLAY 
  }
  else if (songPaused == false){ // DISPLAYS PAUSE ICON
    tft.fillRect(OTHERBOXSIZE*3, OTHERBOXSIZE * 3, OTHERBOXSIZE*2, 2*OTHERBOXSIZE, secondaryColour);
    tft.setRotation(3);
    tft.drawBitmap(OTHERBOXSIZE * 3.5, OTHERBOXSIZE * 3.5, pause_64x64, 64, 64, WHITE); // PLAY 
  }
}

void musicSongName(int songNo){
  if (songNo == 1){
    tft.print("Confused Organ");
  } else if (songNo == 3){
    tft.print("Velvet Room");
  } else if (songNo == 4){
    tft.print("Family Guy");
  } else if (songNo == 5){
    tft.print("Crazy Frog");
  } else if (songNo == 6){
    tft.print("Tongo Rap God");
  } else if (songNo == 7){
    tft.print("Massive Rat");
  } else if (songNo == 8){
    tft.print("Flowers");
  } 
}

void volumeDisplayLogic(){
  tft.setRotation(3);
  if (mp3Player.getCurrentVolume() == 8){
      musicClearTextArea();
      tft.print("Volume : Minumum");
  }
  if (mp3Player.getCurrentVolume() == 12){
      musicClearTextArea();
      tft.print("Volume : Medium");    
  }
  if (mp3Player.getCurrentVolume() == 15){
      musicClearTextArea();
      tft.print("Volume : Maximum");
  }
  tft.setRotation(0);
}

void musicLogic(int side){ // LEFT = 1 , RIGHT = 2
  if (side == 1){
    if (counter == 1){
      musicClearTextArea();
      tft.print("Song : ");
      musicSongName(counter);      
    }
    else if (counter <= 8){
      if (counter == 3){
        counter--;        
      }
      counter--;
      musicClearTextArea();
      tft.print("Song : ");
      musicSongName(counter);
    }
  }
  else if (side == 2){
    if (counter == 8){
      counter = 1;
      musicClearTextArea();
      tft.print("Song : ");
      musicSongName(counter);
    }

    else if (counter > 1){
      counter++;
      musicClearTextArea();
      tft.print("Song : ");
      musicSongName(counter);
    }

    else if (counter == 1){
      musicClearTextArea();

      counter+=2;
      tft.print("Song : ");
      musicSongName(counter);
    }
  }
  
}

void whichFlag(){
  tft.setRotation(3);
  musicClearTextArea();
  tft.setRotation(0);
  delay(250);
  if (timezone == 1){
    //tft.drawRGBBitmap(BOXSIZE, BOXSIZE, irelandFLAG_128x64, 128, 64);
    tft.fillRect((tft.width()/2) - 92,(tft.height()/2) - 92,94,184, BLACK);
    tft.fillRect((tft.width()/2) - 90,(tft.height()/2) - 90,90,180, WHITE);
    tft.fillRect((tft.width()/2) - 90, (tft.height()/2) + 30, 90, 60, DARKGREEN);
    tft.fillRect((tft.width()/2) - 90, (tft.height()/2) - 90, 90, 60, ORANGE);
  }
  if (timezone == 2){
    //tft.drawRGBBitmap(BOXSIZE, BOXSIZE, usFLAG_128x64, 128, 64);
    tft.fillRect((tft.width()/2) - 92,(tft.height()/2) - 92,94,184, BLACK);
    tft.fillRect((tft.width()/2) - 90,(tft.height()/2) - 90,90,180, WHITE);
    tft.setRotation(3);
    tft.drawBitmap((tft.width()/2) - 90,(tft.height()/2) - 90, us_flag_base_180x90, 180, 90, RED);
    tft.fillRect((tft.width()/2) - 90,(tft.height()/2) - 90, 71, 48, WHITE);
    tft.drawBitmap((tft.width()/2) - 90,(tft.height()/2) - 90, us_flag_stars_71x48, 71, 48, BLUE);
    tft.setRotation(0);
  }
  if (timezone == 3){
    tft.fillRect((tft.width()/2) - 92,(tft.height()/2) - 92,94,184, BLACK);
    tft.fillRect((tft.width()/2) - 90,(tft.height()/2) - 90,90,180,WHITE);
    tft.fillCircle((tft.width()/2) - 45,(tft.height()/2), 37, RED);
  }
  if (timezone == 4){
    tft.fillRect((tft.width()/2) - 92,(tft.height()/2) - 92,94,184, BLACK);
    tft.fillRect((tft.width()/2) - 90,(tft.height()/2) - 90,90,180, WHITE);
    tft.setRotation(3);
    tft.setCursor((tft.width()/2) - 45, (tft.height()/2) - 45);
    tft.setTextColor(RED);
    tft.setTextSize(2);
    tft.print("AUSTRALIA");
    tft.setRotation(0);
    //PUT FLAG IN
  }
}

void startupSplash(){
  mp3Player.playIntroMusic();
  tft.fillScreen(BLUE);
  tft.setRotation(3);
  tft.setTextSize(3);
  tft.setTextColor(WHITE);
  tft.println("Beginning Setup...");
  delay(1000);
  tft.println("Setting up TFT Screen...");
  delay(1000);
  tft.println("Orientation Set...");
  delay(1000);

  tft.println("Testing LEDs...");
  for (int i=1; i <= 44; i++) {
    //erial.print(i);
    pinMode(i, OUTPUT);
    delay(100);
  }
  for (int i=1; i <= 44; i++) {
    //erial.print(i);
    digitalWrite(i, HIGH);
    delay(100);
  }

  tft.println("Setting up Binary Clock...");
  delay(3500);
  tft.println("Almost Done...");
  delay(4000);
  tft.println("Setup Finished..."); 
  delay(250);
  tft.drawBitmap(tft.width()/2, tft.height()/1.5 , cactus_24x32, 24,32, GREEN);
  tft.println("");
  tft.println("Booting to CactusOS..."); 
  delay(3500); 
  mp3Player.pausePlay(1);
}

void clockDashboard(){
  tft.fillScreen(primaryColour);
  tft.fillRect(OTHERBOXSIZE*3, OTHERBOXSIZE*4.5, OTHERBOXSIZE*2, 3*OTHERBOXSIZE, secondaryColour);
  tft.setRotation(3);
  tft.drawBitmap(OTHERBOXSIZE*1.3, OTHERBOXSIZE*3.5, backwardsPlay_64x64, 64, 64, WHITE);
  tft.setRotation(0);  

  tft.fillRect(OTHERBOXSIZE*3, OTHERBOXSIZE/2, OTHERBOXSIZE*2, 3*OTHERBOXSIZE, secondaryColour);
  tft.setRotation(3);
  tft.drawBitmap(BOXSIZE*3.1, OTHERBOXSIZE*3.5, play_64x64, 64, 64, WHITE);

  tft.fillRect(0, 0, tft.width(), OTHERBOXSIZE, secondaryColour);
  tft.setCursor(OTHERBOXSIZE/2, OTHERBOXSIZE/2);
  tft.setTextColor(WHITE);
  tft.setTextSize(4);
  tft.print("PRESS HERE TO SAVE");
  tft.setRotation(0);
  whichFlag();
  tft.setRotation(3);
  tft.drawBitmap(tft.width()-30,4, cactus_24x32, 24,32, GREEN);
  tft.setRotation(0);
}

void clockVoidLoop(){ //CLOCK VOID LOOP, STATES DIDN'T LIKE IT BEING A METHOD FROM A HEADER
  bClock.bClockLoop(timezone);
} 

// SETTINGS
// 1 - PRIMARY COLOUR
// 2 - SECONDARY COLOUR
// 3 - VOLUME
void settingsOptions(int setting){ 
  if (setting == 1){
    primaryColour = themeColourSelector(primaryColourNum);
  }
  else if (setting == 2){
    secondaryColour = themeColourSelector(secondaryColourNum);
  }
}

// change == 1 || 2
// 1 - left
// 2 - right
void settingsColourOptionsPrimary(int change){
  if (change == 1){
    if (primaryColourNum == 1){
      primaryColourNum = 10;
    } else {
      primaryColourNum--;
    }
  }else if (change == 2){
    if (primaryColourNum == 10){
      primaryColourNum = 1;
    } else {
      primaryColourNum++;
    }
  }
}


// change == 1 || 2
// 1 - left
// 2 - right
void settingsColourOptionsSecondary(int change){
  if (change == 1){
    if (secondaryColourNum == 1){
      secondaryColourNum = 10;
    } else {
      secondaryColourNum--;
    }
  }else if (change == 2){
    if (secondaryColourNum == 10){
      secondaryColourNum = 1;
    } else {
      secondaryColourNum++;
    }
  }
}

uint16_t themeColourSelector(int colour){
  switch(colour)
  {
    case 1:
      return BLACK;
      break;
    case 2:
      return BLUE;
      break;
    case 3:
      return RED;
      break;
    case 4:
      return GREEN;
      break;
    case 5:
      return DARKGREEN;
      break;
    case 6:
      return CYAN;
      break;
    case 7:
      return MAGENTA;
      break;
    case 8:
      return YELLOW;
      break;
    case 9:
      return WHITE;
      break;
    case 10:
      return ORANGE;
      break;
  }
}

// 1 - UP/RIGHT
// 2 - DOWN/LEFT
void volumeChangeOption(int choice){
  if (choice == 1){
    mp3Player.changeVolume(1);
    if (musicPlayerVolume == 12){
      musicPlayerVolume = 15;
    }
  } else if (choice == 2){
    mp3Player.changeVolume(2);
    if (musicPlayerVolume == 15){
      musicPlayerVolume = 12;
    } 
  }
}

void displayCurrentSetting(int setting){
  if (setting == 1){
    tft.print("Changing Primary Colour");
  } else if (setting == 2){ 
    tft.print("Changing Secondary Colour");
  } else if (setting == 3){
    volumeDisplayLogic();
  }
}

void voidMethod(){} //VOID METHOD FOR ANY TIME STATES NEED TO BE STAGNANT

void ttFrontPage(){tictacGUI.drawFrontPage(tft);} //FRONT PAGE FOR STATE

void ttGridPage(){tictacGUI.drawGrid(tft);} //GRID PAGE FOR STATE
