using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace GameOfLife
{
    public partial class Main : Form
    {
        /* 0,0  1,0  2,0  3,0  
         * 0,1  1,1
         * 0,2
         * 0,3
         * 0,4            4,4
         */

        //private int gridLengthX = 1000;
        //private int gridLengthY = 800;

        private int gridLengthX = 200;
        private int gridLengthY = 200;

        //array of array
        private int[][] LifeGrid;

        private Graphics drawingArea;

        public Main()
        {
            InitializeComponent();

            //LifeGrid initialization

            LifeGrid = new int [gridLengthX][];

            for (int x = 0; x < gridLengthX; x++)
            {
                LifeGrid[x] = new int[gridLengthY];
                for (int y = 0; y<gridLengthY; y++)
                {
                    LifeGrid[x][y] = 0;
                }
            }


            //graphics initialization
            drawingArea = pictureBox1.CreateGraphics();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            //Graphics graphicObject = Main.create
            Pen blackPen = new Pen(Color.Black, 3);

            int x = 900;
            int y = 50;
            int width = 100;
            int height = 50;

            drawingArea.DrawRectangle(blackPen, x, y, width, height);
        }

        private void Main_Paint(object sender, PaintEventArgs e)
        {

            Pen blackPen = new Pen(Color.Black, 3);
            Brush redBrush = new SolidBrush(Color.Red);
            int x = 200;
            int y = 50;
            int width = 50;
            int height = 50;

            //e.Graphics.DrawRectangle(blackPen, x, y, width, height);
            e.Graphics.FillRectangle(redBrush, x, y, width, height);
        }

        private void btn_Randomize_Click(object sender, EventArgs e)
        {
            //there are 1000x800 plots on the grid
            //start with 1000?

            int startLifeCount = 1000;
            Random random = new Random();

            while (startLifeCount > 0)
            {
                int x = random.Next(0, gridLengthX - 1);
                int y = random.Next(0, gridLengthY - 1);

                if (LifeGrid[x][y] == 0)
                {
                    LifeGrid[x][y] = 1;
                    startLifeCount--;
                }
            }

            //DrawLife();
            //DrawTextLife();
        }

        private void DrawLife()
        {
            Brush greenBrush = new SolidBrush(Color.Green);
            Brush blackBrush = new SolidBrush(Color.Black);

            for (int x = 0; x < gridLengthX; x++)
            {
                for (int y = 0; y < gridLengthY; y++)
                {
                    if (LifeGrid[x][y] == 1)
                    {
                        drawingArea.FillRectangle(greenBrush, x, y, 1, 1);
                    }
                    else
                    {
                        drawingArea.FillRectangle(blackBrush, x, y, 1, 1);
                    }
                }
            }
        }

        private void DrawTextLife()
        {
            //StringBuilder textLife = new StringBuilder();
            //string row = "";

            lbl_TextLife.Text = "";

            for (int y = 0; y < gridLengthY; y ++)
            {
                for (int x = 0; x < gridLengthX; x ++)
                {
                    if (LifeGrid[x][y] == 1)
                    {
                        //drawingArea.FillRectangle(greenBrush, x, y, 1, 1);

                        //row += "O ";
                        lbl_TextLife.Text += "O ";
                    }
                    else
                    {
                        //drawingArea.FillRectangle(blackBrush, x, y, 1, 1);
                        //row += "X ";
                        lbl_TextLife.Text += "X ";
                    }
                }
                //textLife += "\n";
                //textLife.AppendLine(row);
                lbl_TextLife.Text += "\n";
            }

            //lbl_TextLife.Text = textLife.ToString();
        }
    }
}
