#include <cassert>
#include <iostream>
#include <string>
#include "BTree.hpp"
  //  test: constructor
sjtu::BTree<int, int> bTree;
void insert(int key, int value){
  bTree.insert(key, value);
}


void erase(int key){
  bTree.erase(key);
}

int query(int key){
  bTree.at(key);
}


void tester(){
  //  test: empty(), size()
  assert(bTree.empty() && bTree.size() == 0);
  int key, value;
  char cmd;
  while(cin >> cmd){
    if(cmd == 'i'){
      cin >> key >> value;
      insert(key, value);
    }else
    if(cmd == 'e'){
      cin >> key;
      erase(key);
    }else
    if(cmd == 'q'){
      cin >> key;
      cout << query(key) << endl;
    }else{
      puts("bad_command");
    }
  }
}

int main(){
  tester();
  return 0;
}
