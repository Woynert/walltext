#include <gtk/gtk.h>
using namespace std;

class PictureView{
private:
	GObject* da; //drawing area
	GdkPixbuf *pixbuf; //pixbuf
 	cairo_surface_t *img_surface; //cairo surface
	string path; //image path

public:
	//constructor
	PictureView(GObject* da, string path, GError* error){
		this->da = da;
		this->path = path;
		this->pixbuf = gdk_pixbuf_new_from_file((this->path).c_str(), &error);
		this->img_surface = gdk_cairo_surface_create_from_pixbuf(this->pixbuf, 1, NULL);
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

		// functions from /usr/include/cairo/cairo.h
		// draw the surface
		cairo_scale(cr, sf, sf);
		cairo_set_source_surface(cr, pv->img_surface, 0, 0);
		cairo_paint(cr);

		int height = 100;
		gtk_widget_set_size_request(GTK_WIDGET(pv->da), -1, height );
	}
};
