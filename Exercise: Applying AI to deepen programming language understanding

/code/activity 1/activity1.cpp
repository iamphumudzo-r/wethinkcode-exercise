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