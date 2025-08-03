#pragma once

#include <memory>
#include <string>
#include <vector>

namespace fast_chat {

class User;
typedef std::vector<std::shared_ptr<User>> Users;

class ChatRoom {
  public:
    ChatRoom(std::string name);
    const std::string& get_name() const;
    void join(std::shared_ptr<User> user);
    void leave(std::string username);
    const Users& get_users() const;

  private:
    std::string name;
    Users users;

    bool has_user(const std::string& username) const;
};
} // namespace fast_chat