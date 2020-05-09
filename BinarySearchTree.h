#include <iostream>
#include <iomanip>  //setw
#include <utility>  //std::move

#pragma once

#include "dsexceptions.h"


using namespace std;

// BinarySearchTree class
//
// CONSTRUCTION: zero parameter
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x
// bool contains( x )     --> Return true if x is present
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable>
class BinarySearchTree {
private:
    struct Node;  // nested class defined in node.h
    

public:
    class Iterator;
    
    //Default constructor
    BinarySearchTree() : root{nullptr} {
    }

    /**
     * Copy constructor
     */
    BinarySearchTree(const BinarySearchTree &rhs) : root{nullptr} {
        root = clone(rhs.root);
    }

    /**
     * Destructor for the tree
     */
    ~BinarySearchTree() {
        makeEmpty();
    }

    /**
     * Copy assignment: copy and swap idiom
     */
    BinarySearchTree &operator=(BinarySearchTree _copy) {
        std::swap(root, _copy.root);
        return *this;
    }

    /**
     * Find the smallest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable &findMin() const {
        if (isEmpty()) {
            throw UnderflowException{};
        }
        return findMin(root)->element;
    }

    /**
     * Find the largest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable &findMax() const {
        if (isEmpty()) {
            throw UnderflowException{};
        }

        return findMax(root)->element;
    }

    /**
     * Returns true if x is found in the tree.
     */
    Iterator contains(const Comparable &x) const {
        Node *tmp = contains(x, root);
                if(tmp!=nullptr){
                    //Call iterator constructor with node input
                    return Iterator(tmp);
                }
        // Call default constructor
        return Iterator();

    }

    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty() const {
        return root == nullptr;
    }

    /**
     * Print the tree contents in sorted order.
     */
    void printTree(ostream &out = cout) const {
        if (isEmpty()) {
            out << "Empty tree";
        } else {
           // Call void function displaytree
            displayTree(root);
        }
    }

    /**
     * Make the tree logically empty.
     */
    void makeEmpty() {
        root = makeEmpty(root);
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert(const Comparable &x) {
        root = insert(x, root);
    }

    /**
     * Remove x from the tree. Nothing is done if x is not found.
     */
    void remove(const Comparable &x) {
        root = remove(x, root);
    }

    /** Return total number of existing nodes
     *
     * Used for debug purposes
     */
    
    static int get_count_nodes() {
        return Node::count_nodes;
    }
    
    // Public getter, calls private function
    int get_parent(int x){
       
        return getParentValue(x,root);
        
    }
    
    // Public funtion that calls private function to find successor and predessor for value x
    std::pair<Comparable, Comparable> find_pred_succ(const Comparable& x) const{
        Comparable a = find_under(x,root)->element;
        Comparable b = find_over(x,root)->element;
        return (std::pair<Comparable,Comparable>{a,b});
    }
    
    // Create Iterator instance for the smallest node
    Iterator begin()const{
        Node * tmp = root;
        while(tmp!=nullptr && tmp->left){
            tmp = tmp->left;
        }
        return Iterator(tmp);
    }
    
    //Create iterator for a nullptr
    Iterator end()const{
        return Iterator(nullptr);
    }
    
private:
    Node *root;
    //Private static Find Successor function
   static Node * find_successor(Node *t)
    {   //cannot find successor for nullptr
        if(t==nullptr){
            return nullptr;
            
        }else if (t->right){ // All values that are greater than t, is at right, find smallest
            return findMin(t->right);
        }else{
            // Go up in tree until the current node is a left node or reach nullptr(no greater value)
        while (t->parentNode != nullptr && t->parentNode->left != t){
            t = t->parentNode;
        }
        return t->parentNode;
        }
    }
    
    
    ///Find Predecessor
    static Node * find_predecessor(Node *t){
       
        if(t==nullptr){
            return nullptr;
        }else if(t->left){
            // Smaller value exist, find max of those that are smaller
            return findMax(t->left);
        }else{
            // If no smaller value exist, go up in tree until nullptr or current node is a right node
            while (t->parentNode != nullptr && t->parentNode->right != t){
            t = t->parentNode;
        }
            return t->parentNode;
        }
    }
    
    //Find predeccor of x
  Node* find_under(const Comparable& x,Node *t) const{
//      if(t!=nullptr){
//          if(x<=t->element&&t->left){ // Go down three until i find a element greater than x.
//              return find_under(x,t->left);
//          }else if(t->right&&t->right->element<x){//If element
//              return find_under(x,t->right);
//          }
//      }
        return t;
    
    }

    //Find successor of x
   Node* find_over(const Comparable& x,Node *t) const{
//       if(t!=nullptr){
//           if(t->element<=x&&t->right){ // Go down three until i find a element greater than x.
//               return find_under(x,t->right);
//           }else if(t->left&&x<t->left->element){//If element
//               return find_under(x,t->right);
//           }
//       }
       return t;
    }
    
    // Find parent for value x
    int getParentValue(int x, Node *t){
        
        if(t!=nullptr){
        //find node storing value x
        if(t->element<x&&t->right!=nullptr){
            return getParentValue(x, t->right);
        }else if(x<t->element&&t->left!=nullptr){
            return getParentValue(x, t->left);
        }else if(t->parentNode!=nullptr && t->element == x){ //return parent if not nullptr
                return t->parentNode->element;
        }
            
        }
            return 0;
        
    }
    
    
    //Private function that displays tree
    void displayTree(Node * t,int offSet = 0) const{
        if(t!=nullptr){
            std::cout<<std::setw(offSet)<<t->element<<"\n"; // display current node t
            if(t->left!=nullptr){
                displayTree(t->left,(offSet+3)); // Display rekurvsivly left subtree first, increase offset by 3 evary new node
            }
            if(t->right!=nullptr){
                displayTree(t->right,(offSet+3)); // Display rekurvsivly right subtree second, increase offset by 3 evary new node
            }
        }else{
            std::cout<<"Tree is empty \n";
        }
    }
    
    
    
    /**
     * Private member function to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Return a pointer to the node storing x.
     */
    Node *insert(const Comparable &x, Node *t ) {
        
        if (t == nullptr) {
            t = new Node{x, nullptr, nullptr};
        } else if (x < t->element) {
            t->left = insert(x, t->left);
             t->left->parentNode = t;
        } else if (t->element < x) {
            t->right = insert(x, t->right);
            t->right->parentNode = t;
        } else {
            ; // Duplicate; do nothing
        }

        return t;
    }

    /**
     * Private member function to remove from a subtree.
     * x is the item to remove.
     * t is the node that roots the subtree.
     * Return a pointer to the new root of the subtree that had root x
     */
    Node *remove(const Comparable &x, Node *t) {
        
        if (t == nullptr) {
            return t;  // Item not found
        }
        if (x < t->element) {
            t->left = remove(x, t->left);
        } else if (t->element < x) {
            t->right = remove(x, t->right);
        }

        else if (t->left != nullptr && t->right != nullptr)  // Two children
        {
            t->element = findMin(t->right)->element;
            t->right = remove(t->element, t->right);
            
        } else {
            Node *oldNode = t;
           
            t = (t->left != nullptr) ? t->left : t->right; // new node takes old nodes place
            
            if(t!=nullptr){
            t->parentNode = oldNode->parentNode; // Node t has it old parent node, update with oldnodes parent
            }
            
            delete oldNode;
        }

        return t;
    }

    /**
     * Private member function to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */
     static Node *findMin(Node *t){
        if (t == nullptr) {
            return nullptr;
        }
        if (t->left == nullptr) {
            return t;
        }

        // Tail recursion can be easily replaced by a loop
        return findMin(t->left);  // recursive call
    }

    /**
     * Private member function to find the largest item in a subtree t.
     * Return node containing the largest item.
     */
    static Node *findMax(Node *t){
        if (t != nullptr) {
            while (t->right != nullptr) {
                t = t->right;
            }
        }

        return t;
    }

    /**
     * Private member function to test if an item is in a subtree.
     * x is item to search for.
     * t is the node that roots the subtree.
     * Return a pointer to the node storing x, if x is found
     * Otherwise, return nullptr
     */
    Node *contains(const Comparable &x, Node *t) const {
        if (t == nullptr) {
            return t;
        } else if (x < t->element) {
            return contains(x, t->left);
        } else if (t->element < x) {
            return contains(x, t->right);
        } else {
            return t;  // Match
        }
    }
    /****** NONRECURSIVE VERSION*************************
    Node *contains(const Comparable &x, Node *t) const {
        while (t != nullptr) {
            if (x < t->element) {
                t = t->left;
            } else if (t->element < x) {
                t = t->right;
            } else {
                return t;  // Match
            }
        }

        return t;  // No match
    }
    *****************************************************/

    /**
     * Private member function to make subtree empty.
     */
    Node *makeEmpty(Node *t) {
        if (t != nullptr) {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }

        return nullptr;
    }

    /**
     * Private member function to print a subtree rooted at t in sorted order.
     * In-order traversal is used
     */
    void inorder(Node *t, ostream &out) const {
        if (t != nullptr) {
            inorder(t->left, out);
            out << t->element << '\n';
            inorder(t->right, out);
        }
    }

    /**
     * Private member function to clone subtree.
     */
    Node *clone(Node *t) const {
        if (t == nullptr) {
            return nullptr;
        } else {
            return new Node{t->element, clone(t->left), clone(t->right),t->parentNode};
        }
    }
};

//Include the definition of class Node
#include "node.h"
#include "iterator.h"
