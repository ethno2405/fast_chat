#include <sodium.h>

#include <iostream>

#include "console_message_notifier.hpp"
#include "domain/chat_server.hpp"
#include "domain/user.hpp"
#include "sha512_password_hasher.hpp"

void print_users_in_room(const fast_chat::ChatRoom& room);

int main()
{
    if (sodium_init() < 0)
    {
        return 1;
    }

    std::cout << "Chat server is starting..." << std::endl;
    auto hasher = std::make_shared<fast_chat::api::Sha512PasswordHasher>();
    auto server = std::make_unique<fast_chat::ChatServer>(hasher);

    auto bob = server->register_user("bob", "123456");
    auto john = server->register_user("john", "123qwe");

    auto notifier = std::make_shared<fast_chat::api::ConsoleMessageNotifier>();
    auto general_room = server->create_room("general", notifier);
    auto teams_room = server->create_room("teams", notifier);

    bob = server->login("bob", "123456");
    john = server->login("john", "123qwe");

    general_room->join(bob);
    general_room->join(john);
    teams_room->join(bob);

    print_users_in_room(*general_room);
    print_users_in_room(*teams_room);

    general_room->leave("bob");

    print_users_in_room(*general_room);
    print_users_in_room(*teams_room);

    server->logout("bob");
    server->logout("john");

    print_users_in_room(*general_room);
    print_users_in_room(*teams_room);

    std::cout << "End!" << std::endl;
}

void print_users_in_room(const fast_chat::ChatRoom& room)
{
    std::cout << "Users in room " << room.get_name() << ":" << std::endl;
    for (const auto& user : room.get_users())
    {
        std::cout << user->get_username() << std::endl;
    }
    std::cout << std::endl;
}
