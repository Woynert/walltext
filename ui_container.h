#include <string>
#include <gtk/gtk.h>

#include "wgt_scaled_image.h"
using namespace std;

class UIContainer{
public:
	GObject* window;

	GObject* drawimage; //gtk drawing area

	WidScaledImage* simg;

	GObject* cbxWppMgr; //combo box wallpaper manager

	GObject* boxManualWallpaper; //box manual wallpaper section

	GObject* btnLoadWallpaper; //button load wallpaper

	GError* error = NULL;

	string path;

	/*UIContainer(){
		simg = WidScaledImage();
	}*/
};
