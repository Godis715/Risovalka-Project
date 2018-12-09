using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Controls;

using KernelWrapper;

namespace WPF_UI
{
	class ViewModel : INotifyPropertyChanged
	{
		public event PropertyChangedEventHandler PropertyChanged;

		private MailBoxWrapper mailBox;

		public enum Event
		{
			// create primitive
			ev_createPoint = 1,
			ev_createSegment,
			ev_createStar,
			ev_createBrokenLine,
			ev_createArc,
			ev_createCircle,
			ev_createCurve,
			// drawingMode
			ev_symmetricalDraw,
			ev_defualtDraw,
			ev_rotationDraw,
			//create requirements
			ev_req_D_point,
			ev_req_Eq_Segment,
			ev_req_on_one_hand,
			ev_req_D_point_segment,
			ev_req_D_point_arc,
			ev_req_angle_segment,
			ev_input,
			//fase create requirements
			ev_req_D_point_fast,
			ev_req_Eq_point_fast,
			// redaction
			ev_moveObjects,
			ev_scaleObjects,
			ev_rotateObjects,
			ev_del,
			ev_delAll,
			ev_undo,
			ev_redu,

			// mouseEvent
			ev_leftMouseClick,
			ev_rightMouseClick,
			ev_leftMouseDown,
			ev_rightMouseDown,
			ev_leftMouseUp,
			ev_rightMouseUp,
			ev_mouseMove,
			ev_scroll,
			// keyboardEvent
			ev_ctrlDown,
			ev_ctrlUp,
			ev_altDown,
			ev_altUp,
			ev_arrowUp,
			ev_arrowDown,
			ev_arrowLeft,
			ev_arrowRight,
			ev_escape,
			ev_enter,
			// Widjets
			ev_click_Req,
			ev_change_Prim,
			ev_change_Req,
			ev_delete_Req,
			ev_delete_display_Prim,
			ev_delete_display_Req,
			// file work
			ev_save,
			ev_download,
			ev_compile,
			ex_set_theme
		};

		public string CurrentState { get; set; }

		private ViewModel()
		{
			mailBox = new MailBoxWrapper();
		}

		private static ViewModel instance = null;

		public static ViewModel GetInstance()
		{
			if (instance == null)
			{
				instance = new ViewModel();
			}
			return instance;	
		}

		public void SetEvent(Event ev, double[] arrParams, string str = "")
		{
			if (str.Equals(""))
			{
				mailBox.SendEvent(ev.GetHashCode(), arrParams);
			}
			else
			{
				mailBox.SendEvent(ev.GetHashCode(), arrParams, str);
			}
		}


	}
}
