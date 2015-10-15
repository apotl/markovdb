#include "db.hpp"
#include <iostream>
#include <ctime>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <vector>
#include <sstream>

using namespace std;

vector<string> markov_primer( string s)
{
	vector<string> m_mkv;
	for( int i; s.find(' ') != -1; i++)
	{
		m_mkv.push_back(s.substr(0,s.find(' ')));
		s = s.substr(s.find(' ')+1,s.size()-1);
	}
	return m_mkv;
}

int main()
{
	srand(time(NULL));
	Tree db = NULL; 

	ifstream chanlog; 
	chanlog.open( "chanlog");
	if ( chanlog.fail())
	{
		cout << "ERROR: chanlog not found. Exiting" << endl;
		return -1;
	}
	string buffer;
	vector<string> bufsplit;
	while ( getline( chanlog, buffer))
	{
		bufsplit = markov_primer( buffer);
		if (bufsplit.size() > 2)
		{
			for( int i = 0; i < bufsplit.size() - 2; i++)
			{
				string cur = bufsplit[i]+" "+bufsplit[i+1];
				string nxt = bufsplit[i+1]+" "+bufsplit[i+2];
				if ( tree_empty( db)) 
				{
					db = tree_makenode( cur, nxt, NULL);
					
					db->key().add(nxt);
				}
				else
				{	
					Tree tmp = tree_search(cur, db);
					if (tmp)
					{
						tmp->key().add(nxt);
					}
					else
					{
						tree_insert( &db, cur, nxt);
					}
				}
			}

			tree_insert( &db, bufsplit[bufsplit.size()-2]+" "+bufsplit[bufsplit.size()-1], "");
		}
	}
	chanlog.close();
	cout << "Database loaded." << endl;

	int cmdskt, readskt;
	unlink("markovdb.sock");
	socklen_t sktlen = sizeof(struct sockaddr_un);
	cmdskt = socket( AF_UNIX, SOCK_STREAM, 0);
	if ( cmdskt == -1) return -1;
	struct sockaddr_un cmdsktaddr;
	cmdsktaddr.sun_family = AF_UNIX;
	strncpy(cmdsktaddr.sun_path, "markovdb.sock", 13);
	if( bind( cmdskt, (struct sockaddr*) &cmdsktaddr, sizeof(struct sockaddr_un))) return -1;

	char cmd[4];
	char thought[510];
	char buf[513];
	stringstream sthought;
	string output, thoughtstr;

	while (1)
	{
		if (!listen( cmdskt, 5))
		{
			if (((readskt = accept( cmdskt, (struct sockaddr*) &cmdsktaddr, &sktlen))) == -1) return -1;
			memset(cmd,'\0',4);
			memset(thought,'\0',509);
			memset(buf,'\0',513);

			read(readskt, buf, 512);

			strncpy(cmd, buf, 3);
			strncpy(thought, buf+3,509);
			thoughtstr = static_cast<string>(thought);

			if ( !strcmp(cmd,"GET"))
			{
				sthought << thoughtstr.substr(0,thoughtstr.find(' ')) << " ";
				Tree tmp;
				do
				{
					tmp = tree_search( thoughtstr, db);
					if (!tmp) break;
					thoughtstr = tmp->key().get();
					sthought << thoughtstr.substr(0,thoughtstr.find(' ')) << " ";
				} while ( thoughtstr != "");
				sthought << thoughtstr.substr(thoughtstr.find(' ')+1,thoughtstr.size()-1);
				output = sthought.str();
				cout << output << endl;
				if (output.size() < 490) output.replace(output.size(),1,491-output.size(),'\0');
				send(readskt,output.c_str(),490,0);
				sthought.str("");

			}
			else if ( !strcmp(cmd,"ADD"))
			{
				cout << "u add" << endl;
			}
		}
	}
	return 0;
}
