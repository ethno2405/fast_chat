#pragma once

#include <chrono>
#include <string>

namespace fast_chat {
class Message {

  public:
    Message(std::string from, std::string content);

    const std::string& get_from() const;
    const std::string& get_content() const;
    std::chrono::system_clock::time_point get_timestamp() const;

  private:
    std::string from;
    std::string content;
    std::chrono::system_clock::time_point timestamp;
};

} // namespace fast_chat
