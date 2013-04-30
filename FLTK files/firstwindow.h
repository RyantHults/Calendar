//spash screen
#include "Graph.h"       
#include "GUI.h"
#include "Window.h"
#include "std_lib_facilities_3.h"
#include <iostream>
#include <sstream>


using namespace Graph_lib;
using namespace std;


struct firstwin : Simple_window {
    firstwin(Point xy, int w, int h, const string& title );
	bool wait_for_input();
	int getmonth();
	int getyear(); 
    void splash_text();
	String Month, Year;
	int day_in_month, day_of_the_week, days_in_month, mo, ye;
private:
    Button start_button;        // add (refresh_x,refresh_y) to lines
    In_box smonth;
	In_box syear;
	bool start_time;
    
    static void cb_start(Address, Address); // callback for store_button
    void start(); 
};


firstwin::firstwin(Point xy, int w, int h, const string& title)
    :Simple_window(xy,w,h,title),
	start_time(false),
	start_button(Point(200,300), 70, 20, "Start!", cb_start),
    smonth(Point(100,250), 100, 20, "Month"),
	syear(Point(300,250), 100, 20, "Year")
	
	//title.set_font_size(30)
    
{
    attach(start_button);
    attach(smonth);
    attach(syear);
	detach(Simple_window::next_button);
}

bool firstwin::wait_for_input()
// modified event loop:
// handle all events (as per default), quit when button_pushed becomes true
// this allows graphics without control inversion
{
    show();
    start_time = false;
#if 1
    // Simpler handler
    while (!start_time) Fl::wait(); //Fl::wait() segfualts... need to ask about that...
    Fl::redraw();
#else
    // To handle the case where the user presses the X button in the window frame
    // to kill the application, change the condition to 0 to enable this branch.
    Fl::run();
#endif
    return start_time;
}

void firstwin::cb_start(Address, Address pw)
// call Simple_window::next() for the window located at pw
{  
    reference_to<firstwin>(pw).start();    
}

void firstwin::start()
{
	mo = smonth.get_int();
	ye = syear.get_int();
	start_time = true;
	hide();
}

int firstwin::getmonth()
{
	return mo;
}

int firstwin::getyear()
{
	return ye;
}

void firstwin::splash_text()
{
Vector_ref<Text> descript;
  Text title(Point(35,45),"Calendar Program Instructions");
   //description (had to be broken up b/c FLTK apparently doesn't know what '\n' is...
  descript.push_back(new Text(Point(15,85),"This program is a C++/FLTK GUI calendar program that has the look and basic"));
  descript.push_back(new Text(Point(15,100),"functionality of Outlook or a similar program. Please enter  a month day and"));
  descript.push_back(new Text(Point(15,115),"year into the text boxes below. There should be no letters hyphens or symbols"));
  descript.push_back(new Text(Point(15,130),"in these boxes, numbers only please. The last text box is for the name of the"));
  descript.push_back(new Text(Point(15,145),"appointment. Please do not use anything other that characters. Click submit"));
  descript.push_back(new Text(Point(15,160),"to save the date to the calendar. This is an interactive calendar."));
  descript.push_back(new Text(Point(15,175),"The buttons at the top of the next screen will navigate through the months."));
  descript.push_back(new Text(Point(15,190),"The text boxes on the calendar page are there to input more appontments"));
  descript.push_back(new Text(Point(15,205),"with the same format as the one in this window."));  
  title.set_font_size(25);
  
  //attaching everything
  for(int j=0; j<8; j++)
  {
  descript[j].set_font_size(12);
  attach(descript[j]);
  }
  attach(title);
}