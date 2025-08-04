#include "domain/chat_room.hpp"
#include "domain/user.hpp"
#include <algorithm>
#include <assert.h>
#include <stdexcept>

namespace fast_chat {

ChatRoom::ChatRoom(std::string name) : name(std::move(name)) {
    if (this->name.empty())
        throw std::runtime_error("Chat room name cannot be empty");
}

const std::string& ChatRoom::get_name() const { return name; }

void ChatRoom::join(std::shared_ptr<User> user) {
    assert(user);

    if (has_user(user->get_username())) {
        return; // log user is already in the chat
    }

    users.push_back(user); // log user joined server
}

void ChatRoom::leave(std::string username) {
    assert(!username.empty());

    if (has_user(username) == false) {
        return; // log user is not in the chat room
    }

    users.erase(std::find_if(users.begin(), users.end(),
                             [&username](const std::shared_ptr<User>& user) {
                                 return user->get_username() == username;
                             }),
                users.end()); // log user left the chat room
}

const Users& ChatRoom::get_users() const { return users; }

bool ChatRoom::has_user(const std::string& username) const {
    return std::any_of(users.begin(), users.end(),
                       [&username](const std::shared_ptr<User>& user) {
                           return user->get_username() == username;
                       });
}

} // namespace fast_chat
