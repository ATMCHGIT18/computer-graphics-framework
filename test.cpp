#include <che_framework_graphics.hpp>

int main(int argc, char** argv) {
	int height = 300;
	int width = 300;
	float font_size = 1.0f;

    bool is_engine_child = (argc > 1 && std::string(argv[1]) == "--engine-child");
    cgf::Image image = cgf::ImageLoader::load("./FrameWork/src/spirit_test.png");

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
    cgf::Point2D p1(-10,45);
    cgf::Point2D p2(250,500);
    cgf::Point2D p3(100,10);
    cgf::Line2D line1(p1,p2);
    line1.render_bren(window.get_pixels(),cgf::Colors::Cyan);

    
    for (int i = 0; i < height; i++) window.get_pixels().set_pixel(i, i, 0, 255, 0);
    for ( int i = height-1; i >=0 ; i--) window.get_pixels().set_pixel(i,height -1 - i,255,0,0);
    for (int i = width - 1; i>= height; i--) {
    	for (int j = height - 1; j >=0; j--){
    		window.get_pixels().set_pixel(i,j,0,0,255);
    	}
    }

    cgf::Renderer render(window.get_pixels());
    render.render(image,150,150);
    render.render_line(p3,p2,cgf::Colors::Purple,'m');
    window.show();
    std::cin.ignore();
    return 0;
}