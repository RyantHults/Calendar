#include "Appointment_Manager.h"

namespace Appt
{
  Appoint::Appoint(Chrono::Date a, string s)
		:aa(a), ss(s)
	{
	
	}
	
	
	ostream& operator<<(ostream& out, const Appoint& b)
	{
		return out<<b.day()<<b.subject ();
	}
	
	istream& operator>>(istream& in, Appoint& bb)
	{
		Chrono::Date date;
		string subject;
		
		in>>date;
		getline(in,subject);
		if(!in)return in;
		
		bb=Appoint(date,subject);
		return in;
	}
}	

int main()
{ 
	return 0;
}
