#include <string>
#include <iostream>
#include <gtk/gtk.h>
using namespace std;

class PictureView{
private:
	//GtkDrawingArea *da; //drawing area
	GObject* da;
	GdkPixbuf *pixbuf; //pixbuf
 	cairo_surface_t *img_surface; //cairo surface
	string path;

public:
	//constructor
	PictureView(GObject* da, string path, GError* error){
		this->da = da;
		this->path = path;
		this->pixbuf = gdk_pixbuf_new_from_file((this->path).c_str(), &error);
		this->img_surface = gdk_cairo_surface_create_from_pixbuf(this->pixbuf, 1, NULL);
		//Null = 0
	}

	int get_useful_height(){
		float aw, pw, ph;
		aw = gtk_widget_get_allocated_width( GTK_WIDGET(this->da) );
		pw = gdk_pixbuf_get_width( this->pixbuf );
		ph = gdk_pixbuf_get_height( this->pixbuf );
		return (aw/pw) * ph;
	}

	float get_scale_factor(){
        float aw, pw;
        aw = gtk_widget_get_allocated_width( GTK_WIDGET(this->da) );
        pw = gdk_pixbuf_get_width( this->pixbuf );
        cout << aw/pw << endl;
        return (float) aw/pw;
	}

	//estos argumentos provienen del evento 'draw' de GtkDrawingArea
	static void do_draw(GtkWidget *widget, cairo_t *cr, gpointer data){

		//cast to PictureView*
		PictureView* pv = (PictureView*) data;
		cout << pv->path << endl;

		float sf = pv->get_scale_factor();
		cout << "sf: " << sf << endl;

		//functions from /usr/include/cairo/cairo.h
		cairo_scale(cr, sf, sf);
		cairo_set_source_surface(cr, pv->img_surface, 0, 0);
		cairo_paint(cr);
		/* draw circle */

	 	cairo_set_source_rgb(cr, 0.17, 0.63, 0.12);
	   	cairo_set_line_width(cr,2);
	   	cairo_arc(cr, 150, 210, 20, 0, 2*G_PI);
	   	cairo_stroke(cr);

		int height = 100;
		gtk_widget_set_size_request(GTK_WIDGET(pv->da), -1, height );
	}
};


int
main (int argc, char **argv){

	string path = "/home/woynert/Pictures/mario-galaxy.jpeg";

	GtkBuilder *builder;
	//GtkDrawingArea *drawimage;
	GObject *drawimage;
	GError *error = NULL;

	//start gtk
	gtk_init ( &argc , &argv );

	//build interface
	builder = gtk_builder_new();
	if (gtk_builder_add_from_file (builder, "builder.glade", &error) == 0 ){
		g_printerr ( "Error loading file: %s\n", error -> message );
		g_clear_error ( &error );
		return 1;
	}

	//get object
	drawimage = gtk_builder_get_object(builder, "drw_imagePreview");
	//GtkDrawingArea* da = drawimage;

	PictureView* pv = new PictureView(drawimage, path, error);
	//gpointer p = &pv;

	//signal needs a callback method (g handler) and a pointer with info (void*) or (gpointer)
	g_signal_connect ( drawimage, "draw", G_CALLBACK (&PictureView::do_draw), pv);


	gtk_main();
	//gtk_main_quit();

	return 0;

}
