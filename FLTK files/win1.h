#include "Graph.h"       
#include "GUI.h"
#include "Window.h"
#include "std_lib_facilities_3.h"
#include <iostream>
#include <sstream>


using namespace Graph_lib;
using namespace std;


struct win1 : Simple_window {
    win1(Point xy, int w, int h, const string& title );
	bool wait_for_month();
	void firsttime(int month, int year);
	int getWeekDay(Chrono::Date);
	void notInMonth(int dayofweek);
    void calendar_grid();
    void calendar_stext();
private:
    Button refresh_button; // refreshes the screen. testing purposes only
    Button store_button; // stores/will store the text from in_box's in appt file
    In_box monthf; //month in_box for appts
    In_box yearf; //year in_box for appts
    In_box dayf; //day in_box for appts
	In_box titlef; //title in_box for appts
	int day_of_the_week; //the # of days to skip at the beginning of the month
    int days_in_month; //how many days a month has
	int omonth; //month
	int oyear; //year
    
    static void cb_refresh(Address, Address); // callback for refresh_button
    void refresh(); 
    static void cb_store(Address, Address); // callback for store_button
    void store(); 
    int monthDays(int dyear, int dmonth, int dday);
    void daysinmonth();
};


win1::win1(Point xy, int w, int h, const string& title)
    :Simple_window(xy,w,h,title),
	refresh_button(Point(x_max()-150,0), 70, 20, "refresh", cb_refresh),
    store_button(Point(x_max()-70,50), 70, 20, "store", cb_store),
    monthf(Point(750,150), 100, 20, "Month"),
    yearf(Point(750,190), 100, 20, "Year"),
    dayf(Point(750,110), 100, 20, "Day"),
	titlef(Point(750,230), 100, 20, "Title")
{
    attach(refresh_button);
    attach(store_button);
    attach(monthf);
    attach(yearf);
    attach(dayf);
	attach(titlef);
}

void win1::cb_store(Address, Address pw)   //to store
{  
       reference_to<win1>(pw).store();
} 

void win1::store()
{
   int month = monthf.get_int();        // gets the input value
   int year = yearf.get_int();
   int day = dayf.get_int();
//   Chrono::Date tdate(year,(Chrono::Date::Month)month,day);
//   int  = getWeekDay(tdate);
//   cout << day_of_the_week << endl;
   //cout << month << ", " << day << ", " << year << endl;
}


void win1::cb_refresh(Address, Address pw)    //to refresh 
{  
    reference_to<win1>(pw).refresh();
} 

void win1::refresh()
{
	//detach(
    redraw();		//redraw
}

//Zellers congruence~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int win1::getWeekDay(Chrono::Date date)
{
	int d=date.day();
	int m=date.month();
	int y=date.year();	
	switch(m)
	{
		case 1:case 2:
			m+=12;
			y-=1;
			break;
	}	
	int k=y%100;
	int j=y/100;	
	int h=(1+((13*(m+1))/5)+k+(k/4)+(j/4)-2*j)%7;	
	switch(h)
	{
		case 0:
			h=7;
		default:
			h-=1;
			break;
	}			
	return h;
}

int win1::monthDays(int dyear, int dmonth, int dday) // determines how many days the month has
{
    int year = dyear;
    int day = dday;
    Chrono::Date::Month d = (Chrono::Date::Month)dmonth;
    
    if(d = Chrono::Date::feb)
    {
        days_in_month=(Chrono::leapyear(year))?29:28;
    }
    else if(d==Chrono::Date::apr || d==Chrono::Date::jun || d==Chrono::Date::sep || d==Chrono::Date::nov)
    {
        days_in_month = 30;
    }
    else
    {
        days_in_month = 31;
    }
}


void win1::notInMonth(int dayofweek) //darkens boxes at the beginning of the month that do not contain days from that month
{
	int dotw = day_of_the_week;
	Vector_ref<Rectangle> rect;
    int count=0;
    for(int startday=0; startday<dotw; startday++)
    {
    rect.push_back(new Rectangle(Point(startday*100,100),100,150));
    count++;
    }
    for(int c=0; c<count; c++)
    {
        rect[c].set_fill_color(Color::black);
        attach(rect[c]);
    }   
}
void win1::firsttime(int month, int year) //gets initial information from the splashscreen (via the main function :/)
{
	omonth = month;
	oyear = year;
	int day = 1;
	Chrono::Date tdate(oyear,(Chrono::Date::Month)omonth,day);
	day_of_the_week = getWeekDay(tdate);
	notInMonth(day_of_the_week);
}

void win1::calendar_stext()
{
//days of the week
	Vector_ref<Text> vweekday;
	vweekday.push_back(new Text(Point(15,95),"Sunday"));
	vweekday.push_back(new Text(Point(114,95),"Monday"));
	vweekday.push_back(new Text(Point(214,95),"Tuesday"));
	vweekday.push_back(new Text(Point(307,95),"Wednesday"));
	vweekday.push_back(new Text(Point(411,95),"Thursday"));
	vweekday.push_back(new Text(Point(517,95),"Friday"));
	vweekday.push_back(new Text(Point(613,95),"Saturday"));
	
	for(int wd=0; wd<7; wd++)
	{
		vweekday[wd].set_font_size(15);
		attach(vweekday[wd]);
	}
}

void win1::daysinmonth() //creates the numbers for each day in the month
{
    Vector_ref<Text> boxdate;
    int day_in_month =1;
//first week in the month 
    for(int collumnumber=0+day_of_the_week; collumnumber<7; collumnumber++)
    {
    stringstream ss;
		ss << day_in_month;
		string Day = ss.str();
        boxdate.push_back(new Text(Point(15+100*collumnumber,130),Day));
        day_in_month++;
    }
//rest of the weeks
    for(int rownumber=1; rownumber<6; rownumber++)
    {    
        for(int collumnumber=0; collumnumber<7; collumnumber++)
        {
        if(day_in_month>days_in_month)
            {
            break;
            }
		stringstream ss;
		ss << day_in_month;
		string Day = ss.str();
        boxdate.push_back(new Text(Point(15+100*collumnumber,130+150*rownumber),Day));
        day_in_month++;
        }
    }
    for(int b=0; b<day_in_month-1; b++)
	{
        boxdate[b].set_font_size(30);
		attach(boxdate[b]);
	}
}
void win1::calendar_grid()
{
    Vector_ref<Line> grid;		
	for(int i=0; i<8; i++)
	{
		grid.push_back(new Line(Point(i*100,75),Point(i*100,1000)));
	}
	for(int j=0; j<8; j++)
	{
		grid.push_back(new Line(Point(0,j*150+100),Point(700,j*150+100)));
	}
	grid.push_back(new Line(Point(0,75),Point(700,75)));
	for(int a=0; a<17; ++a)
	{
		attach(grid[a]);
	}
}
