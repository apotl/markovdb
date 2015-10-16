#include "db.hpp"

Key& Node::key()
{
	return m_key;
}

Node* Node::parent()
{
	return m_parent;
}

Node* Node::leftchild()
{
	return m_leftchild;
}

Node* Node::rightchild()
{
	return m_rightchild;
}

int Node::num_children() 
{
	int count = 0; 
	if ( m_leftchild && m_rightchild)
	{
		count += m_leftchild->num_children();
		count += m_rightchild->num_children();
	}
	else if ( m_leftchild && !m_rightchild)
	{
		count += m_leftchild->num_children();
	}
	else if ( !m_leftchild && m_rightchild)
	{
		count += m_rightchild->num_children();
	}
	count++; 
	return count;
}


void Node::set_key(Key k)
{
	m_key = k;
}

void Node::set_parent( Node* p)
{
	m_parent = p;
}

void Node::set_leftchild( Node* l)
{
	m_leftchild = l;
}

void Node::set_rightchild( Node* r)
{
	m_rightchild = r;
}
/*
void Node::replace_with_successor() 
	                            
{
	Node* tmp = m_rightchild; 
	while ( tmp->leftchild())
	{
		tmp = tmp->leftchild();
	}
	m_key = tmp->key(); 
	tree_remove( tmp, tmp->key().key()); 
}
void Node::replace_with_predecessor() 
	                              
{
	Node* tmp = m_leftchild; 
	while ( tmp->rightchild())
	{
		tmp = tmp->rightchild();
	}
	m_key = tmp->key(); 
	tree_remove( tmp, tmp->key().key()); 
}
*/


void tree_init( Tree* t) 
{
	(*t)->set_parent( NULL);
}


void tree_makenull( Tree t)
{
	if ( !t) return; 
	                 
	tree_makenull( t->leftchild());
	tree_makenull( t->rightchild());
	delete t;
}


Node* tree_makenode( string k, string s, Node* parent)
{
	Node* tmp = new Node();
	Fragment* tmpf = new Fragment();
	tmpf->set(k);
	tmpf->add(s);
	tmp->set_key( *tmpf);
	tmp->set_parent( parent); 
	tmp->set_leftchild( NULL); 
	tmp->set_rightchild( NULL);
	return tmp; 
}


Node* tree_search( string k, Tree t)
{
	if ( !t)
	{
		return NULL;
	}
	else if ( k == t->key().key())
	{
		return t;
	}
	else if ( k < t->key().key()) 
	{
		return tree_search( k, t->leftchild());
	}
	else
	{
		return tree_search( k, t->rightchild());
	}
}

Node* tree_initsearch( string k, Tree t)
{
	vector<string> matches;
	tree_keymatches( t, k, matches);
	if (matches.size() == 0) return NULL;
	return tree_search( matches[rand()%matches.size()], t);
}

void tree_keymatches( Node* n, string k, vector<string>& matches)
{
	if(n->key().key().find(k.substr(0,k.find(' '))+" ") != -1)
	{
		matches.push_back(n->key().key()); 
	}
	if ( n->leftchild() && n->rightchild())
	{
		tree_keymatches( n->leftchild(), k, matches);
		tree_keymatches( n->rightchild(), k, matches);
	}
	else if ( n->leftchild() && !n->rightchild())
	{
		tree_keymatches( n->leftchild(), k, matches);
	}
	else if ( !n->leftchild() && n->rightchild())
	{
		tree_keymatches( n->rightchild(), k, matches);
	}
}

void tree_insert( Tree* t, string k, string s)
{
	if ( k < (*t)->key().key())
	{
		if ( (*t)->leftchild())
		{
			Node* tmp = (*t)->leftchild(); 
			tree_insert( &tmp, k, s);
		}
		else
		{
			(*t)->set_leftchild( tree_makenode( k, s, (*t)));
			(*t)->leftchild()->key().add( s);
		}
	}
	else if ( k > (*t)->key().key())
	{
		if ( (*t)->rightchild())
		{
			Node* tmp = (*t)->rightchild(); 
			tree_insert( &tmp, k, s);
		}
		else
		{
			(*t)->set_rightchild( tree_makenode( k, s, (*t)));
			(*t)->rightchild()->key().add( s);
		}
	}
	
}
/*
void tree_remove( Node* t, string k)
{
	Node* to_rm = tree_search( k, t); 
	if ( !to_rm->leftchild() && !to_rm->rightchild())
	{
		if ( !to_rm->parent()) 
		{
			delete to_rm;
			t = NULL; 
			return;
		}
		if ( to_rm->parent()->leftchild() == to_rm)
		{
			to_rm->parent()->set_leftchild( NULL); 
		}
		else
		{
			to_rm->parent()->set_rightchild( NULL); 
		}
		delete to_rm;
	}
	else if ( to_rm->leftchild() && !to_rm->rightchild()) 
	{
		to_rm->set_key( to_rm->leftchild()->key());
		Node *tmp = to_rm->leftchild(); 
		if ( to_rm->leftchild()->rightchild())
		{
			to_rm->set_rightchild( to_rm->leftchild()->rightchild());
			to_rm->set_leftchild( to_rm->leftchild()->leftchild());
			to_rm->rightchild()->set_parent( to_rm);
		}
		else to_rm->set_leftchild( NULL); 
		delete tmp; 
	}
	else if ( !to_rm->leftchild() && to_rm->rightchild())
	{
		to_rm->set_key( to_rm->rightchild()->key());
		Node *tmp = to_rm->rightchild(); 
		if ( to_rm->rightchild()->leftchild())
		{
			to_rm->set_leftchild( to_rm->rightchild()->leftchild());
			to_rm->set_rightchild( to_rm->rightchild()->rightchild());
			to_rm->leftchild()->set_parent( to_rm);
		}
		else to_rm->set_rightchild( NULL); 
		delete tmp; 
	}
	else
	{
		to_rm->replace_with_successor(); 
		                                 
						 
	}
}
*/
/*
void tree_preorder( Node* n, ofstream &file)
{
	file << n->key() << endl; 
	if ( n->leftchild() && n->rightchild())
	{
		tree_preorder( n->leftchild(), file);
		tree_preorder( n->rightchild(), file);
	}
	else if ( n->leftchild() && !n->rightchild())
	{
		tree_preorder( n->leftchild(), file);
	}
	else if ( !n->leftchild() && n->rightchild())
	{
		tree_preorder( n->rightchild(), file);
	}
}


void tree_postorder( Node* n, ofstream &file)
{
	if ( n->leftchild() && n->rightchild())
	{
		tree_postorder( n->leftchild(), file);
		tree_postorder( n->rightchild(), file);
	}
	else if ( n->leftchild() && !n->rightchild())
	{
		tree_postorder( n->leftchild(), file);
	}
	else if ( !n->leftchild() && n->rightchild())
	{
		tree_postorder( n->rightchild(), file);
	}
	file << n->key() << endl; 
}

void tree_inorder( Node* n, ofstream &file)
{
	if ( n->leftchild() && n->rightchild())
	{
		tree_inorder( n->leftchild(), file);
		file << n->key() << endl; 
		tree_inorder( n->rightchild(), file);
	}
	else if ( n->leftchild() && !n->rightchild())
	{
		tree_inorder( n->leftchild(), file);
		file << n->key() << endl; 
	}
	else if ( !n->leftchild() && n->rightchild())
	{
		file << n->key() << endl; 
		tree_inorder( n->rightchild(), file);
	}
	else file << n->key() << endl; 
}
*/
bool tree_empty( Tree t)
{
	if ( !t) return true;
	return false;
}


int tree_height( Tree t) 
{
	int tmp = 0; 
	int height = 0; 
	if ( t->leftchild() && t->rightchild())
	{
		tmp = tree_height( t->leftchild());
		if ( tmp > height) height = tmp; 
		tmp = tree_height( t->rightchild());
		if ( tmp > height) height = tmp; 
	}
	else if ( t->leftchild() && !t->rightchild())
	{
		tmp = tree_height( t->leftchild());
		if ( tmp > height) height = tmp; 
	}
	else if ( !t->leftchild() && t->rightchild())
	{
		tmp = tree_height( t->rightchild());
		if ( tmp > height) height = tmp; 
	}
	height++;
	return height;
}

void tree_fix_grammar( Tree t)
{
//	vector<string> blacklist;
//	static const string copula[] = { "be", "am", "is", "are", "being", "was", "were", "been"};
//	vector<string> copulas = ( copula, copula + sizeof(copula)/sizeof(copula[0]));
}
