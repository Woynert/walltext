#include <string>
#include <sys/stat.h>
#include <iostream>

using namespace std;

class ImageLoader{
private:
	string path;
public:

	void set_path(string path){
		this->path = path;
	}

	bool image_exists(){
		struct stat buffer;
		return (stat (this->path.c_str(), &buffer) == 0);
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
	imgload->set_path(ui->path);

	//check it exists
	if (!imgload->image_exists()) return;
}
