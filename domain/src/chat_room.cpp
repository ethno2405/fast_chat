#include "domain/chat_room.hpp"
#include "domain/user.hpp"
#include "domain/message.hpp"
#include "domain/message_notifier.hpp"
#include <algorithm>
#include <assert.h>
#include <stdexcept>
#include <ranges>

namespace fast_chat {

    ChatRoom::ChatRoom(std::string name, std::shared_ptr<IMessageNotifier> message_notifier)
        : name(std::move(name)), message_notifier(std::move(message_notifier)) {
        if (this->name.empty())
            throw std::runtime_error("Chat room name cannot be empty");

        if (!this->message_notifier)
            throw std::runtime_error("Chat room requires a message notifier");
    }

    const std::string& ChatRoom::get_name() const { return name; }

    void ChatRoom::join(std::shared_ptr<User> user) {
        assert(user);

        if (has_user(user->get_username())) {
            return; // log user is already in the chat
        }

        users.emplace_back(user); // log user joined server
        message_notifier->notify_user_joined(*user);
    }

    void ChatRoom::leave(std::string username) {
        assert(!username.empty());

        if (has_user(username) == false) {
            return; // log user is not in the chat room
        }

        auto user = std::ranges::find_if(users, [&username](const std::shared_ptr<User>& user) {
            return user->get_username() == username; });
        message_notifier->notify_user_left(*user->get());
        users.erase(user); // log user left the chat room
    }

    const Users& ChatRoom::get_users() const { return users; }

    bool ChatRoom::has_user(const std::string& username) const {
        return std::any_of(users.begin(), users.end(),
            [&username](const std::shared_ptr<User>& user) {
                return user->get_username() == username;
            });
    }

    void ChatRoom::post_message(std::shared_ptr<Message> message) {
        assert(message);
        if (!has_user(message->get_from())) {
            return; // log user is not in the chat room
        }

        messages.push_back(message);
        message_notifier->notify_message_posted(*message);
    }
} // namespace fast_chat
