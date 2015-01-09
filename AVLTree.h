#ifndef AVL_TREE_H
#define AVL_TREE_H
#include "CBTree.h"
template<typename T>
class CAVLTree : public CBTree<T>
{
private:
	CBTNode<T>* Insert(const T &data, CBTNode<T> *p);

public:
	CBTNode<T>* SingleRotateWithLeft(CBTNode<T> *p);
	CBTNode<T>* DoubleRotateWithLeft(CBTNode<T> *p);
	CBTNode<T>* SingleRotateWithRight(CBTNode<T> *p);
	CBTNode<T>* DoubleRotateWithRight(CBTNode<T> *p);
	CBTNode<T>* Insert(const T &data);
	CBTNode<T>* Delete(const T &data);
};

//右旋单次
template<typename T>
inline CBTNode<T>* CAVLTree<T>::SingleRotateWithRight(CBTNode<T> *p)
{
	CBTNode<T> *p2;
	// rotate
	p2 = p->left;
	p->left = p2->right;
	p2->right = p;

	// update parent relationship
	p2->parent = p->parent;
	p->parent = p2;
	if (p->left)
		p->left->parent = p;

	// update root node if necessary
	if (p == m_pNodeRoot)
		m_pNodeRoot = p2;

	return p2;  // New root
}

//右旋双次
template<typename T>
inline CBTNode<T>* CAVLTree<T>::DoubleRotateWithRight(CBTNode<T> *p)
{
	p->left = SingleRotateWithRight(p->left);
	return SingleRotateWithRight(p);
}

//左旋单次
template<typename T>
inline CBTNode<T>* CAVLTree<T>::SingleRotateWithLeft(CBTNode<T> *p)
{
	CBTNode<T> *p2;

	// rotate
	p2 = p->right;
	p->right = p2->left;
	p2->left = p;

	// update parent relationship
	p2->parent = p->parent;
	p->parent = p2;
	if (p->right)
		p->right->parent = p;

	// update root node if necessary
	if (p == m_pNodeRoot)
		m_pNodeRoot = p2;

	return p2;  // New root
}

//左旋双次
template<typename T>
inline CBTNode<T>* CAVLTree<T>::DoubleRotateWithLeft(CBTNode<T> *p)
{
	p->right = SingleRotateWithLeft(p->right);
	return SingleRotateWithLeft(p);
}

//插入操作
template<typename T>
inline CBTNode<T>* CAVLTree<T>::Insert(const T &data)
{
	return Insert(data, m_pNodeRoot);
}

//同上
template<typename T>
inline CBTNode<T>* CAVLTree<T>::Insert(const T &data, CBTNode<T> *p)
{
	if (NULL == p)
	{
		// Create and return a one-node tree
		p = new CBTNode<T>;
		if (NULL == p)
			return NULL;
		else
		{
			p->data = data;
			p->left = NULL;
			p->right = NULL;
			if (NULL == m_pNodeRoot)
			{
				m_pNodeRoot = p;
				m_pNodeRoot->parent = NULL;
			}
		}
	}
	// left child
	else if (data < p->data)
	{
		p->left = Insert(data, p->left);
		if (p->left)
			p->left->parent = p;

		if (2 == (GetDepth(p->left) - GetDepth(p->right)))
		{
			// left tree, need to do single rotation
			if (data < p->left->data)
				p = SingleRotateWithRight(p);
			// right tree, need to do double rotation
			else
				p = DoubleRotateWithRight(p);
		}
	}
	// right child
	else if (data > p->data)
	{
		p->right = Insert(data, p->right);
		if (p->right)
			p->right->parent = p;

		if (2 == (GetDepth(p->right) - GetDepth(p->left)))
		{
			// right tree, need to do single rotation
			if (data > p->right->data)
				p = SingleRotateWithLeft(p);
			// left tree, need to do double rotation
			else
				p = DoubleRotateWithLeft(p);
		}
	}
	// else data is in the tree already, we'll do nothing!

	return p;
}

//删除操作
template<typename T>
inline CBTNode<T>* CAVLTree<T>::Delete(const T &data)
{
	// not completed yet.
	return NULL;
}
#endif 
