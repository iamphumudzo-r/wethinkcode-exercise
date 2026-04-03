#ifndef VIRTUALMOUSE_HPP
#define VIRTUALMOUSE_HPP

#include <X11/Xlib.h>
#include <X11/extensions/XTest.h>
#include <X11/keysym.h>
#include <string>

class Virtualmouse
{
	public:
		Virtualmouse();
		~Virtualmouse();
	
		bool initDisplay();
	
		void moveMouseSmoothly(int targetX, int targetY, int steps = 50);
		void leftClick();
		void clearInputField();
		void typeNumber(int number);
		void getCurrentMousePos(int &x, int &y) const;
		void typeString(std::string text);
	
		int getRandomInt(int min, int max) const;
		Display* getDisplay() const;
		
	private:
		Display *display;
	
};

#endif // VIRTUALMOUSE_HPP
