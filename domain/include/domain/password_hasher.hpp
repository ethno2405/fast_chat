#pragma once

#include <string>

namespace fast_chat {
class IPasswordHasher {
  public:
    virtual ~IPasswordHasher() = default;
    virtual std::string hash(const std::string& password) const = 0;
    virtual bool verify(const std::string& hash,
                        const std::string& password) const = 0;
};
} // namespace fast_chat