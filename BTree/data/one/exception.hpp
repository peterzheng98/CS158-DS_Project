//
// Created by 郑文鑫 on 2019-03-10.
//

#ifndef BPLUSTREE_EXCEPTION_H
#define BPLUSTREE_EXCEPTION_H

#include <cstddef>
#include <cstring>
#include <string>

namespace sjtu {

class exception {
 protected:
  const std::string variant = "";
  std::string detail = "";

 public:
  exception() {}
  exception(const exception &ec) : variant(ec.variant), detail(ec.detail) {}
  virtual std::string what() { return variant + " " + detail; }
};

/**
 * Not needed.
 */
class index_out_of_bound : public exception {
  /* __________________________ */
};

class runtime_error : public exception {
  /* __________________________ */
};

class invalid_iterator : public exception {
  /* __________________________ */
};

class container_is_empty : public exception {
  /* __________________________ */
};
}  // namespace sjtu

#endif  // BPLUSTREE_EXCEPTION_H
