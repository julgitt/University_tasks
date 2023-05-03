using System;

namespace Grid_Task5
{
    /// <summary>
    ///  The Grid class creates an n x m two-dimensional grid in which integers can be stored.
    /// </summary>
    public class Grid
    {
        int n, m;
        int[,] elements;

        /// <summary>
        /// Constructor of the <c>Grid</c>.
        /// </summary>
        /// <param name="n">Number of grid rows</param>
        /// <param name="m">Number of grid columns</param>
        public Grid(int n, int m)
        {
            this.n = n;
            this.m = m;
            elements = new int[this.n, this.m];
        }

        /// <summary>
        /// Indexer that returns array of the values from i-row
        /// </summary>
        /// <param name="i">Row index</param>
        /// <returns> int[] array of the values from i-row</returns>
        public int[] this[int i]
        {
            get
            {
                int[] values = new int[m];
                for (int j = 0; j < m; j++)
                    values[j] = elements[i, j];

                return values;
            }
        }

        /// <summary>
        /// Indexer for setting and getting values from the grid
        /// </summary>
        /// <param name="i">Row indexa</param>
        /// <param name="j">Column index</param>
        public int this[int i, int j]
        {
            get => elements[i - 1, j - 1];
            set => elements[i - 1, j - 1] = value;
        }
    }

    /// <summary>
    /// Main class of the Program
    /// </summary>
    public class Program
    {
        /// <summary>
        /// Main class - task 5
        /// </summary>
        public static void Main()
        {
            // initialization of the grid
            Grid grid = new Grid(4, 4);
            for (int n = 1; n <= 4; n++)
                for (int m = 1; m <= 4; m++)
                    grid[n, m] = n * m;

            for (int n = 1; n <= 4; n++)
            {
                for (int m = 1; m <= 4; m++)
                    Console.Write(grid[n, m] + " ");
                Console.WriteLine();
            }


            int[] rowdata = grid[1];

            Console.WriteLine();
            foreach (int element in rowdata)
                Console.Write(element + " ");

            grid[2, 2] = 5;
            int elem = grid[1, 3];

            Console.WriteLine("\n\n" + elem);

            Console.ReadLine();
        }
    }
}