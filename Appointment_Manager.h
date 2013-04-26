#include "std_lib_facilities_3.h"
#include "Chrono.h"


using namespace std;
namespace Appt
{
  class Appoint
	{
	public:
		Appoint(Chrono::Date aa, string ss);
		Appoint();
		
		Chrono::Date day() const {return aa;}
		string subject() const {return ss;}
		
		
		
	private:
		Chrono:: Date aa;
		string ss;	
	};
	
	ostream& operator<<(ostream& os, const Appoint& aa);
	istream& operator>>(istream& is, Appoint& ss);
}	
