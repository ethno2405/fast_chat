#include "Sha512PasswordHasher.hpp"
#include "domain/chat_server.hpp"
#include "domain/user.hpp"

#include <iostream>
#include <sodium.h>

int main() {
    if (sodium_init() < 0) {
        return 1;
    }

    std::cout << "Chat server is starting..." << std ::endl;
    auto hasher = std::make_shared<fast_chat::api::Sha512PasswordHasher>();
    auto server = std::make_unique<fast_chat::ChatServer>(hasher);

    auto bob = server->register_user("bob", "123456");
    auto john = server->register_user("john", "123qwe");

    auto room = server->create_room("general");

    bob = server->login("bob", "123456");
    john = server->login("john", "123qwe");

    room->join(bob);
    room->join(john);

    for (auto u : room->get_users()) {
        std::cout << "User " << u->get_username() << " in room "
                  << room->get_name() << std::endl;
    }

    room->leave("bob");
    std::cout << std::endl;

    for (auto& u : room->get_users()) {
        std::cout << "User " << u->get_username() << " in room "
                  << room->get_name() << std::endl;
    }

    server->logout("bob");
    server->logout("john");

    std::cout << "Users in room " << room->get_name() << ": "
              << room->get_users().size() << std::endl;

    std::cout << "End!" << std::endl;
}
