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
            if (gameState[0,0] == 0)
            {
                PlayerTurn(0, 0);
            }            
        }
        private void Button01_Click(object sender, RoutedEventArgs e)
        {
            if (gameState[0, 1] == 0)
            {
                PlayerTurn(0, 1);
            }
        }
        private void Button02_Click(object sender, RoutedEventArgs e)
        {
            if (gameState[0, 2] == 0)
            {
                PlayerTurn(0, 2);
            }
        }
        //column 2
        private void Button10_Click(object sender, RoutedEventArgs e)
        {
            if (gameState[1, 0] == 0)
            {
                PlayerTurn(1, 0);
            }
        }
        private void Button11_Click(object sender, RoutedEventArgs e)
        {
            if (gameState[1, 1] == 0)
            {
                PlayerTurn(1, 1);
            }
        }
        private void Button12_Click(object sender, RoutedEventArgs e)
        {
            if (gameState[1, 2] == 0)
            {
                PlayerTurn(1, 2);
            }
        }
        //column 3
        private void Button20_Click(object sender, RoutedEventArgs e)
        {
            if (gameState[2, 0] == 0)
            {
                PlayerTurn(2, 0);
            }
        }
        private void Button21_Click(object sender, RoutedEventArgs e)
        {
            if (gameState[2, 1] == 0)
            {
                PlayerTurn(2, 1);
            }
        }
        private void Button22_Click(object sender, RoutedEventArgs e)
        {
            if (gameState[2, 2] == 0)
            {
                PlayerTurn(2, 2);
            }
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
            if (win == false)
            { win = CheckLine4(); }
            return win;
        }
        //line checks
        //from grid postion[0,0]
        private bool CheckLine1_1()
        {
            bool response = false;
            if (gameState[0,1] != 0)
            {
                bool lineDown2InARow = Compare(0, 0, 0, 1);
                if (lineDown2InARow)
                {
                    response = Compare(0, 0, 0, 2);
                }
            }
            return response;
        }
        private bool CheckLine1_2()
        {
            bool response = false;
            if (gameState[1, 0] != 0)
            {
                bool lineAcross2InARow = Compare(0, 0, 1, 0);
                if (lineAcross2InARow)
                {
                    response = Compare(0, 0, 2, 0);
                }
            }
            return response;
        }
        private bool CheckLine1_3()
        {
            bool response = false;
            if (gameState[1, 1] != 0)
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
        private bool CheckLine2_1()
        {
            bool response = false;
            if (gameState[2, 1] != 0)
            {
                bool lineUp2InARow = Compare(2, 2, 2, 1);
                if (lineUp2InARow)
                {
                    response = Compare(2, 2, 2, 0);
                }
            }
            return response;
        }
        private bool CheckLine2_2()
        {
            bool response = false;
            if (gameState[1, 2] != 0)
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
        private bool CheckLine3_1()
        {
            bool response = false;
            if (gameState[1, 0] != 0)
            {
                bool lineMiddleTop2InARow = Compare(1, 1, 1, 0);
                if (lineMiddleTop2InARow)
                {
                    response = Compare(1, 1, 1, 2);
                }
            }
            return response;
        }
        private bool CheckLine3_2()
        {
            bool response = false;
            if (gameState[0, 1] != 0)
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
        private bool CheckLine4()
        {
            bool response = false;
            if (gameState[0, 2] != 0)
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
        private bool Compare(int postion1Column, int postion1Row, int postion2Column, int postion2Row)
        {
            if (gameState[postion1Column, postion1Row] == gameState[postion2Column, postion2Row])
            {
                return true;
            }
            else return false;
        }

        //Players
        //Ai turn
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
                    UpdateDisplay(randomColumn,randomRow,2);
                }
            }
            
            if (CheckForWin())
                {
                //AI win Screen
                EndScreen("Computer");
            }
            if (CheckDraw())
            {
                EndScreen("Nobody");
            }
            
        }
        //player turn
        private void PlayerTurn(int gridColumn, int gridRow)
        {
            if (gameState[gridColumn, gridRow] == 0)// can only take a go if the position is empty
            {
                gameState[gridColumn, gridRow] = 1;
                UpdateDisplay(gridColumn,gridRow,1);
                if (!CheckForWin()) // if no win
                {
                    if (!CheckDraw())
                    {
                        AIGo();
                    }
                    else EndScreen("Nobody");
                }
                else
                {
                    EndScreen("Player");
                }
                //else player win screen
            }
        }
        //display update
        private void UpdateDisplay(int column, int row, int player)
        {
            switch (column)
            {
                case 0: switch (row)
                    {
                        case 0:
                            switch (player)
                            {
                                case 1: Button00.Content = "X";
                                    break;
                                case 2:
                                    Button00.Content = "O";
                                    break;
                                default:
                                    break;
                            }
                            break;
                        case 1:
                            switch (player)
                            {
                                case 1:
                                    Button01.Content = "X";
                                    break;
                                case 2:
                                    Button01.Content = "O";
                                    break;
                                default:
                                    break;
                            }
                            break;
                        case 2:
                            switch (player)
                            {
                                case 1:
                                    Button02.Content = "X";
                                    break;
                                case 2:
                                    Button02.Content = "O";
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
                                    Button10.Content = "X";
                                    break;
                                case 2:
                                    Button10.Content = "O";
                                    break;
                                default:
                                    break;
                            }
                            break;
                        case 1:
                            switch (player)
                            {
                                case 1:
                                    Button11.Content = "X";
                                    break;
                                case 2:
                                    Button11.Content = "O";
                                    break;
                                default:
                                    break;
                            }
                            break;
                        case 2:
                            switch (player)
                            {
                                case 1:
                                    Button12.Content = "X";
                                    break;
                                case 2:
                                    Button12.Content = "O";
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
                                    Button20.Content = "X";
                                    break;
                                case 2:
                                    Button20.Content = "O";
                                    break;
                                default:
                                    break;
                            }
                            break;
                        case 1:
                            switch (player)
                            {
                                case 1:
                                    Button21.Content = "X";
                                    break;
                                case 2:
                                    Button21.Content = "O";
                                    break;
                                default:
                                    break;
                            }
                            break;
                        case 2:
                            switch (player)
                            {
                                case 1:
                                    Button22.Content = "X";
                                    break;
                                case 2:
                                    Button22.Content = "O";
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
        private void EndScreen (string winner)
        {
            EndScreen gameOver = new EndScreen();
            string text = winner + " WINS!!!";
            gameOver.TextBlock.Text = text;            
            gameOver.Show();
            gameOver.Focus();
            this.Close();
        }
        private bool CheckDraw()
        {
            bool IsDraw = true;
            int jvalue = 0;
            for (int i = 0; i < gameState.GetLength(0); i++)
            {
                for (int j = 0; j < gameState.GetLength(1); j++)
                {
                    jvalue = j;
                    if (gameState[i,j] == 0)
                    {
                        IsDraw = false;
                        break;
                    }
                }
                if (gameState[i, jvalue] == 0)
                {
                    break;
                }
            }
            return IsDraw;

        }
    }
}
