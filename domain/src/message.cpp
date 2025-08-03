#include "domain/message.hpp"
#include <string>

namespace fast_chat {

Message::Message(std::string from, std::string content)
    : from(std::move(from)), content(std::move(content)) {}

const std::string& Message::get_from() const { return from; }
const std::string& Message::get_content() const { return content; }
std::chrono::system_clock::time_point Message::get_timestamp() const {
    return timestamp;
}

} // namespace fast_chat