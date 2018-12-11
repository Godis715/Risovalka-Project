using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Shapes;

namespace WPF_UI
{
	class ControlScene : INotifyPropertyChanged
	{
		public event PropertyChangedEventHandler PropertyChanged;

		private Canvas scene;

		private Themes themes;

		public void Initializated(Canvas _scene)
		{
			scene = _scene;
			themes = Themes.GetInstance();
			Grid = CreateGrid();
		}

		private ControlScene()
		{
		}

		private static ControlScene instance = null;

		public static ControlScene GetInstance()
		{
			if (instance == null)
			{
				instance = new ControlScene();
			}
			return instance;
		}

		private Path Grid = null;

		private Boolean gridIsDraw = false;

		private Path CreateGrid()
		{
			Path gridPath = new Path();
			gridPath.Tag = "Grid";
			gridPath.Stroke = Brushes.Bisque;
			gridPath.StrokeThickness = 0.2;
			var step = 20;
			var grid = new GeometryGroup();
			for (var coordX = 0; coordX < scene.Width; coordX += step)
			{
				var lineHor = new LineGeometry();
				lineHor.StartPoint = new Point(coordX, 0);
				lineHor.EndPoint = new Point(coordX, scene.Height);
				grid.Children.Add(lineHor);
			}
			for (var coordY = 0; coordY < scene.Height; coordY += step)
			{
				var lineVert = new LineGeometry();
				lineVert.StartPoint = new Point(0, coordY);
				lineVert.EndPoint = new Point(scene.Width, coordY);
				grid.Children.Add(lineVert);
			}
			gridPath.Data = grid;
			return gridPath;
		}

		private RelayCommand gridOnOffCommand;

		public RelayCommand GridOnOffCommand
		{
			get
			{
				return gridOnOffCommand ??
				  (gridOnOffCommand = new RelayCommand(obj =>
				  {
					  gridIsDraw = !gridIsDraw;
				  }));
			}
		}

		public enum TypeDrawing { dot, dash, solid, TypeNull };

		private SolidColorBrush currentColor = Brushes.White;

		public void SetColor(int r, int g, int b)
		{
			currentColor = new SolidColorBrush(Color.FromRgb(Convert.ToByte(r), Convert.ToByte(g), Convert.ToByte(b)));
		}

		public TypeDrawing currentType = TypeDrawing.TypeNull;

		

		public void DrawArc(double[] param)
		{
			var arcPath = new Path();
			arcPath.Stroke = currentColor;
			arcPath.StrokeThickness = 1;

			var arcGeometry = new PathGeometry();

			var arc = new PathFigure();
			arc.StartPoint = new Point(param[0], param[1]);

			if (param[7] > Math.PI)
			{
				//  creting 2 arcs, first is half of circle
				double x = 2 * param[4] - param[0];
				double y = 2 * param[5] - param[1];
				// (x;y) is opposite startPoint
				var segmentArc = new ArcSegment();
				segmentArc.Point = new Point(x, y);
				segmentArc.Size = new Size(param[6], param[6]);
				arc.Segments.Add(segmentArc);
				arcGeometry.Figures.Add(arc);

				var arc2 = new PathFigure();
				arc2.StartPoint = new Point(x, y);
				var segmentArc2 = new ArcSegment();
				segmentArc2.Point = new Point(param[2], param[3]);
				segmentArc2.Size = new Size(param[6], param[6]);
				arc2.Segments.Add(segmentArc2);
				arcGeometry.Figures.Add(arc2);
				arcPath.Data = arcGeometry;
				scene.Children.Add(arcPath);
			}
			else
			{
				var segmentArc = new ArcSegment();
				segmentArc.Point = new Point(param[2], param[3]);
				segmentArc.Size = new Size(param[6], param[6]);
				arc.Segments.Add(segmentArc);
				arcGeometry.Figures.Add(arc);
				arcPath.Data = arcGeometry;
				scene.Children.Add(arcPath);
			}
		}

		public void DrawCurve(double[] param)
		{
			var curvePath = new Path();
			curvePath.Stroke = currentColor;
			curvePath.StrokeThickness = 1;

			var curveGeometry = new PathGeometry();

			var curve = new PathFigure();
			curve.StartPoint = new Point(param[0], param[1]);
			for (int i = 2; i < param.Length; i += 6)
			{
				var segmentCurve = new BezierSegment();
				segmentCurve.Point1 = new Point(param[i], param[i + 1]);
				segmentCurve.Point2 = new Point(param[i + 2], param[i + 3]);
				segmentCurve.Point3 = new Point(param[i + 4], param[i + 5]);
				curve.Segments.Add(segmentCurve);
			}

			curveGeometry.Figures.Add(curve);
			curvePath.Data = curveGeometry;
			scene.Children.Add(curvePath);
		}

		public void DrawLine(Vector pointStart, Vector pointEnd)
		{
			scene.Children.Add(new Line
			{
				X1 = pointStart.X,
				Y1 = pointStart.Y,
				X2 = pointEnd.X,
				Y2 = pointEnd.Y,
				StrokeStartLineCap = PenLineCap.Round,
				StrokeEndLineCap = PenLineCap.Round,
				StrokeThickness = 1,
				Stroke = currentColor
			});
		}

		public void DrawPoint(Vector position)
		{
			var pointPath = new Path();
			pointPath.Stroke = currentColor;
			pointPath.Fill = Brushes.Red;
			pointPath.StrokeThickness = 1;
			EllipseGeometry point = new EllipseGeometry();
			point.Center = new System.Windows.Point(position.X, position.Y);
			point.RadiusX = 2;
			point.RadiusY = 2;
			pointPath.Data = point;
			scene.Children.Add(pointPath);
		}

		public void DrawCircle(double[] param)
		{
			var circlePath = new Path();
			circlePath.Stroke = currentColor;
			circlePath.StrokeThickness = 1;
			EllipseGeometry circle = new EllipseGeometry();
			circle.Center = new System.Windows.Point(param[0], param[1]);
			circle.RadiusX = param[2];
			circle.RadiusY = param[2];
			circlePath.Data = circle;
			scene.Children.Add(circlePath);
		}

		public void CleareScene()
		{
			scene.Children.Clear();
			if (gridIsDraw)
			{
				scene.Children.Add(Grid);
			}
		}

	}
}
