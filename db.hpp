#ifndef DB_H
#define DB_H

#include "fragment.hpp"
#include <fstream>
#include <iostream>
#include <vector>
#include <cstdlib>

typedef Fragment Key;

class Node
{
	public:
		
//		friend void tree_remove( Node* t, string k);
		friend void tree_insert( Node** t, string k, string s);
	
		Key& key();
		Node* parent();
		Node* leftchild();
		Node* rightchild();
		int num_children();
		
		void set_key( Key k);
		void set_parent( Node* p);
		void set_leftchild( Node* l);
		void set_rightchild( Node* r);

	private:
		
//		void replace_with_successor();
//		void replace_with_predecessor();

		
		Key m_key;
		Node* m_parent;
		Node* m_leftchild;
		Node* m_rightchild;
};

typedef Node* Tree;

void tree_init( Tree* t);
void tree_makenull( Tree t);
Node* tree_makenode( string k, string s, Node* parent);
Node* tree_search( string k, Tree t);
Node* tree_initsearch( string k, Tree t);
void tree_keymatches( Node* n, string k, vector<string>& matches);
void tree_insert( Tree* t, string k, string s);
void tree_remove( Node* t, string k);
//void tree_preorder( Node* n, ofstream &file);
//void tree_postorder( Node* n, ofstream &file);
//void tree_inorder( Node* n, ofstream &file);
bool tree_empty( Tree t);
int tree_height( Tree t);
void tree_fix_grammar( Tree t);

#endif
