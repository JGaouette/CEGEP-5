namespace Atelier_04
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
      this.lstFilms = new System.Windows.Forms.ListView();
      this.txtFilm = new System.Windows.Forms.Label();
      this.txtAct = new System.Windows.Forms.Label();
      this.lstAct = new System.Windows.Forms.ListView();
      this.lstDist = new System.Windows.Forms.ListView();
      this.btnAjouter = new System.Windows.Forms.Button();
      this.btnSupprimer = new System.Windows.Forms.Button();
      this.txtDist = new System.Windows.Forms.Label();
      this.txtRole = new System.Windows.Forms.Label();
      this.txbRole = new System.Windows.Forms.TextBox();
      this.SuspendLayout();
      // 
      // lstFilms
      // 
      this.lstFilms.Location = new System.Drawing.Point(104, 90);
      this.lstFilms.Name = "lstFilms";
      this.lstFilms.Size = new System.Drawing.Size(288, 518);
      this.lstFilms.TabIndex = 0;
      this.lstFilms.UseCompatibleStateImageBehavior = false;
      this.lstFilms.SelectedIndexChanged += new System.EventHandler(this.lstFilms_SelectedIndexChanged);
      // 
      // txtFilm
      // 
      this.txtFilm.AutoSize = true;
      this.txtFilm.Font = new System.Drawing.Font("Segoe UI", 15F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
      this.txtFilm.Location = new System.Drawing.Point(104, 37);
      this.txtFilm.Name = "txtFilm";
      this.txtFilm.Size = new System.Drawing.Size(86, 41);
      this.txtFilm.TabIndex = 1;
      this.txtFilm.Text = "Films";
      // 
      // txtAct
      // 
      this.txtAct.AutoSize = true;
      this.txtAct.Font = new System.Drawing.Font("Segoe UI", 15F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
      this.txtAct.Location = new System.Drawing.Point(477, 37);
      this.txtAct.Name = "txtAct";
      this.txtAct.Size = new System.Drawing.Size(117, 41);
      this.txtAct.TabIndex = 3;
      this.txtAct.Text = "Acteurs";
      // 
      // lstAct
      // 
      this.lstAct.Location = new System.Drawing.Point(477, 90);
      this.lstAct.Name = "lstAct";
      this.lstAct.Size = new System.Drawing.Size(288, 518);
      this.lstAct.TabIndex = 2;
      this.lstAct.UseCompatibleStateImageBehavior = false;
      // 
      // lstDist
      // 
      this.lstDist.Location = new System.Drawing.Point(104, 688);
      this.lstDist.Name = "lstDist";
      this.lstDist.Size = new System.Drawing.Size(505, 176);
      this.lstDist.TabIndex = 4;
      this.lstDist.UseCompatibleStateImageBehavior = false;
      this.lstDist.SelectedIndexChanged += new System.EventHandler(this.lstDist_SelectedIndexChanged);
      // 
      // btnAjouter
      // 
      this.btnAjouter.Location = new System.Drawing.Point(653, 724);
      this.btnAjouter.Name = "btnAjouter";
      this.btnAjouter.Size = new System.Drawing.Size(112, 34);
      this.btnAjouter.TabIndex = 5;
      this.btnAjouter.Text = "Ajouter";
      this.btnAjouter.UseVisualStyleBackColor = true;
      this.btnAjouter.Click += new System.EventHandler(this.btnAjouter_Click);
      // 
      // btnSupprimer
      // 
      this.btnSupprimer.Location = new System.Drawing.Point(653, 791);
      this.btnSupprimer.Name = "btnSupprimer";
      this.btnSupprimer.Size = new System.Drawing.Size(112, 34);
      this.btnSupprimer.TabIndex = 6;
      this.btnSupprimer.Text = "Supprimer";
      this.btnSupprimer.UseVisualStyleBackColor = true;
      this.btnSupprimer.Click += new System.EventHandler(this.btnSupprimer_Click);
      // 
      // txtDist
      // 
      this.txtDist.AutoSize = true;
      this.txtDist.Font = new System.Drawing.Font("Segoe UI", 15F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
      this.txtDist.Location = new System.Drawing.Point(104, 633);
      this.txtDist.Name = "txtDist";
      this.txtDist.Size = new System.Drawing.Size(173, 41);
      this.txtDist.TabIndex = 7;
      this.txtDist.Text = "Distribution";
      // 
      // txtRole
      // 
      this.txtRole.AutoSize = true;
      this.txtRole.Font = new System.Drawing.Font("Segoe UI", 15F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
      this.txtRole.Location = new System.Drawing.Point(104, 883);
      this.txtRole.Name = "txtRole";
      this.txtRole.Size = new System.Drawing.Size(76, 41);
      this.txtRole.TabIndex = 8;
      this.txtRole.Text = "Rôle";
      // 
      // txbRole
      // 
      this.txbRole.Location = new System.Drawing.Point(215, 893);
      this.txbRole.Name = "txbRole";
      this.txbRole.Size = new System.Drawing.Size(550, 31);
      this.txbRole.TabIndex = 9;
      // 
      // Form1
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF(10F, 25F);
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.ClientSize = new System.Drawing.Size(999, 995);
      this.Controls.Add(this.txbRole);
      this.Controls.Add(this.txtRole);
      this.Controls.Add(this.txtDist);
      this.Controls.Add(this.btnSupprimer);
      this.Controls.Add(this.btnAjouter);
      this.Controls.Add(this.lstDist);
      this.Controls.Add(this.txtAct);
      this.Controls.Add(this.lstAct);
      this.Controls.Add(this.txtFilm);
      this.Controls.Add(this.lstFilms);
      this.Name = "Form1";
      this.Text = "Form1";
      this.Load += new System.EventHandler(this.Form1_Load);
      this.ResumeLayout(false);
      this.PerformLayout();

        }

        #endregion

        private ListView lstFilms;
        private Label txtFilm;
        private Label txtAct;
        private ListView lstAct;
        private ListView lstDist;
        private Button btnAjouter;
        private Button btnSupprimer;
        private Label txtDist;
        private Label txtRole;
        private TextBox txbRole;
    }
}