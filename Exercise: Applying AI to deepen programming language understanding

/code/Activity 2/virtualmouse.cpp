#include "virtualmouse.h"
#include <X11/keysym.h>
#include <iostream>
#include <random>
#include <chrono>
#include <thread>

Virtualmouse::Virtualmouse()
{
	//Empty
}

Virtualmouse::~Virtualmouse()
{
	if(display != nullptr)
	{
		XCloseDisplay(display);
		
		//good practice to avoid dangling pointers
		display = nullptr; 
	}		
}

//Initialize the display
bool Virtualmouse::initDisplay()
{
	display = XOpenDisplay(NULL);
	if(display == nullptr)
	{
		std::cerr << "? Error: Cannot open X display. Are you running Wayland or X11?" <<std::endl;
		return false;
	}
	return true;
}

//Get current mouse position
void Virtualmouse::getCurrentMousePos(int &x, int &y) const
{
	if(display == nullptr)
		return;
	
	//Lol what?????
	Window root_return, child_return;
	int root_x_return, root_y_return, win_x_return, win_y_return;
	unsigned int mask_return;
	
	XQueryPointer(display, DefaultRootWindow(display),
		&root_return, &child_return,
		&root_x_return, &root_y_return, 
		&win_x_return, &win_y_return, 
		&mask_return);
	
	x = root_x_return;
	y = root_y_return;
	
}

//Random number generator for simulating human error/jitter
int Virtualmouse::getRandomInt(int min, int max) const
{
	
	static std::random_device rd;
	static std::mt19937 gen(rd());
	
	//Wow lol is this even C++ haha, first time i see this
	std::uniform_int_distribution<> distr(min, max);
	
	return distr(gen);
}

void Virtualmouse::moveMouseSmoothly(int targetX, int targetY, int steps)
{	
	if (display == nullptr)
		return;
	
	int startX, startY;
	getCurrentMousePos(startX, startY);
	
	for(int i = 0; i <= steps; ++i)
	{
		//Calculate progress from 0.0 to 1.0
		float t = (float)i /steps;
		
		//Apply an "ease-out" curve so it slows down near the target
		float easeOut = t * (2.0f - t); 
		
		//Calculate the current position along the line
		int currentX = startX + (targetX - startX) * easeOut;
		int currentY = startY + (targetY - startY) * easeOut;
		
		//Add a tiny bit of random jitter (± 1 pixel)
		currentX += getRandomInt(-1, 1);
		currentY += getRandomInt(-1, 1);
		
		// Move the mouse
		XTestFakeMotionEvent(display, -1, currentX, currentY, CurrentTime);
		XFlush(display);
		
		// Sleep to create the speed of the movement
		std::this_thread::sleep_for(std::chrono::milliseconds(5));				
	}	
}

//Function to simulate a left click
void Virtualmouse::leftClick()
{
	 if (display == nullptr)
		 return;
	 
	//Press Down
	XTestFakeButtonEvent(display, 1, True, CurrentTime);
	 
	//Random hold time
	std::this_thread::sleep_for(std::chrono::milliseconds(getRandomInt(50, 150)));

	XTestFakeButtonEvent(display, 1, False, CurrentTime);
	XFlush(display);
}

Display* Virtualmouse::getDisplay() const
{
	return display;
}

// Clears the text box using Ctrl + A, then Backspace
void Virtualmouse::clearInputField()
{
    if (display == nullptr)
	    return;

    // Get hardware keycodes for the keys we need
    KeyCode ctrl = XKeysymToKeycode(display, XK_Control_L);
    KeyCode a = XKeysymToKeycode(display, XK_a);
    KeyCode backspace = XKeysymToKeycode(display, XK_BackSpace);

    // Press Ctrl + A
    XTestFakeKeyEvent(display, ctrl, True, CurrentTime);
    XTestFakeKeyEvent(display, a, True, CurrentTime);
    XTestFakeKeyEvent(display, a, False, CurrentTime);
    XTestFakeKeyEvent(display, ctrl, False, CurrentTime);
    
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Small human pause

    // Press Backspace
    XTestFakeKeyEvent(display, backspace, True, CurrentTime);
    XTestFakeKeyEvent(display, backspace, False, CurrentTime);
    
    XFlush(display);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

// Types an integer digit by digit
void Virtualmouse::typeNumber(int number)
{
    if (display == nullptr)
	    return;

    std::string numStr = std::to_string(number);
    
    for(char c : numStr) 
    {
        // In X11, the keysyms for digits '0'-'9' match their ASCII values
        KeyCode code = XKeysymToKeycode(display, c); 
        
        XTestFakeKeyEvent(display, code, True, CurrentTime);
        std::this_thread::sleep_for(std::chrono::milliseconds(getRandomInt(20, 60))); // Hold key briefly
        XTestFakeKeyEvent(display, code, False, CurrentTime);
        
        XFlush(display);
        std::this_thread::sleep_for(std::chrono::milliseconds(getRandomInt(50, 150))); // Delay between keys
    }
}

void Virtualmouse::typeString(std::string text)
{
	if (display == nullptr) return;

	for(char c : text)
	{
		KeyCode code;
		if (c == '.')
		{
			code = XKeysymToKeycode(display, XK_period);
		} 
		else
		{
			code = XKeysymToKeycode(display, c); 
		}
        
		XTestFakeKeyEvent(display, code, True, CurrentTime);
		std::this_thread::sleep_for(std::chrono::milliseconds(20)); // Hold
		XTestFakeKeyEvent(display, code, False, CurrentTime);
		std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Release
		XFlush(display);
	}
}
