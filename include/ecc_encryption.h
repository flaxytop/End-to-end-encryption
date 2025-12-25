#ifndef ECC_ENCRYPTION_H
#define ECC_ENCRYPTION_H

#include "ecc_keypair.h"
#include "ecdh.h"
#include <vector>
#include <string>

namespace e2e {

/**
 * @brief Класс для шифрования/расшифрования данных с использованием ECC
 * Реализует ECIES (Elliptic Curve Integrated Encryption Scheme)
 * Использует ECDH для обмена ключами + AES для шифрования данных
 */
class ECCEncryption {
public:
    /**
     * @brief Зашифровать данные публичным ключом получателя
     * @param plaintext Исходные данные
     * @param recipient_public_key Публичный ключ получателя
     * @param curve Параметры кривой
     * @return Зашифрованные данные (включая эфемерный публичный ключ, IV, tag, ciphertext)
     */
    static std::vector<uint8_t> encrypt(
        const std::vector<uint8_t>& plaintext,
        const ECPoint& recipient_public_key,
        const CurveParams& curve = EllipticCurve::getSecp256r1Params()
    );
    
    /**
     * @brief Расшифровать данные приватным ключом получателя
     * @param ciphertext Зашифрованные данные
     * @param recipient_private_key Приватный ключ получателя
     * @param curve Параметры кривой
     * @return Расшифрованные данные
     */
    static std::vector<uint8_t> decrypt(
        const std::vector<uint8_t>& ciphertext,
        const BigInt& recipient_private_key,
        const CurveParams& curve = EllipticCurve::getSecp256r1Params()
    );
    
    /**
     * @brief Зашифровать строку
     */
    static std::string encryptString(
        const std::string& plaintext,
        const ECPoint& recipient_public_key,
        const CurveParams& curve = EllipticCurve::getSecp256r1Params()
    );
    
    /**
     * @brief Расшифровать строку
     */
    static std::string decryptString(
        const std::string& ciphertext_hex,
        const BigInt& recipient_private_key,
        const CurveParams& curve = EllipticCurve::getSecp256r1Params()
    );

private:
    /**
     * @brief Генерация сессионного ключа AES
     */
    static std::vector<uint8_t> generateSessionKey(size_t key_size = 32);
    
    /**
     * @brief Генерация IV для AES
     */
    static std::vector<uint8_t> generateIV(size_t iv_size = 12);
    
    /**
     * @brief Шифрование данных AES-GCM
     * Для упрощения используем AES-256 в режиме CTR (можно расширить до GCM)
     */
    static std::vector<uint8_t> encryptAES(
        const std::vector<uint8_t>& plaintext,
        const std::vector<uint8_t>& key,
        const std::vector<uint8_t>& iv
    );
    
    /**
     * @brief Расшифрование данных AES
     */
    static std::vector<uint8_t> decryptAES(
        const std::vector<uint8_t>& ciphertext,
        const std::vector<uint8_t>& key,
        const std::vector<uint8_t>& iv
    );
    
    /**
     * @brief KDF (Key Derivation Function) - извлечение ключа из общего секрета
     */
    static std::vector<uint8_t> deriveKey(
        const ECPoint& shared_secret,
        size_t key_length,
        const std::vector<uint8_t>& salt = {}
    );
};

} // namespace e2e

#endif // ECC_ENCRYPTION_H
