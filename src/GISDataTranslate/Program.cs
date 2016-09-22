using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;

namespace GISDataTranslate
{
    static class Program
    {
        static bool IsX86()
        {
            return IntPtr.Size == 4;
        }
        public static string Platform
        {
            get
            {
                return IsX86() ? "x86" : "x64";
            }
        }
        static void AppendPrivatePath(string strPath)
        {
            //获取appdomain的私有方法获取appdomainsetup的内部句柄。
            var funsion = typeof(AppDomain).GetMethod("GetFusionContext", System.Reflection.BindingFlags.NonPublic | System.Reflection.BindingFlags.Instance);
            //获取AppDomainSetup的静态方法，用于更新私有搜索路径
            var m = typeof(AppDomainSetup).GetMethod("UpdateContextProperty",
                System.Reflection.BindingFlags.NonPublic | System.Reflection.BindingFlags.Static);

            if (null != funsion && null != m)
            {
                //执行静态方法。
                m.Invoke(null, new object[] { funsion.Invoke(AppDomain.CurrentDomain, null), "PRIVATE_BINPATH", strPath });
            }
            else //如果这个方法失效则使用传统方法。
                AppDomain.CurrentDomain.AppendPrivatePath(strPath);
        }
        /// <summary>
        /// 应用程序的主入口点。
        /// </summary>
        [STAThread]
        static void Main()
        {
            string strPath = System.IO.Path.Combine(AppDomain.CurrentDomain.BaseDirectory, IsX86() ? "x86" : "amd64");
            //根据程序的类型将64位或者32位的搜索路径添加到程序中。
            AppendPrivatePath(strPath);

            strPath +=";" + Environment.GetEnvironmentVariable("PATH");
            Environment.SetEnvironmentVariable("PATH", strPath);

            //AppDomain.CurrentDomain.AssemblyResolve += new ResolveEventHandler(CurrentDomain_AssemblyResolve);
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new FormMain());
        }

        static System.Reflection.Assembly CurrentDomain_AssemblyResolve(object sender, ResolveEventArgs args)
        {
            string path = System.IO.Path.Combine(AppDomain.CurrentDomain.BaseDirectory, IsX86() ? "x86\\" : "amd64\\");
            path = System.IO.Path.Combine(path, args.Name.Split(',')[0]);
            path = String.Format(@"{0}.dll", path);
            return System.Reflection.Assembly.LoadFrom(path);  
        }
    }
}
