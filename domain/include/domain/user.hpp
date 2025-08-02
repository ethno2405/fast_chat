#pragma once
#include <string>

namespace fast_chat {
class User {
  public:
    User(std::string username, std::string password);
    const std::string& username() const;
    bool check_password(const std::string& password) const;

  private:
    std::string username;
    std::string password_hash;
};
} // namespace fast_chat