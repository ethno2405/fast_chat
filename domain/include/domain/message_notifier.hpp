#pragma once

namespace fast_chat
{

class Message;
class User;

class IMessageNotifier
{
public:
    virtual ~IMessageNotifier() = default;
    virtual void notify_message_posted(const Message& message) = 0;
    virtual void notify_user_joined(const User& user) = 0;
    virtual void notify_user_left(const User& user) = 0;
};
} // namespace fast_chat
