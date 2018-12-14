using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Media;

namespace WPF_UI
{
    class Themes : INotifyPropertyChanged
	{
		public event PropertyChangedEventHandler PropertyChanged;

		public enum NameTheme { Dark, Light, Neutral, Gradient };

		public SolidColorBrush[] colors { get; set; }

		public enum NameColors
		{
			BackGround, Scene, SystemBar, ToolBar
		};
		
		private Themes()
		{
			colors = new SolidColorBrush[4];
			colors[NameColors.BackGround.GetHashCode()] = Brushes.White;
			colors[NameColors.Scene.GetHashCode()] = Brushes.Black;
			colors[NameColors.SystemBar.GetHashCode()] = Brushes.LightBlue;
			colors[NameColors.ToolBar.GetHashCode()] = Brushes.White;
		}

		private static Themes instance = null;

		public static Themes GetInstance()
		{
			if (instance == null)
			{
				instance = new Themes();
			}
			return instance;
		}

		public void SystemBar(SolidColorBrush color) => colors[NameColors.SystemBar.GetHashCode()] = color;
		public void ToolBar(SolidColorBrush color) => colors[NameColors.ToolBar.GetHashCode()] = color;
		public void Scene(SolidColorBrush color) => colors[NameColors.Scene.GetHashCode()] = color;
		public void BackGround(SolidColorBrush color) => colors[NameColors.BackGround.GetHashCode()] = color;

		public SolidColorBrush SystemBar() => colors[NameColors.SystemBar.GetHashCode()];
		public SolidColorBrush ToolBar() => colors[NameColors.ToolBar.GetHashCode()];
		public SolidColorBrush Scene() => colors[NameColors.BackGround.GetHashCode()];
		public SolidColorBrush BackGround() => colors[NameColors.Scene.GetHashCode()];
		
		public void SetTheme(NameTheme nameTheme)
		{
			switch (nameTheme)
			{
				case NameTheme.Dark:
					{
						SystemBar(Brushes.Yellow);
						ToolBar(Brushes.YellowGreen);
						Scene(Brushes.White);
						BackGround(Brushes.Black);
						break;
					}
				case NameTheme.Light:
					{
						SystemBar(Brushes.LightBlue);
						ToolBar(Brushes.White);
						Scene(Brushes.DarkCyan);
						BackGround(Brushes.White);
						break;
					}
				case NameTheme.Neutral:
					{
						SystemBar(Brushes.Yellow);
						ToolBar(Brushes.YellowGreen);
						Scene(Brushes.White);
						BackGround(Brushes.Black);
						break;
					}
				case NameTheme.Gradient:
					{
						SystemBar(Brushes.Yellow);
						ToolBar(Brushes.YellowGreen);
						Scene(Brushes.White);
						BackGround(Brushes.Black);
						break;
					}
			}
			PropertyChanged(this, new PropertyChangedEventArgs(nameof(colors)));
		}
	}
}
