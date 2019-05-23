//
// Created by 郑文鑫 on 2019-03-09.
//

#include "utility.hpp"
#include <functional>
#include <cstddef>
#include "exception.hpp"
namespace sjtu {
template <class Key, class Value, class Compare = std::less<Key> >
class BTree {
 private:
  // Your private members go here
 public:
  typedef pair<const Key, Value> value_type;

  class const_iterator;
  class iterator {
   private:
    // Your private members go here
   public:
    bool modify(const Key& key){
    
    }
    iterator() {
      // TODO Default Constructor
    }
    iterator(const iterator& other) {
      // TODO Copy Constructor
    }
    // Return a new iterator which points to the n-next elements
    iterator operator++(int) {
      // Todo iterator++
    }
    iterator& operator++() {
      // Todo ++iterator
    }
    iterator operator--(int) {
      // Todo iterator--
    }
    iterator& operator--() {
      // Todo --iterator
    }
    // Overloaded of operator '==' and '!='
    // Check whether the iterators are same
    value_type& operator*() const {
      // Todo operator*, return the <K,V> of iterator
    }
    bool operator==(const iterator& rhs) const {
      // Todo operator ==
    }
    bool operator==(const const_iterator& rhs) const {
      // Todo operator ==
    }
    bool operator!=(const iterator& rhs) const {
      // Todo operator !=
    }
    bool operator!=(const const_iterator& rhs) const {
      // Todo operator !=
    }
    value_type* operator->() const noexcept {
      /**
       * for the support of it->first.
       * See
       * <http://kelvinh.github.io/blog/2013/11/20/overloading-of-member-access-operator-dash-greater-than-symbol-in-cpp/>
       * for help.
       */
    }
  };
  class const_iterator {
    // it should has similar member method as iterator.
    //  and it should be able to construct from an iterator.
   private:
    // Your private members go here
   public:
    const_iterator() {
      // TODO
    }
    const_iterator(const const_iterator& other) {
      // TODO
    }
    const_iterator(const iterator& other) {
      // TODO
    }
    // And other methods in iterator, please fill by yourself.
  };
  // Default Constructor and Copy Constructor
  BTree() {
    // Todo Default
  }
  BTree(const BTree& other) {
    // Todo Copy
  }
  BTree& operator=(const BTree& other) {
    // Todo Assignment
  }
  ~BTree() {
    // Todo Destructor
  }
  // Insert: Insert certain Key-Value into the database
  // Return a pair, the first of the pair is the iterator point to the new
  // element, the second of the pair is Success if it is successfully inserted
  pair<iterator, OperationResult> insert(const Key& key, const Value& value) {
    // TODO insert function
  }
  // Erase: Erase the Key-Value
  // Return Success if it is successfully erased
  // Return Fail if the key doesn't exist in the database
  OperationResult erase(const Key& key) {
    // TODO erase function
    return Fail;  // If you can't finish erase part, just remaining here.
  }
  // Return a iterator to the beginning
  iterator begin() {}
  const_iterator cbegin() const {}
  // Return a iterator to the end(the next element after the last)
  iterator end() {}
  const_iterator cend() const {}
  // Check whether this BTree is empty
  bool empty() const {}
  // Return the number of <K,V> pairs
  size_t size() const {}
  // Clear the BTree
  void clear() {}
  /**
   * Returns the number of elements with key
   *   that compares equivalent to the specified argument,
   * The default method of check the equivalence is !(a < b || b > a)
   */
  size_t count(const Key& key) const {}
  /**
   * Finds an element with key equivalent to key.
   * key value of the element to search for.
   * Iterator to an element with key equivalent to key.
   *   If no such element is found, past-the-end (see end()) iterator is
   * returned.
   */
  iterator find(const Key& key) {}
  const_iterator find(const Key& key) const {}
};
}  // namespace sjtu
