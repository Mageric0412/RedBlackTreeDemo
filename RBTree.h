#ifndef RB_TREE_H
#define RB_TREE_H
#include "AVLTree.h"

template<typename T>
class  CRBTree: public CAVLTree<T>
{
private:
	CBTNode<T>*  GandParent(CBTNode<T>* n);
	CBTNode<T>*  Uncle(CBTNode<T>* n);
	CBTNode<T>*  Brother(CBTNode<T>* n);

public:
	//insert
	void insert_root(CBTNode<T>* n);
	void insert_pBlack(CBTNode<T>* n);
	void insert_pRed_uRed(CBTNode<T>* n);
	void insert_pRed_uBlack_Rright(CBTNode<T>* n);
	void insert_pBed_uBlack_Left(CBTNode<T>* n);
	//delete
   void delete_root(CBTNode<T>* n);
   void delete_bRed(CBTNode<T>* n);
   void delete_bBlack_bsBlack_pBlack(CBTNode<T>* n);
   void delete_bBlack_bsBlack_pRed(CBTNode<T>* n);
   void delete_bBlack_blsRed_brsBlack_pLeft(CBTNode<T>* n);
   void delete_bBlack_brsRed_pLeft(CBTNode<T>* n);

};

template<typename T>
CBTNode<T>* CRBTree::GandParent(CBTNode<T>* n)
{
	return n->parent->parent;
}

template<typename T>
CBTNode<T>* CRBTree::Uncle(CBTNode<T>* n)
{
	if (n->parent==GandParent(n)->left)
	return GandParent(n)->right;
	else
	return GandParent(n)->left;
}

template<typename T>
CBTNode<T>* CRBTree::Brother(CBTNode<T>* n)
{
	if (n==n->parent->left)
	return n->parent->right;
	else
	return n->parent->left;
}

template <typename T>
void  CRBTree::insert_root(CBTNode<T>* n)
{
	if (n->parent==NULL)
	n->color=BLACK;
	else
	insert_pBlack(n);
}

template <typename T>
void CRBTree::insert_pBlack(CBTNode<T>* n)
{
	if (n->parent->color==BLACK)
	return;
	else
	insert_pRed_uRed(n);
}

template<typename T>
void CRBTree::insert_pRed_uRed(CBTNode<T>* n)
{
	if (Uncle(n)!=NULL&&Uncle(n)->color==RED)
	{
		n->parent->color=BLACK;
	   Uncle(n)->color=BLACK;
	   GandParent(n)->color=RED;
	   insert_root(GandParent(n));
	} 
	else
	insert_pRed_uBlack_Rright(n);

}

template <typename T>
void CRBTree::insert_pRed_uBlack_Rright(CBTNode<T>* n)
{
	if (n==n->parent->right&&n->parent==GandParent(n)->left)
	{
		SingleRotateWithLeft(n->parent);
		n=n->left;
	} 
	else if(n==n->parent->left&&n->parent==GandParent(n)->right)
	{
		SingleRotateWithRight(n->parent);
		n.=n->parent;
	}
	insert_pBed_uBlack_Left(n);
}

template <typename T>
void CRBTree::insert_pBed_uBlack_Left(CBTNode<T>* n)
{
	n->parent->color=BLACK;
	GandParent(n)->color=RED;
	if (n.==n->parent->left&&n->parent==GandParent(n)->left)
	SingleRotateWithRight(GandParent(n));
	else
	SingleRotateWithLeft(GandParent(n));
}


template <typename T>
void CRBTree::delete_root(CBTNode<T>* n)
{
	if (n->parent!=NULL)
	delete_bRed(n);
}

template <typename T>
void CRBTree::delete_bRed(CBTNode<T>* n)
{
	CBTNode<T>* s=Brother(n);
	if (s->color==RED)
	{
		n->parent->color=RED;
		s->color=BLACK;
		if (n==n->parent->left)
		SingleRotateWithLeft(n->parent);
		else
		SingleRotateWithRight(n->parent);
	} 
	delete_bBlack_bsBlack_pBlack(n);
}

template <typename T>
void CRBTree::delete_bBlack_bsBlack_pBlack(CBTNode<T>* n)
{
	CBTNode<T>* s=Brother(n);
	if ((n->parent->color==BLACK)&&(s->color==BLACK)&&(s->left->color==BLACK)&&(s->right->color==BLACK))
	{
		s->color=RED;
		delete_root(n->parent);
	} 
	else
	delete_bBlack_bsBlack_pRed(n);
}

template <typename T>
void CRBTree::delete_bBlack_bsBlack_pRed(CBTNode<T>* n)
{
	CBTNode<T>* s=Brother(n);
	if ((n->parent->color==RED)&&(s->color==BLACK)&&(s->left->color==BLACK)&&(s->right->color==BLACK))
	{
		s->color=RED;
		n->parent->color=BLACK;
	} 
	else
	delete_bBlack_blsRed_brsBlack_pLeft(n);
}

template <typename T>
void CRBTree::delete_bBlack_blsRed_brsBlack_pLeft(CBTNode<T>* n)
{
	CBTNode<T>* s=Brother(n);

	if (s->color == BLACK) 
	{
		if ((n == n->parent->left) &&(s->right->color == BLACK) &&(s->left->color == RED)) 
	   {
		s->color=RED;
		s->left->color=BLACK;
		SingleRotateWithRight(s);
		} 
		else if((n == n->parent->right) &&(s->left->color == BLACK) &&(s->right->color == RED))
		{
			s->color=RED;
			s->right->color=BLACK;
			SingleRotateWithLeft(s);
		}
	}
	delete_bBlack_brsRed_pLeft(n);
}

template <typename T>
void CRBTree::delete_bBlack_brsRed_pLeft(CBTNode<T>* n)
{
	CBTNode<T>* s=Brother(n);
	s->color=n->parent->color;
	n->parent->color=BLACK;
	if (n==n->parent->left)
	{
		s->right->color=BLACK;
		SingleRotateWithLeft(n->parent);
	} 
	else
	{
		s->left->color=BLACK;
		SingleRotateWithRight(n->parent);
	}
}
#endif