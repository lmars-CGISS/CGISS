using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace GISDataTranslate
{
    partial class FormBatch : Form
    {
        public FormBatch()
        {
            InitializeComponent();
            dataGridView1.Columns[0].Width = dataGridView1.Width / 3;
            dataGridView1.Columns[1].Width = 100;
            dataGridView1.Columns[2].Width = dataGridView1.Width * 2 / 3 - 120;

            dataGridView1.CellEndEdit += new DataGridViewCellEventHandler(dataGridView1_CellEndEdit);
        }

        void dataGridView1_CellEndEdit(object sender, DataGridViewCellEventArgs e)
        {
            if (m_InnerFlag)
                return;
            if (e.ColumnIndex != 2)
                return;
            DataGridViewRow row = dataGridView1.Rows[e.RowIndex];
            KeyValuePair<StorageInformation, Addon> tag = (KeyValuePair<StorageInformation, Addon>)row.Tag;
            if (tag.Key.ContainsKey("Ouput"))
                tag.Key["Output"] = row.Cells[e.ColumnIndex].Value.ToString();
            else
                tag.Key.Server = row.Cells[e.ColumnIndex].Value.ToString();

        }
        bool m_InnerFlag = false;
        public List< KeyValuePair<string, Addon>> SelectBatch()
        {
            if (this.ShowDialog() != System.Windows.Forms.DialogResult.OK)
                return null;
            if (dataGridView1.Rows.Count == 0)
                return null;
            List<KeyValuePair<string, Addon>> vList = new List<KeyValuePair<string, Addon>>();
            foreach (DataGridViewRow item in dataGridView1.Rows)
            {
                KeyValuePair<StorageInformation, Addon> tag = (KeyValuePair<StorageInformation, Addon>)item.Tag;
                vList.Add(new KeyValuePair<string, Addon>(tag.Key.ToString(), tag.Value));
            }
            return vList;

        }

        void Append(List<KeyValuePair<StorageInformation, Addon>> vList)
        {
            m_InnerFlag = true;
            foreach (var item in vList)
            {
                int i = dataGridView1.Rows.Add();
                DataGridViewRow row = dataGridView1.Rows[i];
                row.Tag = item;
                row.Cells[1].Value = item.Value.Type.ToReadableString();
                
                if (item.Value.IsRead)
                {
                    row.Cells[0].Value = item.Key.Server;
                    row.Cells[2].Value = item.Key["Output"];
                }
                else
                {
                    row.Cells[0].Value = item.Key["Input"];
                    row.Cells[2].Value = item.Key.Server;
                }

            }
            m_InnerFlag = false;
        }
        private void buttonImportVector_Click(object sender, EventArgs e)
        {
            using (FormTranslate f = new FormTranslate())
            {
                List<KeyValuePair<StorageInformation, Addon>> vList = f.DoTranslateBatch(true, true);
                if (vList != null)
                    Append(vList);
            }
        }

        private void buttonExportVector_Click(object sender, EventArgs e)
        {
            using (FormTranslate f = new FormTranslate())
            {
                List<KeyValuePair<StorageInformation, Addon>> vList = f.DoTranslateBatch(false, true);
                if (vList != null)
                    Append(vList);
            }
        }

        private void buttonImportRaster_Click(object sender, EventArgs e)
        {
            using (FormTranslate f = new FormTranslate())
            {
                List<KeyValuePair<StorageInformation, Addon>> vList = f.DoTranslateBatch(true, false);
                if (vList != null)
                    Append(vList);
            }
        }

        private void buttonExportRaster_Click(object sender, EventArgs e)
        {
            using (FormTranslate f = new FormTranslate())
            {
                List<KeyValuePair<StorageInformation, Addon>> vList = f.DoTranslateBatch(false, false);
                if (vList != null)
                    Append(vList);
            }
        }

        private void buttonDelete_Click(object sender, EventArgs e)
        {
            List<DataGridViewRow> vList = new List<DataGridViewRow>();
            foreach (DataGridViewRow item in dataGridView1.SelectedRows)
            {
                vList.Add(item);
            }
            if (vList.Count == 0)
                return;
            foreach (var item in vList)
            {
                dataGridView1.Rows.Remove(item);
            }
        }

    }
}
