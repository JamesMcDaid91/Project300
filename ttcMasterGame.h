#include "ttcGUI.h"
#include <TrueRandom.h>
#include <stdio.h>
/*############################################################################################
* 
*   EndScreen() 0 = draw, 1 = player, 2 = ai/player2 etc, 3 = continue
*   UpdateDisplay() function needs the end call for circles and crosses. the number indicates 
      the grid postion. The circle of cross means O or X.

###############################################################################################*/

#ifndef ttcMasterGame_h
#define ttcMasterGame_h

class Game
  {
    private:

    public:

        //game set up
        int gameState[3][3];

        void resetState(){
          for (int i = 0; i < 3; i++)
          {
            for (int j = 0; j < 3; j++)
            {
              Serial.println("reset ");
              Serial.print(gameState[i][j]);
              gameState[i][j] = 0;
            }
          }
        }

        //player's turn
        int PlayerTurn(int gridColumn, int gridRow)
        {
          if (gameState[gridColumn][gridRow] == 0)// can only take a go if the position is empty
          {
            gameState[gridColumn][gridRow] = 1;
            UpdateDisplay(gridColumn, gridRow, 1);
            if (!CheckForWin()) // if no win
            {
              if (!CheckDraw())
              {
                return AIGo();
                
              }

              else {
                resetState();
                return 0;
              }
            }
            else
            {
              resetState();
              return 1;
            }
            return 3;
            //else player win screen
          }
        }
        //AI's turn
        int AIGo()
        {
          bool AITookItsGo = false;
          while (!AITookItsGo)
          {
            int randomColumn = rand() % 3;
            int randomRow = rand() % 3;
            if (gameState[randomColumn][randomRow] == 0)
            {
              gameState[randomColumn][randomRow] = 2;
              AITookItsGo = true;
              UpdateDisplay(randomColumn, randomRow, 2);
            }
          }

          if (CheckForWin())
          {
            //AI win Screen
            resetState();
            return 2;
          }
          if (CheckDraw())
          {
            resetState();
            return 0;
          }
          return 3;
        }

        //display update
        
        void UpdateDisplay(int column, int row, int player)
        {
          switch (column)
          {
          case 0: switch (row)
          {
          case 0:
            switch (player)
            {
            case 1: 
            tictacGUI.Cross_1();
              break;
            case 2:
            tictacGUI.Circle_1();
              break;
            default:
              break;
            }
            break;
          case 1:
            switch (player)
            {
            case 1:
            tictacGUI.Cross_2();
              break;
            case 2:
            tictacGUI.Circle_2();
              break;
            default:
              break;
            }
            break;
          case 2:
            switch (player)
            {
            case 1:
              tictacGUI.Cross_3();
              break;
            case 2:
              tictacGUI.Circle_3();
              break;
            default:
              break;
            }
            break;
          default:
            break;
          }
              break;
          case 1:
            switch (row)
            {
            case 0:
              switch (player)
              {
              case 1:
                tictacGUI.Cross_4();
                break;
              case 2:
                tictacGUI.Circle_4();
                break;
              default:
                break;
              }
              break;
            case 1:
              switch (player)
              {
              case 1:
                tictacGUI.Cross_5();
                break;
              case 2:
                 tictacGUI.Circle_5();
                break;
              default:
                break;
              }
              break;
            case 2:
              switch (player)
              {
              case 1:
                tictacGUI.Cross_6();
                break;
              case 2:
                 tictacGUI.Circle_6();
                break;
              default:
                break;
              }
              break;
            default:
              break;
            }
            break;
          case 2:
            switch (row)
            {
            case 0:
              switch (player)
              {
              case 1:
                 tictacGUI.Cross_7();
                break;
              case 2:
                 tictacGUI.Circle_7();
                break;
              default:
                break;
              }
              break;
            case 1:
              switch (player)
              {
              case 1:
                tictacGUI.Cross_8();
                break;
              case 2:
                 tictacGUI.Circle_8();
                break;
              default:
                break;
              }
              break;
            case 2:
              switch (player)
              {
              case 1:
                 tictacGUI.Cross_9();
                break;
              case 2:
                 tictacGUI.Circle_9();
                break;
              default:
                break;
              }
              break;
            default:
              break;
            }
            break;

          default:
            break;
          }
        }
        

        //win checker
        bool CheckForWin()
        {
          bool win = false;
          if (win == false)
          {
            win = CheckLine1_1();
          }
          if (win == false)
          {
            win = CheckLine1_2();
          }
          if (win == false)
          {
            win = CheckLine1_3();
          }
          if (win == false)
          {
            win = CheckLine2_1();
          }
          if (win == false)
          {
            win = CheckLine2_2();
          }
          if (win == false)
          {
            win = CheckLine3_1();
          }
          if (win == false)
          {
            win = CheckLine3_2();
          }
          if (win == false)
          {
            win = CheckLine4();
          }
          return win;
        }
        //line checks
        //from grid postion[0,0]
        bool CheckLine1_1()
        {
          bool response = false;
          if (gameState[0][1] != 0)
          {
            bool lineDown2InARow = Compare(0, 0, 0, 1);
            if (lineDown2InARow)
            {
              response = Compare(0, 0, 0, 2);
            }
          }
          return response;
        }
        bool CheckLine1_2()
        {
          bool response = false;
          if (gameState[1][0] != 0)
          {
            bool lineAcross2InARow = Compare(0, 0, 1, 0);
            if (lineAcross2InARow)
            {
              response = Compare(0, 0, 2, 0);
            }
          }
          return response;
        }
        bool CheckLine1_3()
        {
          bool response = false;
          if (gameState[1][1] != 0)
          {
            bool lineDiagonal2InARow = Compare(0, 0, 1, 1);
            if (lineDiagonal2InARow)
            {
              response = Compare(0, 0, 2, 2);
            }
          }
          return response;
        }
        //from grid postion[2,2]
        bool CheckLine2_1()
        {
          bool response = false;
          if (gameState[2][1] != 0)
          {
            bool lineUp2InARow = Compare(2, 2, 2, 1);
            if (lineUp2InARow)
            {
              response = Compare(2, 2, 2, 0);
            }
          }
          return response;
        }
        bool CheckLine2_2()
        {
          bool response = false;
          if (gameState[1][2] != 0)
          {
            bool lineBackAcross2InARow = Compare(2, 2, 1, 2);
            if (lineBackAcross2InARow)
            {
              response = Compare(2, 2, 0, 2);
            }
          }
          return response;
        }
        //from grid postion[1,1]
        bool CheckLine3_1()
        {
          bool response = false;
          if (gameState[1][0] != 0)
          {
            bool lineMiddleTop2InARow = Compare(1, 1, 1, 0);
            if (lineMiddleTop2InARow)
            {
              response = Compare(1, 1, 1, 2);
            }
          }
          return response;
        }
        bool CheckLine3_2()
        {
          bool response = false;
          if (gameState[0][1] != 0)
          {
            bool lineMiddleLeft2InARow = Compare(1, 1, 0, 1);
            if (lineMiddleLeft2InARow)
            {
              response = Compare(1, 1, 2, 1);
            }
          }
          return response;
        }
        //from grid postion[0,2] (opposite Diagonal)
        bool CheckLine4()
        {
          bool response = false;
          if (gameState[0][2] != 0)
          {
            bool lineMiddleLeft2InARow = Compare(0, 2, 1, 1);
            if (lineMiddleLeft2InARow)
            {
              response = Compare(0, 2, 2, 0);
            }
          }
          return response;
        }

        //draw checker
        bool CheckDraw()
        {
          //assume a draw
          bool IsDraw = true;
          //store a the row value
          int jvalue = 0;
          for (int i = 0; i < 3; i++)
          {
            for (int j = 0; j < 3; j++)
            {
              jvalue = j;// update row value
              if (gameState[i][j] == 0) //if defualt value
              {
                IsDraw = false; //then it can't be a draw
                break;  //no point checking the rest
              }
            }
            if (gameState[i][jvalue] == 0)
            {
              break; // check to break loop
            }
          }
          return IsDraw;//return whether or not it is a draw

        }

        //comparer tool to check if two grid postions have the same number
        bool Compare(int postion1Column, int postion1Row, int postion2Column, int postion2Row)
        {
          if (gameState[postion1Column][postion1Row] == gameState[postion2Column][postion2Row])
          {
            return true;
          }
          else return false;
        }


      void testEvent(){
        Serial.print("test_from_jame_code");
      }

      void Event_1()
      {
        if (gameState[0][0] == 0)
        {
          PlayerTurn(0, 0);
        }
      }
      void Event_2()
      {
        if (gameState[0][1] == 0)
        {
          PlayerTurn(0, 1);
        }
      }
      void Event_3()
      {
        if (gameState[0][2] == 0)
        {
          PlayerTurn(0, 2);
        }
      } 
      void Event_4()
      {
        if (gameState[1][0] == 0)
        {
        PlayerTurn(1, 0);
        }
      }  
      void Event_5()
      {
        if (gameState[1][1] == 0)
        {
        PlayerTurn(1, 1);
        }
      }
      void Event_6()
      {
        if (gameState[1][2] == 0)
        {
          PlayerTurn(1, 2);
        }
      }
      void Event_7()
      {
        if (gameState[2][0] == 0)
        {
          PlayerTurn(2, 0);
        }
      }
      void Event_8()
      {
        if (gameState[2][1] == 0)
        {
          PlayerTurn(2, 1);
        }
      }
      void Event_9()
      {
        if (gameState[2][2] == 0)
        {
          PlayerTurn(2, 2);
        }
      }
  };
  Game ttcMasterGame;
#endif  
