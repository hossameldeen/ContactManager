#ifndef TREAP_H_
#define TREAP_H_


template<class T, class V>
class Treap {
public:
	class Node {
	public:
		Node *left, *right;
		T key;
		V value;
		int priority;

		Node(T k, V v);

		friend ostream& operator<<(ostream &o, const Node& root) {
			o << root.key << " - " << root.value;
			return o;
		}
	};
private:
	Node* root;

	Node* rotateRight(Node* Q);
	Node* rotateLeft(Node* P);
	Node* balance(Node* root);
	void insert(Node* &root, T k, V v); // updated to be void instead of Node*, also take & of root
	V find(Node* root, T k);

	void inorder(Node* root, ostream &o);
public:
	Treap();
	void insert(T k, V v);
	V find(T k);

	template<class TT, class VV>
	friend ostream& operator<<(ostream &o, Treap<TT, VV>& tree);
};
//============================================================================//
template<class T, class V>
Treap<T, V>::Node::Node(T k, V v) { // testing constructor
	key = k;
	value = v;
	left = right = NULL;
	priority = rand();
}
//============================================================================//
template<class T, class V>
typename Treap<T, V>::Node* Treap<T, V>::rotateRight(Node* Q) {
	Node* P = Q->left;
	Q->left = P->right;
	P->right = Q;
	return P;
}
//============================================================================//
template<class T, class V>
typename Treap<T, V>::Node* Treap<T, V>::rotateLeft(Node* P) {
	Node* Q = P->right;
	P->right = Q->left;
	Q->left = P;
	return Q;
}
//============================================================================//
template<class T, class V>
typename Treap<T, V>::Node* Treap<T, V>::balance(Node* root) { // assuming min heap for priorities
	if (root->left != NULL && // if root's priority is higher than left child's priority
		(root->priority > root->left->priority))
		return rotateRight(root);
	else if (root->right != NULL && // if root's priority is higher than right child's priority
			 (root->priority > root->right->priority))
		return rotateLeft(root);
	return root;
}
//============================================================================//
template<class T, class V>
void Treap<T, V>::insert(Node* &root, T k, V v) {
	if (root == NULL) { // if end reached create new node with key and value
		root = new Node(k, v);
		return;
	}
	else if (root->key == k)	// if this key already exists
		return;

	if (k < root->key)          	 // if value given less than root value
		insert(root->left, k, v);   	// go left
	else if (root->key < k)        		// if value given greater than root value
		insert(root->right, k, v);    	// go right
	root = balance(root);    // balance path on which you've moved
							 // if there's a change happened update the pointer of parent
}
//============================================================================//
template<class T, class V>
V Treap<T, V>::find(Node* root, T k) {
	Node* ptr = root;
	while (ptr != NULL) {
		if (ptr->key == k)
			return ptr->value;

		if (ptr->key < k)
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}
	return NULL;
}
//============================================================================//
template<class T, class V>
Treap<T, V>::Treap() {
	root = NULL;
}
//============================================================================//
template<class T, class V>
void Treap<T, V>::insert(T k, V v) {
	insert(root, k, v);
}
//============================================================================//
template<class T, class V>
V Treap<T, V>::find(T k) {
	return find(root, k);
}
//============================================================================//
template<class T, class V>
void Treap<T, V>::inorder(Node* root, ostream &o) {
	if (root == NULL)
		return;
	inorder(root->left, o);
	o << *(root) << endl;
	inorder(root->right, o);
}
//============================================================================//
template<class TT, class VV>
ostream& operator<<(ostream &o, Treap<TT, VV> &tree) {
	tree.inorder(tree.root, o);
	return o;
}

#endif /* TREAP_H_ */
