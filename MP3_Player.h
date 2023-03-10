/***************************************************
DFPlayer - A Mini MP3 Player For Arduino
 <https://www.dfrobot.com/product-1121.html>
 
 ***************************************************
 This example shows the basic function of library for DFPlayer.
 
 Created 2016-12-07
 By [Angelo qiao](Angelo.qiao@dfrobot.com)
 
 GNU Lesser General Public License.
 See <http://www.gnu.org/licenses/> for details.
 All above must be included in any redistribution
 ****************************************************/

/***********Notice and Trouble shooting***************
 1.Connection and Diagram can be found here
 <https://www.dfrobot.com/wiki/index.php/DFPlayer_Mini_SKU:DFR0299#Connection_Diagram>
 2.This code is tested on Arduino Uno, Leonardo, Mega boards.
 ****************************************************/


// TONES

// 0001 - DIALUP
// 0002 - DRAW
// 0003 - PH INTRO
// 0004 - TOILET FLUSHING
// 0005 - POOP SOUND

// SONGS

// 0001 - CONFUSED ORGAN
// 0002
// 0003 - VELVET ROOM
// 0004 - FAMILY GUY
// 0005 - CRAZY FROG
// 0006 - TONGO RAP GOD
// 0007 - MASSIVE RAT
// 0008 - FLOWERS


#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

SoftwareSerial mySoftwareSerial(51,53); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

class MP3Player{
  private:
  public:

    void mp3Setup(int volume){
      mySoftwareSerial.begin(9600);
      Serial.begin(115200);
      
      Serial.println();
      Serial.println(F("DFRobot DFPlayer Mini Demo"));
      Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));
      
      if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
        Serial.println(F("Unable to begin:"));
        Serial.println(F("1.Please recheck the connection!"));
        Serial.println(F("2.Please insert the SD card!"));
        while(true){
          delay(0); // Code to compatible with ESP8266 watch dog.
        }
      }
      Serial.println(F("DFPlayer Mini online."));
      
      myDFPlayer.volume(volume);  //Set volume value. From 0 to 30. Default is 20
      //myDFPlayer.play(1);
    }

    int fileCount(){
      int a = myDFPlayer.readFileCounts();
      return a;
    }

    void playSongNo(int song){
      myDFPlayer.playMp3Folder(song);
    }

    void playSelectedSong(int song){ // 1 = next 2 = previous
      if (song == 1){
        myDFPlayer.next();
      }
      if (song == 2){
        myDFPlayer.previous();
      }
    }

    int getCurrentVolume(){
      return myDFPlayer.readVolume();
    }

    void playIntroMusic(){
      myDFPlayer.playMp3Folder(8);
      myDFPlayer.advertise(1);
    }

    void stopMusic(){myDFPlayer.pause();}

    void playAdvertisement(int winner){
      myDFPlayer.advertise(winner);
    }

    void stopAdvertisement(){
      myDFPlayer.stopAdvertise();
    }

    void advertWithoutBackgroundMusic(int winner, int currentSong){
      myDFPlayer.playMp3Folder(currentSong);
      myDFPlayer.advertise(winner);
      //delay(3500);
      myDFPlayer.pause();
    }

    void changeVolume(int press){
      if (press == 2){
        if (myDFPlayer.readVolume() == 15){
          myDFPlayer.volume(12);
        } else {myDFPlayer.volume(8);}
      }
      else if (press == 1){
        if (myDFPlayer.readVolume() == 8){
          myDFPlayer.volume(12);
        } else {myDFPlayer.volume(15);}
      }
    }

    void pausePlay(int press){
      if (press == 1){
        myDFPlayer.pause();
      }
      else if (press == 2){
        myDFPlayer.start();
      }
    }

    void stopAndRestartAtStart(){
      myDFPlayer.playMp3Folder(1);
    }


    void errorCheck(){
      if (myDFPlayer.available()) {
        printDetail(myDFPlayer.readType(), myDFPlayer.read()); //Print the detail message from DFPlayer to handle different errors and states.
      }
    }

    
    void printDetail(uint8_t type, int value){
      switch (type) {
        case TimeOut:
          Serial.println(F("Time Out!"));
          break;
        case WrongStack:
          Serial.println(F("Stack Wrong!"));
          break;
        case DFPlayerCardInserted:
          Serial.println(F("Card Inserted!"));
          break;
        case DFPlayerCardRemoved:
          Serial.println(F("Card Removed!"));
          break;
        case DFPlayerCardOnline:
          Serial.println(F("Card Online!"));
          break;
        case DFPlayerUSBInserted:
          Serial.println("USB Inserted!");
          break;
        case DFPlayerUSBRemoved:
          Serial.println("USB Removed!");
          break;
        case DFPlayerPlayFinished:
          Serial.print(F("Number:"));
          Serial.print(value);
          Serial.println(F(" Play Finished!"));
          break;
        case DFPlayerError:
          Serial.print(F("DFPlayerError:"));
          switch (value) {
            case Busy:
              Serial.println(F("Card not found"));
              break;
            case Sleeping:
              Serial.println(F("Sleeping"));
              break;
            case SerialWrongStack:
              Serial.println(F("Get Wrong Stack"));
              break;
            case CheckSumNotMatch:
              Serial.println(F("Check Sum Not Match"));
              break;
            case FileIndexOut:
              Serial.println(F("File Index Out of Bound"));
              break;
            case FileMismatch:
              Serial.println(F("Cannot Find File"));
              break;
            case Advertise:
              Serial.println(F("In Advertise"));
              break;
            default:
              break;
          }
          break;
        default:
          break;
      }
      
    }

};


MP3Player mp3Player;

