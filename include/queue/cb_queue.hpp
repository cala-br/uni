#pragma once

#include <circular_buffer/circular_buffer.hpp>
#include "queue_base.hpp"

namespace uni {
  template <typename T, int MaxLength>
  class CbQueue : public IQueue<T> {
  public:
    CbQueue()
      : buffer({})
    {}

    CbQueue(std::initializer_list<T> values) 
      : buffer(values)
    {}


    bool tryEnqueue(T value) noexcept {
      return buffer.tryPushFront(value);
    }

    std::optional<T> tryDequeue() noexcept {
      return buffer.tryPopBack();
    }


    [[nodiscard]] bool length() const {
      return buffer.length();
    }

    [[nodiscard]] bool isFull() const {
      return buffer.isFull();
    }

    [[nodiscard]] bool isEmpty() const {
      return buffer.isEmpty();
    }

  private:
    CircularBuffer<T, MaxLength> buffer;
  };
}