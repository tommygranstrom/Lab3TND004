#include <iostream>
#include <vector>
#include <iterator>
#include <fstream>
#include <cassert>    //assert
#include <algorithm>  //std::sort
#include <string>

#include "BinarySearchTree.h"
#include "iterator.h"
#include "dsexceptions.h"

bool isforbidden(char s){

    const char tmp[] = "'";
    if(s!=tmp[0]&& ispunct(s)){
        return true;
    }else{
        return false;
    }
}

template<typename Comparable>
class Rows{
public:
    
    
    Rows(string w):word{w},counter{1}{};
    Rows(const Rows &r):word{r.word},counter{r.counter}{};
    
    bool operator<(const Rows& r)const{
        if(word<r.word){
            return true;
        }
        return false;
    }
    bool operator>(const Rows& r)const{
        if(word>r.word){
            return true;
        }
        return false;
    }
    
    //    int counter(){
    //        return counter;
    //    }
private:
    string word;
    int counter;
};


int main() {
    
        //Load file
        std::ifstream file{"/Users/tommygranstrom/Documents/TND004 - DataStrukturer/Code3/other files/text.txt"};

        //If not found
        if (!file) {
            std::cout << "Couldn't open file text.txt\n";
            return 1;
        }

        //Declare vector with words from file
        std::vector<std::string> V{std::istream_iterator<string>{file},
                                   std::istream_iterator<string>{}};
        file.close();

        // Create a instance of BinarySearchTree
        BinarySearchTree<Rows<string>> T;
        Rows<string> rows("hej");
        
        
        auto it2 = T.contains(rows);
        //assert(BinarySearchTree<Rows>::get_count_nodes() == 0);


        // Loop and insert all words from vector V
        for (std::vector<string>::iterator it = V.begin();it!=V.end();++it){
            string word = *it;

//            //Make all characters lower case
//            std::for_each(std::begin(word),std::end(word),[](char & c){c = char(tolower(c));});
//
//            //Erase character if forbidden(Not a letter or apostrophe)
//            word.erase(std::remove_if(word.begin(),word.end(),[](char c){return isforbidden(c);}),word.end());

           
           
//            if(tt==t.end()){
//                t.insert(tmp);
//            }else{
//                //tt->counter++;
//            }
            T.insert(rows);
        }
        //Iterate and print Frequency table
//        for (BinarySearchTree<Rows>::Iterator it = t.begin(); it != t.end(); ++it) {
//            //std::cout<<std::setw(25)<<std::left<<it->word<<it->counter<<"\n";
//            //std::cout<<std::setw(25)<<std::left<<it->word<<it->counter<<"\n";
//        }
        std::cout<<"Sucess!!\n";
    
    return 0;
}
