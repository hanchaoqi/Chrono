#include "std_lib_facilities.h"
namespace{
	class Date{
	public:
		enum Month{
			jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
		};
		class Invalid{};

		Date(int yy, Month mm, int dd);
		Date();

		void add_day(int n);
		void add_month(int n);
		void add_year(int n);


		int year()const{ return y; }
		Month month()const{ return m; }
		int day()const{ return d; }
	private:
		int y, d;
		Month m;
	};

	vector<int> days = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };


	bool is_date(int y, Date::Month m, int d);
	bool is_leapyear(int y);
	int date_to_count(Date dd);
	Date count_to_date(int n);
	Date& default_date()
	{
		static Date dd(1970, Date::jan, 1);
		return dd;
	}
	Date::Month int_to_month(int n);

	bool operator==(const Date& a, const Date& b);
	bool operator!=(const Date& a, const Date& b);

	ostream& operator<<(ostream& os, const Date& d);
	istream& operator>>(istream& is, Date& dd);

}