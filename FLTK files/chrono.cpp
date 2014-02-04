//Chrono.cpp

#include "chrono.h"


namespace Chrono
{//member function definitions
	Date::Date(int yy, Month mm, int dd)
		:y(yy), m(mm), d(dd)
	{
		if(!is_date(yy,mm,dd))throw Invalid();
	}
	
	const Date& default_date()
	{
		static Date dd(2001, Date::jan,1);	//start of 21st century
		return dd;
	}
	
	Date::Date()
		:y(default_date().year()),
		m(default_date().month()),
		d(default_date().day())
	{
	}
	
	void Date:: add_day(int n)
	{
		for(int i=0;i<n;++i)
		{
			d++;
			 if(!is_date(y,m,d))
			{
					d=1;
					if(m==Date::dec)
			{
				m=Date::jan;
				++y;
			}
			else m=Month(m+1);
			}
		}

	}
	
	void Date:: add_month(int n)
	{
		for(int i=0;i<n;++i)
		{
			if(m==dec)
			{
				m=jan;
				y+=1;
			}
			else m=Month(m+1);
			
		}
	}
	
	void Date:: add_year(int n)
	{
		if(m==feb && d==29 && !leapyear(y+n))
		{
			m=mar;	//use March 1 instead of February 29
			d=1;
		}
		y+=n;
	}
	
	//helper functions:
	
	bool is_date(int y, Date::Month m, int d)
	{
		//assume that y is valid
		if(d<=0) return false;	//d must be positive
		if(m<Date::jan || Date::dec<m) return false;
		
		int days_in_month=31;	//most months have 31 days
		
		switch(m)
		{
			case Date::feb:		//the length of February varies
				days_in_month=(leapyear(y))?29:28;
				break;
			case Date::apr: case Date::jun: case Date::sep: case Date::nov:
				days_in_month=30;	//the rest have 30
				break;
		}
		
		if (days_in_month<d) return false;
		
		return true;
	}
	
	bool leapyear(int y)
	{
		//see exercise 10
	}
	
	bool operator==(const Date& a, const Date& b)
	{
		return a.year()==b.year()
			&& a.month()==b.month()
			&& a.day()==b.day();
	}
	
	bool operator!=(const Date& a, const Date& b)
	{
		return !(a==b);
	}
	
	Date& Date::operator++()
	 {
		
		
		 ++d;
		 if(!is_date(y,m,d))
		 {
			d=1;
			if(m==Date::dec)
			{
				m=Date::jan;
				++y;
			}
			else m=Month(m+1);
		}
		 return *this;
	 }
	
	ostream& operator<<(ostream& os, const Date& d)
	{
		return os << '(' << d.year()
					<< ',' << d.month()
					<<',' << d.day() << ')';
					
	}
	
	istream& operator>>(istream& is, Date& dd)
	{
		int y, m, d;
		char ch1, ch2, ch3, ch4;
		is>>ch1>>y>>ch2>>m>>ch3>>d>>ch4;
		if(!is)return is;
		if(ch1!='(' || ch2!=',' || ch3!=',' || ch4!=')')	//format error
		{
			is.clear(ios_base::failbit);	//set the fail bit
			return is;
		}
		
		dd= Date(y,Date::Month(m),d);	//update dd
		
		return is;
	}
	
	enum Day
	{
		sunday, monday, tuesday, wednesday, thursday, friday, saturday
	};
	
	Date day_of_week(const Date& d)
	{
		return d;
	}
	
	Date next_sunday(const Date& d)
	{
		return d;
	}
	
	Date next_weekday(const Date& d)
	{
		return d;
	}
	
	
}//Chrono