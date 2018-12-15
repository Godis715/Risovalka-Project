using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;

using KernelWrapper;

namespace WPF_UI
{
	class ViewModel : INotifyPropertyChanged
	{
		public event PropertyChangedEventHandler PropertyChanged;

		private MailBoxWrapper mailBox;

		private ControlScene controlScene;

		private ControlInterface controlInterface;

		public void Initializated(){}

		public string CurrentState { get; set; }

		public string CursorPosition { get; set; }

		public void SetNewCursorPosition(double X, double Y)
		{
			CursorPosition = "X: " + X.ToString() + " | Y: " + Y.ToString();
			PropertyChanged(this, new PropertyChangedEventArgs(nameof(CursorPosition)));
		}

		private ViewModel()
		{
			mailBox = new MailBoxWrapper();
			controlInterface = ControlInterface.GetInstance();
			controlScene = ControlScene.GetInstance();
			CursorPosition = "X: | Y: ";
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

		enum Code
		{
			draw_point = 0,
			draw_segment,
			draw_circle,
			draw_arc,
			draw_curve,
			properties_point = 10,
			properties_segment,
			properties_circle,
			properties_arc,
			properties_req,
			set_style = 20,
			possible_req,
			translate_scene,
			scale_scene,
			rotate_scene,
			current_draw_mode,
			delete_req_input,

            draw_sign,
        };

		private void MessageHandling(MessageWrapper message)
		{
			switch ((Code)message.GetCode())
			{
				case Code.draw_point:
					{
						controlScene.DrawPoint(new Vector(message.GetDoubleArr()[0], message.GetDoubleArr()[1]));
						break;
					}
				case Code.draw_segment:
					{
						controlScene.DrawLine(new Vector(message.GetDoubleArr()[0], message.GetDoubleArr()[1]),
							new Vector(message.GetDoubleArr()[2], message.GetDoubleArr()[3]));
						break;
					}
				case Code.draw_circle:
					{
						controlScene.DrawCircle(message.GetDoubleArr());
						break;
					}
				case Code.draw_arc:
					{
						controlScene.DrawArc(message.GetDoubleArr());
						break;
					}
				case Code.draw_curve:
					{
						controlScene.DrawCurve(message.GetDoubleArr());
						break;
					}
				case Code.properties_point:
					{
						break;
					}
				case Code.properties_segment:
					{
						break;
					}
				case Code.properties_circle:
					{
						break;
					}
				case Code.properties_arc:
					{
						break;
					}
				case Code.properties_req:
					{
						break;
					}
				case Code.set_style:
					{
						int[] rgb = message.GetIntArr();
						controlScene.SetColor(rgb[0], rgb[1], rgb[2]);
						break;
					}
				case Code.possible_req:
					{
						controlInterface.SetRequirments(message.GetStrArr());
						break; 
					}
				case Code.translate_scene:
					{
						break; 
					}
				case Code.scale_scene:
					{
						break;
					}
				case Code.rotate_scene:
					{
						break;
					}
				case Code.current_draw_mode:
					{
						CurrentState = message.GetStrArr()[0];
						PropertyChanged(this, new PropertyChangedEventArgs(nameof(CurrentState)));
						break;
					}
				case Code.delete_req_input:
					{
						break;
					}
                case Code.draw_sign:
                    {
                        var sign = message.GetStrArr()[0];
                        var position = message.GetDoubleArr();
                        controlScene.DrawSign(sign, position);
                        break;
                    }
			}
		}

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
			ev_newFile,
			ev_openFile,
			ev_addFile,
			ev_saveAsFile,
			ev_saveFile,
			ev_compile,
			ev_set_theme,

            ev_dislayPoints,
            ev_displayParameters,
            ev_displayRequirements
        };

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
			controlScene.CleareScene();
			while(!mailBox.IsEmpty())
			{
				MessageHandling(mailBox.GetMessage());
			}
		}
	}
}
