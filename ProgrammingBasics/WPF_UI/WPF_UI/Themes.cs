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
			SelectedPrim, DependentPrim, ChangingPrim, CreatingPrim, LineForCurve, Primitives,
			BackGround, Scene, SystemBar, ToolBar
		};
		
		private Themes()
		{
			colors = new SolidColorBrush[11];
			colors[NameColors.SelectedPrim.GetHashCode()] = Brushes.Green;
			colors[NameColors.DependentPrim.GetHashCode()] = Brushes.Green;
			colors[NameColors.ChangingPrim.GetHashCode()] = Brushes.Green;
			colors[NameColors.CreatingPrim.GetHashCode()] = Brushes.Green;
			colors[NameColors.LineForCurve.GetHashCode()] = Brushes.Pink;
			colors[NameColors.Primitives.GetHashCode()] = Brushes.White;
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
		public void Primitives(SolidColorBrush color) => colors[NameColors.Primitives.GetHashCode()] = color; 
		public void SelectedPrim(SolidColorBrush color) => colors[NameColors.SelectedPrim.GetHashCode()] = color; 
		public void DependentPrim(SolidColorBrush color) => colors[NameColors.DependentPrim.GetHashCode()] = color;
		public void ChangingPrim(SolidColorBrush color) => colors[NameColors.ChangingPrim.GetHashCode()] = color; 
		public void CreatingPrim(SolidColorBrush color) => colors[NameColors.CreatingPrim.GetHashCode()] = color; 
		public void LineForCurve(SolidColorBrush color) => colors[NameColors.LineForCurve.GetHashCode()] = color;

		public SolidColorBrush SystemBar() => colors[NameColors.SystemBar.GetHashCode()];
		public SolidColorBrush ToolBar() => colors[NameColors.ToolBar.GetHashCode()];
		public SolidColorBrush Scene() => colors[NameColors.BackGround.GetHashCode()];
		public SolidColorBrush BackGround() => colors[NameColors.Scene.GetHashCode()];
		public SolidColorBrush Primitives() => colors[NameColors.Primitives.GetHashCode()];
		public SolidColorBrush SelectedPrim() => colors[NameColors.SelectedPrim.GetHashCode()];
		public SolidColorBrush DependentPrim() => colors[NameColors.DependentPrim.GetHashCode()];
		public SolidColorBrush ChangingPrim() => colors[NameColors.ChangingPrim.GetHashCode()];
		public SolidColorBrush CreatingPrim() => colors[NameColors.CreatingPrim.GetHashCode()];
		public SolidColorBrush LineForCurve() => colors[NameColors.LineForCurve.GetHashCode()];

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
						Primitives(Brushes.Black);
						SelectedPrim(Brushes.Red);
						DependentPrim(Brushes.Green);
						ChangingPrim(Brushes.Green);
						CreatingPrim(Brushes.Green);
						LineForCurve(Brushes.Yellow);
						break;
					}
				case NameTheme.Light:
					{
						SystemBar(Brushes.LightBlue);
						ToolBar(Brushes.White);
						Scene(Brushes.Black);
						BackGround(Brushes.White);
						Primitives(Brushes.White);
						SelectedPrim(Brushes.Green);
						DependentPrim(Brushes.Green);
						ChangingPrim(Brushes.Green);
						CreatingPrim(Brushes.Green);
						LineForCurve(Brushes.Pink);
						break;
					}
				case NameTheme.Neutral:
					{
						SystemBar(Brushes.Yellow);
						ToolBar(Brushes.YellowGreen);
						Scene(Brushes.White);
						BackGround(Brushes.Black);
						Primitives(Brushes.Black);
						SelectedPrim(Brushes.Red);
						DependentPrim(Brushes.Green);
						ChangingPrim(Brushes.Green);
						CreatingPrim(Brushes.Green);
						LineForCurve(Brushes.Yellow);
						break;
					}
				case NameTheme.Gradient:
					{
						SystemBar(Brushes.Yellow);
						ToolBar(Brushes.YellowGreen);
						Scene(Brushes.White);
						BackGround(Brushes.Black);
						Primitives(Brushes.Black);
						SelectedPrim(Brushes.Red);
						DependentPrim(Brushes.Green);
						ChangingPrim(Brushes.Green);
						CreatingPrim(Brushes.Green);
						LineForCurve(Brushes.Yellow);
						break;
					}
			}
			PropertyChanged(this, new PropertyChangedEventArgs(nameof(colors)));
		}
	}
}
