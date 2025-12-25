#ifndef ECDH_H
#define ECDH_H

#include "ecc_keypair.h"
#include "bigint.h"
#include <vector>

namespace e2e {

/**
 * @brief Класс для реализации ECDH (Elliptic Curve Diffie-Hellman)
 * Протокол обмена ключами на эллиптических кривых
 */
class ECDH {
public:
    /**
     * @brief Вычислить общий секретный ключ
     * @param private_key Приватный ключ одной стороны
     * @param public_key Публичный ключ другой стороны
     * @param curve Параметры кривой
     * @return Общий секретный ключ (точка k*Q, где k - приватный ключ, Q - публичный ключ)
     */
    static ECPoint computeSharedSecret(
        const BigInt& private_key,
        const ECPoint& public_key,
        const CurveParams& curve = EllipticCurve::getSecp256r1Params()
    );
    
    /**
     * @brief Вычислить общий секретный ключ и извлечь из него байты
     * @param private_key Приватный ключ одной стороны
     * @param public_key Публичный ключ другой стороны
     * @param key_length Длина ключа в байтах (по умолчанию 32 для AES-256)
     * @return Байты общего секретного ключа
     */
    static std::vector<uint8_t> deriveKey(
        const BigInt& private_key,
        const ECPoint& public_key,
        size_t key_length = 32,
        const CurveParams& curve = EllipticCurve::getSecp256r1Params()
    );
    
    /**
     * @brief Вывести общий секрет из точки (обычно используется x-координата)
     */
    static std::vector<uint8_t> pointToKey(const ECPoint& point, size_t key_length);
};

} // namespace e2e

#endif // ECDH_H

