#ifndef LINKED_LIST_HPP_
#define LINKED_LIST_HPP_
#pragma once

#include "linked_list_node.hpp"
#include "linked_list_iterator.hpp"

namespace uni {
  template <typename T>
  class LinkedList {
  public:
    using TNode = LinkedListNode<T>;
    using Iterator = LinkedListIterator<T>;

    LinkedList()
      : head(nullptr), tail(nullptr)
    {};

    TNode* add(T value) {
      if (!head) {
        return head = tail = new TNode {value};
      }

      return tail = tail->addNext(value);
    };


    Iterator begin() { return {head}; }
    Iterator end() { return {tail->next}; }

  private:
    TNode *head;
    TNode *tail;
  };
}

#endif // !LINKED_LIST_HPP_