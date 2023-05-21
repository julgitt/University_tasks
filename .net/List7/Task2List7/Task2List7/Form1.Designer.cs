namespace Task2List7
{
    partial class Form1
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            progressBar1 = new ProgressBar();
            smoothProgressBar1 = new SmoothProgressBar();
            SuspendLayout();
            // 
            // progressBar1
            // 
            progressBar1.Location = new Point(282, 212);
            progressBar1.Name = "progressBar1";
            progressBar1.Size = new Size(316, 34);
            progressBar1.TabIndex = 0;
            progressBar1.Value = 44;
            // 
            // smoothProgressBar1
            // 
            smoothProgressBar1.Location = new Point(282, 155);
            smoothProgressBar1.Maximum = 75;
            smoothProgressBar1.Minimum = 25;
            smoothProgressBar1.Name = "smoothProgressBar1";
            smoothProgressBar1.Size = new Size(316, 34);
            smoothProgressBar1.TabIndex = 1;
            smoothProgressBar1.Text = "smoothProgressBar1";
            smoothProgressBar1.Value = 56;
            // 
            // Form1
            // 
            AutoScaleDimensions = new SizeF(10F, 25F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(800, 450);
            Controls.Add(smoothProgressBar1);
            Controls.Add(progressBar1);
            Name = "Form1";
            Text = "Form1";
            ResumeLayout(false);
        }

        #endregion

        private ProgressBar progressBar1;
        private SmoothProgressBar smoothProgressBar1;
    }
}