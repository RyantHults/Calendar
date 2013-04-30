#include "std_lib_facilities_3.h"
#include "Simple_window.h"
#include "Graph.h"
#include "Window.h"
#include "chrono.h"
#include "win1.h"
#include "firstwindow.h"
#include <sstream>
#include <iostream>


using namespace Chrono;
using namespace std;

int main()

try {
//splash screen shit
  firstwin splash(Point(100,200),500,350,"Calendar Program");
  
  splash.splash_text();
  cout<<"test" <<endl;
  splash.wait_for_input();
  
  //main window runs
  win1 calendar(Point(100,200),900,1000,"Calendar 360");
  calendar.calendar_grid();
  calendar.calendar_stext();
  String Month, Year; //will be depricated when everything is cleaned up
  int day_in_month, day_of_the_week, days_in_month; //same with most of this
  
  //testing variables
  Month = "January";
  Year = "2012";
  day_of_the_week = 2;//getWeekDay((1993,8,28))+1;
  days_in_month = 30;
  int imonth = splash.getmonth();
  int iyear = splash.getyear();
  calendar.firsttime(imonth, iyear);

//grid~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//lines


//month title    
    Text t(Point(30,55),Month+" "+Year);
    t.set_font_size(30);
    calendar.attach(t);
    

// waiting for button press 
  calendar.wait_for_button();
  return 0;
}
catch(exception& e) {
	cerr << "exception: " << e.what() << '\n';
	return 1;
}

catch (...) {
	cerr << "Some exception\n";
	return 2;
}	



