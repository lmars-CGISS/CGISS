namespace GISDataTranslate
{
    partial class FormBatch
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
            this.dataGridView1 = new System.Windows.Forms.DataGridView();
            this.InputPath = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Format = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Output = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.buttonOk = new System.Windows.Forms.Button();
            this.buttonCanel = new System.Windows.Forms.Button();
            this.buttonImportVector = new System.Windows.Forms.Button();
            this.buttonExportVector = new System.Windows.Forms.Button();
            this.buttonImportRaster = new System.Windows.Forms.Button();
            this.buttonExportRaster = new System.Windows.Forms.Button();
            this.buttonDelete = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).BeginInit();
            this.SuspendLayout();
            // 
            // dataGridView1
            // 
            this.dataGridView1.AllowUserToAddRows = false;
            this.dataGridView1.AllowUserToDeleteRows = false;
            this.dataGridView1.BackgroundColor = System.Drawing.SystemColors.Control;
            this.dataGridView1.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView1.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.InputPath,
            this.Format,
            this.Output});
            this.dataGridView1.Location = new System.Drawing.Point(12, 12);
            this.dataGridView1.Name = "dataGridView1";
            this.dataGridView1.RowHeadersVisible = false;
            this.dataGridView1.RowTemplate.Height = 23;
            this.dataGridView1.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
            this.dataGridView1.Size = new System.Drawing.Size(593, 267);
            this.dataGridView1.TabIndex = 0;
            // 
            // InputPath
            // 
            this.InputPath.HeaderText = "输入";
            this.InputPath.Name = "InputPath";
            this.InputPath.ReadOnly = true;
            // 
            // Format
            // 
            this.Format.HeaderText = "格式";
            this.Format.Name = "Format";
            this.Format.ReadOnly = true;
            this.Format.Resizable = System.Windows.Forms.DataGridViewTriState.True;
            this.Format.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
            // 
            // Output
            // 
            this.Output.HeaderText = "输出";
            this.Output.Name = "Output";
            // 
            // buttonOk
            // 
            this.buttonOk.DialogResult = System.Windows.Forms.DialogResult.OK;
            this.buttonOk.Location = new System.Drawing.Point(530, 285);
            this.buttonOk.Name = "buttonOk";
            this.buttonOk.Size = new System.Drawing.Size(75, 23);
            this.buttonOk.TabIndex = 7;
            this.buttonOk.Text = "确定";
            this.buttonOk.UseVisualStyleBackColor = true;
            // 
            // buttonCanel
            // 
            this.buttonCanel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.buttonCanel.Location = new System.Drawing.Point(611, 285);
            this.buttonCanel.Name = "buttonCanel";
            this.buttonCanel.Size = new System.Drawing.Size(75, 23);
            this.buttonCanel.TabIndex = 8;
            this.buttonCanel.Text = "取消";
            this.buttonCanel.UseVisualStyleBackColor = true;
            // 
            // buttonImportVector
            // 
            this.buttonImportVector.Location = new System.Drawing.Point(611, 12);
            this.buttonImportVector.Name = "buttonImportVector";
            this.buttonImportVector.Size = new System.Drawing.Size(75, 23);
            this.buttonImportVector.TabIndex = 8;
            this.buttonImportVector.Text = "转入矢量";
            this.buttonImportVector.UseVisualStyleBackColor = true;
            this.buttonImportVector.Click += new System.EventHandler(this.buttonImportVector_Click);
            // 
            // buttonExportVector
            // 
            this.buttonExportVector.Location = new System.Drawing.Point(611, 41);
            this.buttonExportVector.Name = "buttonExportVector";
            this.buttonExportVector.Size = new System.Drawing.Size(75, 23);
            this.buttonExportVector.TabIndex = 8;
            this.buttonExportVector.Text = "转出矢量";
            this.buttonExportVector.UseVisualStyleBackColor = true;
            this.buttonExportVector.Click += new System.EventHandler(this.buttonExportVector_Click);
            // 
            // buttonImportRaster
            // 
            this.buttonImportRaster.Location = new System.Drawing.Point(611, 70);
            this.buttonImportRaster.Name = "buttonImportRaster";
            this.buttonImportRaster.Size = new System.Drawing.Size(75, 23);
            this.buttonImportRaster.TabIndex = 8;
            this.buttonImportRaster.Text = "转入栅格";
            this.buttonImportRaster.UseVisualStyleBackColor = true;
            this.buttonImportRaster.Click += new System.EventHandler(this.buttonImportRaster_Click);
            // 
            // buttonExportRaster
            // 
            this.buttonExportRaster.Location = new System.Drawing.Point(611, 99);
            this.buttonExportRaster.Name = "buttonExportRaster";
            this.buttonExportRaster.Size = new System.Drawing.Size(75, 23);
            this.buttonExportRaster.TabIndex = 8;
            this.buttonExportRaster.Text = "转出栅格";
            this.buttonExportRaster.UseVisualStyleBackColor = true;
            this.buttonExportRaster.Click += new System.EventHandler(this.buttonExportRaster_Click);
            // 
            // buttonDelete
            // 
            this.buttonDelete.Location = new System.Drawing.Point(611, 238);
            this.buttonDelete.Name = "buttonDelete";
            this.buttonDelete.Size = new System.Drawing.Size(75, 23);
            this.buttonDelete.TabIndex = 8;
            this.buttonDelete.Text = "删除";
            this.buttonDelete.UseVisualStyleBackColor = true;
            this.buttonDelete.Click += new System.EventHandler(this.buttonDelete_Click);
            // 
            // FormBatch
            // 
            this.AcceptButton = this.buttonOk;
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.CancelButton = this.buttonCanel;
            this.ClientSize = new System.Drawing.Size(698, 319);
            this.Controls.Add(this.buttonOk);
            this.Controls.Add(this.buttonImportVector);
            this.Controls.Add(this.buttonDelete);
            this.Controls.Add(this.buttonExportRaster);
            this.Controls.Add(this.buttonImportRaster);
            this.Controls.Add(this.buttonExportVector);
            this.Controls.Add(this.buttonCanel);
            this.Controls.Add(this.dataGridView1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "FormBatch";
            this.ShowIcon = false;
            this.ShowInTaskbar = false;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "批量转换";
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.DataGridView dataGridView1;
        private System.Windows.Forms.Button buttonOk;
        private System.Windows.Forms.Button buttonCanel;
        private System.Windows.Forms.Button buttonImportVector;
        private System.Windows.Forms.Button buttonExportVector;
        private System.Windows.Forms.Button buttonImportRaster;
        private System.Windows.Forms.Button buttonExportRaster;
        private System.Windows.Forms.Button buttonDelete;
        private System.Windows.Forms.DataGridViewTextBoxColumn InputPath;
        private System.Windows.Forms.DataGridViewTextBoxColumn Format;
        private System.Windows.Forms.DataGridViewTextBoxColumn Output;
    }
}