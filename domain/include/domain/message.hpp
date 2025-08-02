#pragma once

#include <chrono>
#include <string>

namespace fast_chat {
class Message {

  public:
    Message(std::string from, std::string content);

    const std::string& from() const;
    const std::string& content() const;
    std::chrono::system_clock::time_point timestamp() const;

  private:
    std::string from;
    std::string content;
    std::chrono::system_clock::time_point timestamp;
};

} // namespace fast_chat