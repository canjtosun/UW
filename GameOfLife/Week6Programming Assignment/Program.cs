using System;
using System.Threading;

namespace CanTosun.LWTech.GameOfLife
{
    class Program
    {
        const int Xcor = 40;
        const int Ycor = 60;
        const int numMilliSeconds = 150;
        static Random rng = new Random();
        const int percent = 20;
        const int DEAD = 0;
        const int ALIVE = 1;



        static void Main(string[] args)
        {

            int[,] grid = new int[Xcor, Ycor];
            int[,] newGrid = new int[Xcor, Ycor];

            //Populate the new grid randomly with 1's and 0's
            GridInitilize(newGrid);

            bool quit = false;
            int counter = 0;
            int cellTotal = 0;

            while (!quit)
            {
                counter++;
                Console.WriteLine("turn #" + counter);

                grid = (int[,])newGrid.Clone();

                DisplayGrid(grid);


                for (int i = 1; i < Xcor - 1; i++)
                {
                    for (int j = 1; j < Ycor - 1; j++)
                    {
                        cellTotal =
                            grid[i - 1, j - 1] + grid[i - 1, j] + grid[i - 1, j + 1] +
                            grid[i, j - 1] +  /* current cell */  grid[i, j + 1] +
                            grid[i + 1, j - 1] + grid[i + 1, j] + grid[i + 1, j + 1];

                        if ((grid[i, j] == ALIVE) && (cellTotal == 2 || cellTotal == 3))
                            newGrid[i, j] = ALIVE;

                        else if ((grid[i, j] == ALIVE) && (cellTotal == 0 || cellTotal == 1))
                            newGrid[i, j] = DEAD;

                        else if ((grid[i, j] == ALIVE) && (cellTotal > 3))
                            newGrid[i, j] = DEAD;

                        else if ((grid[i, j] == DEAD) && (cellTotal == 3))
                            newGrid[i, j] = ALIVE;

                        else if ((grid[i, j] == 0) && (cellTotal != 3))
                            newGrid[i, j] = DEAD;
                    }

                }
                if (Console.KeyAvailable)
                {
                    ConsoleKey key = Console.ReadKey(true).Key;
                    switch (key)
                    {
                        case ConsoleKey.Q:
                            quit = true;
                            break;
                        case ConsoleKey.R:
                            GridInitilize(newGrid);
                            break;
                        case ConsoleKey.F:
                            FillGrid(newGrid);
                            break;
                        case ConsoleKey.D5:
                            RPento(newGrid);
                            break;
                        case ConsoleKey.C:
                            CleanGrid(newGrid);
                            break;
                        case ConsoleKey.G:
                            GliderGun(newGrid);
                            break;
                        case ConsoleKey.L:
                            LWSS(newGrid);
                            break;
                        default:
                            break;
                    }
                }
                Thread.Sleep(numMilliSeconds);
            }


        }

        public static void GridInitilize(int[,] arr)
        {
            for (int i = 0; i < Xcor; i++)
            {
                for (int j = 0; j < Ycor; j++)
                {
                    int num = rng.Next(0, 100);
                    if (num < percent)
                        arr[i, j] = ALIVE;
                    else
                        arr[i, j] = DEAD;
                }
            }
        }

        public static void DisplayGrid(int[,] arr)
        {
            string line = "";

            for (int i = 0; i < Xcor; i++)
            {

                for (int j = 0; j < Ycor; j++)
                {
                    if (arr[i, j] == ALIVE)
                        line += "*";
                    else
                        line += " ";
                }

                Console.WriteLine(line);
                line = "";
            }
        }


        public static void FillGrid(int[,] arr)
        {
            for (int i = 0; i < Xcor; i++)
            {
                for (int j = 0; j < Ycor; j++)
                {
                    arr[i, j] = ALIVE;
                }
            }
        }

        public static void CleanGrid(int[,] arr)
        {
            for (int i = 0; i < Xcor; i++)
            {
                for (int j = 0; j < Ycor; j++)
                {
                    arr[i, j] = DEAD;
                }
            }
        }

        public static void RPento(int[,] arr)
        {
            CleanGrid(arr);
            arr[20, 31] = ALIVE;
            arr[20, 32] = ALIVE;
            arr[21, 30] = ALIVE;
            arr[21, 31] = ALIVE;
            arr[22, 31] = ALIVE;

        }

        public static void GliderGun(int[,] arr)
        {
            CleanGrid(arr);
            arr[21, 32] = ALIVE;
            arr[22, 33] = ALIVE;
            arr[23, 31] = ALIVE;
            arr[23, 32] = ALIVE;
            arr[23, 33] = ALIVE;

        }

        public static void LWSS(int[,] arr)
        {
            CleanGrid(arr);
            arr[20, 31] = ALIVE;
            arr[20, 34] = ALIVE;
            arr[21, 30] = ALIVE;
            arr[22, 30] = ALIVE;
            arr[22, 34] = ALIVE;
            arr[23, 30] = ALIVE;
            arr[23, 31] = ALIVE;
            arr[23, 32] = ALIVE;
            arr[23, 33] = ALIVE;


        }




    }
}


