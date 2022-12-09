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



 // 1. Velvet Room
 // 2. Family Guy
 // 3. Confused Organ
 // 4. Smooth Jazz
 // 5. Draw
 // 6. Loss
 // 7. Win
#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

SoftwareSerial mySoftwareSerial(51,53); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

class MP3Player{
  private:
  public:

    void mp3Setup(){
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
      
      myDFPlayer.volume(23);  //Set volume value. From 0 to 30. Default is 23
      //myDFPlayer.play(1);
    }

    int fileCount(){
      return myDFPlayer.readFileCounts();
    }

    void playSelectedSong(int song){
      myDFPlayer.play(song);
    }

    void changeVolume(int press){
      if (press == 0){
        myDFPlayer.volumeDown();
      }
      else if (press == 1){
        myDFPlayer.volumeUp();
      }
    }
};
MP3Player mp3Player;

