#include "std_lib_facilities_3.h"
#include "Simple_window.h"
#include "Graph.h"
#include "Window.h"
#include <sstream>

int main()

//click the top left corner to exit

try {
  if(H112 != 201206L)error("Error: incorrect std_lib_facilities_3.h version ",
		  	   H112);
  Simple_window win1(Point(100,200),700,850,"Calendar 360");
  Vector_ref<Rectangle> rect;
  Vector_ref<Line> grid;
  String Month;
  int day_in_month, boxdate_month_starts;
  Month = "January";
//grid~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        rect.push_back(new Rectangle(Point(0,0),900,850));
        rect[0].set_fill_color(FL_WHITE);
        win1.attach(rect[0]);
		
	for(int i=0; i<8; i++)
	{
		grid.push_back(new Line(Point(i*100,100),Point(i*100,850)));
	}
	for(int j=0; j<7; j++)
	{
		grid.push_back(new Line(Point(0,j*150+100),Point(700,j*150+100)));
	}
	
	for(int a=0; a<13; ++a)
	{
		win1.attach(grid[a]);
	}
//month title    
    Text t(Point(30,55),Month);
    t.set_font_size(30);
    win1.attach(t);
//boxes
    Vector_ref<Text> boxdate;
    day_in_month =1;
    
    for(int rownumber=0; rownumber<6; rownumber++)
    {   
        
        for(int collumnumber=0; collumnumber<7; collumnumber++)
        {
        string Day = static_cast<ostringstream*>( &(ostringstream() << day_in_month) )->str();
        boxdate.push_back(new Text(Point(15+100*collumnumber,130+150*rownumber),Day));
        day_in_month++;
        }
    }
    for(int b=0; b<31; b++)
	{
        boxdate[b].set_font_size(30);
		win1.attach(boxdate[b]);
	}
// waiting for button press 
  win1.wait_for_button();
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