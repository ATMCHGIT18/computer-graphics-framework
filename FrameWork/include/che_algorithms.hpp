#ifndef CHE_ALGORITHMS_HPP
#define CHE_ALGORITHMS_HPP

#include <./che_framework_graphics.hpp>

namespace cgf{
	int round(float n){
		if (n- (int)n < 0.5) 
			return (int)n;
		return (int)(n+1);
	}

	class Line{
	public:
		static void dda_line(Point2D& p1 , Point2D& p2, PixelMatrix& matrix_buff, Color& col){
			float dx = p2.x - p1.x;
			float dy = p2.y - p1.y;

			int steps = (std::abs(dx) > std::abs(dy)) ? std::abs(dx) : std::abs(dy);

			float x_incre = dx/(float)steps;
			float y_incre = dy/(float)steps;
			std::cout << x_incre << " " << y_incre << std::endl;

			float x = p1.x;
			float y = p1.y;
			for (int i=0; i < steps; i++){
				// put the pixel as the color;
				matrix_buff.at(round(x),round(y)) = col;
				x += x_incre;
				y += y_incre;
			}

		}

		static void dda_line(Point2D& p1 , Point2D& p2, PixelMatrix& matrix_buff, const Color& col){
			int dx = p2.x - p1.x;
			int dy = p2.y - p1.y;

			int steps = (std::abs(dx) >= std::abs(dy)) ? std::abs(dx) : std::abs(dy);

			float x_incre = (float) dx/steps;
			float y_incre = (float) dy/steps;
			std::cout << x_incre << " " << y_incre << std::endl;

			float x = p1.x;
			float y = p1.y;
			for (int i=0; i < steps; i++){
				// put the pixel as the color;
				matrix_buff.at(round(x),round(y)) = col;
				x += x_incre;
				y += y_incre;
			}

		}

		static void bresenham_line(){
			return;
		}
	};
}

#endif