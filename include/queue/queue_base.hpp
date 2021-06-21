#ifndef QUEUE_BASE_HPP_
#define QUEUE_BASE_HPP_
#pragma once

#include <concepts>
#include <optional>

namespace uni {
  template <typename QueueT>
  concept QueueLike = requires (QueueT q, typename QueueT::ValueType v) {
    { q.tryEnqueue(v) } -> std::same_as<bool>;
    { q.tryDequeue() } -> std::same_as<std::optional<typename QueueT::ValueType>>;
  };

  
  template <typename T>
  struct IQueue {
    using ValueType = T;

    virtual bool tryEnqueue(T) = 0;
    virtual auto tryDequeue() -> std::optional<T> = 0;
  };
}

#endif // !QUEUE_BASE_HPP_
