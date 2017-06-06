using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using CLR_link;
using System.IO;
using System.Threading;

namespace Calculator
{
    /// <summary>
    /// MainWindow.xaml 的交互逻辑
    /// </summary>
    class DataBox
    {
        public void dataBoxAdd(String a, String b, Char op, Int32 pre)
        {
            firNumber = a;
            secNumber = b;
            oper = op;
            prec = pre;
            used = 1;
            end = 0;
            save = 1;
        }
        public String firNumber, secNumber, answer;
        public Char oper;
        public Int32 prec, used, end, save;
    }
    public partial class MainWindow : Window
    {
        private Char op;
        private Int32 prec, outSum;
        private DataBox[] dataBox = new DataBox[110];
        int threadMax;
        public MainWindow()
        {
            InitializeComponent();
            threadMax = 0;
            outSum = 0;
            label5.Visibility = Visibility.Hidden;
            threadNum.Visibility = Visibility.Hidden;
            button2.Visibility = Visibility.Hidden;
            button_C.Visibility = Visibility.Hidden;
            for (int i = 0; i < 100; i++)
            {
                dataBox[i] = new DataBox();
            }
        }

        public void saveFile(String a, String b, Char op0, String ans)
        {
            FileStream fileStream = new FileStream(Environment.CurrentDirectory + "\\data.txt", FileMode.Append);
            StreamWriter streamWriter = new StreamWriter(fileStream, Encoding.Default);
            streamWriter.WriteLine(a + " " + op0 + " " + b + " = " + ans + "\r\n");
            streamWriter.Flush();
            streamWriter.Close();
            fileStream.Close();
        }

        private void button1_Click(object sender, RoutedEventArgs e)
        {
            Close();
        }

        private void button_Clear_Click(object sender, RoutedEventArgs e)
        {
            textBox1.Text = "";
            textBox2.Text = "0";
            textBox3.Text = "";
            textBox4.Text = "";
            radioButton.IsChecked = true;
        }

        public void calculate(int x)
        {
            CLR_link.Class1 temp = new CLR_link.Class1();
            dataBox[x].answer = temp.link(dataBox[x].firNumber, dataBox[x].secNumber, dataBox[x].oper, dataBox[x].prec);
            dataBox[x].used = 0;
            dataBox[x].end = 1;
        }
        private void button_Click(object sender, RoutedEventArgs e)
        {
            textBox4.Text = "";
            op = '+';
            prec = 0;
            if (radioButton.IsChecked == true) op = '+';
            if (radioButton1.IsChecked == true) op = '-';
            if (radioButton2.IsChecked == true) op = '*';
            if (radioButton3.IsChecked == true)
            {
                op = '/';
                if (String.IsNullOrEmpty(textBox2.Text))
                {
                    string message = "请输入除法精度";
                    MessageBoxResult result = MessageBox.Show(message);
                    return;
                }
                prec = Convert.ToInt32(textBox2.Text);
            }
            if (String.IsNullOrEmpty(textBox1.Text))
            {
                string message = "请输入数字1";
                MessageBoxResult result = MessageBox.Show(message);
                return;
            }
            if (String.IsNullOrEmpty(textBox3.Text))
            {
                string message = "请输入数字2";
                MessageBoxResult result = MessageBox.Show(message);
                return;
            }
            String num1 = Convert.ToString(textBox1.Text);
            String num2 = Convert.ToString(textBox3.Text);
            if (op == '/' && num2 == "0")
            {
                string message = "除数不能为0";
                MessageBoxResult result = MessageBox.Show(message);
                return;
            }
            //单线程
            if (radioButton6.IsChecked == true)
            {
                CLR_link.Class1 temp = new CLR_link.Class1();
                String ans = temp.link(num1, num2, op, prec);
                textBox4.Text = ans;
                return;
            }
            //多线程部分
            dataBox[threadMax].dataBoxAdd(num1, num2, op, prec);
            int tmp = threadMax;
            Thread t = new Thread(delegate () { calculate(tmp); });
            ++threadMax;
            threadNum.Text = Convert.ToString(threadMax - outSum);
            t.Start();
        }

        private void button2_Click(object sender, RoutedEventArgs e)
        {
            for (int i = 0; i < threadMax; i++)
            {
                if (dataBox[i].end == 1)
                {
                    textBox1.Text = dataBox[i].firNumber;
                    textBox3.Text = dataBox[i].secNumber;
                    textBox4.Text = dataBox[i].answer;
                    textBox2.Text = Convert.ToString(dataBox[i].prec);
                    switch (dataBox[i].oper)
                    {
                        case '+':
                            radioButton.IsChecked = true;
                            break;
                        case '-':
                            radioButton1.IsChecked = true;
                            break;
                        case '*':
                            radioButton2.IsChecked = true;
                            break;
                        case '/':
                            radioButton3.IsChecked = true;
                            break;
                    }
                    dataBox[i].end = 0;
                    ++outSum;
                    threadNum.Text = Convert.ToString(threadMax - outSum);
                    return;
                }
            }
            threadNum.Text = Convert.ToString(threadMax - outSum);
        }

        private void button_save_Click(object sender, RoutedEventArgs e)
        {
            if (radioButton5.IsChecked == true)
            {
                for (int i = 0; i < threadMax; ++i)
                {
                    if (dataBox[i].save == 0) continue;
                    if (dataBox[i].used == 1)
                    {
                        MessageBoxResult result = MessageBox.Show("第"+(i+1)+"组数据未完成计算，将这组计算数据将不被保存");
                    }
                    else
                    {
                        saveFile(dataBox[i].firNumber, dataBox[i].secNumber, dataBox[i].oper, dataBox[i].answer);
                        dataBox[i].save = 0;
                    }
                    dataBox[i].used = 0;
                    dataBox[i].end = 0;
                }
                threadMax = 0;
            }
            else
                saveFile(textBox1.Text, textBox3.Text, op, textBox4.Text);
        }

        private void button_C_Click(object sender, RoutedEventArgs e)
        {
            for (int i = 0; i < threadMax; i++)
            {
                dataBox[i].used = dataBox[i].end = dataBox[i].save = 0;
            }
            threadMax = 0;
            outSum = 0;
        }

        private void radioButton5_Checked(object sender, RoutedEventArgs e)
        {
            label5.Visibility = Visibility.Visible;
            threadNum.Visibility = Visibility.Visible;
            button2.Visibility = Visibility.Visible;
            button_C.Visibility = Visibility.Visible;
            threadMax = 0;
            outSum = 0;
        }

        private void radioButton6_Click(object sender, RoutedEventArgs e)
        {
            label5.Visibility = Visibility.Hidden;
            threadNum.Visibility = Visibility.Hidden;
            button2.Visibility = Visibility.Hidden;
            button_C.Visibility = Visibility.Hidden;
            threadMax = 0;
            outSum = 0;
        }

        private void button_open_Click(object sender, RoutedEventArgs e)
        {
            System.Diagnostics.Process.Start("notepad", Environment.CurrentDirectory + "\\data.txt");
        }
    }
}
