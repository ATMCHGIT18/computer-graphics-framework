#include <che_framework_graphics.hpp>

int main(int argc, char** argv) {
	int height = 300;
	int width = 300;
	float font_size = 1.0f;

    bool is_engine_child = (argc > 1 && std::string(argv[1]) == "--engine-child");

    if (!is_engine_child) {
        char self_path[4096];
        ssize_t len = readlink("/proc/self/exe", self_path, sizeof(self_path) - 1);
        self_path[len] = '\0';

        cgf::TerminalLauncher terminal(self_path, height, width, font_size); // pass the real binary path, not "test"
        std::cin.ignore();
        return 0;
    }

    cgf::Window window(height, width, font_size, "test");
    window.get_pixels().clear();
    // cgf::Image image(50,50,cgf::Colors::White);
    cgf::SampleBuffer samp(50,50,4);

    // Line, Triangle, Rectangle Test ---------------------------------------------------------
    // cgf::Vertex p1(10,45);
    // cgf::Point2D p2(250,230);
    // cgf::Point2D p3(100,10);
    // cgf::Point2D p4(70,5);
    // cgf::Triangle2D triangle1(p1,p2,p3);
    // triangle1.render_bren(window.get_pixels(),cgf::Colors::Cyan);
    // cgf::Triangle2D triangle2(p2,p3,p4);
    // triangle2.render_bren(window.get_pixels(),cgf::Colors::Purple);
    // cgf::Rectangle2D rect(p1,p2,p3,p4);
    // rect.render_dda(window.get_pixels(),cgf::Colors::Purple);

    // for (int i = 0; i < height; i++) window.get_pixels().set_pixel(i, i, 0, 255, 0);
    // for ( int i = height-1; i >=0 ; i--) window.get_pixels().set_pixel(i,height -1 - i,255,0,0);
    // for (int i = width - 1; i>= height; i--) {
    // 	for (int j = height - 1; j >=0; j--){
    // 		window.get_pixels().set_pixel(i,j,0,0,255);
    // 	}
    // }


    // Circle and Ellips Test ------------------------------------------------------------------

    // cgf::Point2D center(100,30);
    // cgf::Point2D center1(100,80);
    // cgf::Point2D center2(100,130);
    // cgf::Point2D center3(100,170);
    // cgf::Point2D center4(100,220);
    // cgf::Point2D center5(150,60);
    // int radius = 20;

    // cgf::Circle::bresenham(center,radius,window.get_pixels(),cgf::Colors::Blue);
    // cgf::Circle2D circ(center1,radius);
    // circ.render_bren(window.get_pixels(),cgf::Colors::Cyan);

    // cgf::Circle::mid_point(center2,radius,window.get_pixels(),cgf::Colors::Red);
    // cgf::Circle2D circ1(center3,radius);
    // circ1.render_mid(window.get_pixels(),cgf::Colors::Purple);

    // cgf::Ellips::mid_point(center4,20,50,window.get_pixels(),cgf::Colors::Yellow);
    // cgf::Ellips2D elip(center5,20,50);
    // elip.render_mid(window.get_pixels(),cgf::Colors::Green);

    // Image PNG Loading, Spirit Rasterisation Test ---------------------------------------
    
    // cgf::Image sprit = cgf::ImageLoader::load("./FrameWork/src/spirit_test.png");
    // Rendering Section ------------------------------------------------------------------------

    cgf::Renderer render(window.get_pixels());
    // render.render(sprit,150,150);
    // render.render_line(p3,p2,cgf::Colors::Purple,'m');
    window.show();
    std::cin.ignore();
    return 0;
}