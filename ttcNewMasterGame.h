#include "ttcGUI.h"
#include <TrueRandom.h>
#include <stdio.h>

#ifndef ttcNewMasterGame_h
#define ttcNewMasterGame_h

class NewGame
  {
    private:

    public:
      int gameState[3][3];
      int AIState;
      int turncounter = 1;
      bool playerTwoActive = false;

      bool returnSecondPlayer(){return playerTwoActive;}

      void resetState(){
        playerTwoActive = false;
        for (int i = 0; i < 3; i++)
        {
          for (int j = 0; j < 3; j++)
          {
            Serial.println("reset ");
            Serial.print(gameState[i][j]);
            gameState[i][j] = 0;
            turncounter = 1;
          }
        }
      }

      void printCurrentState(){
        for (int i = 0; i < 3; i++){
          for (int j = 0; j < 3; j++){
            Serial.println(gameState[i][j]);
          }
        }
      }

      int returnTurnCounter(){
        return turncounter;
      }

      int returnGameState(int gridRow, int gridCol){
        if (gameState[gridCol][gridRow] == 0){
          return 0;
        }
        else{
          return 1;
        }
      }


      void TicTacToeSetup(int difficulty)
      {
          AIState = difficulty;
          if (difficulty == 0){
            playerTwoActive = true;
          }
          for (int i = 0; i < 3; i++)
          {
              for (int j = 0; j < 3; j++)
              {
                  gameState[i][j] = 0;
              }
          }
      }


      //win checker
      bool CheckForWin(int gameToCheck[3][3])
      {
          bool win = false;
          if (win == false)
          { win = CheckLine1_1(gameToCheck); }
          if (win == false)
          { win = CheckLine1_2(gameToCheck); }
          if (win == false)
          { win = CheckLine1_3(gameToCheck); }
          if (win == false)
          { win = CheckLine2_1(gameToCheck); }
          if (win == false)
          { win = CheckLine2_2(gameToCheck); }
          if (win == false)
          { win = CheckLine3_1(gameToCheck); }
          if (win == false)
          { win = CheckLine3_2(gameToCheck); }
          if (win == false)
          { win = CheckLine4(gameToCheck); }
          return win;
      }
      //line checks
      //from grid postion[0,0]
      bool CheckLine1_1(int gameStateToCheck[3][3])
      {
          bool response = false;
          if (gameStateToCheck[0][1] != 0)
          {
              bool lineDown2InARow = Compare(0, 0, 0, 1);
              if (lineDown2InARow)
              {
                  response = Compare(0, 0, 0, 2);
              }
          }
          return response;
      }
      bool CheckLine1_2(int gameStateToCheck[3][3])
      {
          bool response = false;
          if (gameStateToCheck[1][0] != 0)
          {
              bool lineAcross2InARow = Compare(0, 0, 1, 0);
              if (lineAcross2InARow)
              {
                  response = Compare(0, 0, 2, 0);
              }
          }
          return response;
      }
      bool CheckLine1_3(int gameStateToCheck[3][3])
      {
          bool response = false;
          if (gameStateToCheck[1][1] != 0)
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
      bool CheckLine2_1(int gameStateToCheck[3][3])
      {
          bool response = false;
          if (gameStateToCheck[2][1] != 0)
          {
              bool lineUp2InARow = Compare(2, 2, 2, 1);
              if (lineUp2InARow)
              {
                  response = Compare(2, 2, 2, 0);
              }
          }
          return response;
      }
      bool CheckLine2_2(int gameStateToCheck[3][3])
      {
          bool response = false;
          if (gameStateToCheck[1][2] != 0)
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
      bool CheckLine3_1(int gameStateToCheck[3][3])
      {
          bool response = false;
          if (gameStateToCheck[1][0] != 0)
          {
              bool lineMiddleTop2InARow = Compare(1, 1, 1, 0);
              if (lineMiddleTop2InARow)
              {
                  response = Compare(1, 1, 1, 2);
              }
          }
          return response;
      }
      bool CheckLine3_2(int gameStateToCheck[3][3])
      {
          bool response = false;
          if (gameStateToCheck[0][1] != 0)
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
      bool CheckLine4(int gameStateToCheck[3][3])
      {
          bool response = false;
          if (gameStateToCheck[0][2] != 0)
          {
              bool lineMiddleLeft2InARow = Compare(0, 2, 1, 1);
              if (lineMiddleLeft2InARow)
              {
                  response = Compare(0, 2, 2, 0);
              }
          }
          return response;
      }
      //comparer tool to check if two grid postions have the same number
      bool Compare(int postion1Column, int postion1Row, int postion2Column, int postion2Row)
      {
          if (gameState[postion1Column][postion1Row] == gameState[postion2Column][postion2Row])
          {
              if ((gameState[postion1Column][postion1Row] == 0) && (gameState[postion2Column][postion2Row] == 0))
              {
                  return false; //not sure what it has to return?
              }
              else return true;
          }
          else return false;
      }
      //Players
      //Ai turn
      int AIGo(int State)
      {
          switch (State)
          {
              case 0: break;

              case 1:
                  return AIEasy();

                  break;
              case 2:
                  return AIMedium();
                  break;
              case 3:
                  //AIHard();
                  return AIMedium();
                  break;
              case 4:
                  int r = TrueRandom.random(1,2);
                  AIState = r;
                  if (r == 1){
                    return AIEasy();
                  } else if (r == 2){
                    return AIMedium();
                  }
                  break;
              default:
                  break;

          }
      }
      int AIEasy()
      {
          bool AITookItsGo = false;
          while (!AITookItsGo)
          {
              int randomColumn = TrueRandom.random(3);
              int randomRow = TrueRandom.random(3);
              if (gameState[randomColumn][randomRow] == 0)
              {
                  gameState[randomColumn][randomRow] = 2;
                  AITookItsGo = true;
                  UpdateDisplay(randomColumn,randomRow, 2);
              }
              turncounter++;
          }

          if (CheckForWin(gameState))
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
          
      }
      int AIMedium()
      {
          bool AITookItsGo = false;
          if (!Blocker())
          {
              while (!AITookItsGo)
              {
                  int randomColumn = TrueRandom.random(3);
                  int randomRow = TrueRandom.random(3);
                  if (gameState[randomColumn][randomRow] == 0)
                  {
                      gameState[randomColumn][randomRow] = 2;
                      AITookItsGo = true;
                      UpdateDisplay(randomColumn, randomRow, 2);
                  }
                  turncounter++;
              }
          }
          if (CheckForWin(gameState))
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
      }
      bool Blocker()
      {
          bool blockerUsed = false;
          //Side by side checks from postion:
          //0,0
          if (Compare(0, 0, 1, 0) && gameState[2][0] == 0)
          {
              gameState[2][0] = 2;
              UpdateDisplay(2, 0, 2);
              blockerUsed = true;
          }
          else if (Compare(0, 0, 1, 1) && gameState[2][2] == 0)
          {
              gameState[2][2] = 2;
              UpdateDisplay(2, 2, 2);
              blockerUsed = true;
          }
          else if (Compare(0, 0, 0, 1) && gameState[0][2] == 0)
          {
              gameState[0][2] = 2;
              UpdateDisplay(0, 2, 2);
              blockerUsed = true;
          }
          //1,0
          else if (Compare(1, 0, 2, 0) && gameState[0][0] == 0)
          {
              gameState[0][0] = 2;
              UpdateDisplay(0, 0, 2);
              blockerUsed = true;
          }
          else if (Compare(1, 0, 1, 1) && gameState[1][2] == 0)
          {
              gameState[1][2] = 2;
              UpdateDisplay(1, 2, 2);
              blockerUsed = true;
          }
          //2,0
          else if (Compare(2, 0, 1, 1) && gameState[0][2] == 0)
          {
              gameState[0][2] = 2;
              UpdateDisplay(0, 2, 2);
              blockerUsed = true;
          }
          else if (Compare(2, 0, 2, 1) && gameState[2][2] == 0)
          {
              gameState[2][2] = 2;
              UpdateDisplay(2, 2, 2);
              blockerUsed = true;
          }
          //0,1
          else if (Compare(0, 1, 1, 1) && gameState[2][1] == 0)
          {
              gameState[2][1] = 2;
              UpdateDisplay(2, 1, 2);
              blockerUsed = true;
          }
          else if (Compare(0, 1, 0, 2) && gameState[0][0] == 0)
          {
              gameState[0][0] = 2;
              UpdateDisplay(0, 0, 2);
              blockerUsed = true;
          }
          //1,1
          else if (Compare(1, 1, 0, 2) && gameState[2][0] == 0)
          {
              gameState[2][0] = 2;
              UpdateDisplay(2, 0, 2);
              blockerUsed = true;
          }
          else if (Compare(1, 1, 1, 2) && gameState[1][0] == 0)
          {
              gameState[1][0] = 2;
              UpdateDisplay(1, 0, 2);
              blockerUsed = true;
          }
          else if (Compare(1, 1, 2, 2) && gameState[0][0] == 0)
          {
              gameState[0][0] = 2;
              UpdateDisplay(0, 0, 2);
              blockerUsed = true;
          }
          else if (Compare(1, 1, 2, 1) && gameState[0][1] == 0)
          {
              gameState[0][1] = 2;
              UpdateDisplay(0, 1, 2);
              blockerUsed = true;
          }
          //2,1
          else if (Compare(2, 1, 2, 2) && gameState[2][0] == 0)
          {
              gameState[2][0] = 2;
              UpdateDisplay(2, 0, 2);
              blockerUsed = true;
          }
          //0,2
          else if (Compare(0, 2, 1, 2) && gameState[2][2] == 0)
          {
              gameState[2][2] = 2;
              UpdateDisplay(2, 2, 2);
              blockerUsed = true;
          }
          //1,2
          else if (Compare(1, 2, 2, 2) && gameState[0][2] == 0)
          {
              gameState[0][2] = 2;
              UpdateDisplay(0, 2, 2);
              blockerUsed = true;
          }
          //Opposite Side Check from postion:
          //0,0
          else if (Compare(0, 0, 0, 2) && gameState[0][1] == 0)
          {
              gameState[0][1] = 2;
              UpdateDisplay(0, 1, 2);
              blockerUsed = true;
          }
          else if (Compare(0, 0, 2, 2) && gameState[1][1] == 0)
          {
              gameState[1][1] = 2;
              UpdateDisplay(1, 1, 2);
              blockerUsed = true;
          }
          else if (Compare(0, 0, 2, 0) && gameState[1][0] == 0)
          {
              gameState[1][0] = 2;
              UpdateDisplay(1, 0, 2);
              blockerUsed = true;
          }
          //2,0
          else if (Compare(2, 0, 0, 2) && gameState[1][1] == 0)
          {
              gameState[1][1] = 2;
              UpdateDisplay(1, 1, 2);
              blockerUsed = true;
          }
          else if (Compare(2, 0, 2, 2) && gameState[2][1] == 0)
          {
              gameState[2][1] = 2;
              UpdateDisplay(2, 1, 2);
              blockerUsed = true;
          }
          //0,2
          else if (Compare(0, 2, 2, 2) && gameState[1][2] == 0)
          {
              gameState[1][2] = 2;
              UpdateDisplay(1, 2, 2);
              blockerUsed = true;
          }
          //1,0
          else if (Compare(1, 0, 1, 2) && gameState[1][1] == 0)
          {
              gameState[1][1] = 2;
              UpdateDisplay(1, 1, 2);
              blockerUsed = true;
          }
          //0,1
          else if (Compare(0, 1, 2, 1) && gameState[1][1] == 0)
          {
              gameState[1][1] = 2;
              UpdateDisplay(1, 1, 2);
              blockerUsed = true;
          }
          return blockerUsed;
      }

      
      
      //player turn
      int PlayerTurn(int gridColumn, int gridRow)
      {
          if (gameState[gridColumn][gridRow] > 0){
            Serial.print("cannot place there, occupied by a players move already.");
          }
          else if (gameState[gridColumn][gridRow] == 0)// can only take a go if the position is empty
          {
              gameState[gridColumn][gridRow] = 1;
              UpdateDisplay(gridColumn, gridRow, 1);
              if (!CheckForWin(gameState)) // if no win
              {
                  turncounter++;
                  if (!CheckDraw())
                  {
                      int a = AIGo(AIState);
                      if (a == 2){
                        resetState();
                        return a;
                      }
                  }
                  else if (CheckDraw()){
                    resetState();
                    return 0;
                  }
                  return 4;
              }
              else
              {
                resetState();
                return 1;
              }
              //else player win screen
          }
      }
      int Player2Turn(int gridColumn, int gridRow)
      {
          if (gameState[gridColumn][gridRow] == 0)// can only take a go if the position is empty
          {
              Serial.println("from Player 2 Turn ->");
              gameState[gridColumn][gridRow] = 2;
              UpdateDisplay(gridColumn, gridRow, 2);
              
              if (!CheckForWin(gameState)) // if no win
              {
                  turncounter++;
                  if (CheckDraw())
                  {
                      resetState();
                      return 0;
                  }
                  return 4;
              }
              else if (CheckForWin(gameState))
              {
                  resetState();
                  return 3;
              }
              //else player win screen
          }
      }
      //display update
      void UpdateDisplay(int column, int row, int player)
      {
          switch (column)
          {
              case 0:
                  switch (row)
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
      bool CheckDraw()
      {
          bool IsDraw = true;
          for (int i = 0; i < 3; i++)
          {
              for (int j = 0; j < 3; j++)
              {
                  if (gameState[i][j] == 0)
                  {
                      IsDraw = false;
                      break;
                  }
              }
          }
          return IsDraw;

      }
  };
  NewGame ttcNewMasterGame;
#endif
