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

		private ControlInterface controlInterface;

		public MainWindow()
        {
            InitializeComponent();

			File.DataContext = FileDialog.GetInstance();

			DrawProject.DataContext = Themes.GetInstance();

			viewModel = ViewModel.GetInstance();

			controlInterface = ControlInterface.GetInstance();

			controlInterface.Initializated(Requirments, FieldForDisplays);

			controlScene = ControlScene.GetInstance();
			controlScene.Initializated(Scene);

			StatusBar.DataContext = viewModel;

			GridOnOff.DataContext = controlScene;
		}

		private void ChangedTheme(object sender, RoutedEventArgs e)
		{
			var themes = Themes.GetInstance();
			switch (((MenuItem)sender).Header.ToString())
			{
				case "Dark":
					{
						themes.SetTheme(Themes.NameTheme.Dark);
						viewModel.SetEvent(ViewModel.Event.ev_set_theme, new double[] { 0 });
						break;
					}
				case "Light":
					{
						viewModel.SetEvent(ViewModel.Event.ev_set_theme, new double[] { 1 });
						themes.SetTheme(Themes.NameTheme.Light);
						break;
					}
				case "Neutral":
					{
						viewModel.SetEvent(ViewModel.Event.ev_set_theme, new double[] { 2 });
						themes.SetTheme(Themes.NameTheme.Neutral);
						break;
					}
				case "Gradient":
					{
						viewModel.SetEvent(ViewModel.Event.ev_set_theme, new double[] { 3 });
						themes.SetTheme(Themes.NameTheme.Gradient);
						break;
					}
			}
		}

		private void RotationMode_handler(object sender, RoutedEventArgs e)
		{
			var value = Double.Parse(((Label)sender).Content.ToString().Substring(1));
			viewModel.SetEvent(ViewModel.Event.ev_rotationDraw, new double[] { value });
		}

		private void SymmetricalMode_handler(object sender, RoutedEventArgs e)
		{
			var content = ((Label)sender).Content.ToString();
			var value = (content[1] == 'y') ? 1.0 : Double.Parse(content.Substring(2));
			viewModel.SetEvent(ViewModel.Event.ev_symmetricalDraw, new double[] { value });
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
						viewModel.SetEvent(ViewModel.Event.ev_defualtDraw, new double[0]);
						break;
					}
				case "Rotation":
					{
						Rot_Sym_Conf.Items.Clear();
						Rot_Sym_Conf.Items.Add(" -- ");
						for (int i = 2; i <= 10; i++)
						{
							var label = new Label();
							label.Content = "x" + i.ToString();
							label.AddHandler(Label.MouseDownEvent, new MouseButtonEventHandler(RotationMode_handler));
							Rot_Sym_Conf.Items.Add(label);
						}
						Rot_Sym_Conf.SelectedItem = " -- ";
						break;
					}
				case "Symmetrical":
					{
						Rot_Sym_Conf.Items.Clear();
						Rot_Sym_Conf.Items.Add(" -- ");
						string[] names = { " y2 ", " x2 ", " x4 ", " x8 " };
						for (int i = 0; i < 4; i++)
						{
							var label = new Label();
							label.Content = names[i];
							label.AddHandler(Label.MouseDownEvent, new MouseButtonEventHandler(SymmetricalMode_handler));
							Rot_Sym_Conf.Items.Add(label);
						}
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
			
		}

		private void Button_showReqs_Click(object sender, RoutedEventArgs e)
		{

		}

		private ViewModel.Event lastCreateEvent = ViewModel.Event.ev_ctrlDown;

		private void Primitive_click(object sender, RoutedEventArgs e)
		{
			var namePrim = ((RadioButton)sender).Tag.ToString();
			switch (namePrim)
			{
				case "Point":
					{
						lastCreateEvent = ViewModel.Event.ev_createPoint;
						viewModel.SetEvent(ViewModel.Event.ev_createPoint, new double[0]);
						break;
					}
				case "Segment":
					{
						lastCreateEvent = ViewModel.Event.ev_createSegment;
						viewModel.SetEvent(ViewModel.Event.ev_createSegment, new double[0]);
						break;
					}
				case "Star":
					{
						lastCreateEvent = ViewModel.Event.ev_createStar;
						viewModel.SetEvent(ViewModel.Event.ev_createStar, new double[0]);
						break;
					}
				case "Broken":
					{
						lastCreateEvent = ViewModel.Event.ev_createBrokenLine;
						viewModel.SetEvent(ViewModel.Event.ev_createBrokenLine, new double[0]);
						break;
					}
				case "Circle":
					{
						lastCreateEvent = ViewModel.Event.ev_createCircle;
						viewModel.SetEvent(ViewModel.Event.ev_createCircle, new double[0]);
						break;
					}
				case "Arc":
					{
						lastCreateEvent = ViewModel.Event.ev_createArc;
						viewModel.SetEvent(ViewModel.Event.ev_createArc, new double[0]);
						break;
					}
				case "Curve":
					{
						lastCreateEvent = ViewModel.Event.ev_createCurve;
						viewModel.SetEvent(ViewModel.Event.ev_createCurve, new double[0]);
						break;
					}
			}
			((RadioButton)sender).IsChecked = false;
		}

		Key lastKeyEvent;
		Boolean IsDown;
		private void Window_KeyEvent(object sender, KeyEventArgs e)
		{
			switch (e.Key)
			{
				case Key.Enter:
					{
						viewModel.SetEvent(ViewModel.Event.ev_enter,new double[0]);
						break;
					}
				case Key.Escape:
					{
						viewModel.SetEvent(ViewModel.Event.ev_escape, new double[0]);
						break;
					}
				case Key.LeftCtrl:
					{
						if (e.IsDown) viewModel.SetEvent(ViewModel.Event.ev_ctrlDown, new double[0]);
						if (e.IsUp) viewModel.SetEvent(ViewModel.Event.ev_ctrlUp, new double[0]);
						break;
					}
				case Key.LeftShift:
					{
						viewModel.SetEvent(lastCreateEvent, new double[0]);
						break;
					}
				case Key.Delete:
					{
						//var slider = new Slider();
						//FieldForDisplays.Children.Add(slider);
						viewModel.SetEvent(ViewModel.Event.ev_del, new double[0]);
						break;
					}
				case Key.Z:
					{
						if (lastKeyEvent == Key.LeftCtrl) viewModel.SetEvent(ViewModel.Event.ev_undo, new double[0]);
						break;
					}
				case Key.Y:
					{
						if (lastKeyEvent == Key.LeftCtrl) viewModel.SetEvent(ViewModel.Event.ev_redu, new double[0]);
						break;
					}
			}
			lastKeyEvent = e.Key;
			IsDown = e.IsDown;
		}
		

		//private Vector click1;
		//private Boolean isClick = false;

		private void Scene_MouseMove(object sender, MouseEventArgs e)
		{
			viewModel.SetNewCursorPosition(e.GetPosition(Scene).X, e.GetPosition(Scene).Y);
			if (e.GetPosition(Scene).X < 0 || e.GetPosition(Scene).X > Scene.ActualWidth ||
				e.GetPosition(Scene).Y < 0 || e.GetPosition(Scene).Y > Scene.ActualHeight)
			{
				Scene.ReleaseMouseCapture();
				viewModel.SetEvent(ViewModel.Event.ev_leftMouseUp,
				new double[] { e.GetPosition(Scene).X, e.GetPosition(Scene).Y });
			}
			viewModel.SetEvent(ViewModel.Event.ev_mouseMove,
				new double[] { e.GetPosition(Scene).X, e.GetPosition(Scene).Y });
		}

		private void Scene_MouseLeave(object sender, MouseEventArgs e)
		{
			
		}

		private void Scene_MouseEnter(object sender, MouseEventArgs e)
		{
			Scene.CaptureMouse();
		}

		private void Scene_MouseLeftButtonDown(object sender, MouseButtonEventArgs e)
		{
			Scene.CaptureMouse();
			viewModel.SetEvent(ViewModel.Event.ev_leftMouseDown,
				new double[] { e.GetPosition(Scene).X, e.GetPosition(Scene).Y });
		}

		private void Scene_MouseLeftButtonUp(object sender, MouseButtonEventArgs e)
		{
			viewModel.SetEvent(ViewModel.Event.ev_leftMouseUp,
				new double[] { e.GetPosition(Scene).X, e.GetPosition(Scene).Y });
		}

		private void Scene_MouseRightButtonDown(object sender, MouseButtonEventArgs e)
		{
			viewModel.SetEvent(ViewModel.Event.ev_rightMouseDown,
				new double[] { e.GetPosition(Scene).X, e.GetPosition(Scene).Y });
		}

		private void Scene_MouseRightButtonUp(object sender, MouseButtonEventArgs e)
		{
			//viewModel.SetEvent(ViewModel.Event.ev_rightMouseUp,
			//	new double[] { e.GetPosition(Scene).X, e.GetPosition(Scene).Y });
		}

		private void Scene_MouseWheel(object sender, MouseWheelEventArgs e)
		{
			viewModel.SetEvent(ViewModel.Event.ev_scroll,
				new double[] { e.Delta });
		}

		private void Redaction_click(object sender, RoutedEventArgs e)
		{
			var nameRed = ((MenuItem)sender).Header.ToString();
			switch(nameRed)
			{
				case "Move":
					{
						viewModel.SetEvent(ViewModel.Event.ev_moveObjects, new double[0]);
						break;
					}
				case "Rotate":
					{
						viewModel.SetEvent(ViewModel.Event.ev_rotateObjects, new double[0]);
						break;
					}
				case "Scale":
					{
						viewModel.SetEvent(ViewModel.Event.ev_scaleObjects, new double[0]);
						break;
					}
				case "Delete":
					{
						viewModel.SetEvent(ViewModel.Event.ev_del, new double[0]);
						break;
					}
				case "Clear":
					{
						viewModel.SetEvent(ViewModel.Event.ev_delAll, new double[0]);
						break;
					}
			}
		}
	}
}
