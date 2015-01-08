#ifndef CBTREE_H
#define CBTREE_H
#define  BLACK 1;
#define  RED 2;
#define  UNDEF 0;
template<typename T>
class CBTNode
{
public:
	T data;
	CBTNode<T> *parent;
	CBTNode<T> *left;
	CBTNode<T> *right;
	int color;
	CBTNode(
		T data = T(),
		CBTNode<T> *parent = NULL,
		CBTNode<T> *left = NULL,
		CBTNode<T> *right = NULL,
		int color=UNDEF
		) : data(data), parent(parent), left(left), right(right) color(color) {}
};

template<typename T>
class CBTree
{
protected:
	CBTNode<T> *m_pNodeRoot;

public:
	CBTree(CBTNode<T> *initroot = NULL);
	~CBTree();
	void AssignTo(CBTNode<T> *p);
	void Copy(CBTree<T> &p);

private:
	CBTNode<T>* Copy(CBTNode<T> *p);

	void DestroyNode(CBTNode<T> *p);

	void PreOrderTraverse(
		const CBTNode<T> *p,
		void (*Visit)(const T &data)
		) const;

	void InOrderTraverse(
		const CBTNode<T> *p,
		void (*Visit)(const T &data)
		) const;

	void PostOrderTraverse(
		const CBTNode<T> *p,
		void (*Visit)(const T &data)
		) const;

	void GetNodesCount(const CBTNode<T> *p, unsigned int *unCount) const;

	void GetLeafCount(const CBTNode<T> *p, unsigned int *unCount) const;

public:
	T&              GetNodeData(CBTNode<T> *p);
	T               GetNodeData(const CBTNode<T> *p) const;
	void            SetNodeData(CBTNode<T> *p, const T &data);
	CBTNode<T>*&    GetRoot();
	CBTNode<T>*     GetRoot() const;
	CBTNode<T>*&    GetParent(CBTNode<T> *p);
	CBTNode<T>*     GetParent(const CBTNode<T> *p) const;
	CBTNode<T>*&    GetLeftChild(CBTNode<T> *p);
	CBTNode<T>*     GetLeftChild(const CBTNode<T> *p) const;
	CBTNode<T>*&    GetRightChild(CBTNode<T> *p);
	CBTNode<T>*     GetRightChild(const CBTNode<T> *p) const;
	CBTNode<T>*&    GetLeftSibling(CBTNode<T> *p);
	CBTNode<T>*     GetLeftSiblig(const CBTNode<T> *p) const;
	CBTNode<T>*&    GetRightSibling(CBTNode<T> *p);
	CBTNode<T>*     GetRightSibling(const CBTNode<T> *p) const;

public:
	int             IsEmpty() const;
	void            Destroy();
	void            PreOrderTraverse(void (*Visit)(const T &data)) const;
	void            InOrderTraverse(void (*Visit)(const T &data)) const;
	void            PostOrderTraverse(void (*Visit)(const T &data)) const;
	unsigned int    GetNodesCount() const; // Get how many nodes
	unsigned int    GetLeafCount() const;
	unsigned int    GetDepth() const;
	unsigned int    GetDepth(const CBTNode<T> *p) const;
};

template<typename T>
inline CBTree<T>::CBTree(CBTNode<T> *initroot) : m_pNodeRoot(initroot)
{
}

template<typename T>
inline CBTree<T>::~CBTree()
{
	Destroy();
}

template<typename T>
inline void CBTree<T>::AssignTo(CBTNode<T> *p)
{
	ASSERT(p);
	m_pNodeRoot = p;
}

template<typename T>
inline void CBTree<T>::Copy(CBTree<T> &p)
{
	if (NULL != p.m_pNodeRoot)
		m_pNodeRoot = Copy(p.m_pNodeRoot);
	else
		m_pNodeRoot = NULL;
}

template<typename T>
inline CBTNode<T>* CBTree<T>::Copy(CBTNode<T> *p)
{
	if (p)
	{
		CBTNode<T> *pNewNode = new CBTNode<T>;
		if (NULL == pNewNode)
			return NULL;
		pNewNode->data = p->data;
		pNewNode->parent = p->parent;
		pNewNode->left = Copy(p->left);
		pNewNode->right = Copy(p->right);
		return pNewNode;
	}
	else
		return NULL;
}

template<typename T>
inline CBTNode<T>*& CBTree<T>::GetLeftChild(CBTNode<T> *p)
{
	ASSERT(p);
	return *(&(p->left));
}

template<typename T>
inline CBTNode<T>* CBTree<T>::GetLeftChild(const CBTNode<T> *p) const
{
	ASSERT(p);
	return p->left;
}

template<typename T>
inline CBTNode<T>*& CBTree<T>::GetRightChild(CBTNode<T> *p)
{
	ASSERT(p);
	return *(&(p->right));
}

template<typename T>
inline CBTNode<T>* CBTree<T>::GetRightChild(const CBTNode<T> *p) const
{
	ASSERT(p);
	return p->right;
}

template<typename T>
inline CBTNode<T>*& CBTree<T>::GetLeftSibling(CBTNode<T> *p)
{
	ASSERT(p);

	if (p->parent)
		return *(&(p->parent->left));
	else
		return *(&(p->parent)); // return NULL;
}

template<typename T>
inline CBTNode<T>* CBTree<T>::GetLeftSiblig(const CBTNode<T> *p) const
{
	ASSERT(p);

	if (p->parent)
		return p->parent->left;
	else
		return p->parent;       // return NULL;
}

template<typename T>
inline CBTNode<T>*& CBTree<T>::GetRightSibling(CBTNode<T> *p)
{
	ASSERT(p);

	if (p->parent)
		return *(&(p->parent->right));
	else
		return *(&(p->parent)); // return NULL;
}

template<typename T>
inline CBTNode<T>* CBTree<T>::GetRightSibling(const CBTNode<T> *p) const
{
	ASSERT(p);

	if (p->parent)
		return p->parent->right;
	else
		return p->parent;       // return NULL;
}

template<typename T>
inline CBTNode<T>*& CBTree<T>::GetParent(CBTNode<T> *p)
{
	ASSERT(p);
	return *(&(p->parent));
}

template<typename T>
inline CBTNode<T>* CBTree<T>::GetParent(const CBTNode<T> *p) const
{
	ASSERT(p);
	return p->parent;
}

template<typename T>
inline T& CBTree<T>::GetNodeData(CBTNode<T> *p)
{
	ASSERT(p);
	return p->data;
}

template<typename T>
inline T CBTree<T>::GetNodeData(const CBTNode<T> *p) const
{
	ASSERT(p);
	return p->data;
}

template<typename T>
inline void CBTree<T>::SetNodeData(CBTNode<T> *p, const T &data)
{
	ASSERT(p);
	p->data = data;
}

template<typename T>
inline int CBTree<T>::IsEmpty() const
{
	return NULL == m_pNodeRoot;
}

template<typename T>
inline CBTNode<T>*& CBTree<T>::GetRoot()
{
	return *(&(m_pNodeRoot));
}

template<typename T>
inline CBTNode<T>* CBTree<T>::GetRoot() const
{
	return m_pNodeRoot;
}

template<typename T>
inline void CBTree<T>::DestroyNode(CBTNode<T> *p)
{
	if (p)
	{
		DestroyNode(p->left);
		DestroyNode(p->right);
		delete p;
	}
}

template<typename T>
inline void CBTree<T>::Destroy()
{
	DestroyNode(m_pNodeRoot);
	m_pNodeRoot = NULL;
}

template<typename T>
inline void CBTree<T>::PreOrderTraverse(void (*Visit)(const T &data)) const
{
	PreOrderTraverse(m_pNodeRoot, Visit);
}

template<typename T>
inline void CBTree<T>::PreOrderTraverse(
	const CBTNode<T> *p,
	void (*Visit)(const T &data)
	) const
{
	if (p)
	{
		Visit(p->data);
		PreOrderTraverse(p->left, Visit);
		PreOrderTraverse(p->right, Visit);
	}
}

template<typename T>
inline void CBTree<T>::InOrderTraverse(void (*Visit)(const T &data)) const
{
	InOrderTraverse(m_pNodeRoot, Visit);
}

template<typename T>
inline void CBTree<T>::InOrderTraverse(
	const CBTNode<T> *p,
	void (*Visit)(const T &data)
	) const
{
	if (p)
	{
		InOrderTraverse(p->left, Visit);
		Visit(p->data);
		InOrderTraverse(p->right, Visit);
	}
}

template<typename T>
inline void CBTree<T>::PostOrderTraverse(void (*Visit)(const T &data)) const
{
	PostOrderTraverse(m_pNodeRoot, Visit);
}

template<typename T>
inline void CBTree<T>::PostOrderTraverse(
	const CBTNode<T> *p,
	void (*Visit)(const T &data)
	) const
{
	if (p)
	{
		PostOrderTraverse(p->left, Visit);
		PostOrderTraverse(p->right, Visit);
		Visit(p->data);
	}
}

template<typename T>
inline unsigned int CBTree<T>::GetNodesCount() const
{
	unsigned int unCount;
	GetNodesCount(m_pNodeRoot, &unCount);
	return unCount;
}

template<typename T>
inline void CBTree<T>::GetNodesCount(
	const CBTNode<T> *p,
	unsigned int *unCount
	) const
{
	ASSERT(unCount);

	unsigned int unLeftCount;
	unsigned int unRightCount;

	if (NULL == p)
		*unCount = 0;
	else if ((NULL == p->left) && (NULL == p->right))
		*unCount = 1;
	else
	{
		GetNodesCount(p->left, &unLeftCount);
		GetNodesCount(p->right, &unRightCount);
		*unCount = 1 + unLeftCount + unRightCount;
	}
}

template<typename T>
inline unsigned int CBTree<T>::GetLeafCount() const
{
	unsigned int unCount = 0;
	GetLeafCount(m_pNodeRoot, &unCount);
	return unCount;
}

template<typename T>
inline void CBTree<T>::GetLeafCount(
	const CBTNode<T> *p,
	unsigned int *unCount
	) const
{
	ASSERT(unCount);

	if (p)
	{
		// if the node's left & right children are both NULL, it must be a leaf
		if ((NULL == p->left) && (NULL == p->right))
			++(*unCount);
		GetLeafCount(p->left, unCount);
		GetLeafCount(p->right, unCount);
	}
}

template<typename T>
inline unsigned int CBTree<T>::GetDepth() const
{
	// Minus 1 here because I think the root node's depth should be 0.
	// So, don't do it if u think the root node's depth should be 1.
	return GetDepth(m_pNodeRoot) - 1;
}

template<typename T>
inline unsigned int CBTree<T>::GetDepth(const CBTNode<T> *p) const
{
	unsigned int unDepthLeft;
	unsigned int unDepthRight;

	if (p)
	{
		unDepthLeft = GetDepth(p->left);
		unDepthRight = GetDepth(p->right);
		return 1 +  // if don't plus 1 here, the tree's depth will be always 0
			(unDepthLeft > unDepthRight ? unDepthLeft : unDepthRight);
	}
	else
		return 0;
}
#endif // !CBTREE_H