#include "domain/chat_room.hpp"
#include "domain/message.hpp"
#include "domain/message_notifier.hpp"
#include "domain/user.hpp"

#include <iostream>

namespace fast_chat::api
{

class ConsoleMessageNotifier : public IMessageNotifier
{
public:
    void notify_message_posted(const Message& message) override
    {
        std::cout << message.get_from() << "': " << message.get_content()
                  << std::endl;
    }

    void notify_user_joined(const User& user) override
    {
        std::cout << user.get_username() << " joined the room" << std::endl;
    }

    void notify_user_left(const User& user) override
    {
        std::cout << user.get_username() << " left the room" << std::endl;
    }
};
} // namespace fast_chat::api
