namespace Task1List6
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
            splitContainer1 = new SplitContainer();
            groupBox_uczelnia = new GroupBox();
            splitContainer3 = new SplitContainer();
            label1 = new Label();
            textBox_Nazwa = new TextBox();
            label2 = new Label();
            textBox_Adres = new TextBox();
            splitContainer2 = new SplitContainer();
            groupBox3 = new GroupBox();
            splitContainer4 = new SplitContainer();
            label3 = new Label();
            comboBox_cyklNauki = new ComboBox();
            checkBox_uzup = new CheckBox();
            checkBox_dzienne = new CheckBox();
            button_anuluj = new Button();
            button_akceptuj = new Button();
            ((System.ComponentModel.ISupportInitialize)splitContainer1).BeginInit();
            splitContainer1.Panel1.SuspendLayout();
            splitContainer1.Panel2.SuspendLayout();
            splitContainer1.SuspendLayout();
            groupBox_uczelnia.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)splitContainer3).BeginInit();
            splitContainer3.Panel1.SuspendLayout();
            splitContainer3.Panel2.SuspendLayout();
            splitContainer3.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)splitContainer2).BeginInit();
            splitContainer2.Panel1.SuspendLayout();
            splitContainer2.Panel2.SuspendLayout();
            splitContainer2.SuspendLayout();
            groupBox3.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)splitContainer4).BeginInit();
            splitContainer4.Panel1.SuspendLayout();
            splitContainer4.Panel2.SuspendLayout();
            splitContainer4.SuspendLayout();
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
            splitContainer1.Panel1.Controls.Add(groupBox_uczelnia);
            splitContainer1.Panel1.Padding = new Padding(30);
            // 
            // splitContainer1.Panel2
            // 
            splitContainer1.Panel2.Controls.Add(splitContainer2);
            splitContainer1.Size = new Size(990, 593);
            splitContainer1.SplitterDistance = 231;
            splitContainer1.TabIndex = 0;
            // 
            // groupBox_uczelnia
            // 
            groupBox_uczelnia.Controls.Add(splitContainer3);
            groupBox_uczelnia.Dock = DockStyle.Fill;
            groupBox_uczelnia.Location = new Point(30, 30);
            groupBox_uczelnia.Name = "groupBox_uczelnia";
            groupBox_uczelnia.Size = new Size(930, 171);
            groupBox_uczelnia.TabIndex = 0;
            groupBox_uczelnia.TabStop = false;
            groupBox_uczelnia.Text = "Uczelnia";
            // 
            // splitContainer3
            // 
            splitContainer3.Dock = DockStyle.Fill;
            splitContainer3.Location = new Point(3, 27);
            splitContainer3.Name = "splitContainer3";
            splitContainer3.Orientation = Orientation.Horizontal;
            // 
            // splitContainer3.Panel1
            // 
            splitContainer3.Panel1.Controls.Add(label1);
            splitContainer3.Panel1.Controls.Add(textBox_Nazwa);
            splitContainer3.Panel1.Padding = new Padding(150, 15, 300, 15);
            // 
            // splitContainer3.Panel2
            // 
            splitContainer3.Panel2.Controls.Add(label2);
            splitContainer3.Panel2.Controls.Add(textBox_Adres);
            splitContainer3.Panel2.Padding = new Padding(150, 15, 300, 15);
            splitContainer3.Size = new Size(924, 141);
            splitContainer3.SplitterDistance = 70;
            splitContainer3.TabIndex = 2;
            // 
            // label1
            // 
            label1.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left;
            label1.AutoSize = true;
            label1.Location = new Point(60, 18);
            label1.Name = "label1";
            label1.Size = new Size(68, 25);
            label1.TabIndex = 1;
            label1.Text = "Nazwa:";

            // 
            // textBox_Nazwa
            // 
            textBox_Nazwa.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left;
            textBox_Nazwa.Location = new Point(160, 15);
            textBox_Nazwa.Name = "textBox_Nazwa";
            textBox_Nazwa.Size = new Size(624, 31);
            textBox_Nazwa.TabIndex = 0;
            // 
            // label2
            // 
            label2.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left;
            label2.AutoSize = true;
            label2.Location = new Point(60, 23);
            label2.Name = "label2";
            label2.Size = new Size(62, 25);
            label2.TabIndex = 2;
            label2.Text = "Adres:";
            // 
            // textBox_Adres
            // 
            textBox_Adres.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left;
            textBox_Adres.Location = new Point(160, 20);
            textBox_Adres.Name = "textBox_Adres";
            textBox_Adres.Size = new Size(624, 31);
            textBox_Adres.TabIndex = 1;
            // 
            // splitContainer2
            // 
            splitContainer2.Dock = DockStyle.Fill;
            splitContainer2.Location = new Point(0, 0);
            splitContainer2.Name = "splitContainer2";
            splitContainer2.Orientation = Orientation.Horizontal;
            // 
            // splitContainer2.Panel1
            // 
            splitContainer2.Panel1.Controls.Add(groupBox3);
            splitContainer2.Panel1.Padding = new Padding(30);
            // 
            // splitContainer2.Panel2
            // 
            splitContainer2.Panel2.Controls.Add(button_anuluj);
            splitContainer2.Panel2.Controls.Add(button_akceptuj);
            splitContainer2.Panel2.Padding = new Padding(30);
            splitContainer2.Size = new Size(990, 358);
            splitContainer2.SplitterDistance = 236;
            splitContainer2.TabIndex = 0;
            // 
            // groupBox3
            // 
            groupBox3.Controls.Add(splitContainer4);
            groupBox3.Dock = DockStyle.Fill;
            groupBox3.Location = new Point(30, 30);
            groupBox3.Name = "groupBox3";
            groupBox3.Size = new Size(930, 176);
            groupBox3.TabIndex = 0;
            groupBox3.TabStop = false;
            groupBox3.Text = "Rodzaj Studiów";
            // 
            // splitContainer4
            // 
            splitContainer4.Dock = DockStyle.Fill;
            splitContainer4.Location = new Point(3, 27);
            splitContainer4.Name = "splitContainer4";
            splitContainer4.Orientation = Orientation.Horizontal;
            // 
            // splitContainer4.Panel1
            // 
            splitContainer4.Panel1.Controls.Add(label3);
            splitContainer4.Panel1.Controls.Add(comboBox_cyklNauki);
            splitContainer4.Panel1.Padding = new Padding(150, 15, 300, 15);
            // 
            // splitContainer4.Panel2
            // 
            splitContainer4.Panel2.Controls.Add(checkBox_uzup);
            splitContainer4.Panel2.Controls.Add(checkBox_dzienne);
            splitContainer4.Panel2.Padding = new Padding(150, 15, 375, 0);
            splitContainer4.Size = new Size(924, 146);
            splitContainer4.SplitterDistance = 70;
            splitContainer4.TabIndex = 3;
            // 
            // label3
            // 
            label3.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left;
            label3.AutoSize = true;
            label3.Location = new Point(60, 18);
            label3.Name = "label3";
            label3.Size = new Size(93, 25);
            label3.TabIndex = 3;
            label3.Text = "cykl nauki:";
            // 
            // comboBox_cyklNauki
            // 
            comboBox_cyklNauki.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left;
            comboBox_cyklNauki.FormattingEnabled = true;
            comboBox_cyklNauki.Items.AddRange(new object[] { "3-letnie", "5-letnie" });
            comboBox_cyklNauki.Location = new Point(160, 15);
            comboBox_cyklNauki.Name = "comboBox_cyklNauki";
            comboBox_cyklNauki.Size = new Size(624, 33);
            comboBox_cyklNauki.TabIndex = 2;
            // 
            // checkBox_uzup
            // 
            checkBox_uzup.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left;
            checkBox_uzup.AutoSize = true;
            checkBox_uzup.Location = new Point(480, 17);
            checkBox_uzup.Name = "checkBox_uzup";
            checkBox_uzup.Size = new Size(144, 29);
            checkBox_uzup.TabIndex = 1;
            checkBox_uzup.Text = "uzupełniające";
            checkBox_uzup.UseVisualStyleBackColor = true;
            // 
            // checkBox_dzienne
            // 
            checkBox_dzienne.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left;
            checkBox_dzienne.AutoSize = true;
            checkBox_dzienne.Location = new Point(160, 17);
            checkBox_dzienne.Name = "checkBox_dzienne";
            checkBox_dzienne.Size = new Size(99, 29);
            checkBox_dzienne.TabIndex = 0;
            checkBox_dzienne.Text = "dzienne";
            checkBox_dzienne.UseVisualStyleBackColor = true;
            // 
            // button_anuluj
            // 
            button_anuluj.Anchor = AnchorStyles.Top | AnchorStyles.Right;
            button_anuluj.Location = new Point(848, 30);
            button_anuluj.Name = "button_anuluj";
            button_anuluj.Size = new Size(112, 58);
            button_anuluj.TabIndex = 1;
            button_anuluj.Text = "Anuluj";
            button_anuluj.UseVisualStyleBackColor = true;
            button_anuluj.Click += button_anuluj_Click;
            // 
            // button_akceptuj
            // 
            button_akceptuj.Location = new Point(30, 30);
            button_akceptuj.Name = "button_akceptuj";
            button_akceptuj.Size = new Size(112, 58);
            button_akceptuj.TabIndex = 0;
            button_akceptuj.Text = "Akceptuj";
            button_akceptuj.UseVisualStyleBackColor = true;
            button_akceptuj.Click += button_akceptuj_Click;
            // 
            // Form1
            // 
            AcceptButton = button_akceptuj;
            AutoScaleDimensions = new SizeF(144F, 144F);
            AutoScaleMode = AutoScaleMode.Dpi;
            CancelButton = button_anuluj;
            ClientSize = new Size(990, 593);
            Controls.Add(splitContainer1);
            Name = "Form1";
            Text = "Wybór Uczelni";
            splitContainer1.Panel1.ResumeLayout(false);
            splitContainer1.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)splitContainer1).EndInit();
            splitContainer1.ResumeLayout(false);
            groupBox_uczelnia.ResumeLayout(false);
            splitContainer3.Panel1.ResumeLayout(false);
            splitContainer3.Panel1.PerformLayout();
            splitContainer3.Panel2.ResumeLayout(false);
            splitContainer3.Panel2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)splitContainer3).EndInit();
            splitContainer3.ResumeLayout(false);
            splitContainer2.Panel1.ResumeLayout(false);
            splitContainer2.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)splitContainer2).EndInit();
            splitContainer2.ResumeLayout(false);
            groupBox3.ResumeLayout(false);
            splitContainer4.Panel1.ResumeLayout(false);
            splitContainer4.Panel1.PerformLayout();
            splitContainer4.Panel2.ResumeLayout(false);
            splitContainer4.Panel2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)splitContainer4).EndInit();
            splitContainer4.ResumeLayout(false);
            ResumeLayout(false);
        }

        #endregion

        private SplitContainer splitContainer1;
        private SplitContainer splitContainer2;
        private GroupBox groupBox_uczelnia;
        private GroupBox groupBox3;
        private TextBox textBox_Adres;
        private TextBox textBox_Nazwa;
        private ComboBox comboBox_cyklNauki;
        private CheckBox checkBox_uzup;
        private CheckBox checkBox_dzienne;
        private Button button_anuluj;
        private Button button_akceptuj;
        private SplitContainer splitContainer3;
        private SplitContainer splitContainer4;
        private Label label1;
        private Label label2;
        private Label label3;
    }
}