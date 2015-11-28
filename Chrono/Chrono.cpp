#include "std_lib_facilities.h"

vector<int> days = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

class Date{
public:
	enum Month{
		jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
	};
	class Invalid{};
	void add_day(int n);
	Month int_to_month(int n);

	Date(int yy, Month mm, int dd);
	int year()const{ return y; }
	Month month()const{ return m; }
	int day()const{ return d; }
private:
	int y, d;
	Month m;
	bool check();
};

bool is_leapyear(int y);
int date_to_count(Date dd);
Date count_to_date(int n);
void print(Date dd);

int main()
{
	Date dd1(2015, Date::nov, 27);
	print(dd1);
	dd1.add_day(4);
	print(dd1);
	return 0;
}

bool is_leapyear(int y)
{
	if (((y % 4 == 0 && y % 100 != 0) || y % 400 == 0))
		return true;
	return false;
}

int date_to_count(Date dd)
{
	int cnt = 0;
	for (int i = 0; i < dd.year(); i++)
	if (is_leapyear(i))
		cnt += 366;
	else
		cnt += 365;
	if (is_leapyear(dd.year()))
		days[2]++;
	for (int i = 1; i < dd.month(); i++)
		cnt += days[i];
	cnt += dd.day();
	return cnt;
}
Date count_to_date(int n)
{
	int y, m;
	y = 0;
	m = 1;
	while (n >= 365)
	if (is_leapyear(y++))
	{
		n -= 366;
	}
	else
	{
		n -= 365;
	}

	while (n > days[m])
	{
		n -= days[m];
		m++;
	}

	Date dd(y, Date::Month(m), n);
	return dd;

}
void print(Date dd)
{
	cout << dd.year() << "-" << dd.month() << "-" << dd.day() << endl;
}

bool Date::check()
{
	if (y < 0 || (m<jan || m>dec) || (d>31 || d<1))
		return false;
	if (!is_leapyear(y) && m == 2 && d == 29)
		return false;
	return true;
}
void Date::add_day(int n)
{
	Date t = count_to_date(date_to_count(*this) + n);
	*this = t;
}
Date::Date(int yy, Date::Month mm, int dd)
:y(yy), m(mm), d(dd)
{
	if (!check())
		throw Invalid();
}
Date::Month Date::int_to_month(int n)
{
	if (n<jan || n>dec)
		error("Invalid month");
	return Month(n);
}
