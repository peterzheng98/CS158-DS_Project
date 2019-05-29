//
// Created by 郑文鑫 on 2019-03-09.
//

#include "utility.hpp"
#include <functional>
#include <cstddef>
#include "exception.hpp"
#include <map>
#include <fstream>
namespace sjtu {
    template <class Key, class Value, class Compare = std::less<Key> >
    class BTree {
    private:
        // Your private members go here
        std::fstream fileIO;
        std::map<Key, Value> _core;
    public:
        typedef pair<const Key, Value> value_type;
        
        const std::map<Key, Value, Compare> &getCore() const;
        
        class const_iterator;
        class iterator {
        private:
            // Your private members go here
        public:
            bool modify(const Value& value){
                
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
            std::ifstream ifs("target.txt");
            int sizeT;
            if(ifs){
                ifs >> sizeT;
//                std::cout << "[Debug IO Init] size:" << sizeT << std::endl;
                for(int i = 0; i < sizeT; ++i){
                    Key key;
                    Value value;
                    ifs >> key >> value;
//                    std::cout << "[Debug IO Read] " << key << "->" << value;
                    _core.insert(std::make_pair(key, value));
                }
                } else{
                    std::cout << "Initial";
                }
            
        }
        BTree(const BTree& other) {
            // Todo Copy
        }
        BTree& operator=(const BTree& other) {
            // Todo Assignment
        }
        ~BTree() {
            fileIO.open("target.txt", std::ios::in | std::ios::out | std::ios::trunc);
            fileIO << _core.size() << "\n";
            for(auto it = _core.begin(); it != _core.end(); it++) {
                fileIO << it->first << std::endl;
                fileIO << it->second << std::endl;
//                std::cout << "[Debug IO Write] " << it->first << "->" << it->second << std::endl;

            }
            fileIO.close();
            // Todo Destructor
        }
        pair<iterator, OperationResult> insert(const Key& key, const Value& value) {
//            std::cout << "[Insertion Debug] " << key << "->" << value << std::endl;
            auto result = _core.insert(std::pair<Key, Value>(key, value));
            if(result.second == false) return pair<iterator, OperationResult>(iterator(), Fail);
            else return pair<iterator, OperationResult>(iterator(), Success);
        }
        // Erase: Erase the Key-Value
        // Return Success if it is successfully erased
        // Return Fail if the key doesn't exist in the database
        OperationResult erase(const Key& key) {
            // TODO erase function
            return Fail;  // If you can't finish erase part, just remaining here.
        }
        bool empty() const { return _core.empty(); }
        // Return the number of <K,V> pairs
        size_t size() const { return _core.size(); }
        Value at(const Key& key){
            return _core[key];
        }
    };
    
    template<class Key, class Value, class Compare>
    const std::map<Key, Value, Compare> &BTree<Key, Value, Compare>::getCore() const {
        return _core;
    }
}  // namespace sjtu


