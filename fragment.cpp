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
	if ( m_last < MAX-1)
	{
		int index = exists(val);
		if ( index < 0)
		{
			struct word tmp;
			tmp.data = val;
			tmp.weight = 1;
			m_data[m_last+1] = tmp;
			m_last++;
		}
		else
		{
			m_data[index].weight++;
		}
	}
}

string Fragment::key()
{
	return m_key;
}

string Fragment::get()
{
	int ttl = total();
	int choice = rand()%ttl;
	int i = 0;
	for ( ; choice > 0 && i <= m_last; i++)
	{
		choice -= m_data[i].weight;
	}
	if (i == 1) i--;
	return m_data[i].data;
}

void Fragment::print()
{
	cout << m_key << ":\n";
	for (int i = 0; i <= m_last; i++)
	{
		cout << "	" << m_data[i].data << " (" << m_data[i].weight << ")" << endl;
	}
}

int Fragment::total()
{
	int ttl = 0;
	for ( int i = 0; i <= m_last; i++)
	{
		ttl += m_data[i].weight;
	}
	return ttl;
}

int Fragment::exists( string val)
{
	for (int i = 0; i <= m_last; i++)
	{
		if ( val == m_data[i].data) return i;
	}
	return -1;
}
