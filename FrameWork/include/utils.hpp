#ifndef UTILS_HPP
#define UTILS_HPP

#include <./che_framework_graphics.hpp>

namespace cgf{
	class ImageLoader{
	public:
		static Image load(const std::string& filename){
			int width = 0;
			int height = 0;
			int channels = 0;

			unsigned char* data = stbi_load(filename.c_str(),&width,&height,&channels,4);

			if (data == nullptr){
				throw std::runtime_error(std::string("Failed to load image: ") + stbi_failure_reason());
			}

			Image image(height,width);
			for (int y = 0; y< height ; ++y){
				for (int x=0;x<width;++x){
					int index = (y*width + x) *4;

					image.at(x,y) = Color{
						data[index+0]/255.0f,
						data[index+1]/255.0f,
						data[index+2]/255.0f,
						data[index+3]/255.0f
					};
				}
			}
			stbi_image_free(data);
			return image;
		}
	};

	static void copy_png_text(const std::string& file_path, const std::string& format) {
    std::ifstream source(file_path + "." + format, std::ios::binary);
    std::ofstream destination(file_path + ".txt", std::ios::binary);

    if (!source || !destination) {
        throw std::runtime_error("Failed to open input or output file!");
    }

    destination << source.rdbuf();
}

};
#endif