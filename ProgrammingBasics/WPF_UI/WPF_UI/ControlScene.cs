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

		private Path gridPath = null;

		private void DrawGridOnscene()
		{
			gridPath = new Path();
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
			scene.Children.Add(gridPath);
		}

		private RelayCommand gridOnOffCommand;
		public RelayCommand GridOnOffCommand
		{
			get
			{
				return gridOnOffCommand ??
				  (gridOnOffCommand = new RelayCommand(obj =>
				  {
					  if (gridPath == null)
					  {
						  DrawGridOnscene();
					  }
					  else
					  {
						  scene.Children.Remove(gridPath);
						  gridPath = null;
					  }
				  }));
			}
		}

		public void DrawArc(Vector center, Vector startPoint, Vector endPoint)
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
			scene.Children.Add(arcPath);
		}

		public void DrawCurve(Vector[] points)
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
				Stroke = themes.Primitives()
			});
		}

		public void DrawPoint(Vector position)
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
			scene.Children.Add(pointPath);
		}

		public void DrawCircle(Vector center, double radius)
		{
			var circlePath = new Path();
			circlePath.Stroke = themes.Primitives();
			circlePath.StrokeThickness = 1;
			EllipseGeometry circle = new EllipseGeometry();
			circle.Center = new System.Windows.Point(center.X, center.Y);
			circle.RadiusX = radius;
			circle.RadiusY = radius;
			circlePath.Data = circle;
			scene.Children.Add(circlePath);
		}

	}
}
