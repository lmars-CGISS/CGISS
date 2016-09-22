using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace GISDataTranslate
{
    /// <summary>
    /// 游标管理器。
    /// </summary>
    class CursorMgr
    {
        /// <summary>
        /// 构造。
        /// </summary>
        /// <param name="c"></param>
        public CursorMgr(GeoStar.Utility.Config c)
        {
            foreach (GeoStar.Utility.Config item in c)
            {
                Add(item);    
            }
        }

        /// <summary>
        /// 创建一个游标。要么用系统要么用文件的。
        /// </summary>
        /// <param name="str"></param>
        /// <returns></returns>
        System.Windows.Forms.Cursor Create(string str)
        {
            if (String.Compare(str, "Hand",true) ==0 )
                return System.Windows.Forms.Cursors.Hand;
            else  if (String.Compare(str, "Cross",true) ==0)
                return System.Windows.Forms.Cursors.Cross;
            else if (String.Compare(str, "Default", true) == 0)
                return System.Windows.Forms.Cursors.Default;
            if (!System.IO.Path.IsPathRooted(str))
                str = System.IO.Path.GetFullPath(str);
            if (System.IO.File.Exists(str))
            {
                try
                {
                    return new System.Windows.Forms.Cursor(str);
                }
                catch
                {
                }
            }

            return null;
        }
        /// <summary>
        /// 根据配置添加一个游标
        /// </summary>
        /// <param name="c"></param>
        void Add(GeoStar.Utility.Config c)
        {
            string strVal = c.StringValue("");
            if (string.IsNullOrEmpty(strVal))
                return;
            System.Windows.Forms.Cursor cur = Create(strVal);
            if (null == cur)
                return;
            m_Dic[c.Name] = cur;
        }
        /// <summary>
        /// 缓存所有的游标
        /// </summary>
        Dictionary<string, System.Windows.Forms.Cursor> m_Dic = new Dictionary<string, System.Windows.Forms.Cursor>(
            StringComparer.CurrentCultureIgnoreCase);
        /// <summary>
        /// 根据Key获取一个游标。
        /// </summary>
        /// <param name="key"></param>
        /// <returns></returns>
        public System.Windows.Forms.Cursor Cursor(string key)
        {
            if (m_Dic.ContainsKey(key))
                return m_Dic[key];
            return System.Windows.Forms.Cursors.Default;
        }
    }
    /// <summary>
    /// 用于等待的游标采用using语法
    /// using (WaitCursor c = new WaitCursor())
    /// {
    ///      .......Something busy
    /// }
    /// </summary>
    class WaitCursor:IDisposable
    {
        System.Windows.Forms.Cursor m_Current;
        public WaitCursor()
        {
            m_Current = System.Windows.Forms.Cursor.Current;
            System.Windows.Forms.Cursor.Current =
                System.Windows.Forms.Cursors.WaitCursor;
        }


        public void Dispose()
        {
            System.Windows.Forms.Cursor.Current = m_Current;
        }
    };

}
