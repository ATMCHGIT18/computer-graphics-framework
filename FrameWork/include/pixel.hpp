#ifndef PIXEL_HPP
#define PIXEL_HPP

#include <./che_framework_graphics.hpp>

namespace cgf{
	
	class Image{
	private:
		int width;
		int height;
		std::vector<Color> pixels;

	public:
		Image(int height,int width):width(width), height(height),pixels(width*height,Color(0.0f,0.0f,0.0f)){}
		Image(int height,int width,Color& background_color):width(width), height(height),pixels(width*height,background_color){}
		Image(int height,int width,const Color& background_color):width(width), height(height),pixels(width*height,background_color){}

		Color& at(int x,int y){return pixels[y * width + x];}

		int get_width() const {return width;}

		int get_height() const {return height;}

		void set_pixel(int x , int y,Color& col){
			at(x,y) = col;
		}

	};

	class SampleBuffer{
	private:
		int image_width;
		int image_height;

		int sample_size;

		std::vector<Color> samples;
	public:
		SampleBuffer(int image_width, int image_height, int sample_size):image_width(image_width),
			image_height(image_height),
			sample_size(sample_size),
			samples(image_height*image_width*sample_size){}

		Color& at(int x ,int y, int sample_number) {
			int s = (sample_number <= 2) ? 1 : 0;
			int sample_x = sample_size * x - (sample_number%2);
			int sample_y = sample_size * y - s;
			return samples[sample_y * image_width * sample_size + sample_x];
		}

		const Color& at(int x ,int y, int sample_number) const {
			int s = (sample_number <= 2) ? 1 : 0;
			int sample_x = sample_size * x - (sample_number%2);
			int sample_y = sample_size * y - s;
			return samples[sample_y * image_width * sample_size + sample_x];
		}

		int get_width() const {return image_width*sample_size;}
		int get_height() const {return image_height*sample_size;}

		Image& convert_to_image(Image& image,Color& background_color){
			
			for (int j = 0; j < image_width; j++){
				for (int i = 0; i < image_height;i++){
					Color newCol = (at(i,j,1) + at(i,j,2) + at(i,j,3) + at(i,j,4)) * 0.25f;
					image.set_pixel(i,j,newCol);
				}
			}
			return image;
		}

	private:
		Color coverage(Color& now, Color& back, float coverage){
			return now * coverage + back*(1.0f-coverage);
		}

	};

	class PixelMatrix{
	private:
		int width;
		int height;
		std::vector<Pixel> pixels; // flatten the 2d pixel matrix  index = y * width + x

		int index(int x ,int y) const {
			if (x<0  || y < 0 || x>=width || y>=height){
				throw std::runtime_error("PixelMatrix: coordinate out of range.");
			}

			return y * width + x;
		}
	public:
		PixelMatrix() = default;
		PixelMatrix(int width, int height)
        	: width(width), height(height), pixels(width * height, Pixel{})
    	{}

		Pixel& at(int x,int y){
			return pixels[index(x,y)];
		}

		const Pixel& at(int x, int y) const {
			return pixels[index(x,y)];
		}

		void set_pixel(int x, int y, std::vector<int> colors){
			Pixel& selected_pixel = this->at(x,y);
			if (colors.size() == 4)
				{
					selected_pixel = {colors[0],colors[1],colors[2],colors[3]};
				}
			else if (colors.size() == 3)
				{
					selected_pixel = {colors[0],colors[1],colors[2],0};
				}
			else 
				{
					std::cout << "The color is of " << colors.size() << " matrix which is not supported. Supported size is 3 (R,G,B), 4(R,G,B,Alpha). " << std::endl;
				}
		}

		void set_pixel(int x, int y, uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) {
        	at(x, y) = Pixel{r, g, b, a};
    	}

    	int get_width() const { return width; }
    	int get_height() const { return height; }

    	// For the transparency and alpha channel architecture, uses
    	// result = src_color * src_alpha + dst_color * (1 - src_alpha) where dst is the already color in the pixel
    	
    	// static uint8_t blend_channel(uint8_t src, uint8_t dst, uint8_t alpha) {
		//     return static_cast<uint8_t>((src * alpha + dst * (255 - alpha)) / 255);
		// }

		// void set_pixel(int x, int y, uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) {
		//     Pixel& target = at(x, y);

		//     if (a == 255) {          // fully opaque — cheap path, no math needed
		//         target = Pixel{r, g, b, 255};
		//         return;
		//     }
		//     if (a == 0) {             // fully transparent — no-op
		//         return;
		//     }

		//     // partial transparency — blend against whatever's currently there
		//     target.red   = blend_channel(r, target.red,   a);
		//     target.green = blend_channel(g, target.green, a);
		//     target.blue  = blend_channel(b, target.blue,   a);
		//     target.alpha = 255; // buffer itself stays opaque; only source pixels carry transparency
		// }

		// explicit bypass — useful for clear(), or anywhere you want a hard overwrite
		void set_pixel_raw(int x, int y, uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) {
		    at(x, y) = Pixel{r, g, b, a};
		}

		void clear(uint8_t r = 0, uint8_t g = 0, uint8_t b = 0, uint8_t a = 255) {
		    Pixel bg{r, g, b, a};
		    std::fill(pixels.begin(), pixels.end(), bg);
		}

	};
}
#endif