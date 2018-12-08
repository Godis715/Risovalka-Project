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
		private FileDialog fileDialog;
			
        public MainWindow()
        {
            InitializeComponent();
			fileDialog = new FileDialog();
			File.DataContext = fileDialog;
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

		private Path gridPath;
		private void DrawGridOnScene()
		{
			gridPath = new Path();
			gridPath.Tag = "Grid";
			gridPath.Stroke = Brushes.Bisque;
			gridPath.StrokeThickness = 0.2;
			var step = 20;
			var grid = new GeometryGroup();
			for (var coordX = 0; coordX < Scene.Width; coordX += step)
			{
				var lineHor = new LineGeometry();
				lineHor.StartPoint = new Point(coordX, 0);
				lineHor.EndPoint = new Point(coordX, Scene.Height);
				grid.Children.Add(lineHor);
			}
			for (var coordY = 0; coordY < Scene.Height; coordY += step)
			{
				var lineVert = new LineGeometry();
				lineVert.StartPoint = new Point(0, coordY);
				lineVert.EndPoint = new Point(Scene.Width, coordY);
				grid.Children.Add(lineVert);
			}
			gridPath.Data = grid;
			Scene.Children.Add(gridPath);
		}
		private void Grid_OnOff(object sender, RoutedEventArgs e)
		{
			if (gridPath == null)
			{
				DrawGridOnScene();
			}
			else
			{
				Scene.Children.Remove(gridPath);
				gridPath = null;
			}
		}

		private Vector click1;
		private Boolean isClick = false;
		private void Canvas_OnMouseDown(object sender, MouseEventArgs e)
		{
			if (!isClick)
			{
				click1.X = e.GetPosition(Scene).X;
				click1.Y = e.GetPosition(Scene).Y;
				isClick = true;
			}
			else
			{
				isClick = false;
				//Scene.Children.Clear();
				Scene.Children.Add(new Line
				{
					X1 = click1.X,
					Y1 = click1.Y,
					X2 = e.GetPosition(Scene).X,
					Y2 = e.GetPosition(Scene).Y,
					StrokeStartLineCap = PenLineCap.Round,
					StrokeEndLineCap = PenLineCap.Round,
					StrokeThickness = 1,
					Stroke = Brushes.White
				});
			}
			
			if (e.MouseDevice.LeftButton == MouseButtonState.Pressed)
			{
			}
		}
	}
}
