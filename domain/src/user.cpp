#include "domain/user.hpp"
#include "domain/password_hasher.hpp"
#include <stdexcept>

namespace fast_chat
{
User::User(std::string username, std::string password_hash)
    : username(std::move(username)), password_hash(std::move(password_hash))
{
    if (this->username.empty())
    {
        throw std::runtime_error("Username cannot be empty");
    }

    if (this->password_hash.empty())
    {
        throw std::runtime_error("User's password hash cannot be empty");
    }
}

const std::string& User::get_username() const
{
    return username;
}
bool User::check_password(const std::string& password,
                          const IPasswordHasher& hasher) const
{
    return hasher.verify(password_hash, password);
}
} // namespace fast_chat
