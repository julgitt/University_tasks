namespace Task1List7
{
    public partial class Form1 : Form
    {
        private System.Windows.Forms.Timer timer;
        public Form1()
        {
            InitializeComponent();

            timer = new System.Windows.Forms.Timer();
            timer.Interval = 1000; // Co sekund�
            timer.Tick += Timer_Tick;
            timer.Start();
        }
        private void Timer_Tick(object sender, EventArgs e)
        {
            this.Invalidate(); // Od�wie�enie widoku zegara co sekund�
        }

        private void AnalogClock_Paint(object sender, PaintEventArgs e)
        {
            Graphics g = e.Graphics;
            int centerX = this.ClientSize.Width / 2;
            int centerY = this.ClientSize.Height / 2;
            int radius = Math.Min(centerX, centerY);

            // Rysowanie tarczy zegara
            g.FillEllipse(Brushes.LightGray, centerX - radius, centerY - radius, 2 * radius, 2 * radius);
            g.DrawEllipse(Pens.Black, centerX - radius, centerY - radius, 2 * radius, 2 * radius);

            // Pobranie bie��cego czasu
            DateTime now = DateTime.Now;
            int hour = now.Hour % 12; // Zegar analogowy ma tylko 12 godzin
            int minute = now.Minute;
            int second = now.Second;

            // Rysowanie wskaz�wek godzinowych
            int hourHandLength = radius * 3 / 10; // D�ugo�� wskaz�wki godzinowej
            // 360 / 12  = 30, 60 / 2 = 30
            int hourHandAngle = (hour * 30) + (minute / 2); // K�t wskaz�wki godzinowej
            DrawHand(g, centerX, centerY, hourHandLength, hourHandAngle, Pens.Black);

            // Rysowanie wskaz�wek minutowych
            int minuteHandLength = radius * 4 / 10; // D�ugo�� wskaz�wki minutowej
            // 360 / 60 = 6, 60 / 6 = 10
            int minuteHandAngle = (minute * 6) + (second / 10); // K�t wskaz�wki minutowej
            DrawHand(g, centerX, centerY, minuteHandLength, minuteHandAngle, Pens.Black);

            // Rysowanie wskaz�wek sekundowych
            int secondHandLength = radius * 45 / 100; // D�ugo�� wskaz�wki sekundowej
            int secondHandAngle = second * 6; // K�t wskaz�wki sekundowej
            DrawHand(g, centerX, centerY, secondHandLength, secondHandAngle, Pens.Red);
        }

        private void DrawHand(Graphics g, int centerX, int centerY, int length, int angle, Pen pen)
        {
            double radians = angle * Math.PI / 180;
            int x = (int)(centerX + length * Math.Sin(radians));
            int y = (int)(centerY - length * Math.Cos(radians));

            g.DrawLine(pen, centerX, centerY, x, y);
        }

        protected override void OnResize(EventArgs e)
        {
            this.Invalidate(); // Od�wie�enie widoku zegara po zmianie rozmiaru okna
            base.OnResize(e);
        }
    }
}