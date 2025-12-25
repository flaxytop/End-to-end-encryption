#ifndef HASH_H
#define HASH_H

#include <vector>
#include <string>
#include <cstdint>

namespace e2e {

/**
 * @brief Класс для хеширования (SHA-256)
 * Реализуем SHA-256 самостоятельно
 */
class Hash {
public:
    /**
     * @brief Вычислить SHA-256 хеш
     */
    static std::vector<uint8_t> sha256(const std::vector<uint8_t>& data);
    
    /**
     * @brief Вычислить SHA-256 хеш строки
     */
    static std::vector<uint8_t> sha256(const std::string& data);
    
    /**
     * @brief Вычислить SHA-256 хеш и вернуть в hex формате
     */
    static std::string sha256Hex(const std::vector<uint8_t>& data);
    static std::string sha256Hex(const std::string& data);
    
    /**
     * @brief HMAC-SHA256
     */
    static std::vector<uint8_t> hmacSha256(
        const std::vector<uint8_t>& key,
        const std::vector<uint8_t>& data
    );
    
    /**
     * @brief PBKDF2 (Password-Based Key Derivation Function 2)
     */
    static std::vector<uint8_t> pbkdf2(
        const std::vector<uint8_t>& password,
        const std::vector<uint8_t>& salt,
        size_t iterations,
        size_t key_length
    );

private:
    // Внутренние функции SHA-256
    static void sha256ProcessBlock(
        const uint8_t* block,
        uint32_t* hash
    );
    
    static uint32_t rightRotate(uint32_t value, size_t amount);
};

} // namespace e2e

#endif // HASH_H

