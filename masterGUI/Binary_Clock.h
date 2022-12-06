#include <Wire.h>
//#include <DS3231M.h>
#include <RTClib.h>

int curHour = 0, seconds = 0;
RTC_DS3231 RTC;

class BinaryClock{
  private:
  public:

    void bClockSetup() {
      //Serial.print("Starting Binary Clock Setup ");
      // put your setup code here, to run once:
      for (int i=1; i <= 44; i++) {
        //erial.print(i);
        pinMode(i, OUTPUT);
      }
    

    // 
      if (! RTC.begin()) {
        Serial.println("Couldn't find RTC");
        Serial.flush();
        while (1) delay(10);
      }

      if (RTC.lostPower()) {
        Serial.println("RTC lost power, let's set the time!");
        
        RTC.adjust(DateTime(F(__DATE__), F(__TIME__)));
      }

      // When time needs to be re-set on a previously configured device, the
      // following line sets the RTC to the date & time this sketch was compiled
      //RTC.adjust(DateTime(F(__DATE__), F(__TIME__)));
      //bClockLoop();
    }



    void bClockLoop()
    {  
    //Serial.print("test in clock loop");
    DateTime now = RTC.now();
    seconds = now.second();
    curHour = now.hour();

      //#########################################################################################
      //Hours
      //#########################################################################################
      //1 Hour
      if(curHour == 1 || curHour == 3 || curHour == 5 || curHour == 7 || curHour == 9 || curHour == 11 || curHour == 13 || curHour == 15 || curHour == 17 || curHour == 19 || curHour == 21 || curHour == 23)
        digitalWrite(23, HIGH);
      else
        digitalWrite(23, LOW);

      //2 Hours
      if(curHour == 2 || curHour == 3 || curHour == 6 || curHour == 7 || curHour == 10 || curHour == 11  || curHour == 14 || curHour == 15 || curHour == 18 || curHour == 19  || curHour == 22 || curHour == 23)
        digitalWrite(25, HIGH);
      else
        digitalWrite(25, LOW);

      //4 Hrs
      if(curHour == 4 || curHour == 5 || curHour == 6 || curHour == 7 || curHour == 12 || curHour == 13 || curHour == 14 || curHour == 15 || curHour == 20 || curHour == 21 || curHour == 22 || curHour == 23)
        digitalWrite(27, HIGH);
      else
        digitalWrite(27, LOW);
        
        //8 Hours
      if(curHour == 8 || curHour == 9 || curHour == 10 || curHour == 11 || curHour == 12 || curHour == 13 || curHour == 14 || curHour == 15 || curHour == 24)
        digitalWrite(29, HIGH);
      else
        digitalWrite(29, LOW);

        //16 Hours
      if(curHour == 16 || curHour == 17 || curHour == 18 || curHour == 19 || curHour == 20 || curHour == 21 || curHour == 22 || curHour == 23 || curHour == 24 )
        digitalWrite(31, HIGH);
      else
        digitalWrite(31, LOW);

      //#########################################################################################
      //Minutes
      //#########################################################################################
        //1 Minute
      if(now.minute() == 1 || now.minute() == 3 || now.minute() == 5 || now.minute() == 7 || now.minute() == 9 || now.minute() == 11 || now.minute() == 13 || now.minute() == 15 || now.minute() == 17 || now.minute() == 19 || now.minute() == 21 || now.minute() == 23 || now.minute() == 25 || now.minute() == 27 || now.minute() == 29|| now.minute() == 31 || now.minute() == 33 || now.minute() == 35 || now.minute() == 37 || now.minute() == 39 || now.minute() == 41 || now.minute() == 43 || now.minute() == 45 || now.minute() == 47 || now.minute() == 49 || now.minute() == 51 || now.minute() == 53 || now.minute() == 55 || now.minute() == 57 || now.minute() == 59)
        digitalWrite(22, HIGH);
      else
        digitalWrite(22, LOW);
        
      //2 Minutes
      if(now.minute() == 2 || now.minute() == 3 || now.minute() == 6 || now.minute() == 7 || now.minute() == 10 || now.minute() == 11  || now.minute() == 14 || now.minute() == 15 || now.minute() == 18 || now.minute() == 19  || now.minute() == 22 || now.minute() == 23 || now.minute() == 26 || now.minute() == 27 || now.minute() == 30|| now.minute() == 31 || now.minute() == 34 || now.minute() == 35 || now.minute() == 38 || now.minute() == 39 || now.minute() == 42 || now.minute() == 43 || now.minute() == 46 || now.minute() == 47 || now.minute() == 50 || now.minute() == 51 || now.minute() == 54 || now.minute() == 58 || now.minute() == 59) 
        digitalWrite(24, HIGH);
      else
        digitalWrite(24, LOW);
        
      //4 Minutes
      if(now.minute() == 4 || now.minute() == 5 || now.minute() == 6 || now.minute() == 7 || now.minute() == 12 || now.minute() == 13 || now.minute() == 14 || now.minute() == 15 || now.minute() == 20 || now.minute() == 21 || now.minute() == 22 || now.minute() == 23 || now.minute() == 28 || now.minute() == 29 || now.minute() == 30|| now.minute() == 31 || now.minute() == 36 || now.minute() == 37 || now.minute() == 38 || now.minute() == 39 || now.minute() == 44 || now.minute() == 45 || now.minute() == 46 || now.minute() == 47 || now.minute() == 52 || now.minute() == 53 || now.minute() == 54 || now.minute() == 55) 
        digitalWrite(26, HIGH);
      else
        digitalWrite(26, LOW);
        
      //8 Minutes
      if(now.minute() == 8 || now.minute() == 9 || now.minute() == 10 || now.minute() == 11 || now.minute() == 12 || now.minute() == 13 || now.minute() == 14 || now.minute() == 15 || now.minute() == 24 || now.minute() == 25 || now.minute() == 26 || now.minute() == 27 || now.minute() == 28 || now.minute() == 29 || now.minute() == 30|| now.minute() == 31 || now.minute() == 40 || now.minute() == 41 || now.minute() == 42 || now.minute() == 43 || now.minute() == 44 || now.minute() == 45 || now.minute() == 46 || now.minute() == 47 || now.minute() == 56 || now.minute() == 57 || now.minute() == 58 || now.minute() == 59)
        digitalWrite(28, HIGH);
      else
        digitalWrite(28, LOW);

      //16 Minutes
      if(now.minute() == 16 || now.minute() == 17 || now.minute() == 18 || now.minute() == 19 || now.minute() == 20 || now.minute() == 21 || now.minute() == 22 || now.minute() == 23 || now.minute() == 24 || now.minute() == 25 || now.minute() == 26 || now.minute() == 27 || now.minute() == 28 || now.minute() == 29 || now.minute() == 30|| now.minute() == 31 || now.minute() == 48 || now.minute() == 49 || now.minute() == 50 || now.minute() == 51 || now.minute() == 52 || now.minute() == 53 || now.minute() == 54 || now.minute() == 55 || now.minute() == 56 || now.minute() == 57|| now.minute() == 58 || now.minute() == 59)  {
        digitalWrite(30, HIGH);
      } else {
        digitalWrite(30,LOW);
      }
      //32 Minutes
      if(now.minute() == 32 || now.minute() == 33 || now.minute() == 34 || now.minute() == 35 || now.minute() == 36 || now.minute() == 37 || now.minute() == 38 || now.minute() == 39 || now.minute() == 40 || now.minute() == 41 || now.minute() == 42 || now.minute() == 43 || now.minute() == 44 || now.minute() == 45 || now.minute() == 46 || now.minute() == 47 || now.minute() == 48 || now.minute() == 49 || now.minute() == 50 || now.minute() == 51 || now.minute() == 52 || now.minute() == 53 || now.minute() == 54 || now.minute() == 55 || now.minute() == 56 || now.minute() == 57 || now.minute() == 58 || now.minute() == 59) {
        digitalWrite(32, HIGH);
      } else {
        digitalWrite(32,LOW);
      }

      //#########################################################################################
      //Seconds
      //#########################################################################################
        //1 Second
      if(seconds == 1 || seconds == 3 || seconds == 5 || seconds == 7 || seconds == 9 || seconds == 11 || seconds == 13 || seconds == 15 || seconds == 17 || seconds == 19 || seconds == 21 || seconds == 23 || seconds == 25 || seconds == 27 || seconds == 29|| seconds == 31 || seconds == 33 || seconds == 35 || seconds == 37 || seconds == 39 || seconds == 41 || seconds == 43 || seconds == 45 || seconds == 47 || seconds == 49 || seconds == 51 || seconds == 53 || seconds == 55 || seconds == 57 || seconds == 59)
        digitalWrite(34, HIGH);
      else
        digitalWrite(34, LOW);
        
      //2 Seconds
      if(seconds == 2 || seconds == 3 || seconds == 6 || seconds == 7 || seconds == 10 || seconds == 11  || seconds == 14 || seconds == 15 || seconds == 18 || seconds == 19  || seconds == 22 || seconds == 23 || seconds == 26 || seconds == 27 || seconds == 30|| seconds == 31 || seconds == 34 || seconds == 35 || seconds == 38 || seconds == 39 || seconds == 42 || seconds == 43 || seconds == 46 || seconds == 47 || seconds == 50 || seconds == 51 || seconds == 54 || seconds == 58 || seconds == 59) 
        digitalWrite(36, HIGH);
      else
        digitalWrite(36, LOW);
        
      //4 Seconds
      if(seconds == 4 || seconds == 5 || seconds == 6 || seconds == 7 || seconds == 12 || seconds == 13 || seconds == 14 || seconds == 15 || seconds == 20 || seconds == 21 || seconds == 22 || seconds == 23 || seconds == 28 || seconds == 29 || seconds == 30|| seconds == 31 || seconds == 36 || seconds == 37 || seconds == 38 || seconds == 39 || seconds == 44 || seconds == 45 || seconds == 46 || seconds == 47 || seconds == 52 || seconds == 53 || seconds == 54 || seconds == 55) 
        digitalWrite(38, HIGH);
      else
        digitalWrite(38, LOW);
        
      //8 Seconds
      if(seconds == 8 || seconds == 9 || seconds == 10 || seconds == 11 || seconds == 12 || seconds == 13 || seconds == 14 || seconds == 15 || seconds == 24 || seconds == 25 || seconds == 26 || seconds == 27 || seconds == 28 || seconds == 29 || seconds == 30|| seconds == 31 || seconds == 40 || seconds == 41 || seconds == 42 || seconds == 43 || seconds == 44 || seconds == 45 || seconds == 46 || seconds == 47 || seconds == 56 || seconds == 57 || seconds == 58 || seconds == 59)
        digitalWrite(40, HIGH);
      else
        digitalWrite(40, LOW);

      //16 Seconds
      if(seconds == 16 || seconds == 17 || seconds == 18 || seconds == 19 || seconds == 20 || seconds == 21 || seconds == 22 || seconds == 23 || seconds == 24 || seconds == 25 || seconds == 26 || seconds == 27 || seconds == 28 || seconds == 29 || seconds == 30|| seconds == 31 || seconds == 48 || seconds == 49 || seconds == 50 || seconds == 51 || seconds == 52 || seconds == 53 || seconds == 54 || seconds == 55 || seconds == 56 || seconds == 57|| seconds == 58 || seconds == 59)  {
        digitalWrite(42, HIGH);
      } else {
        digitalWrite(42,LOW);
      }
      //32 Seconds
      if(seconds == 32 || seconds == 33 || seconds == 34 || seconds == 35 || seconds == 36 || seconds == 37 || seconds == 38 || seconds == 39 || seconds == 40 || seconds == 41 || seconds == 42 || seconds == 43 || seconds == 44 || seconds == 45 || seconds == 46 || seconds == 47 || seconds == 48 || seconds == 49 || seconds == 50 || seconds == 51 || seconds == 52 || seconds == 53 || seconds == 54 || seconds == 55 || seconds == 56 || seconds == 57 || seconds == 58 || seconds == 59) {
        digitalWrite(44, HIGH);
      } else {
        digitalWrite(44,LOW);
      }

    // Serial.println(now.hour());
    // Serial.println(now.minute());
    // Serial.println(now.second());
    }

};
BinaryClock bClock;