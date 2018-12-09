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

		private Themes themes;

		public MainWindow()
        {
            InitializeComponent();
			fileDialog = new FileDialog();
			File.DataContext = fileDialog;
			themes = new Themes();
			DrawProject.DataContext = themes;
		}

		private void ChangedTheme(object sender, RoutedEventArgs e)
		{
			switch (((MenuItem)sender).Header.ToString())
			{
				case "Dark":
					{
						themes.SetTheme(Themes.NameTheme.Dark);
						break;
					}
				case "Light":
					{
						themes.SetTheme(Themes.NameTheme.Light);
						break;
					}
				case "Neutral":
					{
						themes.SetTheme(Themes.NameTheme.Neutral);
						break;
					}
				case "Gradient":
					{
						themes.SetTheme(Themes.NameTheme.Gradient);
						break;
					}
			}
		}

		private void Button_DrawMode(object sender, RoutedEventArgs e)
		{
			var NameMode = ((Label)sender).Content.ToString();
			switch (NameMode)
			{
				case "Default":
					{
						Rot_Sym_Conf.Items.Clear();
						Rot_Sym_Conf.Items.Add(" -- ");
						Rot_Sym_Conf.SelectedItem = " -- ";
						break;
					}
				case "Rotation":
					{
						Rot_Sym_Conf.Items.Clear();
						Rot_Sym_Conf.Items.Add(" -- ");
						Rot_Sym_Conf.Items.Add(" x2 ");
						Rot_Sym_Conf.Items.Add(" x3 ");
						Rot_Sym_Conf.Items.Add(" x4 ");
						Rot_Sym_Conf.Items.Add(" x5 ");
						Rot_Sym_Conf.Items.Add(" x6 ");
						Rot_Sym_Conf.Items.Add(" x8 ");
						Rot_Sym_Conf.Items.Add(" x9 ");
						Rot_Sym_Conf.Items.Add(" x10 ");
						Rot_Sym_Conf.SelectedItem = " -- ";
						break;
					}
				case "Symmetrical":
					{
						Rot_Sym_Conf.Items.Clear();
						Rot_Sym_Conf.Items.Add(" -- ");
						Rot_Sym_Conf.Items.Add(" y2 ");
						Rot_Sym_Conf.Items.Add(" x2 ");
						Rot_Sym_Conf.Items.Add(" x4 ");
						Rot_Sym_Conf.Items.Add(" x8 ");
						Rot_Sym_Conf.SelectedItem = " -- ";
						break;
					}
			}
			//Rot_Sym_Conf.Height = ((Label)sender).Height * 2;
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

		private void DrawArc(Vector center, Vector startPoint, Vector endPoint)
		{

			var arcPath = new Path();
			arcPath.Stroke = themes.Primitives();
			arcPath.StrokeThickness = 1;

			var arcGeometry = new PathGeometry();

			var arc = new PathFigure();
			arc.StartPoint = new Point(startPoint.X, startPoint.Y);
			var segmentArc = new ArcSegment();
			segmentArc.Point = new Point(endPoint.X, endPoint.Y);
			var radius = (startPoint - center).Length;
			segmentArc.Size = new Size(radius, radius);
			arc.Segments.Add(segmentArc);

			arcGeometry.Figures.Add(arc);
			arcPath.Data = arcGeometry;
			Scene.Children.Add(arcPath);
		}

		private void DrawCurve(Vector[] points)
		{
			var curvePath = new Path();
			curvePath.Stroke = themes.Primitives();
			curvePath.StrokeThickness = 1;

			var curveGeometry = new PathGeometry();

			var curve = new PathFigure();
			curve.StartPoint = new Point(points[0].X, points[0].Y);
			for (int i = 1; i < points.Length; i += 3)
			{
				var segmentCurve = new BezierSegment();
				segmentCurve.Point1 = new Point(points[i].X, points[i].Y);
				segmentCurve.Point2 = new Point(points[i + 1].X, points[i + 1].Y);
				segmentCurve.Point3 = new Point(points[i + 2].X, points[i + 2].Y);
				curve.Segments.Add(segmentCurve);
			}

			curveGeometry.Figures.Add(curve);
			curvePath.Data = curveGeometry;
			Scene.Children.Add(curvePath);
		}

		private void DrawLine(Vector pointStart, Vector pointEnd)
		{
			Scene.Children.Add(new Line
			{
				X1 = pointStart.X,
				Y1 = pointStart.Y,
				X2 = pointEnd.X,
				Y2 = pointEnd.Y,
				StrokeStartLineCap = PenLineCap.Round,
				StrokeEndLineCap = PenLineCap.Round,
				StrokeThickness = 1,
				Stroke = themes.Primitives()
			});
		}

		private void DrawPoint(Vector position)
		{
			var pointPath = new Path();
			pointPath.Stroke = themes.Primitives();
			pointPath.Fill = Brushes.Red;
			pointPath.StrokeThickness = 1;
			EllipseGeometry point = new EllipseGeometry();
			point.Center = new System.Windows.Point(position.X, position.Y);
			point.RadiusX = 2;
			point.RadiusY = 2;
			pointPath.Data = point;
			Scene.Children.Add(pointPath);
		}

		private void DrawCircle(Vector center, double radius)
		{
			var circlePath = new Path();
			circlePath.Stroke = themes.Primitives();
			circlePath.StrokeThickness = 1;
			EllipseGeometry circle = new EllipseGeometry();
			circle.Center = new System.Windows.Point(center.X, center.Y);
			circle.RadiusX = radius;
			circle.RadiusY = radius;
			circlePath.Data = circle;
			Scene.Children.Add(circlePath);
		}

		private Vector click1;
		private Boolean isClick = false;
		private void Canvas_OnMouseDown(object sender, MouseEventArgs e)
		{
			//DrawArc(new Vector(150, 150), new Vector(250, 150), new Vector(150, 50));
			//Vector[] points = { new Vector(0, 100), new Vector(50, 50), new Vector(100, 150), new Vector(150, 100),
			//new Vector(200, 50), new Vector(250, 150), new Vector(300, 100)};
			//DrawCurve(points);
			if (!isClick)
			{
				//DrawCircle(new Vector(e.GetPosition(Scene).X, e.GetPosition(Scene).Y), 100);
				click1.X = e.GetPosition(Scene).X;
				click1.Y = e.GetPosition(Scene).Y;
				DrawPoint(new Vector(click1.X, click1.Y));
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
					Stroke = themes.Primitives()
				});
				DrawPoint(new Vector(e.GetPosition(Scene).X, e.GetPosition(Scene).Y));
			}
			
			if (e.MouseDevice.LeftButton == MouseButtonState.Pressed)
			{
			}
		}
	}
}
