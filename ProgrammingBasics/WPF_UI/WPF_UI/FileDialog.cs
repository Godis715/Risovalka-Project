using System.ComponentModel;
using System.Runtime.CompilerServices;
using System.Collections.ObjectModel;
using System;
using System.Linq;
using Microsoft.Win32;
using System.Windows;
using System.Windows.Input;

namespace WPF_UI
{
	public class RelayCommand : ICommand
	{
		private Action<object> execute;
		private Func<object, bool> canExecute;

		public event EventHandler CanExecuteChanged
		{
			add { CommandManager.RequerySuggested += value; }
			remove { CommandManager.RequerySuggested -= value; }
		}

		public RelayCommand(Action<object> execute, Func<object, bool> canExecute = null)
		{
			this.execute = execute;
			this.canExecute = canExecute;
		}

		public bool CanExecute(object parameter)
		{
			return this.canExecute == null || this.canExecute(parameter);
		}

		public void Execute(object parameter)
		{
			this.execute(parameter);
		}
	}

	public class DialogService
	{
		public string FilePath { get; set; }

		public bool OpenFileDialog()
		{
			OpenFileDialog openFileDialog = new OpenFileDialog();
			if (openFileDialog.ShowDialog() == true)
			{
				FilePath = openFileDialog.FileName;
				return true;
			}
			return false;
		}

		public bool SaveFileDialog()
		{
			SaveFileDialog saveFileDialog = new SaveFileDialog();
			if (saveFileDialog.ShowDialog() == true)
			{
				FilePath = saveFileDialog.FileName;
				return true;
			}
			return false;
		}

		public void ShowMessage(string message)
		{
			MessageBox.Show(message);
		}
	}

	public class FileDialog : INotifyPropertyChanged
	{
		DialogService dialogService;
		// команда сохранения файла
		private RelayCommand saveCommand;
		public RelayCommand SaveCommand
		{
			get
			{
				return saveCommand ??
				  (saveCommand = new RelayCommand(obj =>
				  {
					  try
					  {
						  if (dialogService.SaveFileDialog() == true)
						  {
							  dialogService.ShowMessage("File is save!");
						  }
					  }
					  catch (Exception ex)
					  {
						  dialogService.ShowMessage(ex.Message);
					  }
				  }));
			}
		}

		// команда открытия файла
		private RelayCommand openCommand;
		public RelayCommand OpenCommand
		{
			get
			{
				return openCommand ??
				  (openCommand = new RelayCommand(obj =>
				  {
					  try
					  {
						  if (dialogService.OpenFileDialog() == true)
						  {
							  dialogService.ShowMessage("File is open!");
							 // Console.WriteLine(dialogService.FilePath);
						  }
					  }
					  catch (Exception ex)
					  {
						  dialogService.ShowMessage(ex.Message);
					  }
				  }));
			}
		}

		public FileDialog()
		{
			dialogService = new DialogService();
		}

		public event PropertyChangedEventHandler PropertyChanged;
		public void OnPropertyChanged([CallerMemberName]string prop = "")
		{
			if (PropertyChanged != null)
				PropertyChanged(this, new PropertyChangedEventArgs(prop));
		}
	}
}