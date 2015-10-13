using System;
using System.Collections.Generic;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace HhdWpfLib
{
    public delegate void HhdCallNativeDele(int thisObj, string msg);

    /// <summary>
    /// Interaction logic for HhdCalcControl.xaml
    /// </summary>
    public partial class HhdCalcControl : UserControl
    {
        public HhdCallNativeDele CallNative;
        private int _thisObj;

        public HhdCalcControl()
        {
            InitializeComponent();
            this.BtnResult.Click += BtnResult_Click;
        }

        public void Init(int thisObj)
        {
            MessageBox.Show("HhdCalcControl.Init thisObj : " + thisObj);
            _thisObj = thisObj;
        }

        void BtnResult_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                var a = int.Parse(this.TbA.Text);
                var b = int.Parse(this.TbB.Text);
                var c = a + b;
                this.TbResult.Text = c.ToString();
            }
            catch (Exception ex)
            {
                this.TbResult.Text = ex.ToString();
            }

            if (this.CallNative != null)
            {
                this.CallNative.Invoke(_thisObj, this.TbResult.Text);
            }
        }
    }
}
