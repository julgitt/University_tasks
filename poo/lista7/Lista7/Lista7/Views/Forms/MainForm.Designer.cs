using Lista7.ViewModels.Classes.Notifications;
using Lista7.ViewModels.Classes;
using Lista7.ViewModels;
using Microsoft.VisualBasic.ApplicationServices;
using Lista7.Models;
using Lista7.Repositories;

namespace Lista7
{
    partial class MainForm
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
            TreeNode treeNode1 = new TreeNode("Jan Kowalski");
            TreeNode treeNode2 = new TreeNode("Studenci", new TreeNode[] { treeNode1 });
            TreeNode treeNode3 = new TreeNode("Bożydar Adamski");
            TreeNode treeNode4 = new TreeNode("Wykładowcy", new TreeNode[] { treeNode3 });
            splitContainer1 = new SplitContainer();
            treeView1 = new TreeView();
            dataGridView1 = new DataGridView();
            surname = new DataGridViewTextBoxColumn();
            name = new DataGridViewTextBoxColumn();
            birthdate = new DataGridViewTextBoxColumn();
            adress = new DataGridViewTextBoxColumn();
            backgroundWorker1 = new System.ComponentModel.BackgroundWorker();
            ((System.ComponentModel.ISupportInitialize)splitContainer1).BeginInit();
            splitContainer1.Panel1.SuspendLayout();
            splitContainer1.Panel2.SuspendLayout();
            splitContainer1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)dataGridView1).BeginInit();
            SuspendLayout();
            // 
            // splitContainer1
            // 
            splitContainer1.Dock = DockStyle.Fill;
            splitContainer1.Location = new Point(0, 0);
            splitContainer1.Name = "splitContainer1";
            // 
            // splitContainer1.Panel1
            // 
            splitContainer1.Panel1.Controls.Add(treeView1);
            // 
            // splitContainer1.Panel2
            // 
            splitContainer1.Panel2.Controls.Add(dataGridView1);
            splitContainer1.Size = new Size(1221, 473);
            splitContainer1.SplitterDistance = 345;
            splitContainer1.TabIndex = 0;
            // 
            // treeView1
            // 
            treeView1.Anchor = AnchorStyles.Top | AnchorStyles.Left | AnchorStyles.Right;
            treeView1.Location = new Point(35, 12);
            treeView1.Name = "treeView1";
            treeNode1.Name = "jan_kowalski";
            treeNode1.Tag = "1";
            treeNode1.Text = "Jan Kowalski";
            treeNode2.Name = "Studenci";
            treeNode2.Tag = "students";
            treeNode2.Text = "Studenci";
            treeNode3.Name = "bozydar_adamski";
            treeNode3.Tag = "1";
            treeNode3.Text = "Bożydar Adamski";
            treeNode4.Name = "teachers";
            treeNode4.Tag = "teachers";
            treeNode4.Text = "Wykładowcy";
            treeView1.Nodes.AddRange(new TreeNode[] { treeNode2, treeNode4 });
            treeView1.Size = new Size(272, 426);
            treeView1.TabIndex = 0;
            treeView1.AfterSelect += treeViewCategories_AfterSelect;
            treeView1.AfterSelect += treeViewUsers_SelectedIndexChanged;
            // 
            // dataGridView1
            // 
            dataGridView1.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            dataGridView1.Columns.AddRange(new DataGridViewColumn[] { });
            dataGridView1.Dock = DockStyle.Fill;
            dataGridView1.Location = new Point(0, 0);
            dataGridView1.Name = "dataGridView1";
            dataGridView1.RowHeadersWidth = 62;
            dataGridView1.RowTemplate.Height = 33;
            dataGridView1.Size = new Size(872, 473);
            dataGridView1.TabIndex = 0;
            // 
            // MainForm
            // 
            AutoScaleDimensions = new SizeF(10F, 25F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(1221, 473);
            Controls.Add(splitContainer1);
            Name = "MainForm";
            Text = "Kartoteka";
            splitContainer1.Panel1.ResumeLayout(false);
            splitContainer1.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)splitContainer1).EndInit();
            splitContainer1.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)dataGridView1).EndInit();
            ResumeLayout(false);
        }

        #endregion

        private SplitContainer splitContainer1;
        private TreeView treeView1;
        private DataGridView dataGridView1;
        private System.ComponentModel.BackgroundWorker backgroundWorker1;
        private DataGridViewTextBoxColumn surname;
        private DataGridViewTextBoxColumn name;
        private DataGridViewTextBoxColumn birthdate;
        private DataGridViewTextBoxColumn adress;
    }
}