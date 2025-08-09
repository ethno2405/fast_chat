#pragma once

#include "domain/chat_room.hpp"
#include "domain/password_hasher.hpp"

#include <memory>
#include <string>
#include <vector>

namespace fast_chat
{

class User;
class ChatRoom;

class ChatServer
{
public:
    ChatServer(std::shared_ptr<IPasswordHasher> hasher);

    std::shared_ptr<User> register_user(const std::string& username,
                                        const std::string& password);
    std::shared_ptr<User> login(const std::string& username,
                                const std::string& password);
    void logout(const std::string& username);

    std::shared_ptr<ChatRoom> find_room(const std::string& name) const;
    std::shared_ptr<ChatRoom> create_room(
        const std::string& name,
        const std::shared_ptr<IMessageNotifier> message_notifier);

private:
    std::vector<std::shared_ptr<ChatRoom>> rooms;
    Users users;
    Users online_users;
    std::shared_ptr<IPasswordHasher> hasher;
    bool is_user_online(const std::string& username) const;
    bool user_exists(const std::string& username) const;
    std::shared_ptr<User> find_user(const std::string& username) const;
};
} // namespace fast_chat
