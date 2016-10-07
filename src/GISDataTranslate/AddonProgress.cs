using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;

namespace GISDataTranslate
{
    /// <summary>
    /// 进度条上下文。
    /// 将插件传递的进度日志信息以安全的方式显示在界面控件中。
    /// </summary>
    class ProgressContext:IDisposable
    {
        System.Windows.Forms.RichTextBox m_Box;
        /// <summary>
        /// 构造。
        /// </summary>
        /// <param name="strTitle"></param>
        /// <param name="strContent"></param>
        /// <param name="box"></param>
        public ProgressContext(string strTitle,string strContent,System.Windows.Forms.RichTextBox box)
        {
            m_Box = box;
            m_strKey = strTitle + "_" + strContent;
            m_strTitle = strTitle;
            m_strContent = strContent;

            //完全委托，初始化
            m_Box.Invoke(new Func<int>(CreateProgressBar));
            //整个过程计时
            m_Watch.Start();
            //两次进度更新之间的计时。
            m_WatchStep.Start();
        }
        string m_strTitle, m_strContent;
        /// <summary>
        /// 初始化进度的安全函数。
        /// </summary>
        /// <returns></returns>
        int CreateProgressBar()
        {
            m_Box.AppendText(m_strTitle + " " + m_strContent);
            m_nStart = m_Box.SelectionStart;
            return m_nStart;
        }
        /// <summary>
        /// 构成日志字符串。
        /// </summary>
        public string Log
        {
            get
            {
                if(m_nTotal <=0)
                    m_strLog = string.Format("\t{0}\t{1}\r\n", m_nPos, m_Watch.Elapsed.ToString());
                return m_strTitle + " " + m_strContent + m_strLog;
            }
        }
        string m_strLog;
        //更新进度时选择的开始位置。
        int m_nStart;

        /// <summary>
        /// 当更新一次进度的时候。
        /// </summary>
        /// <param name="nPos"></param>
        /// <returns></returns>
        int OnProgressBar(long nPos)
        {
            //挂起界面刷新
            m_Box.SuspendLayout();

            //选择一段文本
            m_Box.SelectionStart = m_nStart;
            m_Box.SelectionLength = m_Box.TextLength - m_Box.SelectionStart;
            m_strLog = string.Format("\t{0}%\t{1}\t{2:N0}/{3:N0}\r\n", nPos, m_Watch.Elapsed.ToString(), m_nPos, m_nTotal);
            //替换文本
            m_Box.SelectedText = m_strLog;
            //取消选择
            m_Box.SelectionLength = 0;
            //恢复界面刷新
            m_Box.ResumeLayout();
            //进度显示的开始位置。
            return m_nStart;
        }
        /// <summary>
        /// 当更新进度发生的时候
        /// </summary>
        /// <returns></returns>
        int OnProgressBar()
        {
            return OnProgressBar(m_nPos); 
        }
        string m_strKey;

        /// <summary>
        /// 比较底层显示的进度是否发生了变化。
        /// </summary>
        public bool IsThis(string strKey)
        {
            return string.Compare(m_strKey, strKey, true) == 0;
        }
        
        long m_nTotal = 0;
        long m_nPos = 0;
        long m_nProgres = -1;
        /// <summary>
        /// 当进度改变时判断是否需要更新进度并更新进度。
        /// </summary>
        /// <param name="nPos"></param>
        public void Progress(long nPos)
        {
            if (!NeedUpdate(nPos))
                return;

            m_Box.Invoke(new Func<int>(OnProgressBar));
            //更新界面进度之后重新计时。
            m_WatchStep.Restart();
        }
        /// <summary>
        /// 根据传入的进度判断是否需要更新界面上进度的显示。底层
        /// </summary>
        /// <param name="nPos"></param>
        /// <returns></returns>
        bool NeedUpdate(long nPos)
        {
            //记录进度位置
            m_nPos = nPos;
            //距离上次更新的时间。
            long nTick = m_WatchStep.ElapsedMilliseconds;
            //一秒以内的更新都不需要刷新。太快会闪烁，人眼也识别不清楚。显示效果不好。
            if (nTick < 1000)
                return false;

            //如果前后两次的进度超过了1000则需要更新
            if (nPos - m_nProgres > 1000)
            {
                m_nProgres = nPos;
                return true;
            }
            return false;
        }
        System.Diagnostics.Stopwatch m_WatchStep = new System.Diagnostics.Stopwatch();
        /// <summary>
        /// 是否需要跟新，底层传递当前进度和总进度的时候调用。
        /// </summary>
        /// <param name="nPos"></param>
        /// <param name="nCount"></param>
        /// <returns></returns>
        bool NeedUpdate(long nPos, long nCount)
        {
            //记录基本进度信息
            m_nPos = nPos;
            m_nTotal = nCount;
            long pro = 100 * nPos / nCount;
            //如果进度达到100则一定更新
            if (nPos >= nCount)
            {
                m_nProgres = pro;
                return true;
            }
            //记录当前时间，距离上次更新时间小于1秒则不更新
            long nTick = m_WatchStep.ElapsedMilliseconds;
            if (nTick < 1000)
                return false;
            
            //如果进度发生了变化则更新。
            if (m_nProgres != pro)
            {
                m_nProgres = pro;
                return true;
            }

            return false;
        }
        /// <summary>
        /// 当进度变化时，适用于底层传递了数量和总数。
        /// </summary>
        /// <param name="nPos"></param>
        /// <param name="nCount"></param>
        public void Progress(long nPos, long nCount)
        {
            if (!NeedUpdate(nPos, nCount))
                return;
            
            //如果需要更新则用完全委托更新。
            m_Box.Invoke(new Func<long, int>(OnProgressBar), new object[] { m_nProgres });
            m_WatchStep.Restart();
        }
        /// <summary>
        /// 获取总的转换地物数量。
        /// </summary>
        public long TotalFeature
        {
            get
            {
                if (m_nTotal > 0)
                    return m_nTotal;
                return m_nPos;
            }
        }
        /// <summary>
        /// 总的计时。
        /// </summary>
        System.Diagnostics.Stopwatch m_Watch = new System.Diagnostics.Stopwatch(); 
        public void Dispose()
        {
             
        }
        /// <summary>
        /// 总的转换时间。
        /// </summary>
        public TimeSpan TotalTime
        {
            get
            {
                return m_Watch.Elapsed;
            }
        }
    };
    /// <summary>
    /// 用于和底层C++通讯的进度。
    /// </summary>
    class AddonProgress:GIS.ProgressCallback
    {
        volatile bool m_bBusy = false;
        System.Windows.Forms.RichTextBox m_Box;
        public delegate void LogAppendDelegate(Color color, string text);  

        System.IO.StreamWriter m_Log;
        string m_strLogPath;

        System.Diagnostics.Stopwatch m_Watch = new System.Diagnostics.Stopwatch(); 
        public AddonProgress(System.Windows.Forms.RichTextBox box)
        {
            m_Box = box;

            //日志文件输出路径
            string strPath = System.IO.Path.GetFullPath("..\\log");
            if (!System.IO.Directory.Exists(strPath))
                System.IO.Directory.CreateDirectory(strPath);
            
            DateTime d = DateTime.Now;
            //日志文件
            string strName = string.Format("{0}_{1}_{2}_{3}_{4}_{5}", d.Year, d.Month, d.Day, d.Hour, d.Minute, d.Second);

            m_strLogPath = System.IO.Path.Combine(strPath, strName + ".log");
            m_Log = new System.IO.StreamWriter(m_strLogPath,false,Encoding.GetEncoding("GBK"));
            m_Log.AutoFlush = true;
        }

       
        long m_nAllFeatures;
        /// <summary>
        /// 开始准备数据转换
        /// </summary>
        public void Begin()
        {
            m_Watch.Start();
            m_bBusy = true;
            m_nAllFeatures = 0;
            StringBuilder b = new StringBuilder();
            b.AppendFormat("开始转换时间：{0}\r\n", DateTime.Now.ToString());
            b.AppendLine();

            //输出第一条日志。
            AddLog(Color.Blue, b.ToString()); 
        }
        /// <summary>
        /// 数据转换全部结束。
        /// </summary>
        public void End()
        {
            if (m_Context != null)
            {
                m_nAllFeatures += m_Context.TotalFeature;

                FileLog(m_Context.Log);
            }
            StringBuilder b = new StringBuilder();
            b.AppendFormat("完成时间：{0}\r\n", DateTime.Now.ToString());

            b.AppendFormat("耗费时间：{0}\r\n", m_Watch.Elapsed.ToString());

            
            b.AppendFormat("转换数量：{0:N0}\r\n", m_nAllFeatures);
            b.AppendLine();

            AddLog(Color.Blue, b.ToString());
            m_Log.Close();
            m_Log = null;

            AddLog(Color.Blue, "日志参见：file:///" + m_strLogPath);
            m_bBusy = false;

        }
        /// <summary>
        /// 是否处于工作状态。
        /// </summary>
        public bool Busy
        {
            get
            {
                return m_bBusy;
            }
        }
        void LogAppend(Color color, string text)
        {
            m_Box.SelectionColor = color;
            m_Box.AppendText(text);
            FileLog(text);
        } 
        /// <summary>
        /// 写入日志到文件
        /// </summary>
        /// <param name="strLog"></param>
        void FileLog(string strLog)
        {
            if (null == m_Log)
                return;
            //日志写入到文件
            m_Log.WriteLine(strLog); 
        }
        public void OnLog(string strContent, GIS.ProgressLogLevel level)
        {
            Color color = Color.Black;
            string strHead = "";
            switch (level)
            {
                case GIS.ProgressLogLevel.eError:
                    strHead = DateTime.Now.ToString() + " [错误] ";
                    color = Color.Red;
                    break;
                case GIS.ProgressLogLevel.eLog:
                    strHead = DateTime.Now.ToString() + "\t"; 
                    break;
                case GIS.ProgressLogLevel.eWarning:
                    strHead = DateTime.Now.ToString() + " [警告] ";
                    color = Color.Blue;
                    break;
                default:
                    break;
            }
            strHead += strContent;
            strHead += "\n";
            AddLog(color, strHead);
        } 
        public void AddLog(Color color, string str)
        {
            LogAppendDelegate la = new LogAppendDelegate(LogAppend);
            m_Box.Invoke(la, color, str); 
        }
        
        ProgressContext m_Context;//进度条上下文。
        /// <summary>
        /// 当底层传入进度信息的时候。
        /// </summary>
        /// <param name="nPos"></param>
        /// <param name="nCount"></param>
        /// <param name="strTitile"></param>
        /// <param name="strContent"></param>
        public void OnProgress(long nPos, long nCount, string strTitile, string strContent)
        {
            //进度标题
            string strKey = strTitile + "_" + strContent;
            //第一次创建。
            if (m_Context != null)
                if (!m_Context.IsThis(strKey)) //如果进度内容变化了。
                {
                    ///累加一次数量。
                    m_nAllFeatures += m_Context.TotalFeature;
                    FileLog(m_Context.Log);
                    m_Context.Dispose();
                    m_Context = null;
                }

            if (m_Context == null)
                m_Context = new ProgressContext(strTitile, strContent, m_Box);

            if(nCount <=0)
                m_Context.Progress(nPos);
            else
                m_Context.Progress(nPos, nCount); 
        }
    }
}
