#include "std_lib_facilities.h"

vector<int> days = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

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

int main()
{
	Date dd1(2015, Date::nov, 30);
	cout << dd1 << endl;
	dd1.add_month(3);
	cout << dd1 << endl;
	dd1.add_day(4);
	cout << dd1 << endl;
	dd1.add_year(4);
	cout << dd1 << endl;
	
	return 0;
}

bool is_leapyear(int y)
{
	if (((y % 4 == 0 && y % 100 != 0) || y % 400 == 0))
		return true;
	return false;
}
bool is_date(int y, Date::Month m, int d)
{
	if (y < 0 || (m<Date::jan || m>Date::dec) || (d>31 || d<1))
		return false;
	if (m == Date::feb && d == 29 && !is_leapyear(y))
		return false;
	return true;
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
Date::Month int_to_month(int n)
{
	if (n<Date::jan || n>Date::dec)
		error("Invalid month");
	return Date::Month(n);
}

bool operator==(const Date& a, const Date& b)
{
	return a.year() == b.year()
		&& a.month() == b.year()
		&& a.day() == b.day();
}
bool operator!=(const Date& a, const Date& b)
{
	return !(a == b);
}

ostream& operator<<(ostream& os, const Date& d)
{
	return os << '(' << d.year()
		<< ',' << d.month()
		<< ',' << d.day() << ')';
}
istream& operator>>(istream& is, Date& dd)
{
	int y, m, d;
	char ch1, ch2, ch3, ch4;
	is >> ch1 >> y >> ch2 >> m >> ch3 >> d >> ch4;
	if (!is)
		return is;
	if (ch1 != '(' || ch2 != ',' || ch3 != ',' || ch4 != ')')
	{
		is.clear(ios_base::failbit);
		return is;
	}
	return is;
}

Date::Date(int yy, Date::Month mm, int dd)
:y(yy), m(mm), d(dd)
{
	if (!is_date(yy, mm, dd))
		throw Invalid();
}
Date::Date()
: y(default_date().year()),
m(default_date().month()),
d(default_date().day()){}
void Date::add_day(int n)
{
	Date t = count_to_date(date_to_count(*this) + n);
	*this = t;
}
void Date::add_month(int n)
{
	int mm = m - jan + 1;
	mm += n;
	y += mm / 12;
	if (is_leapyear(y))
		days[2] = 29;
	else
		days[2] = 28;
	mm %= 12;
	int needed = d - days[mm];
	if (needed > 0)
	{
		mm++;
		d = needed;
	}
	m = int_to_month(mm);
}
void Date::add_year(int n)
{
	if (m == feb &&d == 29 && !is_leapyear(y + n))
	{
		m = mar;
		d = 1;
	}
	y += n;
}
