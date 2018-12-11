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
	public class DialogService
	{
		public string FilePath { get; set; }

		public bool OpenFileDialog()
		{
			OpenFileDialog openFileDialog = new OpenFileDialog();
			openFileDialog.Filter = "(*.svg)|*.svg";
			if (openFileDialog.ShowDialog() == true)
			{
				FilePath = openFileDialog.FileName;
				return true;
			}
			return false;
		}

		public bool AddFileDialog()
		{
			OpenFileDialog addFileDialog = new OpenFileDialog();
			addFileDialog.Title = "Добавление";
			addFileDialog.Filter = "(*.svg)|*.svg";
			if (addFileDialog.ShowDialog() == true)
			{
				FilePath = addFileDialog.FileName;
				return true;
			}
			return false;
		}

		public bool SaveAsFileDialog()
		{
			SaveFileDialog saveAsFileDialog = new SaveFileDialog();

			saveAsFileDialog.Filter = "(*.svg)|*.svg";
			if (saveAsFileDialog.ShowDialog() == true)
			{
				FilePath = saveAsFileDialog.FileName;
				return true;
			}
			return false;
		}

		public bool NewFileDialog()
		{
			SaveFileDialog newFileDialog = new SaveFileDialog();
			newFileDialog.Title = "Создание";
			newFileDialog.Filter = "(*.svg)|*.svg";
			if (newFileDialog.ShowDialog() == true)
			{
				FilePath = newFileDialog.FileName;
				return true;
			}
			return false;
		}

		public bool ScriptDialog()
		{
			OpenFileDialog scriptDialog = new OpenFileDialog();
			scriptDialog.Title = "Загрузка скрипта";
			scriptDialog.Filter = "(*.dps)|*.dps";
			if (scriptDialog.ShowDialog() == true)
			{
				FilePath = scriptDialog.FileName;
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

		ViewModel viewModel;

		// команда сохранения файла в новый файл
		private RelayCommand saveAsCommand;
		public RelayCommand SaveAsCommand
		{
			get
			{
				return saveAsCommand ??
				  (saveAsCommand = new RelayCommand(obj =>
				  {
					  try
					  {
						  if (dialogService.SaveAsFileDialog() == true)
						  {
							  viewModel.SetEvent(ViewModel.Event.ev_saveAsFile, new double[0], dialogService.FilePath);
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
						  viewModel.SetEvent(ViewModel.Event.ev_saveFile, new double[0]);
						  dialogService.ShowMessage("File is save!");
					  }
					  catch (Exception ex)
					  {
						  dialogService.ShowMessage(ex.Message);
					  }
				  }));
			}
		}

		// команда создания файла
		private RelayCommand newCommand;
		public RelayCommand NewCommand
		{
			get
			{
				return newCommand ??
				  (newCommand = new RelayCommand(obj =>
				  {
					  try
					  {
						  if (dialogService.NewFileDialog() == true)
						  {
							  viewModel.SetEvent(ViewModel.Event.ev_newFile, new double[0], dialogService.FilePath);
							  dialogService.ShowMessage("File is created!");
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
							  viewModel.SetEvent(ViewModel.Event.ev_openFile, new double[0], dialogService.FilePath);
							  dialogService.ShowMessage("File is opened!");
						  }
					  }
					  catch (Exception ex)
					  {
						  dialogService.ShowMessage(ex.Message);
					  }
				  }));
			}
		}

		// команда добавления файла
		private RelayCommand addCommand;
		public RelayCommand AddCommand
		{
			get
			{
				return addCommand ??
				  (addCommand = new RelayCommand(obj =>
				  {
					  try
					  {
						  if (dialogService.AddFileDialog() == true)
						  {
							  viewModel.SetEvent(ViewModel.Event.ev_addFile, new double[0], dialogService.FilePath);
							  dialogService.ShowMessage("File is added!");
						  }
					  }
					  catch (Exception ex)
					  {
						  dialogService.ShowMessage(ex.Message);
					  }
				  }));
			}
		}

		// команда добавления скрипта
		private RelayCommand scriptCommand;
		public RelayCommand ScriptCommand
		{
			get
			{
				return scriptCommand ??
				  (scriptCommand = new RelayCommand(obj =>
				  {
					  try
					  {
						  if (dialogService.ScriptDialog() == true)
						  {
							  viewModel.SetEvent(ViewModel.Event.ev_compile, new double[0], dialogService.FilePath);
							  dialogService.ShowMessage("Script is loaded!");
						  }
					  }
					  catch (Exception ex)
					  {
						  dialogService.ShowMessage(ex.Message);
					  }
				  }));
			}
		}

		private FileDialog()
		{
			dialogService = new DialogService();
			viewModel = ViewModel.GetInstance();
		}

		private static FileDialog instance = null;

		public static FileDialog GetInstance()
		{
			if (instance == null)
			{
				instance = new FileDialog();
			}
			return instance;
		}

		public event PropertyChangedEventHandler PropertyChanged;
		public void OnPropertyChanged([CallerMemberName]string prop = "")
		{
			if (PropertyChanged != null)
				PropertyChanged(this, new PropertyChangedEventArgs(prop));
		}
	}
}