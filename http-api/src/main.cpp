#include <drogon/drogon.h>
#include <sodium.h>

#include "console_message_notifier.hpp"
#include "domain/chat_server.hpp"
#include "domain/user.hpp"
#include "sha512_password_hasher.hpp"

#include <iostream>

void print_users_in_room(const fast_chat::ChatRoom& room);

int main(int argc, char* argv[])
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

    uint16_t port = 8080u;
    if (argc > 1)
    {
        for (int i = 1; i < argc; ++i)
        {
            if (std::string(argv[i]) == "-p" && i + 1 < argc)
            {
                port = static_cast<uint16_t>(std::stoi(argv[i + 1]));
            }
        }
    }

    std::cout << "Starting HTTP server on port " << port << "..." << std::endl;
    drogon::app()
        .setLogLevel(trantor::Logger::kDebug)
        .addListener("0.0.0.0", port)
        .setThreadNum(0)
        .registerHandler(
            "/ping",
            [](const drogon::HttpRequestPtr& req,
               std::function<void(const drogon::HttpResponsePtr&)>&& callback) {
                auto resp = drogon::HttpResponse::newHttpResponse(
                    drogon::k200OK, drogon::ContentType::CT_TEXT_PLAIN);
                resp->setBody("pong");
                callback(resp);
            },
            {drogon::Get})
        .run();

    std::cout << "End!" << std::endl;
}

void print_users_in_room(const fast_chat::ChatRoom& room)
{
    std::cout << "Users in room " << room.get_name() << ":\n";
    for (const auto& user : room.get_users())
    {
        std::cout << user->get_username() << '\n';
    }
    std::cout << std::endl;
}
