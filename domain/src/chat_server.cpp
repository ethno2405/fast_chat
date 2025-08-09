#include "domain/chat_server.hpp"
#include "domain/chat_room.hpp"
#include "domain/message_notifier.hpp"
#include "domain/password_hasher.hpp"
#include "domain/user.hpp"

#include <algorithm>
#include <assert.h>
#include <memory>
#include <ranges>
#include <stdexcept>
#include <string>

namespace fast_chat
{

ChatServer::ChatServer(std::shared_ptr<IPasswordHasher> hasher)
    : hasher(std::move(hasher))
{
    if (!this->hasher)
    {
        throw std::runtime_error("Chat server requires a password hasher");
    }
}

std::shared_ptr<User> ChatServer::register_user(const std::string& username,
                                                const std::string& password)
{
    assert(!username.empty());
    assert(!password.empty());

    if (user_exists(username))
    {
        return nullptr; // log user already exists
    }

    auto new_user = std::make_shared<User>(username, hasher->hash(password));
    users.push_back(new_user);
    return new_user;
}

std::shared_ptr<User> ChatServer::login(const std::string& username,
                                        const std::string& password)
{
    assert(!username.empty());
    assert(!password.empty());

    auto user = find_user(username);
    if (!user)
    {
        return nullptr; // log user doesn't exists
    }

    if (is_user_online(user->get_username()))
    {
        return nullptr; // log user is already logged in (online)
    }

    if (user->check_password(password, *hasher) == false)
    {
        return nullptr; // log invalid password attempt
    }

    online_users.push_back(user);
    return user;
}

void ChatServer::logout(const std::string& username)
{
    assert(!username.empty());

    if (is_user_online(username) == false)
    {
        return; // log user is offline
    }

    auto rooms_to_clear =
        rooms | std::views::filter([username](std::shared_ptr<ChatRoom> room) {
            return room->has_user(username);
        });

    for (auto room : rooms_to_clear)
    {
        room->leave(username);
    }

    online_users.erase(
        std::find_if(online_users.begin(), online_users.end(),
                     [&username](const std::shared_ptr<User>& user) {
                         return user->get_username() == username;
                     }),
        online_users.end());
}

std::shared_ptr<ChatRoom> ChatServer::find_room(const std::string& name) const
{
    assert(!name.empty());

    return *std::find_if(rooms.begin(), rooms.end(),
                         [&name](const std::shared_ptr<ChatRoom>& room) {
                             return room->get_name() == name;
                         });
}

std::shared_ptr<ChatRoom> ChatServer::create_room(
    const std::string& name,
    const std::shared_ptr<IMessageNotifier> message_notifier)
{
    assert(!name.empty());

    if (std::ranges::any_of(rooms,
                            [&name](const std::shared_ptr<ChatRoom>& room) {
                                return room->get_name() == name;
                            }))
    {
        return nullptr; // log room already exists
    }

    auto new_room = std::make_shared<ChatRoom>(name, message_notifier);
    rooms.push_back(new_room);
    return new_room;
}

bool ChatServer::user_exists(const std::string& username) const
{
    assert(!username.empty());

    return std::any_of(users.begin(), users.end(),
                       [&username](const std::shared_ptr<User>& user) {
                           return user->get_username() == username;
                       });
}

bool ChatServer::is_user_online(const std::string& username) const
{
    assert(!username.empty());

    return std::any_of(online_users.begin(), online_users.end(),
                       [&username](const std::shared_ptr<User>& user) {
                           return user->get_username() == username;
                       });
}

std::shared_ptr<User> ChatServer::find_user(const std::string& username) const
{
    assert(!username.empty());

    return *std::find_if(users.begin(), users.end(),
                         [&username](const std::shared_ptr<User>& user) {
                             return user->get_username() == username;
                         });
}

} // namespace fast_chat
