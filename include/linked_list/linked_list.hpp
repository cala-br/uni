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
      : 
      head(nullptr),
      tail(nullptr),
      last({})
    {};


    TNode* addBack(T value) {
      if (!head)
        return createHead(value);

      return updateTail(value);
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
      std::advance(curr, index);
      return *curr;
    }


    Iterator begin() { return {head}; }
    Iterator end() { return {&last}; }

    auto rbegin() {
      return std::make_reverse_iterator(Iterator{&last});
    }

    auto rend() {
      return std::make_reverse_iterator(Iterator{head});
    }

  private:
    TNode* createHead(T value) {
      head = tail = new TNode {value};
      return linkLast();
    }

    TNode* updateTail(T value) {
      tail = tail->addNext(value);
      return linkLast();
    }

    TNode* linkLast() {
      TNode::link(tail, &last);
      return tail;
    }

    TNode *head;
    TNode *tail;
    TNode last;
  };
}

#endif // !LINKED_LIST_HPP_