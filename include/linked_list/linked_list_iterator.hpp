#ifndef LINKED_LIST_ITERATOR_HPP_
#define LINKED_LIST_ITERATOR_HPP_
#pragma once

#include "linked_list_node.hpp"

namespace uni {
  template <typename T>
  class LinkedListIterator {
  public:
    using TNode = LinkedListNode<T>;
    using TIterator = LinkedListIterator<T>;

    LinkedListIterator(TNode *start)
      : current(start)
    {};

    TIterator& operator ++() {
      current = current->next;
      return *this;
    }

    TIterator operator ++(int) {
      auto result = *this;
      ++(*this);
      return result;
    }

    TNode& operator *() {
      return *current;
    }

    TNode* operator ->() {
      return current;
    }

    bool operator ==(const TIterator& other) {
      return current == other.current;
    };

    bool operator !=(const TIterator& other) {
      return current != other.current;
    };     

  private:
    TNode *current;
  };
}

#endif // !LINKED_LIST_ITERATOR_HPP_
