#pragma once

#include <memory>
#include <string>
#include <vector>

namespace fast_chat {

class User;

class ChatRoom {
  public:
    ChatRoom(std::string name);
    const std::string& get_name() const;
    void join(std::shared_ptr<User> user);
    void leave(std::string username);
    const std::vector<std::shared_ptr<User>>& get_users() const;

  private:
    std::string name;
    std::vector<std::shared_ptr<User>> users;
};
} // namespace fast_chat