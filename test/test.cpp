#include "queue_test.hpp"
#include <linked_list/linked_list.hpp>
#include <iostream>
#include <algorithm>

struct Person {
  const char *name;
  const char *surname;
};

int main() {
  using namespace uni;

  LinkedList<Person> ll;
  ll.add({"luca"});
  ll.add({"mario"});
  ll.add({"gino"})
    ->addPrev({"carlo"})
    ->addPrev({"franco"})
    ->addNext({"mauro"});


  for (auto n : ll) {
    std::clog << n->name << '\n';
  }

  // test::queues();
}