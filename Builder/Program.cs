using System;
using System.Collections.Generic;
using System.Windows.Forms;
using OpenGUI_Net;

namespace Builder {

	static class Program {
		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		[STAThread]
		static void Main() {
			Radian r1, r2;
			r1.fValue = 4;
			r2.fValue = 5;
			TestRenderer render = new TestRenderer();
			OpenGUI_Net.System sys = OpenGUI_Net.System.initialize( render );
			Viewport vp = render.getViewport();
			FVector2 size;
			size.x = 800;
			size.y = 600;
			OpenGUI_Net.Screen screen = OpenGUI_Net.ScreenManager.getHandle().createScreen( "test", size );
			OpenGUI_Net.ScreenManager.getHandle().destroyScreen( screen );
			sys.shutdown();
			r2 = r1 + r2;
			r1 = r1 - r2;
			OpenGUI_Net.Widget w = new OpenGUI_Net.Widget();
			List<Widget> wl = w.getChildrenAt(size);

			//wa;
			TextAlignment ta;
			ta.horizontal = TextAlignment.Alignment.LEFT;
			ta.vertical = TextAlignment.Alignment.CENTER;

			Color c = Color.PresetWhite();
			c = Color.PresetGreen();

			Application.EnableVisualStyles();
			Application.SetCompatibleTextRenderingDefault( false );
			Application.Run( new Form1() );
		}
	}
}
