#ifndef ECC_KEYPAIR_H
#define ECC_KEYPAIR_H

#include "elliptic_curve.h"
#include "bigint.h"
#include <string>
#include <vector>

namespace e2e {

/**
 * @brief Класс для работы с парой ключей ECC (приватный и публичный)
 */
class ECCKeyPair {
public:
    /**
     * @brief Конструктор - генерирует новую пару ключей
     * @param curve Параметры кривой (по умолчанию secp256r1)
     */
    explicit ECCKeyPair(const CurveParams& curve = EllipticCurve::getSecp256r1Params());
    
    /**
     * @brief Конструктор из существующего приватного ключа
     * @param private_key Приватный ключ (BigInt)
     * @param curve Параметры кривой
     */
    ECCKeyPair(const BigInt& private_key, const CurveParams& curve = EllipticCurve::getSecp256r1Params());
    
    /**
     * @brief Конструктор из приватного ключа в hex формате
     */
    ECCKeyPair(const std::string& private_key_hex, const CurveParams& curve = EllipticCurve::getSecp256r1Params());
    
    /**
     * @brief Получить приватный ключ
     */
    const BigInt& getPrivateKey() const { return private_key_; }
    
    /**
     * @brief Получить публичный ключ (точка на кривой)
     */
    const ECPoint& getPublicKey() const { return public_key_; }
    
    /**
     * @brief Получить приватный ключ в hex формате
     */
    std::string getPrivateKeyHex() const;
    
    /**
     * @brief Получить публичный ключ в hex формате (x, y)
     */
    std::string getPublicKeyHex() const;
    
    /**
     * @brief Получить публичный ключ в сжатом формате (0x02/0x03 + x)
     */
    std::vector<uint8_t> getPublicKeyCompressed() const;
    
    /**
     * @brief Получить публичный ключ в несжатом формате (0x04 + x + y)
     */
    std::vector<uint8_t> getPublicKeyUncompressed() const;
    
    /**
     * @brief Загрузить публичный ключ из сжатого формата
     */
    static ECPoint loadPublicKeyCompressed(const std::vector<uint8_t>& compressed, const CurveParams& curve = EllipticCurve::getSecp256r1Params());
    
    /**
     * @brief Загрузить публичный ключ из несжатого формата
     */
    static ECPoint loadPublicKeyUncompressed(const std::vector<uint8_t>& uncompressed, const CurveParams& curve = EllipticCurve::getSecp256r1Params());
    
    /**
     * @brief Проверить валидность ключа
     */
    bool isValid() const;
    
    /**
     * @brief Получить кривую
     */
    const CurveParams& getCurve() const { return curve_; }

private:
    BigInt private_key_;
    ECPoint public_key_;
    CurveParams curve_;
    EllipticCurve curve_impl_;
    
    void generatePublicKey();
};

} // namespace e2e

#endif // ECC_KEYPAIR_H
