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

		void render(Window& window, Color& col){
			line_gen::dda_line(p1,p2,window,col);
		}

		void render(Window& window,const Color& col){
			line_gen::dda_line(p1,p2,window,col);
		}
	};

}
#endif