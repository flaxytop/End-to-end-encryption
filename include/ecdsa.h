#ifndef ECDSA_H
#define ECDSA_H

#include "ecc_keypair.h"
#include "bigint.h"
#include <vector>
#include <string>

namespace e2e {

/**
 * @brief Структура для хранения подписи ECDSA (r, s)
 */
struct ECDSASignature {
    BigInt r;
    BigInt s;
    
    /**
     * @brief Сериализовать подпись в DER формат
     */
    std::vector<uint8_t> toDER() const;
    
    /**
     * @brief Загрузить подпись из DER формата
     */
    static ECDSASignature fromDER(const std::vector<uint8_t>& der);
    
    /**
     * @brief Конвертировать в hex строку (r:s)
     */
    std::string toHex() const;
    
    /**
     * @brief Загрузить из hex строки
     */
    static ECDSASignature fromHex(const std::string& hex);
};

/**
 * @brief Класс для создания и проверки цифровых подписей ECDSA
 */
class ECDSA {
public:
    /**
     * @brief Создать цифровую подпись
     * @param message Данные для подписи
     * @param private_key Приватный ключ
     * @param curve Параметры кривой
     * @return Подпись (r, s)
     */
    static ECDSASignature sign(
        const std::vector<uint8_t>& message,
        const BigInt& private_key,
        const CurveParams& curve = EllipticCurve::getSecp256r1Params()
    );
    
    /**
     * @brief Проверить цифровую подпись
     * @param message Исходные данные
     * @param signature Подпись (r, s)
     * @param public_key Публичный ключ
     * @param curve Параметры кривой
     * @return true если подпись валидна
     */
    static bool verify(
        const std::vector<uint8_t>& message,
        const ECDSASignature& signature,
        const ECPoint& public_key,
        const CurveParams& curve = EllipticCurve::getSecp256r1Params()
    );
    
    /**
     * @brief Создать подпись строки
     */
    static std::string signString(
        const std::string& message,
        const BigInt& private_key,
        const CurveParams& curve = EllipticCurve::getSecp256r1Params()
    );
    
    /**
     * @brief Проверить подпись строки
     */
    static bool verifyString(
        const std::string& message,
        const std::string& signature_hex,
        const ECPoint& public_key,
        const CurveParams& curve = EllipticCurve::getSecp256r1Params()
    );

private:
    /**
     * @brief Хеширование сообщения (используем SHA-256)
     */
    static std::vector<uint8_t> hashMessage(const std::vector<uint8_t>& message);
    
    /**
     * @brief Конвертировать хеш в BigInt
     */
    static BigInt hashToBigInt(const std::vector<uint8_t>& hash);
    
    /**
     * @brief Генерация случайного k для подписи
     */
    static BigInt generateK(const BigInt& private_key, const std::vector<uint8_t>& message_hash, const CurveParams& curve);
};

} // namespace e2e

#endif // ECDSA_H

