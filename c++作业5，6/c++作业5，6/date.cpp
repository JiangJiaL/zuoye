#include "Date.h"
static uint getMonthDay(int y,uint m)
{
	if (m > 12 || m == 0)
	{
		return 0;
	}
	if (m == 4 || m == 6 || m == 9 || m == 11)
	{
		return 30;
	}
	if (m == 2)
	{
		return 28 + ((y % 400 == 0) || (y % 4 == 0 && y % 100));
	}
	else
	{
		return 31;
	}
}
#if 0
int getLeapNum(int sy, int ey)
{
	int tmp = sy % 4;
	if (tmp)
	{
		sy += (4 - tmp);
	}
	return (ey - sy) / 4 + 1;
}
Date Date:: operator +(uint delay) const
{
	Date res = *this;
	uint tmp;

	int numy = delay / 365;
	int numd = delay % 365;
	int flag = 0;

	if (res.m_month > 2)
	{
		flag = 1;
	}
	int leapnum = getLeapNum(res.m_year + flag, res.m_year + numy);
	while (numd < leapnum)
	{
		numy--;
		leapnum = getLeapNum(res.m_year + flag, res.m_year + numy - 1);
		numd += 365;
	}
	numd -= leapnum;
	res.m_year += numy;
	delay = numd;
#endif 

	Date Date:: operator +(uint delay) const
	{
		Date res = *this;
		uint tmp;
	tmp = getMonthDay(res.m_year, res.m_month);
	while (delay >= tmp )//不能用delay - tmp == 0来作为判断条件，
		                 //因为delay - tmp 的类型为unsigned int;
	{
		delay -= tmp;
		res.m_month++;
		if (res.m_month > 12)
		{
			res.m_month = 1;
			res.m_year++;
		}
		tmp = getMonthDay(res.m_year, res.m_month);
	}
	res.m_day += delay;
	if (res.m_day > tmp)
	{
		res.m_month++;
		if (m_month > 12)
		{
			res.m_month = 1;
			res.m_year++;
		}
		res.m_day -= tmp;
	}
	return res;
}

	Date Date:: operator -(uint delay) const
	{
		Date res = *this;
		uint tmp;
		if (res.m_month == 0)
		{
			res.m_year--;
			res.m_month = 12;
		}
		else
			res.m_month--;
		tmp = getMonthDay(res.m_year, res.m_month);
		while (delay >= tmp)
		{
			delay -= tmp;
			res.m_month--;
			if (res.m_month == 0)
			{
				res.m_month = 12;
				res.m_year--;
			}
			tmp = getMonthDay(res.m_year, res.m_month);
		}
		int tmpday = res.m_day;
		tmpday = res.m_day - delay;
		if (tmpday <= 0)
		{
			tmpday += tmp;
		}
		else
		{
			res.m_month++;
			if (res.m_month > 12)
			{
				res.m_month = 1;
				res.m_year++;
			}
		}
		res.m_day = tmpday;
		return res;
	}



ostream &operator << (ostream & os, Date & d) //输出流
{
	os << d.m_year << '-' << d.m_month << '-' << d.m_day;
	return os;
}

bool Date ::operator <(const Date & d) const
{
	if (m_year < d.m_year)
	{
		return true;
	}
	else if (m_year == d.m_year && m_month < d.m_month)
	{
		return true;
	}
	else if (m_year == d.m_year && m_month == d.m_month && m_day < d.m_day)
	{
		return true;
	}
		return false;
}
bool Date ::operator <=(const  Date & d) const
{
	return !(*this > d);
}
bool Date ::operator >(const  Date & d) const
{
	if (m_year > d.m_year)
	{
		return true;
	}
	else if (m_year == d.m_year && m_month > d.m_month)
	{
		return true;
	}
	else if (m_year == d.m_year && m_month == d.m_month && m_day > d.m_day)
	{
		return true;
	}
		return false;
}

bool Date ::operator >=(const  Date & d) const
{
	return !(*this < d);
}
bool Date ::operator ==(const  Date & d) const
{
	if (m_year == d.m_year &&
		m_month == d.m_month &&
		m_day == d.m_day)
	{
		return true;
	}
	
		return false;
	
}
bool Date ::operator !=(const  Date & d) const
{
	return !(*this == d);
}

Date Date:: operator ++()
{
	int d = getMonthDay(m_year, m_month);
	m_day++;
	if (m_day > d)
	{
		m_day = 1;
		m_month++;
		if (m_month > 12)
		{
			m_month = 1;
			m_year++;
		}
	}
	return *this;
}
Date Date:: operator ++(int)
{
	Date tmp = *this;
	int d = getMonthDay(m_year, m_month);
	m_day++;
	if (m_day > d)
	{
		m_day = 1;
		m_month++;
		if (m_month > 12)
		{
			m_month = 1;
			m_year++;
		}
	}
	return tmp;
}
Date Date::operator --()
{
	m_day--;
	if (m_day < 1)
	{
		m_month--;
		if (m_month < 1)
		{
			m_month = 12;
			m_year--;
		}
		m_day = getMonthDay(m_year, m_month);
	}
	return *this;
}
Date Date::operator --(int)
{
	Date tmp = *this;
	m_day--;
	if (m_day < 1)
	{
		m_month--;
		if (m_month < 1)
		{
			m_month = 12;
			m_year--;
		}
		m_day = getMonthDay(m_year, m_month);
	}
	return tmp;
}