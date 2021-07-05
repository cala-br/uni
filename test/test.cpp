#include "queue_test.hpp"
#include <linked_list/linked_list.hpp>
#include <iostream>
#include <algorithm>
#include <string_view>

struct Person {
  std::string_view name;
  std::string_view surname;

  bool operator ==(const Person& other) {
    return name == other.name && surname == other.surname; 
  }
};

int main() {
  using namespace uni;

  LinkedList<std::string_view> ll;
  ll.addBack({"luca"});
  ll.addBack({"mario"});
  ll.addBack({"gino"})
    ->addPrev({"carlo"})
    ->addPrev({"franco"})
    ->addNext({"mauro"});

  ll.remove(ll[1]);
  ll.tryRemove({"carlo"});

  std::reverse(ll.begin(), ll.end());

  for (auto n = ll.rbegin(); n != ll.rend(); ++n) {
    std::clog << (*n).value << '\n';
  }

  // test::queues();
}