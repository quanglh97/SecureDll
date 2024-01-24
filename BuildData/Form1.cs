using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Web;

namespace BuildData
{
    public partial class BuildData : Form
    {
        public BuildData()
        {
            InitializeComponent();
        }

        private void BuildBtn_Click(object sender, EventArgs e)
        {
            var md5 = md5Tbox.Text;
            var eviMD5 = md5_Q8tools(md5);

            string dataNormal = eviMD5 + "|http://95.216.80.182:8080/|normal";  // check MD5 file  -6
            string dataVIP = eviMD5 + "|http://95.216.80.182:8080/|VIP";  // check MD5 file  -6

            string test2 = AFunction(dataNormal);
            string test3 = AFunction(dataVIP);

            normalTbox.Text = test2;
            vipTbox.Text = test3;
        }

        public string AFunction(string sData) //build data key
        {
            //for (int i = 0; i < sData.Length; i++)
            //    if (sData[i] != '\0')
            //        sData[i] = sData[i] - 6;

            //return sData;


            string finalValue = "";
            int value;
            foreach (char c in sData)
            {
                if (c != '\0')
                {
                    value = Convert.ToInt32(c);
                    value = value - 6;
                    finalValue += Char.ConvertFromUtf32(value);
                }
                else
                {
                    value = Convert.ToInt32(c);
                    finalValue += Char.ConvertFromUtf32(value);
                }
                
            }
            return finalValue;

        }


        public string Tru2Line(string sData) //build Proxy
        {
            string finalValue = "";
            int value;
            foreach (char c in sData)
            {
                if (c != '\0')
                {
                    value = Convert.ToInt32(c);
                    value = value - 2;
                    finalValue += Char.ConvertFromUtf32(value);
                }
                else
                {
                    value = Convert.ToInt32(c);
                    finalValue += Char.ConvertFromUtf32(value);
                }

            }
            return finalValue;

        }



        public string ReplaceAt(string str, int index, int length, string replace)
        {
            return str.Remove(index, Math.Min(length, str.Length - index))
                    .Insert(index, replace);
        }

        public string md5_Q8tools(string sMD5)
        {
            sMD5 = ReplaceAt(sMD5, 0, 1, "Q");
            sMD5 = ReplaceAt(sMD5, 4, 1, "8");
            sMD5 = ReplaceAt(sMD5, 8, 1, "T");
            sMD5 = ReplaceAt(sMD5, 12, 1, "O");
            sMD5 = ReplaceAt(sMD5, 16, 1, "O");
            sMD5 = ReplaceAt(sMD5, 20, 1, "L");
            sMD5 = ReplaceAt(sMD5, 24, 1, "S");

            return sMD5;
        }

        private void CopyNormalBtn_Click(object sender, EventArgs e)
        {
            Clipboard.SetData(DataFormats.Text, normalTbox.Text);
            AutoClosingMessageBox.Show("đã copy data normal", "Thông báo", 1000);
        }

        private void CopyVipBtn_Click(object sender, EventArgs e)
        {
            Clipboard.SetData(DataFormats.Text, vipTbox.Text);
            AutoClosingMessageBox.Show("đã copy data vip", "Thông báo", 1000);
        }

        private void GenProxyBtn_Click(object sender, EventArgs e)
        {
            //try
            //{
            //	std::ifstream f("D:\\MMO\\CSharp\\ServerProduct\\SecureDll\\x64\\Debug\\proxy_k2_check_pass.txt");

            //	if (!f)
            //	{
            //		std::cerr << "ERROR: Cannot open 'teste.txt'!" << std::endl;
            //		exit(1);
            //	}
            //	std::string line;
            //	std::list<std::string> mylist;

            //	while (std::getline(f, line))
            //	{
            //		string tempPrx = urlEncode(line);
            //		tempPrx = Tru2line(tempPrx);
            //		mylist.push_back(tempPrx);
            //		std::cout << mylist.back() << std::endl;
            //	}
            //}
            //catch (const std::exception& ex)
            //{
            //	std::cerr << "Exception: '" << ex.what() << "'!" << std::endl;
            //	exit(1);
            //}



            List<string> lsRawPrx = RawPrxTbox.Text.Split('\n').ToList();
            List<string> lsGenPrx = new List<string>();
            for(int i = 0;i< lsRawPrx.Count; i++)
            {
                string ip = lsRawPrx[i].Split(':')[0];
                string port = lsRawPrx[i].Split(':')[1];
                var ele_ip = ip.Split('.');
                ele_ip[0] = (Int32.Parse(ele_ip[0]) + 2).ToString();
                ele_ip[1] = (Int32.Parse(ele_ip[1]) + 2).ToString();
                ele_ip[2] = (Int32.Parse(ele_ip[2]) + 2).ToString();
                ele_ip[3] = (Int32.Parse(ele_ip[3]) + 6).ToString();
                port = (Int32.Parse(port) + 6000).ToString();
                string newPrx = ele_ip[0] + "." + ele_ip[1] + "." + ele_ip[2] + "." + ele_ip[3] + ":" + port;
                string tempPrx = Uri.EscapeDataString(newPrx);
                tempPrx = Tru2Line(tempPrx);
                lsGenPrx.Add(tempPrx);
            }
            GenPrxTBox.Text = String.Join(Environment.NewLine, lsGenPrx);

        }

        private void CopyProxyGenBtn_Click(object sender, EventArgs e)
        {
            Clipboard.SetData(DataFormats.Text, GenPrxTBox.Text);
            AutoClosingMessageBox.Show("đã copy gen proxy", "Thông báo", 1000);
        }
    }
    public class AutoClosingMessageBox
    {
        System.Threading.Timer _timeoutTimer;
        string _caption;
        AutoClosingMessageBox(string text, string caption, int timeout)
        {
            _caption = caption;
            _timeoutTimer = new System.Threading.Timer(OnTimerElapsed,
                null, timeout, System.Threading.Timeout.Infinite);
            using (_timeoutTimer)
                MessageBox.Show(text, caption);
        }
        public static void Show(string text, string caption, int timeout)
        {
            new AutoClosingMessageBox(text, caption, timeout);
        }
        void OnTimerElapsed(object state)
        {
            IntPtr mbWnd = FindWindow("#32770", _caption); // lpClassName is #32770 for MessageBox
            if (mbWnd != IntPtr.Zero)
                SendMessage(mbWnd, WM_CLOSE, IntPtr.Zero, IntPtr.Zero);
            _timeoutTimer.Dispose();
        }
        const int WM_CLOSE = 0x0010;
        [System.Runtime.InteropServices.DllImport("user32.dll", SetLastError = true)]
        static extern IntPtr FindWindow(string lpClassName, string lpWindowName);
        [System.Runtime.InteropServices.DllImport("user32.dll", CharSet = System.Runtime.InteropServices.CharSet.Auto)]
        static extern IntPtr SendMessage(IntPtr hWnd, UInt32 Msg, IntPtr wParam, IntPtr lParam);

    }
}
