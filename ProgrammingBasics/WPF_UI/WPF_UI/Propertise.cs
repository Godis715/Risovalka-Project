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
	public partial class Propertise : INotifyPropertyChanged
	{

		public event PropertyChangedEventHandler PropertyChanged;


		private Grid fieldForDisplays;
		private ViewModel viewModel;
	}
}
