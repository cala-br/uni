#include <iostream>
#include <string_view>
#include <queues>

namespace test {
  using namespace uni;
  using namespace std;

  using StringQueue = CbQueue<string_view, 10>;
  using IntQueue = CbQueue<int, 5>;


  ostream& enqueue(auto &q, auto gen, int times) {
    for (int i = 0; i < times; i++) {
      auto val = gen();
      q.tryEnqueue(val);

      clog << "put: " << val << '\n';
    }

    return clog;
  }

  ostream& dequeue(auto &q, int times) {
    for (int i = 0; i < times; i++) {
      clog << "got: " << *q.tryDequeue() << '\n';
    }

    return clog;
  }


  class StringGen {
  public:
    auto operator ()() {
      return values[++i %= values.size()];
    }

  private:
    int i = -1;
    static constexpr array values = {
      "abc"sv,
      "def"sv,
      "ghi"sv,
    };
  };


  inline void queues() {
    try {
      StringQueue queue;

      auto generator = StringGen{};

      enqueue(queue, generator, 10) << '\n';
      dequeue(queue, 5) << '\n';

      clog << "testQueue: ✅\n";
    }
    catch (...) {
      cerr << "testQueue: ❌\n";
    }
  }
}