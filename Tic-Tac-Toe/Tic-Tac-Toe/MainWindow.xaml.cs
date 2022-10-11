using System.Windows;
using System;

namespace Tic_Tac_Toe
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public int[,] gameState = new int[3, 3];

        public MainWindow()
        {
            InitializeComponent();
            for (int i = 0; i < gameState.GetLength(0); i++)
            {
                for (int j = 0; j < gameState.GetLength(1); j++)
                {
                    gameState[i, j] = 0;
                }
            }
        }

        //buttons
        //column 1
        private void Button00_Click(object sender, RoutedEventArgs e)
        {
            PlayerTurn(0, 0);
        }
        private void Button01_Click(object sender, RoutedEventArgs e)
        {
            PlayerTurn(0, 1);
        }
        private void Button02_Click(object sender, RoutedEventArgs e)
        {
            PlayerTurn(0, 2);
        }
        //column 2
        private void Button10_Click(object sender, RoutedEventArgs e)
        {
            PlayerTurn(1, 0);
        }
        private void Button11_Click(object sender, RoutedEventArgs e)
        {
            PlayerTurn(1, 1);
        }
        private void Button12_Click(object sender, RoutedEventArgs e)
        {
            PlayerTurn(1, 2);
        }
        //column 3
        private void Button20_Click(object sender, RoutedEventArgs e)
        {
            PlayerTurn(2, 0);
        }
        private void Button21_Click(object sender, RoutedEventArgs e)
        {
            PlayerTurn(2, 1);
        }
        private void Button22_Click(object sender, RoutedEventArgs e)
        {
            PlayerTurn(2, 2);
        }

        //win checker
        private bool CheckForWin()
        {
            bool win = false;
            if (win == false)
            { win = CheckLine1_1(); }
            if (win == false)
            { win = CheckLine1_2(); }
            if (win == false)
            { win = CheckLine1_3(); }
            if (win == false)
            { win = CheckLine2_1(); }
            if (win == false)
            { win = CheckLine2_2(); }
            if (win == false)
            { win = CheckLine3_1(); }
            if (win == false)
            { win = CheckLine3_2(); }
            return win;
        }
        //line checks
        //from grid postion[0,0]
        private bool CheckLine1_1()
        {
            bool response = false;
            bool lineDown2InARow = Compare(0, 0, 0, 1);
            if (lineDown2InARow)
            {
                response = Compare(0, 0, 0, 2);
            }
            return response;
        }
        private bool CheckLine1_2()
        {
            bool response = false;
            bool lineAcross2InARow = Compare(0, 0, 1, 0);
            if (lineAcross2InARow)
            {
                response = Compare(0, 0, 2, 0);
            }
            return response;
        }
        private bool CheckLine1_3()
        {
            bool response = false;
            bool lineAcross2InARow = Compare(0, 0, 1, 0);
            if (lineAcross2InARow)
            {
                response = Compare(0, 0, 2, 0);
            }
            return response;
        }
        //from grid postion[2,2]
        private bool CheckLine2_1()
        {
            bool response = false;
            bool lineUp2InARow = Compare(2, 2, 2, 1);
            if (lineUp2InARow)
            {
                response = Compare(2, 2, 2, 0);
            }
            return response;
        }
        private bool CheckLine2_2()
        {
            bool response = false;
            bool lineBackAcross2InARow = Compare(2, 2, 1, 2);
            if (lineBackAcross2InARow)
            {
                response = Compare(2, 2, 0, 2);
            }
            return response;
        }
        //from grid postion[1,1]
        private bool CheckLine3_1()
        {
            bool response = false;
            bool lineMiddleTop2InARow = Compare(1, 1, 1, 0);
            if (lineMiddleTop2InARow)
            {
                response = Compare(1, 1, 1, 2);
            }
            return response;
        }
        private bool CheckLine3_2()
        {
            bool response = false;
            bool lineMiddleLeft2InARow = Compare(1, 1, 0, 1);
            if (lineMiddleLeft2InARow)
            {
                response = Compare(1, 1, 2, 1);
            }
            return response;
        }
        //comparer tool to check if two grid postions have the same number
        private bool Compare(int postion1Column, int postion1Row, int postion2Column, int postion2Row)
        {
            if (gameState[postion1Column, postion1Row] == gameState[postion2Column, postion2Row])
            {
                return true;
            }
            else return false;
        }

        private void AIGo()
        {
            Random randomSeed = new Random();
            Random randomNumber = new Random(randomSeed.Next());
            bool AITookItsGo = false;
            while(!AITookItsGo)
            {
                int randomColumn = randomNumber.Next(0, 3);
                int randomRow = randomNumber.Next(0, 3);
                if ( gameState[randomColumn,randomRow] == 0)
                {
                    gameState[randomColumn, randomRow] = 2;
                    AITookItsGo = true;
                }
            }
            if (CheckForWin())
                {
                //AI win Screen
            }
            
        }
        private void PlayerTurn(int gridColumn, int gridRow)
        {
            if (gameState[gridColumn, gridRow] == 0)// can only take a go if the position is empty
            {
                gameState[gridColumn, gridRow] = 1;
                if (!CheckForWin()) // if no win
                    { AIGo(); }//AI plays
                //else player win screen
            }
        }
    }
}
