#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include <cstdint>

namespace e2e {

/**
 * @brief Утилиты для работы с кодированием
 */
namespace utils {

/**
 * @brief Кодировать данные в Base64
 */
std::string base64Encode(const std::vector<uint8_t>& data);

/**
 * @brief Декодировать данные из Base64
 */
std::vector<uint8_t> base64Decode(const std::string& encoded);

/**
 * @brief Конвертировать вектор байт в hex строку
 */
std::string toHex(const std::vector<uint8_t>& data);

/**
 * @brief Конвертировать hex строку в вектор байт
 */
std::vector<uint8_t> fromHex(const std::string& hex);

} // namespace utils

} // namespace e2e

#endif // UTILS_H

