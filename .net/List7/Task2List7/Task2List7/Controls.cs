using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Task2List7
{
    public class SmoothProgressBar : Control
    {
        private int minimum;
        private int maximum;
        private int value;

        public int Minimum
        {
            get { return minimum; }
            set
            {
                minimum = value;
                Invalidate();
            }
        }

        public int Maximum
        {
            get { return maximum; }
            set
            {
                maximum = value;
                Invalidate();
            }
        }

        public int Value
        {
            get { return value; }
            set
            {
                this.value = value;
                Invalidate();
            }
        }

        public SmoothProgressBar()
        {
            minimum = 0;
            maximum = 100;
            value = 0;
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            base.OnPaint(e);

            Graphics graphics = e.Graphics;
            Rectangle progressBarRect = new Rectangle(ClientRectangle.X, ClientRectangle.Y,
                ClientRectangle.Width, ClientRectangle.Height);

            // Draw background
            graphics.FillRectangle(Brushes.LightGray, progressBarRect);

            // Calculate progress
            int progressWidth = (int)((value - minimum) / (double)(maximum - minimum) * progressBarRect.Width);

            // Draw progress bar
            Rectangle progressRect = new Rectangle(progressBarRect.X, progressBarRect.Y,
                progressWidth, progressBarRect.Height);

            graphics.FillRectangle(Brushes.Blue, progressRect);
        }
    }
}
      
