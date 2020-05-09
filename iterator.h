#include "BinarySearchTree.h"

#pragma once

/* **********************************************************
 * Class to represent a bi-directional iterator for BSTs     *
 * Bi-directional iterators can be moved in both directions, *
 * increasing and decreasing order of items keys             *
 * ***********************************************************/

template <typename Comparable>

class BinarySearchTree<Comparable>::Iterator {
friend class BinarySearchTree;
    
public:
    //Default constructor
    Iterator();
    
    bool operator==(const Iterator& it)const{
        if(current == it.current){
            return true;
        }
        return false;
    }

    bool operator!=(const Iterator& it)const{
        if(current != it.current){
            return true;
        }
        return false;
    }

    Comparable& operator*() const{
        return current->element;
    }
        
   Comparable* operator->() const{
        return &(current->element);
   }
    
    Iterator& operator++(){
        current = find_successor(current); 
        return *this;
    }

    Iterator& operator--(){
      current = find_predecessor(current);
       return *this;
   }

private:
    Iterator(Node *t):current{t}{}
    Node * current;
    
};
