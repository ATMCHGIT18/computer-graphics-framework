#ifndef TERMINAL_HPP
#define TERMINAL_HPP

#include <./che_framework_graphics.hpp>

namespace cgf{
	/*Handling the creation of visual terminal by running the given name of the application.
	remember this class is only for running the terminal application.*/
	class Terminal{
	private:
		int row;
		int col;
		float font_size;
		int master_fd;
		std::string application;
		bool open;
		bool closed;
	public:
		Terminal(std::string application_name, int row,int col,float font_size):application(application_name),row(row),col(col),font_size(font_size){
			std::string launch_string = "xdg-terminal-exec -geometry " + std::to_string(col) + "x" + std::to_string(row) + application_name;
			std::system(launch_string.c_str());
			
		}

		~Terminal(){}

		std::string get_name(){return this->application;}

		std::vector<int> get_dimention(){return std::vector<int>{this->row,this->col};}

		int get_size(){return this->font_size;}

		// bool is_open(){}

		// bool is_closed(){}

		// void poll_event(){}
	};

	/*`TerminalWindow` is an object that holds the data for the new instance of the PTY slave and master.
	It is usefull to create a new PTY for the current master file dscriptor and then work in background.
	It does not recommended for creating a new visualised terminal.*/
	class TerminalWindow{
	private:
		int master_fd;
		pid_t child_pid;		
	public:
		TerminalWindow(){
			master_fd = -1;
			child_pid = forkpty(&master_fd,nullptr,nullptr,nullptr);

			if (child_pid == -1){
				throw std::runtime_error("forkpty failed");
			}

			if (child_pid == 0){
				// Child
				 execlp("xdg-terminal-exec","xdg-terminal-exec",nullptr);
				 perror("execlp");
				 _exit(1);
			}

			// Parent
			std::cout << "PTY created \n";
			std::cout << "Master FD: " << master_fd << "\n";
			std::cout << "Child PID: " << child_pid << "\n";
			
		}

		~TerminalWindow(){
			if (master_fd != -1){
				close(master_fd);
			}
		}

	};

	/*TerminalLauncer is the newest and most complete version of the terminal components.
	It can creates and handles the both visual and non-vesual terminals to handles your needs.
	For now I use this terminallauncher instead of the Terminal object and TerminalWindow has its own
	uses for the hidden and behind the scene actions like event-polling and so on.*/

	class TerminalLauncher{
		private:
		    pid_t child_pid = -1;
		    int row = 0;
		    int col = 0;
		    float font_size = 1.0f;
		    std::string application;
		    bool open_ = false;
		    std::string font_family = "font.normal.family=\"JetBrains Mono\"";
		public:
			TerminalLauncher() = default;

			// TerminalLauncher — now uses plain fork(), no pty involved
			TerminalLauncher(std::string application_name, int row, int col, float font_size)
			    : row(row), col(col), font_size(font_size), application(std::move(application_name))
			{
			    child_pid = fork();
			    if (child_pid == -1) {
			        throw std::runtime_error("fork failed");
			    }

			    if (child_pid == 0) {
			        std::string fontArg = "font.size=" + std::to_string(font_size);
			        std::vector<std::string> args = {
			            "alacritty",
			            "-o", fontArg,
			            "-o",font_family,
			            "-o window.dimensions.columns="+ std::to_string(col*3+6),
			            "-o window.dimensions.lines="+ std::to_string(row+4),
			            "-e", application, "--engine-child"  // two separate argv tokens
			        };
			        std::vector<char*> argv;
			        for (auto& a : args) argv.push_back(const_cast<char*>(a.c_str()));
			        argv.push_back(nullptr);

			        execvp("alacritty", argv.data());
			        perror("execvp alacritty"); // now visible in YOUR original terminal
			        _exit(127);
			    }
			    open_ = true;
			}

			~TerminalLauncher(){
				close();
			}

			// No copying policy
			TerminalLauncher(const TerminalLauncher&) = delete;
			TerminalLauncher& operator=(const TerminalLauncher&) = delete;

			TerminalLauncher(TerminalLauncher&& other) noexcept {
				*this = std::move(other);
			}

			TerminalLauncher& operator=(TerminalLauncher&& other) noexcept {
				if(this != &other){
					close(); // release whatever this object currently have
		            child_pid   = other.child_pid;
		            row         = other.row;
		            col         = other.col;
		            font_size   = other.font_size;
		            application = std::move(other.application);
		            open_       = other.open_;

		            other.child_pid = -1;
		            other.open_     = false;
				}
				return *this;
			}


			bool is_open() const {return open_;}

			void close() {
		        if (child_pid > 0) {
		            kill(child_pid, SIGTERM);
		            waitpid(child_pid, nullptr, 0);
		            child_pid = -1;
		        }
        		open_ = false;
			}

			std::string get_name() const {return application;}

			std::vector<int> get_dimension() const {return {row,col};}
			float get_font_size() const {return font_size;}

	};
};
#endif