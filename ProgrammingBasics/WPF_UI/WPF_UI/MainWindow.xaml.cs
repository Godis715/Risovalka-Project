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

namespace WPF_UI
{
    /// <summary>
    /// Логика взаимодействия для MainWindow.xaml
    /// </summary>
    public class Paramet
    {
        public string Name { get; set; }
        public double Value { get; set; }
    }
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        private void Button_Save_Click(object sender, RoutedEventArgs e)
        {

        }

        private void Button_Script_Click(object sender, RoutedEventArgs e)
        {

        }

        private void Button_Download_Click(object sender, RoutedEventArgs e)
        {

        }

        private void Button_Undo_Click(object sender, RoutedEventArgs e)
        {
            Reqs.Items.Add(new MenuItem
            {
                Header = "1"
            });
            Reqs.Items.Add(new MenuItem
            {
                Header = "2"
            });
            Reqs.Items.Add(new MenuItem
            {
                Header = "3"
            });
        }

        private void Button_Redo_Click(object sender, RoutedEventArgs e)
        {
            Reqs.Items.Clear();
            Reqs.Items.Add(new MenuItem
            {
                Header = "1"
            });
            Reqs.Items.Add(new MenuItem
            {
                Header = "2"
            });
            Reqs.Items.Add(new MenuItem
            {
                Header = "3"
            });
        }

        private void Button_showParams_Click(object sender, RoutedEventArgs e)
        {
            DataGrid paramtable = new DataGrid();
            paramtable.AutoGenerateColumns = true;
            paramtable.ColumnWidth = 10;
            List<Paramet> plist = new List<Paramet>
            {
                new Paramet {Name = "x1", Value = 0},
                new Paramet {Name = "y1", Value = 1},
                new Paramet {Name = "x2", Value = 2},
                new Paramet {Name = "y2", Value = 3},
                new Paramet {Name = "x1", Value = 0},
                new Paramet {Name = "y1", Value = 1},
                new Paramet {Name = "x2", Value = 2},
                new Paramet {Name = "y2", Value = 3}
            };
            datagr.ItemsSource = plist;
            //test.Children.Add(paramtable);
        }

        private void Button_showReqs_Click(object sender, RoutedEventArgs e)
        {

        }
    }
}
