#include <./che_framework_graphics.hpp>


int main(){
    cgf::Image sprit = cgf::ImageLoader::load("../spirit_test.png");

	cgf::Window_X11 window(800,600);
	cgf::Renderer_X11 render(window.get_pixels(),window);
	cgf::Renderer raw_renderer(window.get_pixels());
	cgf::Point2D p{50,50};
	cgf::Point2D p1(15,30);
    cgf::Point2D p3(20,80);
    cgf::Point2D p2(10,90);
    cgf::Point2D p4(60,10);
    cgf::Image img(100,100,cgf::Colors::Red);
    cgf::Shape::Triangle2D tri(p1,p2,p3);
    cgf::Shape::Rectangle2D rect(p1,p2,p3,p4);
    tri.render_fill_flood(img,cgf::Colors::Red,cgf::Colors::Blue);

    rect.render_fill_flood(img,cgf::Colors::Red,cgf::Colors::Green);


	// render.render(p1,sprit);
	
	while (true){
	    XEvent event;
	    XNextEvent(window.display,&event);

	    switch(event.type){
	    case KeyPress:
	    	std::cout << "Key Pressed" << std::endl;
	    	break;
	    case KeyRelease:
	    	std::cout << "Key released!" << std::endl;
	    	break;
	    case ButtonPress:
	    	std::cout << "Mouse pressed" << std::endl;
	    	break;
	    case ButtonRelease:
	    	std::cout << "Mouse released!" << std::endl;
	    	std::cout << "X: "<< event.xmotion.x << " Y: " << event.xmotion.y << std::endl;
	    	break;
	    case Expose:
	    	std::cout << "Exposure Event" << std::endl;
	    	render.render(p,sprit);
	    	break;
	    }
	}
	// window.createWindow();
	return 0;
}