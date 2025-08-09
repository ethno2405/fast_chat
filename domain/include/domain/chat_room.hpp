#pragma once

#include <memory>
#include <string>
#include <vector>

namespace fast_chat
{

class Message;
class User;
class IMessageNotifier;

typedef std::vector<std::shared_ptr<User>> Users;

class ChatRoom
{
    public:
        ChatRoom(std::string name,
                 std::shared_ptr<IMessageNotifier> message_notifier);
        const std::string& get_name() const;
        void join(std::shared_ptr<User> user);
        void leave(std::string username);
        const Users& get_users() const;
        bool has_user(const std::string& username) const;
        void post_message(std::shared_ptr<Message> message);
        const std::vector<std::shared_ptr<Message>>& get_chat_history() const;

    private:
        std::string name;
        Users users;
        std::vector<std::shared_ptr<Message>> messages;
        std::shared_ptr<IMessageNotifier> message_notifier;
};
} // namespace fast_chat
