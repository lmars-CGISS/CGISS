using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace GISDataTranslate
{
    class GConfig:GeoStar.Utility.Config
    {
        public static GConfig GlobalConfig;
        public IconManager Icons;
        public GConfig(string file):base(file)
        {
            GlobalConfig = this;
        }
    }
}
