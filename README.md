# Project300
ATUSligo Year3 Group Project

Hardware Used
-------------
* Arduino Mega 2560 Rev3
* MB-102 Breadboard 830 Point Solderless
* Nikou TFT LCD Display - 3.5" TFT LCD Screen Module 480x320
* DS3231 RTC
* DFMini Player MP3

Software
---------
This uses multiple libraries such as MCUFriend and DFMiniPlayer to display, detect and output the various GUIs made in conjunction with the hardware specs.
On the screen you can play preset music based on the SD card inputted into the MP3 Player Module, from there it is then sent to the module, cached and plays through the connected speakers. 
The Tic-Tac-Toe logic is a custom made library which does all the computing and logic behind checking the moves, deciding which player to move and finally outputs using the other custom library made to output the X or O depending on the player. 
It also has a settings menu which you can adjust the volume on the MP3 Player and theme of the GUI. 
