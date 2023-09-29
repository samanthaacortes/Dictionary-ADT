/*********************************************************************************
 * Samantha Cortes
 * Dictionary.cpp 
 * Implementation file for Dictionary ADT
 *********************************************************************************/

#include <iostream>
#include <string>
#include "Dictionary.h"

#define BLACK -1
#define RED -2

// Private Constructor ---------------------------------------------------------

// Node Constructor
Dictionary::Node::Node(keyType k, valType v) {
  key = k;
  val = v;
  parent = nullptr;
  left = nullptr;
  right = nullptr;
  color = BLACK;
}


// Helper Functions ---------------------------------------------------------

// inOrderString()
// Appends a string representation of the tree rooted at R to string s. The
// string appended consists of: "key : value \n" for each key-value pair in
// tree R, arranged in order by keys.
void Dictionary::inOrderString(std::string &s, Node* R) const {
  if( R != nil ) {
    inOrderString(s, R->left);
    s += R->key + " : " + std::to_string(R->val) + "\n";
    inOrderString(s, R->right);
  }
}

// preOrderString()
// Appends a string representation of the tree rooted at R to s. The appended
// string consists of keys only, separated by "\n", with the order determined
// by a pre-order tree walk.
void Dictionary::preOrderString(std::string &s, Node *R) const {
  if( R != nil) {
    s += R->key +"\n";
    preOrderString(s, R->left);
    preOrderString(s, R->right);
  }
}

// preOrderCopy()
// Recursively inserts a deep copy of the subtree rooted at R into this 
// Dictionary. Recursion terminates at N.
void Dictionary::preOrderCopy(Node *R, Node *N) {
  if(R != nil && R->key != N->key) {
    setValue(R->key, R->val);
    preOrderCopy(R->left, N);
    preOrderCopy(R->right, N);
  }
}

// postOrderDelete()
// Deletes all Nodes in the subtree rooted at R, sets R to nil.
void Dictionary::postOrderDelete(Node *R) { 
  if(num_pairs > 0 && R != nil) {
    postOrderDelete(R->left);
    postOrderDelete(R->right);
    R->left = nil;
    R->right = nil;
    delete R;
    num_pairs--;
  }
}

// search()
// Searches the subtree rooted at R for a Node with key==k. Returns
// the address of the Node if it exists, returns nil otherwise.
Dictionary::Node* Dictionary::search(Node* R, keyType k) const {
  if(R == nil || R->key == k) {
    return R;
  } else if(k < R->key) {
    return search(R->left, k);
  } else {
    return search(R->right, k);
  }
}

// findMin()
// If the subtree rooted at R is not empty, returns a pointer to the 
// leftmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMin(Node *R) {
  if(num_pairs <= 0) {
    return nil;
  }
  Node* temp = R;
  while(temp->left != nil) {
    temp = temp->left;
  }
  return temp;
}

// findMax()
// If the subtree rooted at R is not empty, returns a pointer to the 
// rightmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMax(Node *R) {
  if(num_pairs <= 0) {
    return nil;
  }
  Node* temp = R;
  while(temp->right != nil) {
    temp = temp->right;
  }
  return temp;
}

// findNext()
// If N does not point to the rightmost Node, returns a pointer to the
// Node after N in an in-order tree walk.  If N points to the rightmost 
// Node, or is nil, returns nil. 
Dictionary::Node* Dictionary::findNext(Node *N) {
  if(N->right != nil) { 
    return findMin(N->right);
  }
  Node *temp = N->parent;
  while(temp != nil && N == temp->right) {
    N = temp;
    temp = temp->parent;
  }
  return temp;
}

// findPrev()
// If N does not point to the leftmost Node, returns a pointer to the
// Node before N in an in-order tree walk.  If N points to the leftmost 
// Node, or is nil, returns nil.
Dictionary::Node* Dictionary::findPrev(Node *N) {
  if(N->left != nil) {
    return findMax(N->left);
  }
  Node *temp = N->parent;
  while(temp != nil && N == temp->left) {
    N = temp;
    temp = temp->parent;
  }
  return temp;
}

// RBT Helper Functions ---------------------------------------------
   
// LeftRotate()
void Dictionary::LeftRotate(Node* N) {
  Node *temp = N->right;

  N->right = temp->left;
  if(temp->left != nil) {
    temp->left->parent = N;
  }

  temp->parent = N->parent;
  if(N->parent == nil) {
    root = temp;
  }
  else if(N == N->parent->left) {
    N->parent->left = temp;
  }
  else {
    N->parent->right = temp;
  }

  temp->left = N;
  N->parent = temp;
}

// RightRotate()
void Dictionary::RightRotate(Node* N) {
  Node *temp = N->left;

  N->left = temp->right;
  if(temp->right != nil) {
    temp->right->parent = N;
  }

  temp->parent = N->parent;
  if(N->parent == nil) {
    root = temp;
  }
  else if(N == N->parent->right) {
    N->parent->right = temp;
  }
  else {
    N->parent->left = temp;
  }

  temp->right = N;
  N->parent = temp;
}

// RB_InsertFixUP()
void Dictionary::RB_InsertFixUp(Node* N) {
  Node *temp1 = N;
  while(temp1->parent->color == RED) {
    if(temp1->parent == temp1->parent->parent->left) {
      Node *temp2 = temp1->parent->parent->right;
      if(temp2->color == RED) {
        temp1->parent->color = BLACK; 
        temp2->color = BLACK; 
        temp1->parent->parent->color = RED; 
        temp1 = temp1->parent->parent; 
      } else {
	if (temp1 == temp1->parent->right) { 
	  temp1 = temp1->parent; 
	  LeftRotate(temp1); 
	}
	temp1->parent->color = BLACK; 
	temp1->parent->parent->color = RED; 
	RightRotate(temp1->parent->parent);
      }
    } else {
      Node *temp2 = temp1->parent->parent->left;
      if(temp2->color == RED) {
	temp1->parent->color = BLACK; 
	temp2->color = BLACK;
	temp1->parent->parent->color = RED; 
	temp1 = temp1->parent->parent; 
      } else {
	if(temp1 == temp1->parent->left) {
	  temp1 = temp1->parent; 
	  RightRotate(temp1); 
	}
	temp1->parent->color = BLACK; 
	temp1->parent->parent->color = RED; 
	LeftRotate(temp1->parent->parent); 
      }
    }
  }
  root->color = BLACK;
}

// RB_Transplant()
void Dictionary::RB_Transplant(Node* u, Node* v) {
  if(u->parent == nil) {
    root = v;
  } else if(u == u->parent->left) {
    u->parent->left = v;
  } else {
    u->parent->right = v;
  }
  v->parent = u->parent;
}

// RB_DeleteFixUp()
void Dictionary::RB_DeleteFixUp(Node* N) {
  Node *temp1 = N;
  while(temp1 != root && temp1->color == BLACK) {
    if(temp1 == temp1->parent->left) {
      Node *temp2 = temp1->parent->right;
      if(temp2->color == RED){
        temp2->color = BLACK;
        temp1->parent->color = RED;
        LeftRotate(temp1->parent);
        temp2 = temp1->parent->right;
      }
      if(temp2->left->color == BLACK && temp2->right->color == BLACK) {
        temp2->color = RED;
        temp1 = temp1->parent;
      } else {
        if(temp2->right->color == BLACK) {
          temp2->left->color = BLACK;
          temp2->color = RED;
          RightRotate(temp2);
          temp2 = temp1->parent->right;
        }
        temp2->color = temp1->parent->color;
        temp1->parent->color = BLACK;
        temp2->right->color = BLACK;
        LeftRotate(temp1->parent);
        temp1 = root;
      }
    } else {
      Node *temp2 = temp1->parent->left;
      if(temp2->color == RED){
	temp2->color = BLACK;
	temp1->parent->color = RED;
	RightRotate(temp1->parent);
	temp2 = temp1->parent->left;
      }
      if(temp2->right->color == BLACK && temp2->left->color == BLACK) {
	temp2->color = RED;
	temp1 = temp1->parent;
      } else {
	if(temp2->left->color == BLACK){
	  temp2->right->color = BLACK;
	  temp2->color = RED;
	  LeftRotate(temp2);
	  temp2 = temp1->parent->left;
        }
	temp2->color = temp1->parent->color;
	temp1->parent->color = BLACK;
	temp2->left->color = BLACK;
	RightRotate(temp1->parent);
	temp1 = root;
      }
    }
  }
  temp1->color = BLACK;
}

// RB_Delete()
void Dictionary::RB_Delete(Node* N) {
  Node *temp1 = N;
  int originalTemp1Color = temp1->color;
  Node *temp2;
  if(N->left == nil) {
    temp2 = N->right;
    RB_Transplant(N, N->right);
  }
  else if(N->right == nil) {
    temp2 = N->left;
    RB_Transplant(N, N->left);
  }
  else {
    temp1 = findMin(N->right);
    originalTemp1Color = temp1->color;
    temp2 = temp1->right;
    if(temp1->parent == N) {
      temp2->parent = temp1;
    }
    else {
      RB_Transplant(temp1, temp1->right);
      temp1->right = N->right;
      temp1->right->parent = temp1;
    }
    RB_Transplant(N, temp1);
    temp1->left = N->left;
    temp1->left->parent = temp1;
    temp1->color = N->color;
  }
  if(originalTemp1Color == 1) {
    RB_DeleteFixUp(temp2);
  }
}

// Class Constructors & Destructors ----------------------------------------

// Creates new Dictionary in the empty state. 
Dictionary::Dictionary() {
  nil = new Node("\0", 0);
  nil->left = nullptr;
  nil->right = nullptr;
  nil->parent = nullptr;
  nil->color = BLACK;
  current = nil;
  root = nil;
  num_pairs = 0;
}


// Copy constructor.
Dictionary::Dictionary(const Dictionary &D) {
  nil = new Node("\0", 0);
  nil->left = nullptr;
  nil->right = nullptr;
  nil->parent = nullptr;
  nil->color = BLACK;
  current = nil;
  root = nil;
  num_pairs = 0;
  preOrderCopy(D.root, nil);
}

// Destructor
Dictionary::~Dictionary() {
  postOrderDelete(root);
  nil->left = nullptr;
  nil->right = nullptr;
  nil->parent = nullptr;
  root = nil;
  current = nil;
  delete nil;
}

// Access functions --------------------------------------------------------

// size()
// Returns the size of this Dictionary.
int Dictionary::size() const {
  return num_pairs;
}

// contains()
// Returns true if there exists a pair such that key==k, and returns false
// otherwise.
bool Dictionary::contains(keyType k) const {
  Node *temp = search(root, k);
  return (temp != nil);
}

// getValue()
// Returns a reference to the value corresponding to key k.
// Pre: contains(k)
valType& Dictionary::getValue(keyType k) const {
  Node *temp = this->search(root, k);
  if (temp == nil) {
    throw std::logic_error("Dictionary: getValue(): key \""+ k +"\" not defined");
  }
  return temp->val;
}

// hasCurrent()
// Returns true if the current iterator is defined, and returns false 
// otherwise.
bool Dictionary::hasCurrent() const {
  if(current != nil) {
    return true;
  }
  return false;
}


// currentKey()
// Returns the current key.
// Pre: hasCurrent() 
keyType Dictionary::currentKey() const {
  if(hasCurrent()) {
    return current->key;
  } else {
    throw std::logic_error("Dictionary: currentKey(): current not defined");
  }
}

// currentVal()
// Returns a reference to the current value.
// Pre: hasCurrent()
valType& Dictionary::currentVal() const {
  if(hasCurrent()) {
    return current->val;
  } else {
    throw std::logic_error("Dictionary: currentVal(): current not defined");
  }
}

// Manipulation procedures -------------------------------------------------

// clear()
// Resets this Dictionary to the empty state, containing no pairs.
void Dictionary::clear() {
  if(this->num_pairs > 0) {
    postOrderDelete(root);
    root = nil;
    current = nil;
    num_pairs = 0;
  }
}

// setValue()
// If a pair with key==k exists, overwrites the corresponding value with v, 
// otherwise inserts the new pair (k, v).
void Dictionary::setValue(keyType k, valType v) {
  Node *X = nil;
  Node *Y = root;
  Node *Z = new Node(k,v);

  while(Y != nil) {
    X = Y;
    if(Z->key < Y->key) {
      Y = Y->left;
    } else if(Y->key == Z->key) {
      Y->val = v;
      delete Z;
      return; 
    } else {
      Y = Y->right;
    }
  }
  Z->parent = X;
  Z->left = nil;
  Z->right = nil;
  if(X == nil) {
    root = Z; 
  } else if(Z->key < X->key) {
    X->left = Z;
  } else {
    X->right = Z;
  }

  Z->left = nil;
  Z->right = nil;
  Z->color = RED;
  RB_InsertFixUp(Z);
  num_pairs++;
}

// transplant()
// Helper function to swap two nodes.
void Dictionary::transplant(Node* U, Node* V) {
  if(U->parent == nil) {
    root = V;
  } else if (U == U->parent->left) {
    U->parent->left = V;
  } else {
    U->parent->right = V;
  }
  if(V != nil) {
    V->parent = U->parent;
  }
}

// remove()
// Deletes the pair for which key==k. If that pair is current, then current
// becomes undefined.
// Pre: contains(k).
void Dictionary::remove(keyType k) {
  if(!contains(k)) {
    throw std::logic_error("Dictionary: remove(): key \""+ k +"\" does not exist");
  }
  Node *temp = search(root, k);
  if(temp == current){
    current = nil;
  }
  RB_Delete(temp);
  temp->parent = nullptr;
  temp->left = nullptr;
  temp->right = nullptr;
  delete temp;
  num_pairs--;
}

// begin()
// If non-empty, places current iterator at the first (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::begin() {
  current = findMin(root);
}

// end()
// If non-empty, places current iterator at the last (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::end() {
  current = findMax(root);
}

// next()
// If the current iterator is not at the last pair, advances current 
// to the next pair (as defined by the order operator < on keys). If 
// the current iterator is at the last pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::next() {
  if(!hasCurrent()) {
    throw std::logic_error("Dictionary: next(): current not defined");
  }
  current = findNext(current);
}

// prev()
// If the current iterator is not at the first pair, moves current to  
// the previous pair (as defined by the order operator < on keys). If 
// the current iterator is at the first pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::prev() {
  if(!hasCurrent()) {
    throw std::logic_error("Dictionary: prev(): current not defined");
  }
  current = findPrev(current);
}

// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this Dictionary. Consecutive (key, value)
// pairs are separated by a newline "\n" character, and the items key and value 
// are separated by the sequence space-colon-space " : ". The pairs are arranged 
// in order, as defined by the order operator <.
std::string Dictionary::to_string() const {
  std::string temp = "";
  inOrderString(temp, root);
  return temp;
}

// pre_string()
// Returns a string consisting of all keys in this Dictionary. Consecutive
// keys are separated by newline "\n" characters. The key order is given
// by a pre-order tree walk.
std::string Dictionary::pre_string() const {
  std::string temp = "";
  preOrderString(temp,root);
  return temp;
}

// equals()
// Returns true if and only if this Dictionary contains the same (key, value)
// pairs as Dictionary D.
bool Dictionary::equals(const Dictionary &D) const {
  std::string temp1;
  std::string temp2;
  
  if (this->num_pairs != D.num_pairs) {
    return false;
  }
  temp1 = this->to_string();
  temp2 = D.to_string();

  if (temp1 == temp2) {
    return true;
  }
  else {
    return false;
  }
}

// Overloaded Operators ----------------------------------------------------

// operator<<()
// Inserts string representation of Dictionary D into stream, as defined by
// member function to_string().
std::ostream& operator<<( std::ostream& stream, Dictionary& D) {
  return stream<< D.Dictionary::to_string();
}

// operator==()
// Returns true if and only if Dictionary A equals Dictionary B, as defined
// by member function equals(). 
bool operator==( const Dictionary& A, const Dictionary& B ) {
  return A.Dictionary::equals(B);
}

// operator=()
// Overwrites the state of this Dictionary with state of D, and returns a
// reference to this Dictionary.
Dictionary& Dictionary::operator=(const Dictionary& D) {
  if(this != &D){
    Dictionary temp = D;
    std::swap(num_pairs, temp.num_pairs);
    std::swap(nil, temp.nil);
    std::swap(root, temp.root);
    std::swap(current, temp.current);
  }
  return *this;
}
