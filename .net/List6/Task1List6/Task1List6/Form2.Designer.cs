namespace Task1List6
{
    partial class Form2
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
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
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            splitContainer1 = new SplitContainer();
            label_infoUczelnia = new Label();
            button_ok = new Button();
            ((System.ComponentModel.ISupportInitialize)splitContainer1).BeginInit();
            splitContainer1.Panel1.SuspendLayout();
            splitContainer1.Panel2.SuspendLayout();
            splitContainer1.SuspendLayout();
            SuspendLayout();
            // 
            // splitContainer1
            // 
            splitContainer1.Dock = DockStyle.Fill;
            splitContainer1.Location = new Point(0, 0);
            splitContainer1.Name = "splitContainer1";
            splitContainer1.Orientation = Orientation.Horizontal;
            // 
            // splitContainer1.Panel1
            // 
            splitContainer1.Panel1.Controls.Add(label_infoUczelnia);
            splitContainer1.Panel1.Padding = new Padding(10);
            // 
            // splitContainer1.Panel2
            // 
            splitContainer1.Panel2.Controls.Add(button_ok);
            splitContainer1.Size = new Size(458, 304);
            splitContainer1.SplitterDistance = 218;
            splitContainer1.TabIndex = 0;
            // 
            // label_infoUczelnia
            // 
            label_infoUczelnia.AutoSize = true;
            label_infoUczelnia.Dock = DockStyle.Fill;
            label_infoUczelnia.Location = new Point(10, 10);
            label_infoUczelnia.Name = "label_infoUczelnia";
            label_infoUczelnia.Size = new Size(49, 25);
            label_infoUczelnia.TabIndex = 0;
            label_infoUczelnia.Text = "label";
            // 
            // button_ok
            // 
            button_ok.Anchor = AnchorStyles.Top | AnchorStyles.Left | AnchorStyles.Right;
            button_ok.Location = new Point(190, 25);
            button_ok.Name = "button_ok";
            button_ok.Size = new Size(93, 36);
            button_ok.TabIndex = 1;
            button_ok.Text = "OK";
            button_ok.UseVisualStyleBackColor = true;
            button_ok.Click += button_ok_Click;
            // 
            // Form2
            // 
            AcceptButton = button_ok;
            AutoScaleDimensions = new SizeF(10F, 25F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(458, 304);
            Controls.Add(splitContainer1);
            FormBorderStyle = FormBorderStyle.FixedDialog;
            MaximizeBox = false;
            MinimizeBox = false;
            Name = "Form2";
            StartPosition = FormStartPosition.CenterScreen;
            Text = "Uczelnia";
            splitContainer1.Panel1.ResumeLayout(false);
            splitContainer1.Panel1.PerformLayout();
            splitContainer1.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)splitContainer1).EndInit();
            splitContainer1.ResumeLayout(false);
            ResumeLayout(false);
        }

        #endregion

        private SplitContainer splitContainer1;
        private Button button_ok;
        private Label label_infoUczelnia;
    }
}