using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;

namespace WPF_UI
{
	class ControlInterface : INotifyPropertyChanged
	{
		public event PropertyChangedEventHandler PropertyChanged;

		private ViewModel viewModel;

		public ControlInterface()
		{
		}

		private static ControlInterface instance = null;

		public static ControlInterface GetInstance()
		{
			if (instance == null)
			{
				instance = new ControlInterface();
			}
			return instance;
		}

		private MenuItem menuRequirments;

		private Grid fieldForDisplays;

		private GroupBox inputDisplay;

		private void b_Ok_handler(object sender, RoutedEventArgs e)
		{
            double value;
            var inputTextBox = ((TextBox)((StackPanel)((Button)sender).Parent).Children[0]);
            bool result = Double.TryParse(inputTextBox.Text, out value);
            if (result)
            {
                viewModel.SetEvent(ViewModel.Event.ev_input, new double[] { value });
                fieldForDisplays.Children.Remove(inputDisplay);
            }
            else
            {
                inputTextBox.Clear();
            }
		}

		private void CreateInputDisplay()
		{
			inputDisplay = new GroupBox();
			inputDisplay.Header = "Input";

			StackPanel stackPanel = new StackPanel();

			var textBox = new TextBox();
			stackPanel.Children.Add(textBox);

			var b_Ok = new Button();
			b_Ok.Content = "Ok";
			b_Ok.Click += b_Ok_handler;
			//b_Ok.AddHandler(Button.MouseDownEvent, new MouseButtonEventHandler(b_Ok_handler));
			stackPanel.Children.Add(b_Ok);

			inputDisplay.Content = stackPanel;

			fieldForDisplays.Children.Add(inputDisplay);
		}

		public void Initializated(MenuItem _menuRequirments, Grid _fieldForDisplays)
		{
			viewModel = ViewModel.GetInstance();
			menuRequirments = _menuRequirments;
			fieldForDisplays = _fieldForDisplays;
		}

		private void Requirments_handler(object sender, RoutedEventArgs e)
		{

			var name = ((MenuItem)sender).Header.ToString();
			switch (name)
			{
				case "Dist points":
					{
						CreateInputDisplay();
						viewModel.SetEvent(ViewModel.Event.ev_req_D_point, new double[0]);
						break;
					}
				case "Equal segment":
					{
						viewModel.SetEvent(ViewModel.Event.ev_req_Eq_Segment, new double[0]);
						break;
					}
				case "Points on one hand":
					{
						viewModel.SetEvent(ViewModel.Event.ev_req_on_one_hand, new double[0]);
						break;
					}
				case "Dist point segment":
					{
						CreateInputDisplay();
						viewModel.SetEvent(ViewModel.Event.ev_req_D_point_segment, new double[0]);
						break;
					}
				case "Angle between segment":
					{
						CreateInputDisplay();
						viewModel.SetEvent(ViewModel.Event.ev_req_angle_segment, new double[0]);
						break;
					}
				case "Dist point arc":
					{
						CreateInputDisplay();
						viewModel.SetEvent(ViewModel.Event.ev_req_D_point_arc, new double[0]);
						break;
					}
			}
			
		}

		public void SetRequirments(string[] requirments)
		{
			menuRequirments.Items.Clear();
			for (int i = 0; i < requirments.Length; i++)
			{
                var newItem = new MenuItem();
                newItem.Header = requirments[i];
                newItem.AddHandler(MenuItem.ClickEvent, new RoutedEventHandler(Requirments_handler));
                menuRequirments.Items.Add(newItem);
            }
        }
	}
}
