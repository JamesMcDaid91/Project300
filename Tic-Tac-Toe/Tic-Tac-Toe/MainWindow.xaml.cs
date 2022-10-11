using System.Windows;

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

        private void CheckForWin()
        {
            bool win = false;
            if (win == false)
            { win = checkLine1_1(); }
            if (win == false)
            { win = checkLine1_2(); }
            if (win == false)
            { win = checkLine1_3(); }
            if (win == false)
            { win = checkLine2_1(); }
            if (win == false)
            { win = checkLine2_2(); }
            if (win == false)
            { win = checkLine3_1(); }
            if (win == false)
            { win = checkLine3_2(); }
        }
        private void AIGo()
        {

        }
        private void PlayerTurn(int gridColumn, int gridRow)
        {
            if (gameState[gridColumn, gridRow] == 0)
            {
                gameState[gridColumn, gridRow] = 1;
                CheckForWin();
                AIGo();
            }
        }
    }
}
