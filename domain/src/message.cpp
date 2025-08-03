#include "domain/message.hpp"
#include <stdexcept>

namespace fast_chat {

Message::Message(std::string from, std::string content)
    : from(std::move(from)), content(std::move(content)),
      timestamp(std::chrono::system_clock::now()) {
    if (this->from.empty()) {
        throw std::runtime_error("Message sender 'from' cannot be empty");
    }

    if (this->content.empty()) {
        throw std::runtime_error("Message content cannot be empty");
    }
}

const std::string& Message::get_from() const { return from; }
const std::string& Message::get_content() const { return content; }
std::chrono::system_clock::time_point Message::get_timestamp() const {
    return timestamp;
}

} // namespace fast_chat