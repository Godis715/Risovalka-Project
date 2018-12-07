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
    public class paramet
    {
        public string name;
        public double value;
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
            List<paramet> plist = new List<paramet>
            {
                new paramet {name = "x1", value = 0},
                new paramet {name = "y1", value = 1},
                new paramet {name = "x2", value = 2},
                new paramet {name = "y2", value = 3},
                new paramet {name = "x1", value = 0},
                new paramet {name = "y1", value = 1},
                new paramet {name = "x2", value = 2},
                new paramet {name = "y2", value = 3}
            };
            datagr.ItemsSource = plist;
            //test.Children.Add(paramtable);
        }

        private void Button_showReqs_Click(object sender, RoutedEventArgs e)
        {

        }
    }
}
