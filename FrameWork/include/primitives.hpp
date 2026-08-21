#ifndef PRIMITIVES_HPP
#define PRIMITIVES_HPP

#include <./che_framework_graphics.hpp>

namespace cgf{

	class Line2D{
	private:
		Point2D& p1;
		Point2D& p2;
		float slope;
		float intecept;
	public:
		Line2D(Point2D& p1,Point2D& p2):p1(p1),p2(p2){}

		std::pair<Point2D,Point2D> get_points(){return std::make_pair(p1,p2);}
		const std::pair<Point2D,Point2D> get_points() const {return std::make_pair(p1,p2);}

		void render(PixelMatrix& matrix_buff, Color& col){
			Line::dda_line(p1,p2,matrix_buff,col);
		}

		void render(PixelMatrix& matrix_buff,const Color& col){
			Line::dda_line(p1,p2,matrix_buff,col);
		}
	};

}
#endif