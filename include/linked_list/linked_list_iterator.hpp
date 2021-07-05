#ifndef LINKED_LIST_ITERATOR_HPP_
#define LINKED_LIST_ITERATOR_HPP_
#pragma once

#include <iterator>
#include "linked_list_node.hpp"

namespace uni {
  template <typename T>
  class LinkedListIterator {
  public:
    using TNode = LinkedListNode<T>;
    using TIterator = LinkedListIterator<T>;

    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = TNode;
    using difference_type = std::ptrdiff_t;
    using pointer = TNode*;
    using reference = TNode&;

    LinkedListIterator(TNode *start)
      : current(start)
    {};

    TIterator& operator ++() {
      current = current->next;
      return *this;
    }

    TIterator& operator --() {
      current = current->prev;
      return *this;
    }

    TIterator operator ++(int) {
      auto result = *this;
      ++(*this);
      return result;
    }

    TIterator operator --(int) {
      auto result = *this;
      --(*this);
      return result;
    }

    reference operator *() {
      return *current;
    }

    pointer operator ->() {
      return current;
    }


    int operator -(const TIterator& other) {
      return current - other.current;
    }

    bool operator ==(const TIterator& other) {
      return current == other.current;
    };

    bool operator !=(const TIterator& other) {
      return current != other.current;
    };


    TNode* get() const {
      return current;
    }

  private:
    TNode *current;
  };
}

#endif // !LINKED_LIST_ITERATOR_HPP_
