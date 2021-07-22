template<class T>
class Trees {
	struct Node{
		Node* lchild, * rchild, *parent;
		T key, data;
		Node() {
			lchild = rchild = parent = nullptr;
			key = data = 0;
		}
		Node(T k, T d, Node* par, Node* l = nullptr, Node* r = nullptr) {
			key = k;
			data = d;
			lchild = l;
			rchild = r;
			parent = par;
		}
	};
	Node* root;
	int size = 0;

	// HELPER PRIVATE FUNCTIONS ;)
	
	void printInOrder(Node* curr) {
		if (curr == nullptr) {
			return;
		}
		printInOrder(curr->lchild);
		cout << curr->key << " " << curr->data << endl;
		printInOrder(curr->rchild);
	}

	// copy for printInOrder(), ig never used ...
	//void inOrderTraversal(Node* curr) {
	//	if (curr == nullptr) {
	//		return;
	//	}
	//	printInOrder(curr->lchild);
	//	cout << curr->key << " " << curr->data << endl;
	//	printInOrder(curr->rchild);
	//}

	void printPreOrder(Node* curr) {
		if (curr == nullptr) {
			return;
		}
		cout << curr->key << " " << curr->data << endl;
		printPreOrder(curr->lchild);
		printPreOrder(curr->rchild);
	}

	void printPostOrder(Node* curr) {
		if (curr == nullptr) {
			return;
		}
		printPostOrder(curr->lchild);
		printPostOrder(curr->rchild);
		cout << curr->key << " " << curr->data << endl;
	}

	int heightOfNode(Node* curr) {
		int count = 0;
		while (curr) {
			curr = curr->parent;
			count++;
		}
		return count;
	}

	void printNodesAtHeight(Node* curr, int k) {
		if (!curr) {
			return;
		}
		while (heightOfNode(curr) <= k) {
			if (heightOfNode(curr) == k) {
				cout << curr->key << " " << endl;
			}
			printNodesAtHeight(curr->lchild, k);
			printNodesAtHeight(curr->rchild, k);
		}
	}

	Node* getNode(T key) {
		Node* curr = root;
		while (curr != nullptr) {
			if (curr->key == key)
				return curr;
			if (curr->key > key) {
				curr = curr->lchild;
			}
			else {
				curr = curr->rchild;
			}
		}
	}

	bool isKeyPresent(T key) {
		Node* curr = root;
		while (curr != nullptr) {
			if (key == curr->key) {
				return true;
			}
			else if (key < curr->key) {
				curr = curr->lchild;
			}
			else if (key > curr->key) {
				curr = curr->rchild;
			}
		}
		return false;
	}	

	Node* findMin(Node* curr) {
		while (curr) {
			curr = curr->lchild;
		}
		return curr->parent;
	}

	bool areTreesIdentical(Node* curr, Node* curr2) {
		if (curr->key == curr2->key) {
			areTreesIdentical(curr->lchild, curr2->lchild);
			areTreesIdentical(curr->rchild, curr2->rchild);
			return true;
		}
		else
			return false;		
	}

	void mirrorTree(Node* curr) {
		if (curr == nullptr)
			return;
		
		Node* temp = curr->lchild;
		curr->lchild = curr->rchild;
		curr->rchild = temp;
		
		mirrorTree(curr->lchild);
		mirrorTree(curr->rchild);
	}

	bool isIsomorphic(Node* curr, Node* curr2) {
		if (!curr && !curr2) 
			return true;
		if (!curr || !curr2)
			return false;
		if (isIsomorphic(curr->lchild, curr2->lchild) && isIsomorphic(curr->rchild, curr2->rchild)
			|| isIsomorphic(curr->lchild, curr2->rchild) && isIsomorphic(curr->rchild, curr2->lchild)) {
			return true;
		}		
	}

public:
	Trees() {
		root = new Node;
	}

	void printInOrder() {					      //MICROSOFT INTERVIEW QUESTION
		printInOrder(root);
	}

	void printPreOrder() {					      //MICROSOFT INTERVIEW QUESTION
		printPreOrder(root);
	}

	void printPostOrder() {					      //MICROSOFT INTERVIEW QUESTION
		printPostOrder(root);
	}
	/*
	*					 18
	*				10		  20
	*			  8    11	19   21
	*			5	9	 18            23
	*		  4   6						25
	*	   2								29
	*	NULL									30
	*	if k == 0 
	* 
	*	
	*/
	
	bool areTreesIdentical(Trees& t) {					      //MICROSOFT INTERVIEW QUESTION
		return areTreesIdentical(root, t.root);
	}

	// Check wether Trees are Isomorphic? 
	
	/// <summary>
	/// an Isomorphic tree is the one, which can be found in other tree in any flipped way
	/// 
		/// if curr/root of both trees are nullptr -> isomorphic
		/// if any one curr node is nullptr and other's tree is not null, they are not null
		/// traverse through out the tree, in seedhy raasty sy as well as flipped rasty sy bhi
	/// 
	/// </summary>
	/// <param name="t"></param>
	/// <returns></returns>	
	bool isIsomorphic(Trees& t) {					      //MICROSOFT INTERVIEW QUESTION
		if (!root || !t.root) {
			return false;
		}
		return isIsomorphic(root, t.root);
	}

	// size of tree ?? 
	int size() {					      //MICROSOFT INTERVIEW QUESTION
		return size;
	}
	
	void printNodesAtHeight(int k) {		      //MICROSOFT INTERVIEW QUESTION		    
		Node* curr = root;
		printNodesAtHeight(curr, k);
	}

	void findMin() {				      //MICROSOFT INTERVIEW QUESTION
		cout << findMin(root)->key << endl;
	}

	void postOrderTraversalWithoutRecursion() {		//MICROSOFT INTERVIEW QUESTION
		Node* curr = root;
		stack<Node*> s1, s2;
		s1.push(curr);
		while (!s1.empty()) {
			curr = s1.top();
			s1.pop();
			s2.push(curr);
			if(curr->lchild)
				s1.push(curr->lchild);
			if(curr->rchild)
				s1.push(curr->rchild);
		}
		while (!s2.empty()) {
			cout << s2.top()->key << " ";			
			s2.pop();
		}
		cout << endl;
	}

	/// <Morris Algorithm>
	/// Morris Algorithm is used for inorder traversal without using recursion and stack
	///	Morris Algorithm states, go to the right most in the left tree 
	///	and connect the curr node with the right most of the left tree without braeking link of curr
	/// if you have already traversed through the left tree of node, simply print the key
	/// and move to the right and so on... till the curr node is not null
	/// </Morris ALgorithm>										
	void inOrderTraversalWithoutRecursion(){		//MICROSOFT INTERVIEW QUESTION
		Node* curr = root;

		while (curr) {
			if (curr->lchild) {
				Node* right_most_in_left_tree = curr->lchild;
				while (right_most_in_left_tree->rchild && right_most_in_left_tree != curr) {
					right_most_in_left_tree = right_most_in_left_tree->rchild;
				}
				// now we are at the most right node of the left subtree of any node :/
				if (!right_most_in_left_tree->rchild) {
					right_most_in_left_tree->rchild = curr;
					curr = curr->rchlid;				
				}
				else {
					cout << curr->key << " " << endl;
					right_most_in_left_tree->rchild = nullptr;
					curr = curr->rchild;
				}
			}
			else {
				cout << curr->key << " " << endl;
				curr = curr->rchild;
			}
		}
	}

	// if node has K parents then, it is at height K
	int heightOfTree(Node* curr) {						// MICROSOFT INTERVIEW QUESTION
		if (curr == nullptr) {
			return 0;
		}
		int left_Height = heightOfTree(curr->lchild);
		int right_Height = heightOfTree(curr->rchild);

		return max(left_Height, right_Height) + 1;
	}

	void mirrorTree() {					//MICROSOFT INTERVIEW QUESTION
		mirrorTree(root);
	}

	void printPreOrderWithoutRecursion() {			//MICROSOFT INTERVIEW QUESTION
		Node* curr = root;
		stack<Node*> s;
		while (curr != nullptr) {										
			cout << curr->key << endl;
			curr = curr->lchild;
			if (curr->rchild != nullptr) {
				s.push(curr);
			}			
		}
		while (!s.empty()) {
			curr = s.top();
			s.pop();
			cout << curr->rchild << endl;
		}
	}

	// insertion :
	void insert(T key, T data) {			        //MICROSOFT INTERVIEW QUESTION
		if (root == nullptr) {
			root = new Node(key, data, nullptr,nullptr, nullptr);
			size++;
			return;
		}
		if (isKeyPresent(key)) {
			return;
		}
		Node* curr = root;
		Node* par = curr->parent;
		while (curr != nullptr) {
			if (key < curr->key) {
				par = curr;
				curr = curr->lchild;				
			}
			else if (key > curr->key) {
				par = curr;
				curr = curr->rchild;
			}
		}
		curr = new Node(key, data, nullptr, nullptr, par);
		size++;
	}

	// deletion : 
	/*
	*  Case 1: leaf node : 
	*					  leaf node does not have (lchild and rchild), to remove it,
	*				just go to parent, and parent's child should be nullptr
	*				but, which child? if(parents->key > key) -> parent->lchlild be nullptr
	*				else parent -> rchild be nullptr
	* 
	*  Case 2 : Has One Child :
	*						we can attach it's child with the the parent
	*				if(toRemove is the lchild)
	*								attach the (parent->lchild = toRemove->Child)
	*				else
	*								attach the (parent->rchild = toRemove->Child)
	*  Case 3 : Has both Child :
	*						we can attach the rchild of curr node to the curr->parent
	*				we will find inorder successor and replace node with inorder successor
	*				and remove the inorder successor
	* 
	*/
	void remove(T key) {					      //MICROSOFT INTERVIEW QUESTION
		if (!isKeyPresent(key))
			return;
		Node* toRemove = getNode(key);
		Node* parentOfRemoval = toRemove->parent;
		// CASE I :
		if (!toRemove->lchild && !toRemove->rchild) {
			if (toRemove->key < parentOfRemoval->key) {
				parentOfRemoval->lchild = nullptr;
			}
			else {
				parentOfRemoval->rchild = nullptr;
			}
		}
		// CASE II : 
		if (!toRemove->lchild && toRemove->rchild) {
			if (toRemove->key < parentOfRemoval->key) {
				parentOfRemoval->lchild = toRemove->rchild;
			}
			else {
				parentOfRemoval->rchild = toRemove->rchild;
			}
		}
		if (toRemove->lchild && !toRemove->rchild) {
			if (toRemove->key < parentOfRemoval->key) {
				parentOfRemoval->lchild = toRemove->rchild;
			}
			else {
				parentOfRemoval->rchild = toRemove->rchild;
			}
		}
		// CASE III : Both Child Exists
		if (toRemove->lchild && toRemove->rchild) {
			Node* temp = toRemove->rchild;
			temp = findMin(temp);
			toRemove->key = temp->key;
			temp = nullptr;			
		}
	}

};
