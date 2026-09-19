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

    // Cursor cursor = XCreateFontCursor(window.get_display(),84);

    // window.assign_cursor(cursor);

	// render.render(p1,sprit);
    cgf::Event_X11 event;
    while(true){
    	std::cout << window.poll_event(event) << std::endl;
		while (window.poll_event(event)){

			if(event.inside_window){ // Making sure that event system is only works when we are actually inside the window ( we will have different idea for making window active or not)
			    switch(event.type){
			    case cgf::EventType_X11::KeyPressed:
			    	std::cout << "Key Pressed" << std::endl;
			    	std::cout << event.key_code << std::endl;
			    	if (event.key_code == 39){
			    		window.get_pixels().clear();
			    		render.render(p,sprit);
			    	}
			    	else if (event.key_code == 40){
			    		window.get_pixels().clear();
			    		render.render(cgf::Point2D{400,300},img);
			    	}
			    	else if (event.key_code == 114){
			    		window.get_pixels().clear();
			    		render.render(p+10,sprit);
			    	}
			    	break;

			    case cgf::EventType_X11::KeyReleased:
			    	std::cout << "Key released!" << std::endl;
			    	break;
			    case cgf::EventType_X11::MouseButtonPressed:
			    	std::cout << "Mouse pressed" << std::endl;
			    	break;
			    case cgf::EventType_X11::MouseButtonReleased:
			    	std::cout << "Mouse released!" << std::endl;
			    	std::cout << "X: "<< event.mouse_x << " Y: " << event.mouse_y << std::endl;
			    	break;
			    case cgf::EventType_X11::Exposed:
			    	std::cout << "Exposure Event" << std::endl;
			    	break;
			    case cgf::EventType_X11::Resized:
			    	std::cout << "Resized Event" << std::endl;
			    	std::cout << "X: "<< event.width << " Y: " << event.height << std::endl;
			    	break;
			    }
			}
		}
	}
	// window.createWindow();
	return 0;
}