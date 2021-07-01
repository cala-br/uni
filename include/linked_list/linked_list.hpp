#ifndef LINKED_LIST_HPP_
#define LINKED_LIST_HPP_
#pragma once

#include <concepts>
#include "linked_list_node.hpp"
#include "linked_list_iterator.hpp"

namespace uni {
  template <typename FPredicate, typename T>
  concept Predicate = requires (FPredicate p, const T& n) {
    { p(n) } -> std::same_as<bool>;
  };


  template <typename T>
  class LinkedList {
  public:
    using TNode = LinkedListNode<T>;
    using Iterator = LinkedListIterator<T>;

    LinkedList()
      : head(nullptr), tail(nullptr)
    {};


    TNode* addBack(T value) {
      if (!head)
        return createHead(value);

      return tail = tail->addNext(value);
    };

    TNode* addFront(T value) {
      if (!head)
        return createHead(value);

      return head = head->addPrev(value);
    }


    bool tryRemove(T value) {
      auto v = find(value);
      if (v)
        remove(*v);

      return !!v;
    }

    void remove(TNode& node) {
      remove(&node);
    }

    void remove(TNode *node) {
      node->unlink();

      if (node == head)
        head = head->next;

      else if (node == tail)
        tail = tail->prev;

      delete node;
    }


    TNode* find(T value) {
      auto v = std::find(begin(), end(), value);
      return v != end()
        ? v.get()
        : nullptr;
    }


    TNode& operator[](int index) {
      return nodeAt(index);
    }

    TNode& nodeAt(int index) {
      auto curr = begin();
      for (; index > 0 && curr != end(); --index, ++curr)
        ;

      return *curr;
    }


    Iterator begin() { return {head}; }
    Iterator end() { return {tail->next}; }

  private:
    TNode* createHead(T value) {
      return head = tail = new TNode {value};
    }

    TNode *head;
    TNode *tail;
  };
}

#endif // !LINKED_LIST_HPP_