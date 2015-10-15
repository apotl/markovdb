#ifndef FRAGMENT_H
#define FRAGMENT_H

#include <string>
#include <cstdlib>

#define MAX 128

using namespace std;

class Fragment
{
	public:
		Fragment();
		void set( string val);
		void add( string s);
		string key();
		string get();
		void print();

	private:
		string m_key;
		string m_data[MAX];
		int m_last;
		bool exists(string val);
};

#endif
