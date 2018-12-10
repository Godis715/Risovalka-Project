using System;
using System.Collections.Generic;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Shapes;

using KernelWrapper;

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
		private ViewModel viewModel;

		private ControlScene controlScene;

		public MainWindow()
        {
            InitializeComponent();

			File.DataContext = FileDialog.GetInstance();
			DrawProject.DataContext = Themes.GetInstance();
			viewModel = ViewModel.GetInstance();
			controlScene = ControlScene.GetInstance();
			controlScene.Initializated(Scene);
		}

		private void ChangedTheme(object sender, RoutedEventArgs e)
		{
			var themes = Themes.GetInstance();
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
			viewModel.SetEvent(ViewModel.Event.ev_undo, new double[0]);
		}

		private void Button_Redo_Click(object sender, RoutedEventArgs e)
		{
			viewModel.SetEvent(ViewModel.Event.ev_redu, new double[0]);
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

		Key lastKeyEvent;
		Boolean IsDown;
		private void Window_KeyEvent(object sender, KeyEventArgs e)
		{
			lastKeyEvent = e.Key;
			IsDown = e.IsDown;
		}
		

		//private Vector click1;
		//private Boolean isClick = false;
		private void Scene_OnMouseDown(object sender, MouseEventArgs e)
		{
			viewModel.SetEvent(ViewModel.Event.ev_leftMouseDown,
				new double[] { e.GetPosition(Scene).X, e.GetPosition(Scene).Y });
			//if (lastKeyEvent == Key.LeftCtrl && IsDown)
			//{
			//	if (!isClick)
			//	{
			//		click1.X = e.GetPosition(Scene).X;
			//		click1.Y = e.GetPosition(Scene).Y;
			//		controlScene.DrawPoint(new Vector(click1.X, click1.Y));
			//		isClick = true;
			//	}
			//	else
			//	{
			//		isClick = false;
			//		controlScene.DrawLine(click1, new Vector(e.GetPosition(Scene).X, e.GetPosition(Scene).Y));
			//		controlScene.DrawPoint(new Vector(e.GetPosition(Scene).X, e.GetPosition(Scene).Y));
			//	}
			//}
			//DrawArc(new Vector(150, 150), new Vector(250, 150), new Vector(150, 50));
			//Vector[] points = { new Vector(0, 100), new Vector(50, 50), new Vector(100, 150), new Vector(150, 100),
			//new Vector(200, 50), new Vector(250, 150), new Vector(300, 100)};
			//DrawCurve(points);
			
			
			/*
			if (e.MouseDevice.LeftButton == MouseButtonState.Pressed)
			{
			
			}*/
		}

		private void Scene_MouseMove(object sender, MouseEventArgs e)
		{
			//viewModel.SetEvent(ViewModel.Event.ev_mouseMove,
			//	new double[] { e.GetPosition(Scene).X, e.GetPosition(Scene).Y });
		}

		private void Primitive_click(object sender, RoutedEventArgs e)
		{
			var namePrim = ((RadioButton)sender).Tag.ToString(); 
			switch (namePrim)
			{
				case "Point":
					{
						viewModel.SetEvent(ViewModel.Event.ev_createPoint, new double[0]);
						break;
					}
				case "Segment":
					{
						viewModel.SetEvent(ViewModel.Event.ev_createSegment, new double[0]);
						break;
					}
				case "Star":
					{
						viewModel.SetEvent(ViewModel.Event.ev_createStar, new double[0]);
						break;
					}
				case "Broken":
					{
						viewModel.SetEvent(ViewModel.Event.ev_createBrokenLine, new double[0]);
						break;
					}
				case "Circle":
					{
						viewModel.SetEvent(ViewModel.Event.ev_createCircle, new double[0]);
						break;
					}
				case "Arc":
					{
						viewModel.SetEvent(ViewModel.Event.ev_createArc, new double[0]);
						break;
					}
				case "Curve":
					{
						viewModel.SetEvent(ViewModel.Event.ev_createCurve, new double[0]);
						break;
					}
			}
		}
	}
}
