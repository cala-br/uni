#include <iostream>
#include <string_view>
#include <queues>

namespace test {
  using namespace uni;
  using namespace std;

  using StringQueue = CbQueue<string_view, 10>;
  using IntQueue = CbQueue<int, 5>;

  struct FewDequeued {
    int actual;
    int expected;
  };

  template <typename T>
  struct WrongDequeued {
    T actual;
    T expected;
  };


  ostream& enqueueMany(auto &q, auto gen, int times) {
    for (int i = 0; i < times; i++) {
      auto val = gen();
      q.tryEnqueue(val);

      clog << "put: " << val << '\n';
    }

    return clog;
  }

  ostream& dequeueMany(auto &q, auto gen, int times) {
    for (int i = 0; i < times; i++) {
      auto val = q.tryDequeue();
      if (!val) {
        throw FewDequeued{i, times};
      }

      auto expected = gen();
      if (expected != *val) {
        throw WrongDequeued{*val, expected};
      }
      
      clog << "got: " << *val << '\n';
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

      enqueueMany(queue, StringGen{}, 10) << '\n';
      dequeueMany(queue, StringGen{}, 5) << '\n';

      clog << "testQueue: ✅\n";
    }
    catch (FewDequeued &err) {
      cerr << "testQueue: dequeued just " << err.actual << " out of " << err.expected << " ❌\n";
    }
    catch (WrongDequeued<string_view> &err) {
      cerr << "testQueue: dequeued '" << err.actual << "' instead of '" << err.expected << "' ❌\n";
    }
    catch (...) {
      cerr << "testQueue: general error ❌\n";
    }
  }
}