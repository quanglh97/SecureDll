namespace BuildData
{
    partial class BuildData
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(BuildData));
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.md5Tbox = new System.Windows.Forms.TextBox();
            this.vipTbox = new System.Windows.Forms.TextBox();
            this.normalTbox = new System.Windows.Forms.TextBox();
            this.BuildBtn = new System.Windows.Forms.Button();
            this.CopyNormalBtn = new System.Windows.Forms.Button();
            this.CopyVipBtn = new System.Windows.Forms.Button();
            this.RawPrxTbox = new System.Windows.Forms.TextBox();
            this.GenPrxTBox = new System.Windows.Forms.TextBox();
            this.GenProxyBtn = new System.Windows.Forms.Button();
            this.CopyProxyGenBtn = new System.Windows.Forms.Button();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(99, 57);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(30, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "MD5";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(99, 97);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(85, 13);
            this.label2.TabIndex = 1;
            this.label2.Text = "DATA NORMAL";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(99, 143);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(56, 13);
            this.label3.TabIndex = 2;
            this.label3.Text = "DATA VIP";
            // 
            // md5Tbox
            // 
            this.md5Tbox.Location = new System.Drawing.Point(186, 50);
            this.md5Tbox.Name = "md5Tbox";
            this.md5Tbox.Size = new System.Drawing.Size(437, 20);
            this.md5Tbox.TabIndex = 3;
            // 
            // vipTbox
            // 
            this.vipTbox.Location = new System.Drawing.Point(186, 140);
            this.vipTbox.Name = "vipTbox";
            this.vipTbox.Size = new System.Drawing.Size(437, 20);
            this.vipTbox.TabIndex = 4;
            // 
            // normalTbox
            // 
            this.normalTbox.Location = new System.Drawing.Point(186, 94);
            this.normalTbox.Name = "normalTbox";
            this.normalTbox.Size = new System.Drawing.Size(437, 20);
            this.normalTbox.TabIndex = 5;
            // 
            // BuildBtn
            // 
            this.BuildBtn.Location = new System.Drawing.Point(658, 50);
            this.BuildBtn.Name = "BuildBtn";
            this.BuildBtn.Size = new System.Drawing.Size(75, 23);
            this.BuildBtn.TabIndex = 6;
            this.BuildBtn.Text = "Build";
            this.BuildBtn.UseVisualStyleBackColor = true;
            this.BuildBtn.Click += new System.EventHandler(this.BuildBtn_Click);
            // 
            // CopyNormalBtn
            // 
            this.CopyNormalBtn.Location = new System.Drawing.Point(658, 94);
            this.CopyNormalBtn.Name = "CopyNormalBtn";
            this.CopyNormalBtn.Size = new System.Drawing.Size(75, 23);
            this.CopyNormalBtn.TabIndex = 7;
            this.CopyNormalBtn.Text = "copy";
            this.CopyNormalBtn.UseVisualStyleBackColor = true;
            this.CopyNormalBtn.Click += new System.EventHandler(this.CopyNormalBtn_Click);
            // 
            // CopyVipBtn
            // 
            this.CopyVipBtn.Location = new System.Drawing.Point(658, 140);
            this.CopyVipBtn.Name = "CopyVipBtn";
            this.CopyVipBtn.Size = new System.Drawing.Size(75, 23);
            this.CopyVipBtn.TabIndex = 8;
            this.CopyVipBtn.Text = "copy";
            this.CopyVipBtn.UseVisualStyleBackColor = true;
            this.CopyVipBtn.Click += new System.EventHandler(this.CopyVipBtn_Click);
            // 
            // RawPrxTbox
            // 
            this.RawPrxTbox.Location = new System.Drawing.Point(12, 193);
            this.RawPrxTbox.Multiline = true;
            this.RawPrxTbox.Name = "RawPrxTbox";
            this.RawPrxTbox.Size = new System.Drawing.Size(352, 245);
            this.RawPrxTbox.TabIndex = 9;
            // 
            // GenPrxTBox
            // 
            this.GenPrxTBox.Location = new System.Drawing.Point(436, 193);
            this.GenPrxTBox.Multiline = true;
            this.GenPrxTBox.Name = "GenPrxTBox";
            this.GenPrxTBox.Size = new System.Drawing.Size(352, 245);
            this.GenPrxTBox.TabIndex = 10;
            // 
            // GenProxyBtn
            // 
            this.GenProxyBtn.Location = new System.Drawing.Point(369, 193);
            this.GenProxyBtn.Name = "GenProxyBtn";
            this.GenProxyBtn.Size = new System.Drawing.Size(61, 23);
            this.GenProxyBtn.TabIndex = 11;
            this.GenProxyBtn.Text = "Gen";
            this.GenProxyBtn.UseVisualStyleBackColor = true;
            this.GenProxyBtn.Click += new System.EventHandler(this.GenProxyBtn_Click);
            // 
            // CopyProxyGenBtn
            // 
            this.CopyProxyGenBtn.Location = new System.Drawing.Point(369, 280);
            this.CopyProxyGenBtn.Name = "CopyProxyGenBtn";
            this.CopyProxyGenBtn.Size = new System.Drawing.Size(61, 23);
            this.CopyProxyGenBtn.TabIndex = 12;
            this.CopyProxyGenBtn.Text = "Copy";
            this.CopyProxyGenBtn.UseVisualStyleBackColor = true;
            this.CopyProxyGenBtn.Click += new System.EventHandler(this.CopyProxyGenBtn_Click);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(125, 177);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(145, 13);
            this.label4.TabIndex = 13;
            this.label4.Text = "PROXY RAW ( 2-2-2-6-6000)";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(550, 177);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(70, 13);
            this.label5.TabIndex = 14;
            this.label5.Text = "PROXY GEN";
            // 
            // BuildData
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.CopyProxyGenBtn);
            this.Controls.Add(this.GenProxyBtn);
            this.Controls.Add(this.GenPrxTBox);
            this.Controls.Add(this.RawPrxTbox);
            this.Controls.Add(this.CopyVipBtn);
            this.Controls.Add(this.CopyNormalBtn);
            this.Controls.Add(this.BuildBtn);
            this.Controls.Add(this.normalTbox);
            this.Controls.Add(this.vipTbox);
            this.Controls.Add(this.md5Tbox);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "BuildData";
            this.Text = "Buid - Data";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox md5Tbox;
        private System.Windows.Forms.TextBox vipTbox;
        private System.Windows.Forms.TextBox normalTbox;
        private System.Windows.Forms.Button BuildBtn;
        private System.Windows.Forms.Button CopyNormalBtn;
        private System.Windows.Forms.Button CopyVipBtn;
        private System.Windows.Forms.TextBox RawPrxTbox;
        private System.Windows.Forms.TextBox GenPrxTBox;
        private System.Windows.Forms.Button GenProxyBtn;
        private System.Windows.Forms.Button CopyProxyGenBtn;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
    }
}

