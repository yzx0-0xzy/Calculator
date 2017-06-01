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

namespace Calculator
{
    /// <summary>
    /// MainWindow.xaml 的交互逻辑
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
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

        private void button_Click(object sender, RoutedEventArgs e)
        {
            Char op = '+';
            Int32 prec = 0;
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
            CLR_link.Class1 temp = new CLR_link.Class1();
            String ans = temp.link(num1, num2, op, prec);
            textBox4.Text = ans;
        }

        private void button_save_Click(object sender, RoutedEventArgs e)
        {
            FileStream fileStream = new FileStream(Environment.CurrentDirectory + "\\data.txt", FileMode.Append);
            StreamWriter streamWriter = new StreamWriter(fileStream, Encoding.Default);
            if (radioButton.IsChecked == true) streamWriter.WriteLine(textBox1.Text + " + " + textBox3.Text + " = " + textBox4.Text + "\r\n");
            if (radioButton1.IsChecked == true) streamWriter.WriteLine(textBox1.Text + " - " + textBox3.Text + " = " + textBox4.Text + "\r\n");
            if (radioButton2.IsChecked == true) streamWriter.WriteLine(textBox1.Text + " * " + textBox3.Text + " = " + textBox4.Text + "\r\n");
            if (radioButton3.IsChecked == true) streamWriter.WriteLine(textBox1.Text + " / " + textBox3.Text + " = " + textBox4.Text + "\r\n");
            streamWriter.Flush();
            streamWriter.Close();
            fileStream.Close();
        }

        private void button_open_Click(object sender, RoutedEventArgs e)
        {
            System.Diagnostics.Process.Start("notepad", Environment.CurrentDirectory + "\\data.txt");
        }
    }
}
