#pragma once

#include "domain/password_hasher.hpp"
#include <iomanip>
#include <sodium.h>
#include <sstream>

namespace fast_chat::api {
class Sha512PasswordHasher : public IPasswordHasher {
  public:
    std::string hash(const std::string& password) const override {
        unsigned char hash_bin[crypto_hash_sha512_BYTES];
        crypto_hash_sha512(
            hash_bin, reinterpret_cast<const unsigned char*>(password.data()),
            password.size());

        std::ostringstream oss;
        for (size_t i = 0; i < crypto_hash_sha512_BYTES; ++i) {
            oss << std::hex << std::setw(2) << std::setfill('0')
                << static_cast<int>(hash_bin[i]);
        }

        return oss.str();
    }

    bool verify(const std::string& hash,
                const std::string& password) const override {
        return hash == this->hash(password);
    }
};
} // namespace fast_chat::api