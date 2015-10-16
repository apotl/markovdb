#ifndef FRAGMENT_H
#define FRAGMENT_H

#include <string>
#include <cstdlib>

#define MAX 128

using namespace std;

struct word
{
	string data;
	int weight;
};

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
		void set( );
		string m_key;
		struct word m_data[MAX];
		int m_last;
		int exists(string val);
		int total();
};

#endif
