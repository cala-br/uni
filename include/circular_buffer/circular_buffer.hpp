#pragma once

#include <initializer_list>
#include <array>
#include <optional>

namespace uni {
  template <typename T, int MaxLength>
  class CircularBuffer {
  public:
    CircularBuffer()
      : buffer({}), front(0), count(0)
    {};

    CircularBuffer(std::initializer_list<T> values): CircularBuffer() {
      for (auto& v : values) {
        tryPushFront(v);
      }
    }


    bool tryPushFront(T value) noexcept {
      if (isFull())
        return false;

      getFront() = value;
      incrementFront();
      count++;
      return true;
    }

    bool tryPushBack(T value) noexcept {
      if (isFull())
        return false;

      count++;
      getBack() = value;
      return true;
    }


    std::optional<T> tryPopFront() noexcept {
      if (isEmpty())
        return {};

      count--;
      decrementFront();
      return getFront();
    }

    std::optional<T> tryPopBack() noexcept {
      if (isEmpty())
        return {};

      auto res = getBack();
      count--;

      return res;
    }


    [[nodiscard]]
    int length() const {
      return count;
    }

    [[nodiscard]]
    bool isFull() const {
      return count == MaxLength;
    }

    [[nodiscard]]
    bool isEmpty() const {
      return count == 0;
    }

  private:
    void incrementFront() {
      ++front %= MaxLength;
    }

    void decrementFront() {
      front = --front < 0
        ? MaxLength + front
        : front;
    }

    T& getFront() {
      return buffer[front];
    }

    T& getBack() {
      return buffer[getIndexOfLast()];
    }

    [[nodiscard]]
    int getIndexOfLast() const {
      const int last = 
        front - count;
    
      return last < 0
        ? MaxLength + last
        : last;
    }

    std::array<T, MaxLength> buffer;
    int front;
    int count;
  };
}