#include "fragment.hpp"
#include <iostream>

Fragment::Fragment()
{
	m_last = -1;
}

void Fragment::set(string val)
{
	m_key = val;
}

void Fragment::add( string val)
{
	if ( !exists(val) && m_last < MAX-1 )
	{
		m_data[m_last+1] = val;
		m_last++;
	}
}

string Fragment::key()
{
	return m_key;
}

string Fragment::get()
{
	if ((rand()%16)<15) return m_data[rand()%(m_last+1)];
	return "";
}

void Fragment::print()
{
	cout << m_key << ":\n";
	for (int i = 0; i <= m_last; i++)
	{
		cout << "	" << m_data[i] << endl;
	}
}

bool Fragment::exists( string val)
{
	for (int i = 0; i <= m_last; i++)
	{
		if ( val == m_data[i]) return true;
	}
	return false;
}
