#include <cassert>
#include <iostream>
#include <string>
#include "BTree.hpp"

class Integer {
 public:
  static int counter;
  int val;
  Integer(int val) : val(val) { counter++; }
  Integer(const Integer &rhs) {
    val = rhs.val;
    counter++;
  }
  Integer &operator=(const Integer &rhs) { assert(false); }
  ~Integer() { counter--; }
};

int Integer::counter = 0;

class Compare {
 public:
  bool operator()(const Integer &lhs, const Integer &rhs) const {
    return lhs.val < rhs.val;
  }
};

void tester(void) {
  //	test: constructor
  sjtu::BTree<Integer, std::string, Compare> bTree;
  //	test: empty(), size()
  assert(bTree.empty() && bTree.size() == 0);
  //	test: operator[], insert()
  for (int i = 0; i < 100000; ++i) {
    std::string string = "";
    for (int number = i; number; number /= 10) {
      char digit = '0' + number % 10;
      string = digit + string;
    }
    if (i & 1) {
      bTree[Integer(i)] = string;
      auto result =
          bTree.insert(Integer(i), string);
      assert(!result.second);   
    } else {
      auto result =
          bTree.insert(Integer(i), string);
      assert(result.second);
    }
  }
  //	test: count(), find(), erase()
  for (int i = 0; i < 100000; ++i) {
    if (i > 1896 && i <= 2016) {
      continue;
    }
    assert(bTree.count(Integer(i)) == 1);
    assert(bTree.find(Integer(i)) != bTree.end());
  }
  //	test: constructor, operator=, clear();
  for (int i = 0; i < (int)bTree.size(); ++i) {
    sjtu::BTree<Integer, std::string, Compare> copy(bTree);
    bTree.clear();
    std::cout << bTree.size() << " " << copy.size() << " ";
    bTree = copy;
    copy.clear();
    std::cout << bTree.size() << " " << copy.size() << " ";
    copy = bTree;
    bTree.clear();
    std::cout << bTree.size() << " " << copy.size() << " ";
    bTree = copy;
    copy.clear();
    std::cout << bTree.size() << " " << copy.size() << " ";
  }
  std::cout << std::endl;
  //	test: const_iterator, cbegin(), cend(), operator++, at()
  sjtu::BTree<Integer, std::string, Compare>::const_iterator const_iterator;
  const_iterator = bTree.cbegin();
  while (const_iterator != bTree.cend()) {
    const Integer integer(const_iterator->first);
    const_iterator++;
    std::cout << bTree.at(integer) << " ";
  }
  std::cout << std::endl;
  //	test: iterator, operator--, operator->
  sjtu::BTree<Integer, std::string, Compare>::iterator iterator;
  iterator = bTree.end();
  while (true) {
    sjtu::BTree<Integer, std::string, Compare>::iterator peek = iterator;
    if (peek == bTree.begin()) {
      std::cout << std::endl;
      break;
    }
    std::cout << (--iterator)->second << " ";
  }
  //	test: operator[]
  for (int i = 0; i < 100000; ++i) {
    std::cout << bTree[Integer(i)];
  }
  std::cout << bTree.size() << std::endl;
}

int main() {
  tester();
  std::cout << Integer::counter << std::endl;
}
