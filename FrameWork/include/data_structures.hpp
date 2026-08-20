#ifndef DATA_STRUCTURES_HPP
#define DATA_STRUCTURES_HPP

#include <./che_framework_graphics.hpp>

namespace cgf{

	struct Pixel;

	struct Point2D{
		float x;
		float y;

		Point2D(float x, float y):x(x),y(y){}
		Point2D() = default;

	};

	struct Point3D{
		float x;
		float y;
		float z;
	};

	struct Color{
		float red = 0.0f;
		float green = 0.0f;
		float blue = 0.0f;
		float alpha = 1.0f;

		constexpr Color(float r, float g, float b,float a) 
        : red(r), green(g), blue(b), alpha(a) {}

		Color operator+(const Color& another){
			return Color(red + another.red,green + another.green,blue + another.blue,alpha);
		}

		Color operator*(float f){
			return Color(red*f,green*f,blue*f,alpha*f);
		}

		Color() = default;

		explicit Color(const Pixel& pixel);
	};

	namespace Colors {
        inline constexpr cgf::Color Black{0.0f, 0.0f, 0.0f,1.0f};
        inline constexpr cgf::Color White{1.0f, 1.0f, 1.0f,1.0f};
        inline constexpr cgf::Color Red{1.0f, 0.0f, 0.0f,1.0f};
        inline constexpr cgf::Color Green{0.0f, 1.0f, 0.0f,1.0f};
        inline constexpr cgf::Color Blue{0.0f, 0.0f, 1.0f,1.0f};
    }

	struct Pixel{
		uint8_t red = 0;
		uint8_t green = 0;
		uint8_t blue = 0;
		uint8_t alpha = 255;

		Pixel() = default;

		Pixel(int red, int green, int blue, int alpha = 255)
            : red(static_cast<uint8_t>(red)),
              green(static_cast<uint8_t>(green)),
              blue(static_cast<uint8_t>(blue)),
              alpha(static_cast<uint8_t>(alpha)) {}

		Pixel(const Color& col) 
            : red(static_cast<uint8_t>(col.red * 255.0f)),
              green(static_cast<uint8_t>(col.green * 255.0f)),
              blue(static_cast<uint8_t>(col.blue * 255.0f)),
              alpha(static_cast<uint8_t>(col.alpha * 255.0f)) {}
	};

	inline Color::Color(const Pixel& pixel)
        : red(pixel.red / 255.0f),
          green(pixel.green / 255.0f),
          blue(pixel.blue / 255.0f),
          alpha(pixel.alpha / 255.0f) {}

}

#endif