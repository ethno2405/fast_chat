#pragma once

#include <string>

namespace fast_chat {
class IPasswordHash {
  public:
    virtual const std::string& hash(const std::string& password) const = 0;
    virtual const bool verify(const std::string& hash,
                              const std::string& password) const = 0;
};
} // namespace fast_chat