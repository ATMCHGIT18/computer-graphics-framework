#ifndef CHE_ALGORITHMS_HPP
#define CHE_ALGORITHMS_HPP

#include <./che_framework_graphics.hpp>

namespace cgf{
	int round(float n){
		if (n- (int)n < 0.5) 
			return (int)n;
		return (int)(n+1);
	}

	int sign(int x){
		return (x<0) ? -1 : 1;
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
				if (x >= 0.0f && x < matrix_buff.get_width() && y >= 0.0f && y < matrix_buff.get_height()) {
		            matrix_buff.at(round(x),round(y)) = col;
					x += x_incre;
					y += y_incre;
		        }
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
				if (x >= 0.0f && x < matrix_buff.get_width() && y >= 0.0f && y < matrix_buff.get_height()) {
		            matrix_buff.at(round(x),round(y)) = col;
					x += x_incre;
					y += y_incre;
		        }
				
			}

		}

		static void bresenham_line(Point2D& p1, Point2D& p2,PixelMatrix& matrix_buff,Color& col){
			int dx(std::abs(p2.x - p1.x)),dy(std::abs(p2.y - p1.y));
			int sx = sign(p2.x - p1.x);
			int sy = sign(p2.y - p1.y);
			int err = dx - dy;
			int x(p1.x) , y(p1.y);
			while(true){
				if (x >= 0 && x < matrix_buff.get_width() && y >= 0 && y < matrix_buff.get_height()) {
		            matrix_buff.at(x, y) = col;
		        }
				if (x == p2.x && y == p2.y){
					break;
				}
				int e2 = 2 * err;

				if(e2 > -dy){
					err -=dy;
					x +=sx;
				}
				if(e2 < dx){
					err +=dx;
					y +=sy;
				}
			}

		}

		static void bresenham_line(Point2D& p1, Point2D& p2,PixelMatrix& matrix_buff,const Color& col){
			int dx(std::abs(p2.x - p1.x)),dy(std::abs(p2.y - p1.y));
			int sx = sign(p2.x - p1.x);
			int sy = sign(p2.y - p1.y);
			int err = dx - dy;
			int x(p1.x) , y(p1.y);
			while(true){
				if (x >= 0 && x < matrix_buff.get_width() && y >= 0 && y < matrix_buff.get_height()) {
		            matrix_buff.at(x, y) = col;
		        }
				if (x == p2.x && y == p2.y){
					break;
				}
				int e2 = 2 * err;

				if(e2 > -dy){
					err -=dy;
					x +=sx;
				}
				if(e2 < dx){
					err +=dx;
					y +=sy;
				}
			}

		}
	};
}

#endif