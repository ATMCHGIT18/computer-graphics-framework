#ifndef EVENT_HPP
#define EVENT_HPP

#include <./che_framework_graphics.hpp>

/*This file contains not tested features.
All objects here are for creating an Event-driven data structure to capture the input for our game but
the problem here is that they needs to be checked.
TerminalEvent is working but for the pressing and the Event object is actually a X11 for linux and now so good,
due to the fact if you use the Window_X11 for windowing then the Event handling is outsourced to the X11 server
and this file is just nothing.
The other Event on the other machines needs to be checked and tested.*/


namespace cgf{
	/*`TerminalEvent` is an object which let's you to have a terminal based Event system which only reads
	key pressed. It does not support any key holding or key releasing events but it is enough and easy
	to use for Terminal based projects.

	Be aware that this object will only works for Windows,Linux, and Mac machines.*/
	class TerminalEvent{
	public:
		#if defined(_WIN32) || defined(_WIN64)
			static bool is_key_pressed(){
				return _kbhit() != 0;
			}

			static char read_key(){
				return _getch();
			}
		#elif defined(__APPLE__) || defined(__MACH__) || defined(__linux__)
			static void set_terminal_mode(bool enable_raw){
				struct termios t;
				tcgetattr(STDIN_FILENO,&t);
				if(enable_raw){
					t.c_lflag &= ~(ICANON | ECHO);
				}else{
					t.c_lflag |= (ICANON | ECHO);
				}
				tcsetattr(STDIN_FILENO,TCSANOW,&t);
			}


			static bool is_key_pressed(){
				set_terminal_mode(true);

				struct timeval tv = {0L,0L};

				fd_set fds;
				FD_ZERO(&fds);
				FD_SET(STDIN_FILENO,&fds);

				int result = select(STDIN_FILENO + 1,&fds,NULL,NULL,&tv);

				set_terminal_mode(false);
				return result > 0;
			}

			static char read_key(){
				set_terminal_mode(true);
				char ch;
				auto bytes_read = read(STDIN_FILENO,&ch,1);
				set_terminal_mode(false);
				return (bytes_read > 0) ? ch : 0;
			}
		#else
			static bool is_key_pressed(){return false;}
			static char read_key() {return 0;}
		#endif

	};

	class Event{
	public:
		#if defined(_WIN64) || defined(_WIN32)
			static bool is_key_down(char key){
				int vk = key;
				if(key >= 'a' && key <= 'z') vk = key - 32;
				return (GetAsyncKeyState(vk) & 0x8000) != 0; // High bit set means key is currently physically down
			}
		#elif defined(__linux__)
			static bool is_key_down(char key){
				Display* dpy = XOpenDisplay(NULL);
				if(!dpy) {
					std::cerr << "CRITICAL ERROR: X11 Display context cannot be opened!" << std::endl;
					return false;
				}

				char keys_return[32];
				XQueryKeymap(dpy,keys_return);

				KeyCode kc = XKeysymToKeycode(dpy,key);

				bool is_down = (keys_return[kc >> 3] && (1 << (kc&7))) != 0;

				XCloseDisplay(dpy);
				return is_down;
			}

		#elif defined(__APPLE__) || defined(__MACH__)
			static bool is_key_down(int apple_vk_code){
				return CGEventSourceKeyState(KCGEventSourceStateCombinedSessionState,apple_vk_code);
			}
		#endif
	};

	enum KeyState{UP,PRESSED,HELD,RELEASED};

}

#endif