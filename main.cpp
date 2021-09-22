#include <string>
#include <iostream>

#include "ui_container.h"
#include "image_loader.h"


using namespace std;


//toggle widget visibility
//GtkWidget receiver, Gpointer data
void wdk_toggle_visibility(GtkWidget* cbx, gpointer data){

	//get widget
	GtkWidget* wid = GTK_WIDGET(data);

	//check its 'manual'
	if (gtk_combo_box_get_active(GTK_COMBO_BOX(cbx)) == 0){
		gtk_widget_show(GTK_WIDGET(wid));
	}
	else{
		gtk_widget_hide(GTK_WIDGET(wid));
	}

	cout << "combo box toggled to: " << (int) gtk_combo_box_get_active(GTK_COMBO_BOX (cbx)) << endl;
}

int
main (int argc, char **argv){

	string path = "/home/woynert/Pictures/NewTux.svg";

	//ui container
	UIContainer ui;
	ui.path = path;

	GtkBuilder* builder;

	//start gtk
	gtk_init ( &argc , &argv );

	//build interface
	builder = gtk_builder_new();
	if (gtk_builder_add_from_file (builder, "./ui/builder.ui", &ui.error) == 0 ){
		g_printerr ( "Error loading file: %s\n", ui.error -> message );
		g_clear_error ( &ui.error );
		return 1;
	}

	//get window
	ui.window = gtk_builder_get_object (builder, "window");
	g_signal_connect ( ui.window, "destroy", G_CALLBACK (gtk_main_quit), NULL);

	//get drawing area
	ui.drawimage = gtk_builder_get_object(builder, "drw_imagePreview");
	ui.simg = new WidScaledImage(ui.drawimage);
	//ui.simg->set_path(ui.path);
	//ui.simg->load_image(ui.error);

	//signal needs a callback method (g handler) and a pointer with info (void*) or (gpointer)
	g_signal_connect ( ui.drawimage, "draw", G_CALLBACK (&WidScaledImage::do_draw), ui.simg);




	//wallpaper manager
	ui.cbxWppMgr = gtk_builder_get_object (builder, "cbxWallpaperManager");

	//populate combobox
	gtk_combo_box_text_append (GTK_COMBO_BOX_TEXT (ui.cbxWppMgr), NULL, "Manual");
	gtk_combo_box_text_append (GTK_COMBO_BOX_TEXT (ui.cbxWppMgr), NULL, "Nitrogen");
	gtk_combo_box_text_append (GTK_COMBO_BOX_TEXT (ui.cbxWppMgr), NULL, "Xfce4");

	//set default
	gtk_combo_box_set_active (GTK_COMBO_BOX (ui.cbxWppMgr), NITROGEN);




	//manual config container
	ui.boxManualWallpaper = gtk_builder_get_object (builder, "boxManualWallpaper");

	//set signal
	g_signal_connect ( ui.cbxWppMgr, "changed", G_CALLBACK (wdk_toggle_visibility), ui.boxManualWallpaper);




	//button load wallpaper from manager
	ui.btnLoadWallpaper = gtk_builder_get_object (builder, "btnLoadWallpaper");

	//set signal
	g_signal_connect ( ui.btnLoadWallpaper, "clicked", G_CALLBACK (load_image_and_show), &ui);


	gtk_main();

	return 0;

}
