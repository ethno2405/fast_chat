#pragma once

#include "chat_room.hpp"
#include "user.hpp"

#include <memory>
#include <optional>
#include <string>
#include <vector>

namespace fast_chat {
class ChatServer {
  public:
    std::shared_ptr<User> register_user(const std::string& username,
                                        const std::string& password);
    std::shared_ptr<User> login(const std::string& username,
                                const std::string& password);

    std::shared_ptr<ChatRoom> find_room(const std::string& name) const;
    std::shared_ptr<ChatRoom> create_room(const std::string& name);

  private:
    std::vector<std::shared_ptr<ChatRoom>> rooms;
    std::vector<std::shared_ptr<User>> users;
};
} // namespace fast_chat