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
	public class ObjectProperties : INotifyPropertyChanged
	{

		public event PropertyChangedEventHandler PropertyChanged;
		public void PropertyPoint(double[] param, string[] reqNames)
		{
			DataGrid nametable = new DataGrid();
			nametable.AutoGenerateColumns = true;
			nametable.ColumnWidth = 5;
			List<Paramet> namelist = new List<Paramet>
			{
				new Paramet {Name = "x1"},
				new Paramet {Name = "y1"},
				new Paramet {Name = "x2"},
				new Paramet {Name = "y2"}
			};
			nametable.IsReadOnly = true;
			nametable.ItemsSource = namelist;
			DataGrid valuetable = new DataGrid();
			valuetable.AutoGenerateColumns = true;
			valuetable.ColumnWidth = 10;
			List<Paramet> valuelist = new List<Paramet>
			{
				new Paramet {Value = param[0]},
				new Paramet {Value = param[1]},
				new Paramet {Value = param[2]},
				new Paramet {Value = param[3]}
			};
			valuetable.ItemsSource = valuelist;
			//test.Children.Add(paramtable);


			StackPanel stackPanel = new StackPanel();

			stackPanel.Children.Add(nametable);
			stackPanel.Children.Add(valuetable);

			var b_Ok = new Button();
			b_Ok.Content = "Ok";
			b_Ok.Click += b_Ok_handler;
			stackPanel.Children.Add(b_Ok);
			var b_Close = new Button();
			b_Close.Content = "X";
			b_Close.Click += b_Prim_close_handler;
			stackPanel.Children.Add(b_Close);

			var menuRequirments = new MenuItem();
			for (int i = 0; i < reqNames.Length; i++)
			{
				var label = new Label();
				label.Content = reqNames[i];
				label.AddHandler(Label.MouseDownEvent, new MouseButtonEventHandler(Requirments_handler));
				menuRequirments.Items.Add(label);
			}

			inputDisplay = new GroupBox();
			inputDisplay.Header = "Propeties";
			inputDisplay.Content = stackPanel;

			fieldForDisplays.Children.Add(inputDisplay);
		}

		private void Requirments_handler(object sender, RoutedEventArgs e)
		{
		}

		private void b_Prim_close_handler(object sender, RoutedEventArgs e)
		{
		}

		private void b_Ok_handler(object sender, RoutedEventArgs e)
		{
		}

		public static ObjectProperties GetInstance()
		{
			if (instance == null)
			{
				instance = new ObjectProperties();
			}
			return instance;
		}
		private ObjectProperties()
		{

		}

		private GroupBox inputDisplay;
		private static ObjectProperties instance = null;
		private Grid fieldForDisplays;
		private ViewModel viewModel;
	}
}
