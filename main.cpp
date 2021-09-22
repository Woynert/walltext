#include <string>
#include <iostream>
#include "wgt_scaled_image.h"
//#include <gtk/gtk.h>

using namespace std;


int
main (int argc, char **argv){

	string path = "/home/woynert/Pictures/NewTux.svg";

	GtkBuilder* builder;
	GObject* window;
	GObject* drawimage; //gtk drawing area
	GError* error = NULL;

	//start gtk
	gtk_init ( &argc , &argv );

	//build interface
	builder = gtk_builder_new();
	if (gtk_builder_add_from_file (builder, "builder.glade", &error) == 0 ){
		g_printerr ( "Error loading file: %s\n", error -> message );
		g_clear_error ( &error );
		return 1;
	}

	//get window
	window = gtk_builder_get_object (builder, "window");
	g_signal_connect ( window, "destroy", G_CALLBACK (gtk_main_quit), NULL);

	//get drawing area
	drawimage = gtk_builder_get_object(builder, "drw_imagePreview");
	PictureView* pv = new PictureView(drawimage, path, error);

	//signal needs a callback method (g handler) and a pointer with info (void*) or (gpointer)
	g_signal_connect ( drawimage, "draw", G_CALLBACK (&PictureView::do_draw), pv);



	//wallpaper manager
	GObject* cbxWppMgr = gtk_builder_get_object (builder, "cbxWallpaperManager");

	//populate combobox
	gtk_combo_box_text_append (GTK_COMBO_BOX_TEXT (cbxWppMgr), "0", "Manual");
	gtk_combo_box_text_append (GTK_COMBO_BOX_TEXT (cbxWppMgr), "1", "Nitrogen");
	gtk_combo_box_text_append (GTK_COMBO_BOX_TEXT (cbxWppMgr), "2", "Xfce4");

	//set default
	gtk_combo_box_set_active (GTK_COMBO_BOX (cbxWppMgr), 0);


	gtk_main();

	return 0;

}
