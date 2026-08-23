#ifndef PRIMITIVES_HPP
#define PRIMITIVES_HPP

#include <./che_framework_graphics.hpp>

namespace cgf{

	class Primitive{};

	class Line2D : Primitive{
	private:
		Point2D& p1;
		Point2D& p2;
		float slope;
		float intercept;
	public:
		Line2D(Point2D& p1,Point2D& p2):p1(p1),p2(p2){
			slope = (p2.y - p1.y)/(p2.x - p1.x);
			intercept = p2.y - (slope)*p2.x;
		}
		Line2D(std::array<Point2D*,2> points):p1(*points[0]),p2(*points[1]){
			slope = (p2.y - p1.y)/(p2.x - p1.x);
			intercept = p2.y - (slope)*p2.x;
		}

		std::pair<Point2D,Point2D> get_points(){return std::make_pair(p1,p2);}
		const std::pair<Point2D,Point2D> get_points() const {return std::make_pair(p1,p2);}

		float get_slope() const {return slope;}
		float get_intercept() const {return intercept;}

		void render_dda(PixelMatrix& matrix_buff, Color& col){
			Line::dda(p1,p2,matrix_buff,col);
		}

		void render_dda(PixelMatrix& matrix_buff,const Color& col){
			Line::dda(p1,p2,matrix_buff,col);
		}

		void render_bren(PixelMatrix& matrix_buff,Color& col){
			Line::bresenham(p1,p2,matrix_buff,col);
		}

		void render_bren(PixelMatrix& matrix_buff,const Color& col){
			Line::bresenham(p1,p2,matrix_buff,col);
		}

		void render_mid(PixelMatrix& matrix_buff,Color& col){
			Line::mid_point(p1,p2,matrix_buff,col);
		}

		void render_mid(PixelMatrix& matrix_buff,const Color& col){
			Line::mid_point(p1,p2,matrix_buff,col);
		}
	};

	class Triangle2D : Primitive{
	private:
		Point2D& p1;
		Point2D& p2;
		Point2D& p3;
		Line2D l1;
		Line2D l2;
		Line2D l3;
	public:
		Triangle2D(Point2D& p1,Point2D& p2,Point2D& p3):p1(p1),p2(p2),p3(p3),l1(p1,p2),l2(p2,p3),l3(p3,p1){}
		Triangle2D(std::array<Point2D*,3> points):p1(*points[0]),p2(*points[1]),p3(*points[2]),l1(*points[0],*points[1]),l2(*points[1],*points[2]),l3(*points[2],*points[0]){}

		std::array<const Point2D*,3> get_points() const {return {&p1,&p2,&p3};}
		std::array<const Line2D*,3> get_lines() const {return {&l1,&l2,&l3};}

		void render_dda(PixelMatrix& matrix_buff,const Color& col){
			Line::dda(p1,p2,matrix_buff,col);
			Line::dda(p2,p3,matrix_buff,col);
			Line::dda(p3,p1,matrix_buff,col);
		}
		void render_dda(PixelMatrix& matrix_buff,Color& col){
			Line::dda(p1,p2,matrix_buff,col);
			Line::dda(p2,p3,matrix_buff,col);
			Line::dda(p3,p1,matrix_buff,col);
		}

		void render_bren(PixelMatrix& matrix_buff,Color& col){
			Line::bresenham(p1,p2,matrix_buff,col);
			Line::bresenham(p2,p3,matrix_buff,col);
			Line::bresenham(p3,p1,matrix_buff,col);
		}
		void render_bren(PixelMatrix& matrix_buff,const Color& col){
			Line::bresenham(p1,p2,matrix_buff,col);
			Line::bresenham(p2,p3,matrix_buff,col);
			Line::bresenham(p3,p1,matrix_buff,col);
		}

		void render_mid(PixelMatrix& matrix_buff,Color& col){
			Line::mid_point(p1,p2,matrix_buff,col);
			Line::mid_point(p2,p3,matrix_buff,col);
			Line::mid_point(p3,p1,matrix_buff,col);
		}
		void render_mid(PixelMatrix& matrix_buff,const Color& col){
			Line::mid_point(p1,p2,matrix_buff,col);
			Line::mid_point(p2,p3,matrix_buff,col);
			Line::mid_point(p3,p1,matrix_buff,col);
		}

	};

	class Rectangle : Primitive{
	private:
		Point2D& p1;
		Point2D& p2;
		Point2D& p3;
		Point2D& p4;

		Line2D l1;
		Line2D l2;
		Line2D l3;
		Line2D l4;
	public:
		Rectangle(Point2D& p1,Point2D& p2,Point2D& p3,Point2D& p4):p1(p1),p2(p2),p3(p3),p4(p4),l1(p1,p2),l2(p2,p3),l3(p3,p4),l4(p4,p1){}
		Rectangle(std::array<Point2D*,4> points):p1(*points[0]),p2(*points[1]),p3(*points[2]),p4(*points[3])
												,l1(*points[0],*points[1]),l2(*points[1],*points[2]),l3(*points[2],*points[3]),l4(*points[3],*points[0]){}

		std::array<Point2D*,4> get_points() const {return {&p1,&p2,&p3,&p4};}
		std::array<const Line2D*,4> get_lines() const {return {&l1,&l2,&l3,&l4};}

		void render_dda(PixelMatrix&matrix_buff,Color& col){
			Line::dda(p1,p2,matrix_buff,col);
			Line::dda(p2,p3,matrix_buff,col);
			Line::dda(p3,p4,matrix_buff,col);
			Line::dda(p4,p1,matrix_buff,col);
		}
		void render_dda(PixelMatrix&matrix_buff,const Color& col){
			Line::dda(p1,p2,matrix_buff,col);
			Line::dda(p2,p3,matrix_buff,col);
			Line::dda(p3,p4,matrix_buff,col);
			Line::dda(p4,p1,matrix_buff,col);
		}

		void render_bren(PixelMatrix& matrix_buff,Color& col){
			Line::bresenham(p1,p2,matrix_buff,col);
			Line::bresenham(p2,p3,matrix_buff,col);
			Line::bresenham(p3,p4,matrix_buff,col);
			Line::bresenham(p4,p1,matrix_buff,col);
		}
		void render_bren(PixelMatrix& matrix_buff,const Color& col){
			Line::bresenham(p1,p2,matrix_buff,col);
			Line::bresenham(p2,p3,matrix_buff,col);
			Line::bresenham(p3,p4,matrix_buff,col);
			Line::bresenham(p4,p1,matrix_buff,col);
		}

		void render_mid(PixelMatrix& matrix_buff,Color& col){
			Line::mid_point(p1,p2,matrix_buff,col);
			Line::mid_point(p2,p3,matrix_buff,col);
			Line::mid_point(p3,p4,matrix_buff,col);
			Line::mid_point(p4,p1,matrix_buff,col);
		}
		void render_mid(PixelMatrix& matrix_buff,const Color& col){
			Line::mid_point(p1,p2,matrix_buff,col);
			Line::mid_point(p2,p3,matrix_buff,col);
			Line::mid_point(p3,p4,matrix_buff,col);
			Line::mid_point(p4,p1,matrix_buff,col);
		}
	};

}
#endif