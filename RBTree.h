#ifndef RB_TREE_H
#define RB_TREE_H
#include "CBTree.h"

#define  BLACK 1
#define  RED 0
#define  UNDEF 0
template<typename T>
class  CRBTree: public CBTree<T>
{
private:
	CBTNode<T>*  GandParent(CBTNode<T>* n);
	CBTNode<T>*  Uncle(CBTNode<T>* n);
	CBTNode<T>*  Brother(CBTNode<T>* n);
    CBTNode<T>* Rotate_left(CBTNode<T>* node,CBTNode<T>* root);
	 CBTNode<T>* Rotate_right(CBTNode<T>* node,CBTNode<T>* root);
	 CBTNode<T>* Search_Auxiliary(T key, CBTNode<T>* root, CBTNode<T>** save);
	CBTNode<T>* Search(T key,CBTNode<T>* root);
	CBTNode<T>* newNode(T key,T data);
public:
	//insert
	void insert_root(CBTNode<T>* n);
	void insert_pBlack(CBTNode<T>* n);
	void insert_pRed_uRed(CBTNode<T>* n);
	void insert_pRed_uBlack_Rright(CBTNode<T>* n);
	void insert_pBed_uBlack_Left(CBTNode<T>* n);
	//insert comp
	CBTNode<T>* insert(T key,T data,CBTNode<T>* root);
   CBTNode<T>* insert_rebalance(CBTNode<T>* node,CBTNode<T>* root);

	//delete
   void delete_root(CBTNode<T>* n);
   void delete_bRed(CBTNode<T>* n);
   void delete_bBlack_bsBlack_pBlack(CBTNode<T>* n);
   void delete_bBlack_bsBlack_pRed(CBTNode<T>* n);
   void delete_bBlack_blsRed_brsBlack_pLeft(CBTNode<T>* n);
   void delete_bBlack_brsRed_pLeft(CBTNode<T>* n);

   //delete comp
    CBTNode<T>* Erase(T key,CBTNode<T>* root);
    CBTNode<T>* Erase_rebalance(CBTNode<T>* node,CBTNode<T>* parent,CBTNode<T>* root);
};


template<typename T>
inline CBTNode<T>* CRBTree<T>::newNode(T key,T data)
{
	CBTNode<T>* node=new CBTNode<T>;
	if (!node)
	{
		exit(-1);
	}
	node->key=key,node->data=data;
	return node;
}

template<typename T>
inline CBTNode<T>* CRBTree<T>::Rotate_left(CBTNode<T>* node,CBTNode<T>* root)
{
	CBTNode<T>* right = node->right;    //ָ��ָ��ָ�� right<--node->right  
	if ((node->right = right->left))    
	{  
		right->left->parent = node;  //�ñ������ע��ͼ��node��Ϊb�ĸ�ĸ  
	}  
	right->left = node;   //node��Ϊright������  

	if ((right->parent = node->parent))  
	{  
		if (node == node->parent->right)  
		{  
			node->parent->right = right;  
		}  
		else  
		{  
			node->parent->left = right;  
		}  
	}  
	else  
	{  
		root = right;  
	}  
	node->parent = right;  //right��Ϊnode�ĸ�ĸ  
	return root;  
}


template<typename T>
inline CBTNode<T>* CRBTree<T>::Rotate_right(CBTNode<T>* node,CBTNode<T>* root)
{
	CBTNode<T>* left = node->left;  
	if ((node->left = left->right))  
	{  
		left->right->parent = node;  
	}  
	left->right = node;  

	if ((left->parent = node->parent))  
	{  
		if (node == node->parent->right)  
		{  
			node->parent->right = left;  
		}  
		else  
		{  
			node->parent->left = left;  
		}  
	}  
	else  
	{  
		root = left;  
	}  
	node->parent = left;  
	return root;
}

template<typename T>
inline CBTNode<T>* CRBTree<T>::Search_Auxiliary(T key, CBTNode<T>* root, CBTNode<T>** save)
{
	CBTNode<T>* node = root, *parent = NULL;  
	int ret;  
	while (node)  
	{  
		parent = node;  
		ret = node->key - key;  
		if (0 < ret)  
		{  
			node = node->left;  
		}  
		else if (0 > ret)  
		{  
			node = node->right;  
		}  
		else  
		{  
			return node;  
		}  
	}  
	if (save)  
	{  
		*save = parent;  
	}  
	return NULL;
}

template<typename T>
inline CBTNode<T>* CRBTree<T>::Search(T key,CBTNode<T>* root)
{
	return Search_Auxiliary(key,root,NULL);
}

template<typename T>
inline CBTNode<T>* CRBTree<T>::insert(T key,T data,CBTNode<T>* root)
{
	CBTNode<T> *parent = NULL, *node;  
	parent = NULL;  
	if ((node = Search_Auxiliary(key, root, &parent)))  //����rb_search_auxiliary�ҵ�������ĵط�  
	{  
		return root;  
	}  
	node = newNode(key, data);  //������  
	node->parent = parent;     
	node->left = node->right = NULL;  
	node->color = RED;  
	if (parent)  
	{  
		if (parent->key > key)  
		{  
			parent->left = node;  
		}  
		else  
		{  
			parent->right = node;  
		}  
	}  
	else  
	{  
		root = node;  
	}  
	return insert_rebalance(node, root);   //������󣬵���rb_insert_rebalance�޸������ 
}

template<typename T>
inline CBTNode<T>* CRBTree<T>::insert_rebalance(CBTNode<T>* node,CBTNode<T>* root)
{
	CBTNode<T>* parent, *gparent, *uncle, *tmp;  //��ĸp[z]���游p[p[z]]������y����ʱ���*tmp  
	while ((parent = node->parent) && parent->color == RED)  
	{     //parent Ϊnode�ĸ�ĸ���ҵ���ĸ����ɫΪ��ʱ  
		gparent = parent->parent;   //gparentΪ�游  

		if (parent == gparent->left)  //���游�����Ӽ�Ϊ��ĸʱ��  
			//��ʵ����������䣬�޷Ǿ�����˳���ӡ���ĸ���游�Ĺ�ϵ��:D��  
		{  
			uncle = gparent->right;  //��������ĸ������y���Ǹ�ĸ���Һ��ӡ�  

			if (uncle && uncle->color == RED) //���1��z������y�Ǻ�ɫ��  
			{  
				uncle->color = BLACK;   //��������y��Ϊ��ɫ  
				parent->color = BLACK;  //z�ĸ�ĸp[z]Ҳ��Ϊ��ɫ�����z��p[z]���Ǻ�ɫ�����⡣  
				gparent->color = RED;    
				node = gparent;     //���游�����������z��ָ��z�������㣬����Ϊ��ɫ��  
				//�������1�У�ֻ������z��Ϊ��ĸ���Һ��ӵ������  
			}  
			else                     //���2��z������y�Ǻ�ɫ�ģ�  
			{     
				if (parent->right == node)  //��zΪ�Һ���  
				{  
					root = Rotate_left(parent, root); //����[���z���븸ĸ���]  
					tmp = parent;  
					parent = node;  
					node = tmp;     //parent��node ������ɫ  
				}  
				//���3��z������y�Ǻ�ɫ�ģ���ʱz��Ϊ�����ӡ�  
				//ע�⣬1�����3�����������2�仯�����ġ�  
				//......2��z���������Ǻ�ɫ�ģ�����������1�ˡ�  
				parent->color = BLACK;   //z�ĸ�ĸp[z]��Ϊ��ɫ  
				gparent->color = RED;    //ԭ�游�����Ϊ��ɫ  
				root = Rotate_right(gparent, root); //����[���z�����游���]  
			}  
		}   
		else   
		{       
			// if (parent == gparent->right) ���游���Һ��Ӽ�Ϊ��ĸʱ���������뿴���������µ�23¥��ͬʱ����лSupremeHoverָ������  
			uncle = gparent->left;  //�游��������Ϊ�����㡣[ԭ�������ϲ���һ����]  
			if (uncle && uncle->color == RED)  //���1��z������y�Ǻ�ɫ��  
			{  
				uncle->color = BLACK;  
				parent->color = BLACK;  
				gparent->color = RED;  
				node = gparent;           //ͬ�ϡ�  
			}  
			else                               //���2��z������y�Ǻ�ɫ�ģ�  
			{  
				if (parent->left == node)  //��zΪ����  
				{  
					root = Rotate_right(parent, root);  //�Խ��parent��root����  
					tmp = parent;  
					parent = node;  
					node = tmp;       //parent��node ������ɫ  
				}   
				//�������2�ı仯����Ϊ�����3.  
				parent->color = BLACK;  
				gparent->color = RED;  
				root = Rotate_left(gparent, root);   //�Խ��gparent��root����  
			}  
		}  
	}  
	root->color = BLACK; //����㣬����������������Ϊ��ɫ��  
	return root;      //���ظ���㡣
}

template<typename T>
inline CBTNode<T>* CRBTree<T>::Erase(T key,CBTNode<T>* root)
{
	CBTNode<T> *child, *parent, *old, *left, *node;  
	Color color;  
	if (!(node = Search_Auxiliary(key, root, NULL)))  //����rb_search_auxiliary����Ҫɾ����  
	{  
		printf("key %d is not exist!/n");  
		return root;  
	}  
	old = node;  
	if (node->left && node->right)  
	{  
		node = node->right;  
		while ((left = node->left) != NULL)  
		{  
			node = left;  
		}  
		child = node->right;  
		parent = node->parent;  
		color = node->color;  
		if (child)  
		{  
			child->parent = parent;  
		}  
		if (parent)  
		{  
			if (parent->left == node)  
			{  
				parent->left = child;  
			}  
			else  
			{  
				parent->right = child;  
			}  
		}  
		else  
		{  
			root = child;  
		}  
		if (node->parent == old)  
		{  
			parent = node;  
		}  
		node->parent = old->parent;  
		node->color = old->color;  
		node->right = old->right;  
		node->left = old->left;  
		if (old->parent)  
		{  
			if (old->parent->left == old)  
			{  
				old->parent->left = node;  
			}  
			else  
			{  
				old->parent->right = node;  
			}  
		}   
		else  
		{  
			root = node;  
		}  
		old->left->parent = node;  
		if (old->right)  
		{  
			old->right->parent = node;  
		}  
	}  
	else  
	{  
		if (!node->left)  
		{  
			child = node->right;  
		}  
		else if (!node->right)  
		{  
			child = node->left;  
		}  
		parent = node->parent;  
		color = node->color;  

		if (child)  
		{  
			child->parent = parent;  
		}  
		if (parent)  
		{  
			if (parent->left == node)  
			{  
				parent->left = child;  
			}  
			else  
			{  
				parent->right = child;  
			}  
		}  
		else  
		{  
			root = child;  
		}  
	}  
	free(old);  
	if (color == BLACK)  
	{  
		root = Erase_rebalance(child, parent, root); //����rb_erase_rebalance���ָ������
	}  
	return root;  
}

template<typename T>
inline CBTNode<T>* CRBTree<T>::Erase_rebalance(CBTNode<T>* node,CBTNode<T>* parent,CBTNode<T>* root)
{
	CBTNode<T> *other, *o_left, *o_right;   //x���ֵ�*other���ֵ�����*o_left,*o_right  
	while ((!node || node->color == BLACK) && node != root)   
	{  
		if (parent->left == node)  
		{  
			other = parent->right;  
			if (other->color == RED)   //���1��x���ֵ�w�Ǻ�ɫ��  
			{  
				other->color = BLACK;    
				parent->color = RED;   //�����У��ı���ɫ��w->�ڡ�p[x]->�졣  
				root = Rotate_left(parent, root);  //�ٶ�p[x]��һ������  
				other = parent->right;  //x�����ֵ�new w ����ת֮ǰw��ĳ�����ӡ���ʵ����������Ч��  
			}  
			if ((!other->left || other->left->color == BLACK) &&  
				(!other->right || other->right->color == BLACK))    //���2��x���ֵ�w�Ǻ�ɫ����w����������Ҳ  ���Ǻ�ɫ��  
			{                         //����w��w���������Ӷ��Ǻ�ɫ�ģ�����x��w�ϵ�ȥ��һ��ɫ��  
				other->color = RED;   //���ǣ��ֵ�w��Ϊ��ɫ��  
				node = parent;    //p[x]Ϊ�½��x  
				parent = node->parent;  //x<-p[x]  
			}  
			else                       //���3��x���ֵ�w�Ǻ�ɫ�ģ�  
			{                          //�ң�w�������Ǻ�ɫ���Һ���Ϊ��ɫ��  
				if (!other->right || other->right->color == BLACK)  
				{  
					if ((o_left = other->left))   //w��������left[w]����ɫ������  
					{  
						o_left->color = BLACK;    //w�����ӱ�Ϊ�ɺ�->��ɫ  
					}   
					other->color = RED;           //w�ɺ�->��  
					root = Rotate_right(other, root);  //�ٶ�w�����������Ӷ�������ʻָ���  
					other = parent->right;        //�仯��ģ��������Һ��ӣ���Ϊ�µ��ֵܽ�� w��  
				}  
				//���4��x���ֵ�w�Ǻ�ɫ��  
				other->color = parent->color;  //���ֵܽڵ�Ⱦ�ɵ�ǰ�ڵ㸸�ڵ����ɫ��  
				parent->color = BLACK;  //�ѵ�ǰ�ڵ㸸�ڵ�Ⱦ�ɺ�ɫ  
				if (other->right)      //��w���Һ����Ǻ�  
				{  
					other->right->color = BLACK;  //�ֵܽڵ�w�Һ���Ⱦ�ɺ�ɫ  
				}  
				root = Rotate_left(parent, root);  //������һ������  
				node = root;   //����x��Ϊ����  
				break;  
			}  
		}  
		//������������������ԭ��һ�¡������ԡ�  
		else  
		{  
			other = parent->left;  
			if (other->color == RED)  
			{  
				other->color = BLACK;  
				parent->color = RED;  
				root = Rotate_right(parent, root);  
				other = parent->left;  
			}  
			if ((!other->left || other->left->color == BLACK) &&  
				(!other->right || other->right->color == BLACK))  
			{  
				other->color = RED;  
				node = parent;  
				parent = node->parent;  
			}  
			else  
			{  
				if (!other->left || other->left->color == BLACK)  
				{  
					if ((o_right = other->right))  
					{  
						o_right->color = BLACK;  
					}  
					other->color = RED;  
					root = Rotate_left(other, root);  
					other = parent->left;  
				}  
				other->color = parent->color;  
				parent->color = BLACK;  
				if (other->left)  
				{  
					other->left->color = BLACK;  
				}  
				root = Rotate_right(parent, root);  
				node = root;  
				break;  
			}  
		}  
	}  
	if (node)  
	{  
		node->color = BLACK;  //���node[����������Ϊ�˸����]����Ϊ��ɫ��  
	}    
	return root;  //����root 
}


template<typename T>
inline CBTNode<T>* CRBTree<T>::GandParent(CBTNode<T>* n)
{
	return n->parent->parent;
}

template<typename T>
inline CBTNode<T>* CRBTree<T>::Uncle(CBTNode<T>* n)
{
	if (n->parent==GandParent(n)->left)
	return GandParent(n)->right;
	else
	return GandParent(n)->left;
}

template<typename T>
inline CBTNode<T>* CRBTree<T>::Brother(CBTNode<T>* n)
{
	if (n==n->parent->left)
	return n->parent->right;
	else
	return n->parent->left;
}

template <typename T>
void  CRBTree<T>::insert_root(CBTNode<T>* n)
{
	if (n->parent==NULL)
	n->color=BLACK;
	else
	insert_pBlack(n);
}

template <typename T>
void CRBTree<T>::insert_pBlack(CBTNode<T>* n)
{
	if (n->parent->color==BLACK)
	return;
	else
	insert_pRed_uRed(n);
}

template<typename T>
void CRBTree<T>::insert_pRed_uRed(CBTNode<T>* n)
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
void CRBTree<T>::insert_pRed_uBlack_Rright(CBTNode<T>* n)
{
	if (n==n->parent->right&&n->parent==GandParent(n)->left)
	{
		doublerRotateWithLeft(n->parent);
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
void CRBTree<T>::insert_pBed_uBlack_Left(CBTNode<T>* n)
{
	n->parent->color=BLACK;
	GandParent(n)->color=RED;
	if (n.==n->parent->left&&n->parent==GandParent(n)->left)
	SingleRotateWithRight(GandParent(n));
	else
	SingleRotateWithLeft(GandParent(n));
}


template <typename T>
void CRBTree<T>::delete_root(CBTNode<T>* n)
{
	if (n->parent!=NULL)
	delete_bRed(n);
}

template <typename T>
void CRBTree<T>::delete_bRed(CBTNode<T>* n)
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
void CRBTree<T>::delete_bBlack_bsBlack_pBlack(CBTNode<T>* n)
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
void CRBTree<T>::delete_bBlack_bsBlack_pRed(CBTNode<T>* n)
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
void CRBTree<T>::delete_bBlack_blsRed_brsBlack_pLeft(CBTNode<T>* n)
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
void CRBTree<T>::delete_bBlack_brsRed_pLeft(CBTNode<T>* n)
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