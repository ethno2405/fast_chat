#pragma once
#include <memory>
#include <string>

namespace fast_chat
{
class IPasswordHasher;
class User
{
public:
    User(std::string username, std::string password_hash);
    const std::string& get_username() const;
    bool check_password(const std::string& password,
                        const IPasswordHasher& hasher) const;

private:
    std::string username;
    std::string password_hash;
};

} // namespace fast_chat
