#ifndef ELLIPTIC_CURVE_H
#define ELLIPTIC_CURVE_H

#include "bigint.h"
#include <vector>
#include <optional>

namespace e2e {

/**
 * @brief Точка на эллиптической кривой
 */
struct ECPoint {
    BigInt x;
    BigInt y;
    bool isInfinity; // Бесконечно удаленная точка (нейтральный элемент)
    
    ECPoint() : isInfinity(true) {}
    ECPoint(const BigInt& x, const BigInt& y) : x(x), y(y), isInfinity(false) {}
    
    bool operator==(const ECPoint& other) const;
    bool operator!=(const ECPoint& other) const;
    
    std::string toString() const;
};

/**
 * @brief Параметры эллиптической кривой y^2 = x^3 + ax + b (mod p)
 */
struct CurveParams {
    BigInt p;  // Модуль поля
    BigInt a;  // Коэффициент a
    BigInt b;  // Коэффициент b
    ECPoint G; // Генерирующая точка (базовая точка)
    BigInt n;  // Порядок группы (количество точек)
    BigInt h;  // Кофактор (обычно 1)
    
    std::string name; // Имя кривой (например, "secp256r1")
};

/**
 * @brief Класс для работы с эллиптической кривой
 */
class EllipticCurve {
public:
    explicit EllipticCurve(const CurveParams& params);
    
    /**
     * @brief Проверить, лежит ли точка на кривой
     */
    bool isPointOnCurve(const ECPoint& point) const;
    
    /**
     * @brief Сложение двух точек (P + Q)
     */
    ECPoint add(const ECPoint& P, const ECPoint& Q) const;
    
    /**
     * @brief Удвоение точки (2P)
     */
    ECPoint doublePoint(const ECPoint& P) const;
    
    /**
     * @brief Скалярное умножение (k * P)
     * Использует метод "double-and-add"
     */
    ECPoint scalarMultiply(const BigInt& k, const ECPoint& P) const;
    
    /**
     * @brief Скалярное умножение базовой точки (k * G)
     */
    ECPoint scalarMultiplyBase(const BigInt& k) const;
    
    /**
     * @brief Отрицание точки (-P)
     */
    ECPoint negate(const ECPoint& P) const;
    
    /**
     * @brief Получить параметры кривой
     */
    const CurveParams& getParams() const { return params_; }
    
    /**
     * @brief Получить предопределенные параметры кривой secp256r1 (P-256)
     */
    static CurveParams getSecp256r1Params();

private:
    CurveParams params_;
    
    // Модульная арифметика в поле F_p
    BigInt modInverse(const BigInt& value) const;
    BigInt modAdd(const BigInt& a, const BigInt& b) const;
    BigInt modSub(const BigInt& a, const BigInt& b) const;
    BigInt modMul(const BigInt& a, const BigInt& b) const;
    BigInt modDiv(const BigInt& a, const BigInt& b) const;
};

} // namespace e2e

#endif // ELLIPTIC_CURVE_H

