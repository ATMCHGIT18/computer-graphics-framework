#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <./che_framework_graphics.hpp>

// Calling the namespace as cgf like che_graphics_framework
namespace cgf{

	/*Create a Window. Window object will create Terminal itself so you need only to put it there the name and font size.
	You can have only one Window object*/

	class WindowTerminal{
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
		WindowTerminal(int height, int width, float font_size, std::string application_name)
        : height(height), width(width),
          resolution_X(width), resolution_Y(height), // same for now, split later if needed
          font_size(font_size),
          pixels(width, height),
          terminal(application_name, height, width, font_size)
    	{}

    	static WindowTerminal headless(int height, int width) {
        	WindowTerminal w(height, width);
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
		                       << "███"; // one logical pixel = 2 terminal columns, same row
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
    WindowTerminal(int height, int width)
        : height(height), width(width),
          resolution_X(width), resolution_Y(height),
          pixels(width, height)
    {}

	};


	#if defined(__linux__)
	class Window_X11{
	public:
		int width;
		int height;
		PixelMatrix pixels;
		Display* display;
		int screen;
		Window window;
		GC gc;
		Visual* visual;
		int depth;

		Window_X11(int w, int h): width(w),height(h),pixels(width,height){
			createWindow();
		}
		Window_X11(int w,int h, PixelMatrix& vertices): width(w),height(h),pixels(vertices){}
		~Window_X11(){
			XCloseDisplay(display);
		}

		int get_width() {return width;}
		const int get_width() const {return width;}

		int get_height(){return height;}
		const int get_height() const {return height;}

		PixelMatrix& get_pixels() {return pixels;}
		const PixelMatrix& get_pixels() const {return pixels;}


	private:
		void createWindow(){
			display = XOpenDisplay(nullptr);

			if(!display){
				std::cerr << "Failed to open X display!" << std::endl;
				return;
			}

			screen = DefaultScreen(display);

			window = XCreateSimpleWindow(
				display,
				RootWindow(display,screen),
				100,
				100,
				width,
				height,
				1,
				WhitePixel(display,screen),
				BlackPixel(display,screen)
				);

			XSelectInput(display,window,ExposureMask | StructureNotifyMask | KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask | ButtonMotionMask | PointerMotionMask);

			XMapWindow(display,window);

			gc = XCreateGC(display,window,0,nullptr);
			visual = DefaultVisual(display,screen);
			depth = DefaultDepth(display,screen);

			XFlush(display);
		}
		void copy_to_ximage(Matrix& matrix,XImage* image){
		    uint32_t* destination = reinterpret_cast<uint32_t*>(image->data);

		    int stride =
		        image->bytes_per_line / sizeof(uint32_t);

		    for (int y = 0; y < matrix.get_height(); ++y)
		    {
		        for (int x = 0; x < matrix.get_width(); ++x)
		        {
		            const Pixel& p =
		                matrix.at(x,y);

		            if (p.alpha == 0) continue;

		            uint32_t xpixel =
		                  (static_cast<uint32_t>(p.red)   << 16)
		                | (static_cast<uint32_t>(p.green) << 8)
		                |  static_cast<uint32_t>(p.blue);

		            destination[y * stride + x] = xpixel;
		        }
		    }
		}
	};
	#endif


	class Renderer{
	private:
		PixelMatrix& pixels;
	public:
		Renderer(PixelMatrix& pixels):pixels(pixels){}

		int render(Image& image,int start_x, int start_y)
		{
		    int win_w = pixels.get_width();
		    int win_h = pixels.get_height();

		    int img_w = image.get_width();
		    int img_h = image.get_height();

		    for (int y = 0; y < img_h; ++y)
		    {
		        for (int x = 0; x < img_w; ++x)
		        {
		            int pixels_x = start_x + x;
		            int pixels_y = start_y + y;

		            // Don't render outside the window
		            if (pixels_x < 0 || pixels_x >= win_w ||
		                pixels_y < 0 || pixels_y >= win_h)
		            {
		                continue;
		            }

		            if(image.at(x,y).alpha == 0){
		            	continue;
		            }

		            pixels.at(pixels_x, pixels_y) = image.at(x, y);
		        }
		    }
		    return 1;
		}

		// Primitive renders _ low level renders

		void render_pixel(int x, int y,Color& col){
			if(x >= 0 && y >= 0 && x < pixels.get_width() && y < pixels.get_height()){
				if (col.alpha != 0){
					pixels.at(x,y) = col;
				}
			}
		}
		void render_pixel(int x, int y,const Color& col){
			if(x >= 0 && y >= 0 && x < pixels.get_width() && y < pixels.get_height()){
				if (col.alpha != 0){
					pixels.at(x,y) = col;
				}
			}
		}

		/* Rendering a line with having a two end points.
		algorithms codes are :
		1. DDA : d
		2. Bresenham Line Generation : b
		3. Mid-point line generation: m*/
		void render_line(Point2D& p1,Point2D& p2,Color& col,char& algorithm_code){

			switch (algorithm_code){
				case 'd':
					Algo::Line::dda(p1,p2,pixels,col);
					return;
				case 'b':
					Algo::Line::bresenham(p1,p2,pixels,col);
					return;
				case 'm':
					Algo::Line::mid_point(p1,p2,pixels,col);
					return;
				default:
					std::cout << "The selected code does not exists but as default programme uses mid point algorithms" << std::endl;
					Algo::Line::mid_point(p1,p2,pixels,col);
					return;
			}

		}
		void render_line(Point2D& p1,Point2D& p2,const Color& col,const char& algorithm_code){

			switch (algorithm_code){
				case 'd':
					Algo::Line::dda(p1,p2,pixels,col);
					return;
				case 'b':
					Algo::Line::bresenham(p1,p2,pixels,col);
					return;
				case 'm':
					Algo::Line::mid_point(p1,p2,pixels,col);
					return;
				default:
					std::cout << "The selected code does not exists but as default programme uses mid point algorithms" << std::endl;
					Algo::Line::mid_point(p1,p2,pixels,col);
					return;
			}

		}

		/*Render a trangle with having 3 points and then now we could decide what to put inside of it.
		We could use the implemented algorithms of filling.*/

		void render_triangle(){}

		/*Render a rectangle using 4 points and have a variable to make it filled or not filled with color
		or another things like a sprit or something else.*/
		void render_rectangle(){}
	};

	#if defined(__linux__)
	class Renderer_X11{
	private:
		PixelMatrix& pixels;
		Window_X11& window;
	public:
		Renderer_X11(PixelMatrix& pixel,Window_X11& win):pixels(pixel),window(win){}

			void render(Point2D& start,Matrix& matrix_buff){
				XImage* image = XCreateImage(
									        window.display,
									        window.visual,
									        window.depth,
									        ZPixmap,
									        0,
									        nullptr,
									        matrix_buff.get_width(),
									        matrix_buff.get_height(),
									        32,
									        0);

			 	if (!image)
		   		{
		        std::cerr << "Failed to create XImage\n";
		        return;
		    	}

		    	image->data = new char[
		        	image->bytes_per_line * image->height
		    	];

				copy_to_ximage(matrix_buff,image);

				XPutImage(window.display,window.window,window.gc,image,0,0,start.x,start.y,window.get_width(),window.get_height());
				XDestroyImage(image);
				XFlush(window.display);
			}

	private:
		void copy_to_ximage(Matrix& matrix,XImage* image){
		    uint32_t* destination = reinterpret_cast<uint32_t*>(image->data);

		    int stride =
		        image->bytes_per_line / sizeof(uint32_t);

		    for (int y = 0; y < matrix.get_height(); ++y)
		    {
		        for (int x = 0; x < matrix.get_width(); ++x)
		        {
		            const Pixel& p =
		                matrix.at(x,y);

		            if (p.alpha == 0) continue;

		            uint32_t xpixel =
		                  (static_cast<uint32_t>(p.red)   << 16)
		                | (static_cast<uint32_t>(p.green) << 8)
		                |  static_cast<uint32_t>(p.blue);

		            destination[y * stride + x] = xpixel;
		        }
		    }
		}
	};
	#endif

};

#endif