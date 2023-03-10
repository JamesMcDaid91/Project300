#include <Wire.h>
//#include <DS3231M.h>
#include <RTClib.h>

DateTime CurrentTime;
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

      if (! RTC.begin()) {
        Serial.println("Couldn't find RTC");
        Serial.flush();
        while (1) delay(10);
      }

      if (RTC.lostPower()) {
        Serial.println("RTC lost power, let's set the time!");
        
        RTC.adjust(DateTime(F(__DATE__), F(__TIME__)));
      }

      //RTC.adjust(DateTime(F(__DATE__), F(__TIME__)));
      //bClockLoop();
    }

    void SetTimezones(int Timezone)
    {
      //I know this entire Timezone changing feature is incorrect and will only function in GMT but it will be enough for our project
      //London // GMT
      if(Timezone == 1){
      CurrentTime = RTC.now();
      }
      //New York // GMT -5
      else if(Timezone == 2){
      CurrentTime = RTC.now()  - TimeSpan(0, 5, 0, 0);
      }
      //Japan // GMT + 9
      else if(Timezone == 3){
      CurrentTime = RTC.now() + TimeSpan(0, 9, 0, 0);
      }
      //Sydney // GMT + 11
      else if(Timezone == 4){
      CurrentTime = RTC.now()+ TimeSpan(0, 11, 0, 0);
      }
    }


    void bClockLoop(int timezoneChoice)
    {  
      //Calls the Timezone method
      //REQUIRES AN INPUT OF 1-5 TO SET THE TIME SO IT CAN BE USED IN THE LOOP TO OUTPUT TIME, WITHOUT THIS TIME WILL NOT OUTPUT
      if (timezoneChoice < 1 || timezoneChoice > 5){
        SetTimezones(1);
      }
      else {
        SetTimezones(timezoneChoice); 
      }
      

      //#########################################################################################
      //Hours
      //#########################################################################################
      //1 Hour
      if(CurrentTime.hour() == 1 || CurrentTime.hour() == 3 || CurrentTime.hour() == 5 || CurrentTime.hour() == 7 || CurrentTime.hour() == 9 || CurrentTime.hour() == 11 || CurrentTime.hour() == 13 || CurrentTime.hour() == 15 || CurrentTime.hour() == 17 || CurrentTime.hour() == 19 || CurrentTime.hour() == 21 || CurrentTime.hour() == 23)
        digitalWrite(23, HIGH);
      else
        digitalWrite(23, LOW);

      //2 Hours
      if(CurrentTime.hour() == 2 || CurrentTime.hour() == 3 || CurrentTime.hour() == 6 || CurrentTime.hour() == 7 || CurrentTime.hour() == 10 || CurrentTime.hour() == 11  || CurrentTime.hour() == 14 || CurrentTime.hour() == 15 || CurrentTime.hour() == 18 || CurrentTime.hour() == 19  || CurrentTime.hour() == 22 || CurrentTime.hour() == 23)
        digitalWrite(25, HIGH);
      else
        digitalWrite(25, LOW);

      //4 Hrs
      if(CurrentTime.hour() == 4 || CurrentTime.hour() == 5 || CurrentTime.hour() == 6 || CurrentTime.hour() == 7 || CurrentTime.hour() == 12 || CurrentTime.hour() == 13 || CurrentTime.hour() == 14 || CurrentTime.hour() == 15 || CurrentTime.hour() == 20 || CurrentTime.hour() == 21 || CurrentTime.hour() == 22 || CurrentTime.hour() == 23)
        digitalWrite(27, HIGH);
      else
        digitalWrite(27, LOW);
        
        //8 Hours
      if(CurrentTime.hour() == 8 || CurrentTime.hour() == 9 || CurrentTime.hour() == 10 || CurrentTime.hour() == 11 || CurrentTime.hour() == 12 || CurrentTime.hour() == 13 || CurrentTime.hour() == 14 || CurrentTime.hour() == 15 || CurrentTime.hour() == 24)
        digitalWrite(29, HIGH);
      else
        digitalWrite(29, LOW);

        //16 Hours
      if(CurrentTime.hour() == 16 || CurrentTime.hour() == 17 || CurrentTime.hour() == 18 || CurrentTime.hour() == 19 || CurrentTime.hour() == 20 || CurrentTime.hour() == 21 || CurrentTime.hour() == 22 || CurrentTime.hour() == 23 || CurrentTime.hour() == 24 )
        digitalWrite(31, HIGH);
      else
        digitalWrite(31, LOW);

      //#########################################################################################
      //Minutes
      //#########################################################################################
        //1 Minute
      if(CurrentTime.minute()== 1 || CurrentTime.minute() == 3 || CurrentTime.minute() == 5 || CurrentTime.minute() == 7 || CurrentTime.minute() == 9 || CurrentTime.minute() == 11 || CurrentTime.minute() == 13 || CurrentTime.minute() == 15 || CurrentTime.minute() == 17 || CurrentTime.minute() == 19 || CurrentTime.minute() == 21 || CurrentTime.minute() == 23 || CurrentTime.minute() == 25 || CurrentTime.minute() == 27 || CurrentTime.minute() == 29|| CurrentTime.minute() == 31 || CurrentTime.minute() == 33 || CurrentTime.minute() == 35 || CurrentTime.minute() == 37 || CurrentTime.minute() == 39 || CurrentTime.minute() == 41 || CurrentTime.minute() == 43 || CurrentTime.minute() == 45 || CurrentTime.minute() == 47 || CurrentTime.minute() == 49 || CurrentTime.minute() == 51 || CurrentTime.minute() == 53 || CurrentTime.minute() == 55 || CurrentTime.minute() == 57 || CurrentTime.minute() == 59)
        digitalWrite(22, HIGH);
      else
        digitalWrite(22, LOW);
        
      //2 Minutes
      if(CurrentTime.minute() == 2 || CurrentTime.minute() == 3 || CurrentTime.minute() == 6 || CurrentTime.minute() == 7 || CurrentTime.minute() == 10 || CurrentTime.minute() == 11  || CurrentTime.minute() == 14 || CurrentTime.minute() == 15 || CurrentTime.minute() == 18 || CurrentTime.minute() == 19  || CurrentTime.minute() == 22 || CurrentTime.minute() == 23 || CurrentTime.minute() == 26 || CurrentTime.minute() == 27 || CurrentTime.minute() == 30|| CurrentTime.minute() == 31 || CurrentTime.minute() == 34 || CurrentTime.minute() == 35 || CurrentTime.minute() == 38 || CurrentTime.minute() == 39 || CurrentTime.minute() == 42 || CurrentTime.minute() == 43 || CurrentTime.minute() == 46 || CurrentTime.minute() == 47 || CurrentTime.minute() == 50 || CurrentTime.minute() == 51 || CurrentTime.minute() == 54 || CurrentTime.minute() == 58 || CurrentTime.minute() == 59) 
        digitalWrite(24, HIGH);
      else
        digitalWrite(24, LOW);
        
      //4 Minutes
      if(CurrentTime.minute() == 4 || CurrentTime.minute() == 5 || CurrentTime.minute() == 6 || CurrentTime.minute() == 7 || CurrentTime.minute() == 12 || CurrentTime.minute() == 13 || CurrentTime.minute() == 14 || CurrentTime.minute() == 15 || CurrentTime.minute() == 20 || CurrentTime.minute() == 21 || CurrentTime.minute() == 22 || CurrentTime.minute() == 23 || CurrentTime.minute() == 28 || CurrentTime.minute() == 29 || CurrentTime.minute() == 30|| CurrentTime.minute() == 31 || CurrentTime.minute() == 36 || CurrentTime.minute() == 37 || CurrentTime.minute() == 38 || CurrentTime.minute() == 39 || CurrentTime.minute() == 44 || CurrentTime.minute() == 45 || CurrentTime.minute() == 46 || CurrentTime.minute() == 47 || CurrentTime.minute() == 52 || CurrentTime.minute() == 53 || CurrentTime.minute() == 54 || CurrentTime.minute() == 55) 
        digitalWrite(26, HIGH);
      else
        digitalWrite(26, LOW);
        
      //8 Minutes
      if(CurrentTime.minute() == 8 || CurrentTime.minute() == 9 || CurrentTime.minute() == 10 || CurrentTime.minute() == 11 || CurrentTime.minute() == 12 || CurrentTime.minute() == 13 || CurrentTime.minute() == 14 || CurrentTime.minute() == 15 || CurrentTime.minute() == 24 || CurrentTime.minute() == 25 || CurrentTime.minute() == 26 || CurrentTime.minute() == 27 || CurrentTime.minute() == 28 || CurrentTime.minute() == 29 || CurrentTime.minute() == 30|| CurrentTime.minute() == 31 || CurrentTime.minute() == 40 || CurrentTime.minute() == 41 || CurrentTime.minute() == 42 || CurrentTime.minute() == 43 || CurrentTime.minute() == 44 || CurrentTime.minute() == 45 || CurrentTime.minute() == 46 || CurrentTime.minute() == 47 || CurrentTime.minute() == 56 || CurrentTime.minute() == 57 || CurrentTime.minute() == 58 || CurrentTime.minute() == 59)
        digitalWrite(28, HIGH);
      else
        digitalWrite(28, LOW);

      //16 Minutes
      if(CurrentTime.minute() == 16 || CurrentTime.minute() == 17 || CurrentTime.minute() == 18 || CurrentTime.minute() == 19 || CurrentTime.minute() == 20 || CurrentTime.minute() == 21 || CurrentTime.minute() == 22 || CurrentTime.minute() == 23 || CurrentTime.minute() == 24 || CurrentTime.minute() == 25 || CurrentTime.minute() == 26 || CurrentTime.minute() == 27 || CurrentTime.minute() == 28 || CurrentTime.minute() == 29 || CurrentTime.minute() == 30|| CurrentTime.minute() == 31 || CurrentTime.minute() == 48 || CurrentTime.minute() == 49 || CurrentTime.minute() == 50 || CurrentTime.minute() == 51 || CurrentTime.minute() == 52 || CurrentTime.minute() == 53 || CurrentTime.minute() == 54 || CurrentTime.minute() == 55 || CurrentTime.minute() == 56 || CurrentTime.minute() == 57|| CurrentTime.minute() == 58 || CurrentTime.minute() == 59)  {
        digitalWrite(30, HIGH);
      } else {
        digitalWrite(30,LOW);
      }
      //32 Minutes
      if(CurrentTime.minute() == 32 || CurrentTime.minute() == 33 || CurrentTime.minute() == 34 || CurrentTime.minute() == 35 || CurrentTime.minute() == 36 || CurrentTime.minute() == 37 || CurrentTime.minute() == 38 || CurrentTime.minute() == 39 || CurrentTime.minute() == 40 || CurrentTime.minute() == 41 || CurrentTime.minute() == 42 || CurrentTime.minute() == 43 || CurrentTime.minute() == 44 || CurrentTime.minute() == 45 || CurrentTime.minute() == 46 || CurrentTime.minute() == 47 || CurrentTime.minute() == 48 || CurrentTime.minute() == 49 || CurrentTime.minute() == 50 || CurrentTime.minute() == 51 || CurrentTime.minute() == 52 || CurrentTime.minute() == 53 || CurrentTime.minute() == 54 || CurrentTime.minute() == 55 || CurrentTime.minute() == 56 || CurrentTime.minute() == 57 || CurrentTime.minute() == 58 || CurrentTime.minute() == 59) {
        digitalWrite(32, HIGH);
      } else {
        digitalWrite(32,LOW);
      }

      //#########################################################################################
      //Seconds
      //#########################################################################################
        //1 Second
      if(CurrentTime.second() == 1 || CurrentTime.second() == 3 || CurrentTime.second() == 5 || CurrentTime.second() == 7 || CurrentTime.second() == 9 || CurrentTime.second() == 11 || CurrentTime.second() == 13 || CurrentTime.second() == 15 || CurrentTime.second() == 17 || CurrentTime.second() == 19 || CurrentTime.second() == 21 || CurrentTime.second() == 23 || CurrentTime.second() == 25 || CurrentTime.second() == 27 || CurrentTime.second() == 29|| CurrentTime.second() == 31 || CurrentTime.second() == 33 || CurrentTime.second() == 35 || CurrentTime.second() == 37 || CurrentTime.second() == 39 || CurrentTime.second() == 41 || CurrentTime.second() == 43 || CurrentTime.second() == 45 || CurrentTime.second() == 47 || CurrentTime.second() == 49 || CurrentTime.second() == 51 || CurrentTime.second() == 53 || CurrentTime.second() == 55 || CurrentTime.second() == 57 || CurrentTime.second() == 59)
        digitalWrite(34, HIGH);
      else
        digitalWrite(34, LOW);
        
      //2 Seconds
      if(CurrentTime.second() == 2 || CurrentTime.second() == 3 || CurrentTime.second() == 6 || CurrentTime.second() == 7 || CurrentTime.second() == 10 || CurrentTime.second() == 11  || CurrentTime.second() == 14 || CurrentTime.second() == 15 || CurrentTime.second() == 18 || CurrentTime.second() == 19  || CurrentTime.second() == 22 || CurrentTime.second() == 23 || CurrentTime.second() == 26 || CurrentTime.second() == 27 || CurrentTime.second() == 30|| CurrentTime.second() == 31 || CurrentTime.second() == 34 || CurrentTime.second() == 35 || CurrentTime.second() == 38 || CurrentTime.second() == 39 || CurrentTime.second() == 42 || CurrentTime.second() == 43 || CurrentTime.second() == 46 || CurrentTime.second() == 47 || CurrentTime.second() == 50 || CurrentTime.second() == 51 || CurrentTime.second() == 54 || CurrentTime.second() == 58 || CurrentTime.second() == 59) 
        digitalWrite(36, HIGH);
      else
        digitalWrite(36, LOW);
        
      //4 Seconds
      if(CurrentTime.second() == 4 || CurrentTime.second() == 5 || CurrentTime.second() == 6 || CurrentTime.second() == 7 || CurrentTime.second() == 12 || CurrentTime.second() == 13 || CurrentTime.second() == 14 || CurrentTime.second() == 15 || CurrentTime.second() == 20 || CurrentTime.second() == 21 || CurrentTime.second() == 22 || CurrentTime.second() == 23 || CurrentTime.second() == 28 || CurrentTime.second() == 29 || CurrentTime.second() == 30|| CurrentTime.second() == 31 || CurrentTime.second() == 36 || CurrentTime.second() == 37 || CurrentTime.second() == 38 || CurrentTime.second() == 39 || CurrentTime.second() == 44 || CurrentTime.second() == 45 || CurrentTime.second() == 46 || CurrentTime.second() == 47 || CurrentTime.second() == 52 || CurrentTime.second() == 53 || CurrentTime.second() == 54 || CurrentTime.second() == 55) 
        digitalWrite(38, HIGH);
      else
        digitalWrite(38, LOW);
        
      //8 Seconds
      if(CurrentTime.second() == 8 || CurrentTime.second() == 9 || CurrentTime.second() == 10 || CurrentTime.second() == 11 || CurrentTime.second() == 12 || CurrentTime.second() == 13 || CurrentTime.second() == 14 || CurrentTime.second() == 15 || CurrentTime.second() == 24 || CurrentTime.second() == 25 || CurrentTime.second() == 26 || CurrentTime.second() == 27 || CurrentTime.second() == 28 || CurrentTime.second() == 29 || CurrentTime.second() == 30|| CurrentTime.second() == 31 || CurrentTime.second() == 40 || CurrentTime.second() == 41 || CurrentTime.second() == 42 || CurrentTime.second() == 43 || CurrentTime.second() == 44 || CurrentTime.second() == 45 || CurrentTime.second() == 46 || CurrentTime.second() == 47 || CurrentTime.second() == 56 || CurrentTime.second() == 57 || CurrentTime.second() == 58 || CurrentTime.second() == 59)
        digitalWrite(40, HIGH);
      else
        digitalWrite(40, LOW);

      //16 Seconds
      if(CurrentTime.second() == 16 || CurrentTime.second() == 17 || CurrentTime.second() == 18 || CurrentTime.second() == 19 || CurrentTime.second() == 20 || CurrentTime.second() == 21 || CurrentTime.second() == 22 || CurrentTime.second() == 23 || CurrentTime.second() == 24 || CurrentTime.second() == 25 || CurrentTime.second() == 26 || CurrentTime.second() == 27 || CurrentTime.second() == 28 || CurrentTime.second() == 29 || CurrentTime.second() == 30|| CurrentTime.second() == 31 || CurrentTime.second() == 48 || CurrentTime.second() == 49 || CurrentTime.second() == 50 || CurrentTime.second() == 51 || CurrentTime.second() == 52 || CurrentTime.second() == 53 || CurrentTime.second() == 54 || CurrentTime.second() == 55 || CurrentTime.second() == 56 || CurrentTime.second() == 57|| CurrentTime.second() == 58 || CurrentTime.second() == 59)  {
        digitalWrite(42, HIGH);
      } else {
        digitalWrite(42,LOW);
      }
      //32 Seconds
      if(CurrentTime.second() == 32 || CurrentTime.second() == 33 || CurrentTime.second() == 34 || CurrentTime.second() == 35 || CurrentTime.second() == 36 || CurrentTime.second() == 37 || CurrentTime.second() == 38 || CurrentTime.second() == 39 || CurrentTime.second() == 40 || CurrentTime.second() == 41 || CurrentTime.second() == 42 || CurrentTime.second() == 43 || CurrentTime.second() == 44 || CurrentTime.second() == 45 || CurrentTime.second() == 46 || CurrentTime.second() == 47 || CurrentTime.second() == 48 || CurrentTime.second() == 49 || CurrentTime.second() == 50 || CurrentTime.second() == 51 || CurrentTime.second() == 52 || CurrentTime.second() == 53 || CurrentTime.second() == 54 || CurrentTime.second() == 55 || CurrentTime.second() == 56 || CurrentTime.second() == 57 || CurrentTime.second() == 58 || CurrentTime.second() == 59) {
        digitalWrite(44, HIGH);
      } else {
        digitalWrite(44,LOW);
      }
    }

};
BinaryClock bClock;