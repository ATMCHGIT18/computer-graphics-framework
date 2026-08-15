#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <./che_framework_graphics.hpp>

// Calling the namespace as cgf like che_graphics_framework
namespace cgf{

	/*Create a Window. Window object will create Terminal itself so you need only to put it there the name and font size.
	You can have only one Window object*/
	class Window{
	private:
		int height;
		int width;
		int resolution_X;
		int resolution_Y;
		float size_res_x;
		float size_res_y;
		float font_size = 1.0f;
		PixelMatrix pixels;
		TerminalLauncher terminal;
	public:
		Window(int height, int width, float font_size, std::string application_name)
        : height(height), width(width),
          resolution_X(width), resolution_Y(height), // same for now, split later if needed
          font_size(font_size),
          pixels(width, height),
          terminal(application_name, height, width, font_size)
    	{}

    	static Window headless(int height, int width) {
        	Window w(height, width);
        	return w;
    	}


		void print(){
			std::cout << "Height: " << this->height << " Width: " << this->width << std::endl;
		}

		PixelMatrix& get_pixels(){return this->pixels;}

		int get_width() const {return this->width;}
		int get_height() const {return this->height;}
		std::vector<int> get_resolution() const {return {this->resolution_X,this->resolution_Y};}
		bool is_open() const {return terminal.is_open();}

		// std::vector<int,int> get() {return std::vector<this->height,this->width>;}


		void show() {
		    std::cout << "\033[2J\033[H";
		    for (int y = 0; y < height; y++) {
		        for (int x = 0; x < width; x++) {
		            auto& p = pixels.at(x, y);
		            std::cout << "\033[38;2;" << (int)p.red << ";" << (int)p.green << ";" << (int)p.blue << "m"
		                       << "██"; // one logical pixel = 2 terminal columns, same row
		        }
		        std::cout << "\033[0m\n";
		    }
		}

		void close(){terminal.close();}

		void set_terminal(std::string app_name,float font_size){
			this->terminal = TerminalLauncher(app_name,this->height,this->width,font_size);
			std::cout << "Termianl has set" << std::endl;
		}

	private:
    Window(int height, int width)
        : height(height), width(width),
          resolution_X(width), resolution_Y(height),
          pixels(width, height)
    {}

	};


	class Renderer{
	private:
		Image& image ;
		Window& window ;
	public:
		Renderer(Window& window,Image& image):image(image),window(window){}

		Image& get_image() const {return image;}
		Window& get_window() const {return window;}

		// In what position the window should start and the image should be rendered there
		int render(int start_x, int start_y)
		{
		    int win_w = window.get_width();
		    int win_h = window.get_height();

		    int img_w = image.get_width();
		    int img_h = image.get_height();

		    for (int y = 0; y < img_h; ++y)
		    {
		        for (int x = 0; x < img_w; ++x)
		        {
		            int window_x = start_x + x;
		            int window_y = start_y + y;

		            // Don't render outside the window
		            if (window_x < 0 || window_x >= win_w ||
		                window_y < 0 || window_y >= win_h)
		            {
		                continue;
		            }

		            window.get_pixels().at(window_x, window_y) = image.at(x, y);
		        }
		    }

		    return 1;
		}
	};

};

#endif