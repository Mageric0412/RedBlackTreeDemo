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
	CBTNode<T>* right = node->right;    //指定指针指向 right<--node->right  
	if ((node->right = right->left))    
	{  
		right->left->parent = node;  //好比上面的注释图，node成为b的父母  
	}  
	right->left = node;   //node成为right的左孩子  

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
	node->parent = right;  //right成为node的父母  
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
	if ((node = Search_Auxiliary(key, root, &parent)))  //调用rb_search_auxiliary找到插入结点的地方  
	{  
		return root;  
	}  
	node = newNode(key, data);  //分配结点  
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
	return insert_rebalance(node, root);   //插入结点后，调用rb_insert_rebalance修复红黑树 
}

template<typename T>
inline CBTNode<T>* CRBTree<T>::insert_rebalance(CBTNode<T>* node,CBTNode<T>* root)
{
	CBTNode<T>* parent, *gparent, *uncle, *tmp;  //父母p[z]、祖父p[p[z]]、叔叔y、临时结点*tmp  
	while ((parent = node->parent) && parent->color == RED)  
	{     //parent 为node的父母，且当父母的颜色为红时  
		gparent = parent->parent;   //gparent为祖父  

		if (parent == gparent->left)  //当祖父的左孩子即为父母时。  
			//其实上述几行语句，无非就是理顺孩子、父母、祖父的关系。:D。  
		{  
			uncle = gparent->right;  //定义叔叔的概念，叔叔y就是父母的右孩子。  

			if (uncle && uncle->color == RED) //情况1：z的叔叔y是红色的  
			{  
				uncle->color = BLACK;   //将叔叔结点y着为黑色  
				parent->color = BLACK;  //z的父母p[z]也着为黑色。解决z，p[z]都是红色的问题。  
				gparent->color = RED;    
				node = gparent;     //将祖父当做新增结点z，指针z上移俩层，且着为红色。  
				//上述情况1中，只考虑了z作为父母的右孩子的情况。  
			}  
			else                     //情况2：z的叔叔y是黑色的，  
			{     
				if (parent->right == node)  //且z为右孩子  
				{  
					root = Rotate_left(parent, root); //左旋[结点z，与父母结点]  
					tmp = parent;  
					parent = node;  
					node = tmp;     //parent与node 互换角色  
				}  
				//情况3：z的叔叔y是黑色的，此时z成为了左孩子。  
				//注意，1：情况3是由上述情况2变化而来的。  
				//......2：z的叔叔总是黑色的，否则就是情况1了。  
				parent->color = BLACK;   //z的父母p[z]着为黑色  
				gparent->color = RED;    //原祖父结点着为红色  
				root = Rotate_right(gparent, root); //右旋[结点z，与祖父结点]  
			}  
		}   
		else   
		{       
			// if (parent == gparent->right) 当祖父的右孩子即为父母时。（解释请看本文评论下第23楼，同时，感谢SupremeHover指正！）  
			uncle = gparent->left;  //祖父的左孩子作为叔叔结点。[原理还是与上部分一样的]  
			if (uncle && uncle->color == RED)  //情况1：z的叔叔y是红色的  
			{  
				uncle->color = BLACK;  
				parent->color = BLACK;  
				gparent->color = RED;  
				node = gparent;           //同上。  
			}  
			else                               //情况2：z的叔叔y是黑色的，  
			{  
				if (parent->left == node)  //且z为左孩子  
				{  
					root = Rotate_right(parent, root);  //以结点parent、root右旋  
					tmp = parent;  
					parent = node;  
					node = tmp;       //parent与node 互换角色  
				}   
				//经过情况2的变化，成为了情况3.  
				parent->color = BLACK;  
				gparent->color = RED;  
				root = Rotate_left(gparent, root);   //以结点gparent和root左旋  
			}  
		}  
	}  
	root->color = BLACK; //根结点，不论怎样，都得置为黑色。  
	return root;      //返回根结点。
}

template<typename T>
inline CBTNode<T>* CRBTree<T>::Erase(T key,CBTNode<T>* root)
{
	CBTNode<T> *child, *parent, *old, *left, *node;  
	Color color;  
	if (!(node = Search_Auxiliary(key, root, NULL)))  //调用rb_search_auxiliary查找要删除的  
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
		root = Erase_rebalance(child, parent, root); //调用rb_erase_rebalance来恢复红黑树
	}  
	return root;  
}

template<typename T>
inline CBTNode<T>* CRBTree<T>::Erase_rebalance(CBTNode<T>* node,CBTNode<T>* parent,CBTNode<T>* root)
{
	CBTNode<T> *other, *o_left, *o_right;   //x的兄弟*other，兄弟左孩子*o_left,*o_right  
	while ((!node || node->color == BLACK) && node != root)   
	{  
		if (parent->left == node)  
		{  
			other = parent->right;  
			if (other->color == RED)   //情况1：x的兄弟w是红色的  
			{  
				other->color = BLACK;    
				parent->color = RED;   //上俩行，改变颜色，w->黑、p[x]->红。  
				root = Rotate_left(parent, root);  //再对p[x]做一次左旋  
				other = parent->right;  //x的新兄弟new w 是旋转之前w的某个孩子。其实就是左旋后效果  
			}  
			if ((!other->left || other->left->color == BLACK) &&  
				(!other->right || other->right->color == BLACK))    //情况2：x的兄弟w是黑色，且w的俩个孩子也  都是黑色的  
			{                         //由于w和w的俩个孩子都是黑色的，则在x和w上得去掉一黑色，  
				other->color = RED;   //于是，兄弟w变为红色。  
				node = parent;    //p[x]为新结点x  
				parent = node->parent;  //x<-p[x]  
			}  
			else                       //情况3：x的兄弟w是黑色的，  
			{                          //且，w的左孩子是红色，右孩子为黑色。  
				if (!other->right || other->right->color == BLACK)  
				{  
					if ((o_left = other->left))   //w和其左孩子left[w]，颜色交换。  
					{  
						o_left->color = BLACK;    //w的左孩子变为由黑->红色  
					}   
					other->color = RED;           //w由黑->红  
					root = Rotate_right(other, root);  //再对w进行右旋，从而红黑性质恢复。  
					other = parent->right;        //变化后的，父结点的右孩子，作为新的兄弟结点 w。  
				}  
				//情况4：x的兄弟w是黑色的  
				other->color = parent->color;  //把兄弟节点染成当前节点父节点的颜色。  
				parent->color = BLACK;  //把当前节点父节点染成黑色  
				if (other->right)      //且w的右孩子是红  
				{  
					other->right->color = BLACK;  //兄弟节点w右孩子染成黑色  
				}  
				root = Rotate_left(parent, root);  //并再做一次左旋  
				node = root;   //并把x置为根。  
				break;  
			}  
		}  
		//下述情况与上述情况，原理一致。分析略。  
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
		node->color = BLACK;  //最后将node[上述步骤置为了根结点]，改为黑色。  
	}    
	return root;  //返回root 
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