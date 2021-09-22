#include <string>
#include <sys/stat.h>
#include <iostream>

#include "exec.h"

using namespace std;

class ImageLoader{
private:
	string path;
	
public:

	void set_path(string path){
		this->path = path;
	}

	string get_path(){
		return this->path;
	}

	//check the image exists
	bool image_exists(){
		struct stat buffer;
		return (stat (this->path.c_str(), &buffer) == 0);
	}

	//select a path
	void get_path_from_wallpaper_manager(int wppmgr){
		string command;
		string newpath;

		switch (wppmgr){
			case MANUAL:
				break;
			case NITROGEN:
				command = "bash ./sh/nitrogen_image_path.sh";
				newpath = exec(command.c_str());
				cout << "extracted image path: " << newpath;
				break;

			case XFCE4:
				break;
		}

		//set
		this->set_path(newpath);
	}

	void load_image(){
	}
};

//click event
void load_image_and_show(GtkWidget* btn, gpointer data){

	//get widget
	UIContainer* ui = (UIContainer*) data;

	cout << "loading image "<< ui->path << endl;

	ImageLoader* imgload = new ImageLoader();

	//set path
	imgload->get_path_from_wallpaper_manager((int) gtk_combo_box_get_active(GTK_COMBO_BOX (ui->cbxWppMgr)));

	//check it exists
	cout << "current path:" << imgload->get_path().c_str() << "." << endl;

	//DEBUG
	//imgload->set_path("/home/woynert/Pictures/NewTux.svg");
	//cout << "1. "<< imgload->image_exists() << endl;

	//imgload->set_path("/data/Biblioteca/Pictures/Wallpapers/1629764445756.jpg");
	//cout << "2. "<< imgload->image_exists() << endl;

	if (!imgload->image_exists()){
		cout << "Image does not exists." << endl;
		return;
	}

	//load image
	ui->simg->set_path(imgload->get_path());
	ui->simg->load_image(ui->error);

	//force update
	ui->simg->update_drawing_area();

}
