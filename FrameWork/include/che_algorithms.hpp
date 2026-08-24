#ifndef CHE_ALGORITHMS_HPP
#define CHE_ALGORITHMS_HPP

#include <./che_framework_graphics.hpp>

namespace cgf{
	namespace Algo{
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
			static void dda(Point2D& p1 , Point2D& p2, Matrix& matrix_buff, Color& col){
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
			            matrix_buff.set_pixel(round(x),round(y),col);
						x += x_incre;
						y += y_incre;
			        }
				}

			}

			static void dda(Point2D& p1 , Point2D& p2, Matrix& matrix_buff, const Color& col){
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
			            matrix_buff.set_pixel(round(x),round(y),col);
						x += x_incre;
						y += y_incre;
			        }
					
				}

			}

			static void bresenham(Point2D& p1, Point2D& p2,Matrix& matrix_buff,Color& col){
				int dx(std::abs(p2.x - p1.x)),dy(std::abs(p2.y - p1.y));
				int sx = sign(p2.x - p1.x);
				int sy = sign(p2.y - p1.y);
				int err = dx - dy;
				int x(p1.x) , y(p1.y);
				while(true){
					if (x >= 0 && x < matrix_buff.get_width() && y >= 0 && y < matrix_buff.get_height()) {
			            matrix_buff.set_pixel(x, y,col);
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

			static void bresenham(Point2D& p1, Point2D& p2,Matrix& matrix_buff,const Color& col){
				int dx(std::abs(p2.x - p1.x)),dy(std::abs(p2.y - p1.y));
				int sx = sign(p2.x - p1.x);
				int sy = sign(p2.y - p1.y);
				int err = dx - dy;
				int x(p1.x) , y(p1.y);
				while(true){
					if (x >= 0 && x < matrix_buff.get_width() && y >= 0 && y < matrix_buff.get_height()) {
			            matrix_buff.set_pixel(x, y,col);
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

			static void mid_point(Point2D& p1 ,Point2D& p2, Matrix& matrix_buff,Color& col){
				int dx(std::abs(p2.x - p1.x)) ,dy(std::abs(p2.y-p1.y));
				int sx = sign(p2.x - p1.x);
				int sy = sign(p2.y - p1.y);
				int err = dx - dy;

				int x(p1.x) , y(p1.y);

				if(dx > dy){
					int d = dy - dx/2;

					while(x != p2.x){
						if(x >= 0 && x < matrix_buff.get_width() && y >= 0 && y < matrix_buff.get_height()){
							matrix_buff.set_pixel(x,y,col);
						}
						x += sx;
						if(d < 0){
							d +=dy;
						}
						else{
							y += sy;
							d += dy - dx;
						}
					}
				}
				else{
					int d = dx - dy/2;
					while(y != p2.y ){
						if(x >= 0 && x < matrix_buff.get_width() && y >= 0 && y < matrix_buff.get_height()){
							matrix_buff.set_pixel(x,y,col);
						}
						y += sy;
						if(d < 0){
							d += dx;
						}
						else{
							x += sx;
							d += dx - dy;
						}

					}
				}

			}

			static void mid_point(Point2D& p1 ,Point2D& p2, Matrix& matrix_buff,const Color& col){
				int dx(std::abs(p2.x - p1.x)) ,dy(std::abs(p2.y-p1.y));
				int sx = sign(p2.x - p1.x);
				int sy = sign(p2.y - p1.y);
				int err = dx - dy;

				int x(p1.x) , y(p1.y);

				if(dx > dy){
					int d = dy - dx/2;

					while(x != p2.x){
						if(x >= 0 && x < matrix_buff.get_width() && y >= 0 && y < matrix_buff.get_height()){
							matrix_buff.set_pixel(x,y,col);
						}
						x += sx;
						if(d < 0){
							d +=dy;
						}
						else{
							y += sy;
							d += dy - dx;
						}
					}
				}
				else{
					int d = dx - dy/2;
					while(y != p2.y ){
						if(x >= 0 && x < matrix_buff.get_width() && y >= 0 && y < matrix_buff.get_height()){
							matrix_buff.set_pixel(x,y,col);
						}
						y += sy;
						if(d < 0){
							d += dx;
						}
						else{
							x += sx;
							d += dx - dy;
						}

					}
				}

			}
		};

		class Circle{

		public:
			
			static void bresenham(Point2D& center,int radius,Matrix& matrix_buff,Color& col){
				int d = 3 - 2* radius;
				int x = 0;
				int y = radius;

				while(x <= y){
					if (x>= 0 && y >= 0 && x < matrix_buff.get_width() && y < matrix_buff.get_height() ){
						matrix_buff.set_pixel(x+center.x,y+center.y,col);
						matrix_buff.set_pixel(-x+center.x,y+center.y,col);
						matrix_buff.set_pixel(x+center.x,-y+center.y,col);
						matrix_buff.set_pixel(-x+center.x,-y+center.y,col);
						matrix_buff.set_pixel(y+center.x,x+center.y,col);
						matrix_buff.set_pixel(-y+center.x,x+center.y,col);
						matrix_buff.set_pixel(y+center.x,-x+center.y,col);
						matrix_buff.set_pixel(-y+center.x,-x+center.y,col);
					}
					if (d < 0)
						d += 4*x +6;
					else{
						d += 4*x - 4*y;
						y -=1;
					}
					x++;
				}
			}
			static void bresenham(Point2D& center,int radius,Matrix& matrix_buff,const Color& col){
				int d = 3 - 2* radius;
				int x = 0;
				int y = radius;

				while(x <= y){
					if (x>= 0 && y >= 0 && x < matrix_buff.get_width() && y < matrix_buff.get_height() ){
						matrix_buff.set_pixel(x+center.x,y+center.y,col);
						matrix_buff.set_pixel(-x+center.x,y+center.y,col);
						matrix_buff.set_pixel(x+center.x,-y+center.y,col);
						matrix_buff.set_pixel(-x+center.x,-y+center.y,col);
						matrix_buff.set_pixel(y+center.x,x+center.y,col);
						matrix_buff.set_pixel(-y+center.x,x+center.y,col);
						matrix_buff.set_pixel(y+center.x,-x+center.y,col);
						matrix_buff.set_pixel(-y+center.x,-x+center.y,col);
					}
					if (d < 0)
						d += 4*x +6;
					else{
						d += 4*x - 4*y;
						y -=1;
					}
					x++;
				}
			}

			static void mid_point(Point2D& center,int radius, Matrix& matrix_buff,Color& col){
				int x(radius),y(0);
				int d = 1 - radius;

				while(x >= y){
					if(x>=0 && y>=0 && x < matrix_buff.get_width() && y < matrix_buff.get_height()){
						matrix_buff.set_pixel(center.x + x,center.y + y,col);
						matrix_buff.set_pixel(center.x - x,center.y + y,col);
						matrix_buff.set_pixel(center.x - x,center.y - y,col);
						matrix_buff.set_pixel(center.x + x,center.y - y,col);
						matrix_buff.set_pixel(center.x + y,center.y + x,col);
						matrix_buff.set_pixel(center.x - y,center.y + x,col);
						matrix_buff.set_pixel(center.x + y,center.y - x,col);
						matrix_buff.set_pixel(center.x - y,center.y - x,col);
					}

					if (d <= 0) 
						d += 2*y + 1;
					else{
						d += 2*y - 2*x +1;
						x--;
					}
					y++;
				}
			}
			static void mid_point(Point2D& center,int radius, Matrix& matrix_buff,const Color& col){
				int x(radius),y(0);
				int d = 1 - radius;

				while(x >= y){
					if(x>=0 && y>=0 && x < matrix_buff.get_width() && y < matrix_buff.get_height()){
						matrix_buff.set_pixel(center.x + x,center.y + y,col);
						matrix_buff.set_pixel(center.x - x,center.y + y,col);
						matrix_buff.set_pixel(center.x - x,center.y - y,col);
						matrix_buff.set_pixel(center.x + x,center.y - y,col);
						matrix_buff.set_pixel(center.x + y,center.y + x,col);
						matrix_buff.set_pixel(center.x - y,center.y + x,col);
						matrix_buff.set_pixel(center.x + y,center.y - x,col);
						matrix_buff.set_pixel(center.x - y,center.y - x,col);
					}

					if (d <= 0) 
						d += 2*y + 1;
					else{
						d += 2*y - 2*x +1;
						x--;
					}
					y++;
				}
			}
		};

		class Ellips{
		public:
			static void mid_point(Point2D& center,int radius_x,int radius_y,Matrix& matrix_buff, Color& col){
				int x(0),y(radius_y);
				int d1 = radius_y*radius_y + (radius_x*radius_x)/4 - (radius_x*radius_x)*radius_y;
				int dx = 2 *(radius_y*radius_y)*x;
				int dy = 2 * (radius_x*radius_x)*y;

				while(dx < dy){
					if (x>=0 && y >=0 && x < matrix_buff.get_width() && y < matrix_buff.get_height()){
						matrix_buff.set_pixel(center.x + x,center.y + y,col);
						matrix_buff.set_pixel(center.x + x,center.y - y,col);
						matrix_buff.set_pixel(center.x - x,center.y + y,col);
						matrix_buff.set_pixel(center.x - x,center.y - y,col);
					}
					x++;
					if (d1 < 0){
						dx = dx + (2 * radius_y*radius_y);
	                    d1 = d1 + dx + (radius_y*radius_y);
					}
					else{
						y--;
						dx = dx + (2 * radius_y * radius_y);
			            dy = dy - (2 * radius_x * radius_x);
						d1 += dx - dy + (radius_y*radius_y);
					}
				}

				int d2 = (radius_y*radius_y)*((x+0.5) * (x+0.5))+(radius_x*radius_x)*((y-1)*(y-1)) - (radius_x*radius_x)*(radius_y*radius_y);

				while(y >= 0){
					if (x>=0 && y >=0 && x < matrix_buff.get_width() && y < matrix_buff.get_height()){
						matrix_buff.set_pixel(center.x + x,center.y + y,col);
						matrix_buff.set_pixel(center.x + x,center.y - y,col);
						matrix_buff.set_pixel(center.x - x,center.y + y,col);
						matrix_buff.set_pixel(center.x - x,center.y - y,col);
					}
					y--;
					if(d2 > 0){
						dy = dy - (2 * radius_x * radius_x);
			            d2 = d2 + (radius_x * radius_x) - dy;
					}
					else{
						x++;
						dx = dx + (2 * radius_y * radius_y);
			            dy = dy - (2 * radius_x * radius_x);
			            d2 = d2 + dx - dy + (radius_x * radius_x);
					}
				}
			}
			static void mid_point(Point2D& center,int radius_x,int radius_y,Matrix& matrix_buff,const Color& col){
				int x(0),y(radius_y);
				int d1 = radius_y*radius_y + (radius_x*radius_x)/4 - (radius_x*radius_x)*radius_y;
				int dx = 2 *(radius_y*radius_y)*x;
				int dy = 2 * (radius_x*radius_x)*y;

				while(dx < dy){
					if (x>=0 && y >=0 && x < matrix_buff.get_width() && y < matrix_buff.get_height()){
						matrix_buff.set_pixel(center.x + x,center.y + y,col);
						matrix_buff.set_pixel(center.x + x,center.y - y,col);
						matrix_buff.set_pixel(center.x - x,center.y + y,col);
						matrix_buff.set_pixel(center.x - x,center.y - y,col);
					}
					x++;
					if (d1 < 0){
						dx = dx + (2 * radius_y*radius_y);
	                    d1 = d1 + dx + (radius_y*radius_y);
					}
					else{
						y--;
						dx = dx + (2 * radius_y * radius_y);
			            dy = dy - (2 * radius_x * radius_x);
						d1 += dx - dy + (radius_y*radius_y);
					}
				}

				int d2 = (radius_y*radius_y)*((x+0.5) * (x+0.5))+(radius_x*radius_x)*((y-1)*(y-1)) - (radius_x*radius_x)*(radius_y*radius_y);

				while(y >= 0){
					if (x>=0 && y >=0 && x < matrix_buff.get_width() && y < matrix_buff.get_height()){
						matrix_buff.set_pixel(center.x + x,center.y + y,col);
						matrix_buff.set_pixel(center.x + x,center.y - y,col);
						matrix_buff.set_pixel(center.x - x,center.y + y,col);
						matrix_buff.set_pixel(center.x - x,center.y - y,col);
					}
					y--;
					if(d2 > 0){
						dy = dy - (2 * radius_x * radius_x);
			            d2 = d2 + (radius_x * radius_x) - dy;
					}
					else{
						x++;
						dx = dx + (2 * radius_y * radius_y);
			            dy = dy - (2 * radius_x * radius_x);
			            d2 = d2 + dx - dy + (radius_x * radius_x);
					}
				}
			}
		};

		class Filling{
		public:
			static void scanline(std::vector<Point2D>& vertices,Matrix& matrix_buff,Color& col){
				float y_max(0.0f),y_min(100000.0f);

				for (auto point : vertices){
					y_min = std::min(y_min,point.y);
					y_max = std::max(y_max,point.y);
				}

				for (int y = y_min; y <= y_max;y++){
					std::vector<int> intersections;

					for(int i=0; i< vertices.size();i++){
						Point2D p1 = vertices.at(i);
						Point2D p2 = vertices.at((i+1)%vertices.size());

						if(p1.y == p2.y){ continue;}
						if(y >= std::min(p1.y,p2.y) && y < std::max(p1.y,p2.y)){
							int x = p1.x + (y - p1.y)*(p2.x -p1.x)/(p2.y-p1.y);
							intersections.push_back(x);
						}
					}
					std::sort(intersections.begin(),intersections.end());

					for (size_t i=0;i+1 < intersections.size();i+=2){
						for (int x = intersections.at(i);x<=intersections.at(i+1);x++){
							if (x >=0 && y>= 0 && x < matrix_buff.get_width() && y < matrix_buff.get_height()){
								matrix_buff.set_pixel(x,y,col);
							}
						}
					}
				}

			}
			static void scanline(const std::vector<Point2D>& vertices,Matrix& matrix_buff,const Color& col){
				float y_max(0),y_min(100000);

				for (auto point : vertices){
					y_min = std::min(y_min,point.y);
					y_max = std::max(y_max,point.y);
				}

				for (int y = y_min; y <= y_max;y++){
					std::vector<int> intersections;

					for(int i=0; i< vertices.size();i++){
						Point2D p1 = vertices.at(i);
						Point2D p2 = vertices.at((i+1)%vertices.size());

						if(p1.y == p2.y){ continue;}
						if(y >= std::min(p1.y,p2.y) && y < std::max(p1.y,p2.y)){
							int x = p1.x + (y - p1.y)*(p2.x -p1.x)/(p2.y-p1.y);
							intersections.push_back(x);
						}
					}
					std::sort(intersections.begin(),intersections.end());

					for (size_t i=0;i+1 < intersections.size();i+=2){
						for (int x = intersections.at(i);x<=intersections.at(i+1);x++){
							if (x >=0 && y>= 0 && x < matrix_buff.get_width() && y < matrix_buff.get_height()){
								matrix_buff.set_pixel(x,y,col);
							}
						}
					}
				}

			}

			static void flood_fill(Point2D& p,Matrix& matrix_buff,Color& target_col,Color& fill_col){
				//4-connected

				if (p.x < 0 || p.y < 0 || p.x >= matrix_buff.get_width() || p.y >= matrix_buff.get_height())
					return;

				Color current(matrix_buff.at(p.x,p.y));
				if(current != target_col)
					return;

				matrix_buff.set_pixel(p.x,p.y,fill_col);

				flood_fill(Point2D{p.x+1,p.y},matrix_buff,target_col,fill_col);
				flood_fill(Point2D{p.x,p.y+1},matrix_buff,target_col,fill_col);
				flood_fill(Point2D{p.x-1,p.y},matrix_buff,target_col,fill_col);
				flood_fill(Point2D{p.x,p.y-1},matrix_buff,target_col,fill_col);
			}
			static void flood_fill(const Point2D& p,Matrix& matrix_buff,const Color& target_col,const Color& fill_col){
				//4-connected

				if (p.x < 0 || p.y < 0 || p.x >= matrix_buff.get_width() || p.y >= matrix_buff.get_height())
					return;

				Color current(matrix_buff.at(p.x,p.y));
				if(current != target_col)
					return;

				matrix_buff.set_pixel(p.x,p.y,fill_col);

				flood_fill(Point2D{p.x+1,p.y},matrix_buff,target_col,fill_col);
				flood_fill(Point2D{p.x,p.y+1},matrix_buff,target_col,fill_col);
				flood_fill(Point2D{p.x-1,p.y},matrix_buff,target_col,fill_col);
				flood_fill(Point2D{p.x,p.y-1},matrix_buff,target_col,fill_col);
			}


		};
	}
}

#endif