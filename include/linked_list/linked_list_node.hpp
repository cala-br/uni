#ifndef LINKED_LIST_NODE_HPP_
#define LINKED_LIST_NODE_HPP_
#pragma once

namespace uni {
  template <typename T>
  struct LinkedListNode {
    using TNode = LinkedListNode<T>;

    T value;
    TNode *prev;
    TNode *next;


    T& operator *() { return value; }
    T* operator ->() { return &value; }

    T& operator =(T&& other) { return value = other; }
    T& operator =(const T& other) { return value = other; }

    bool operator ==(T&& other) { return value == other; }
    bool operator ==(const T& other) { return value == other; }


    TNode* addNext(T value) {
      auto next = new TNode {
        .value = value,
      };

      link(this, next, this->next);
      return next;
    }

    TNode* addPrev(T value) {
      auto prev = new TNode {
        .value = value,
      };

      link(this->prev, prev, this);
      return prev;
    }


    void unlink() {
      link(prev, next);
    }


    static void link(TNode *prev, TNode *middle, TNode *next) {
      link(prev, middle);
      link(middle, next);
    }

    static void link(TNode *prev, TNode *next) {
      if (prev) prev->next = next;
      if (next) next->prev = prev;
    }
  };
}

#endif // !LINKED_LIST_NODE_HPP_
