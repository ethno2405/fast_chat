#include "domain/chat_room.hpp"
#include "domain/user.hpp"

namespace fast_chat {

ChatRoom::ChatRoom(std::string name) : name(std::move(name)) {}

const std::string& ChatRoom::get_name() const { return name; }

void ChatRoom::join(std::shared_ptr<User> user) {
    if (has_user(user->get_username())) {
        return; // log user is already in the chat
    }

    users.push_back(user); // log user joined server
}

void ChatRoom::leave(std::string username) {
    if (has_user(username) == false) {
        return; // log user is not in the chat room
    }

    std::remove_if(users.begin(), users.end(),
                   [username](const std::shared_ptr<User>& user) {
                       return user->get_username() == username;
                   });
}

const Users& ChatRoom::get_users() const { return users; }

bool ChatRoom::has_user(const std::string& username) const {
    return std::any_of(users.begin(), users.end(),
                       [&username](const std::shared_ptr<User>& user) {
                           return user->get_username() == username;
                       });
}

} // namespace fast_chat