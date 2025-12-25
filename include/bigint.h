#ifndef BIGINT_H
#define BIGINT_H

#include <vector>
#include <string>
#include <cstdint>
#include <ostream>

namespace e2e {

/**
 * @brief Класс для работы с большими целыми числами
 * Используется для арифметики в конечных полях
 */
class BigInt {
public:
    BigInt();
    explicit BigInt(uint64_t value);
    explicit BigInt(const std::string& hex_string);
    explicit BigInt(const std::vector<uint8_t>& bytes, bool little_endian = false);
    
    // Арифметические операции
    BigInt operator+(const BigInt& other) const;
    BigInt operator-(const BigInt& other) const;
    BigInt operator*(const BigInt& other) const;
    BigInt operator/(const BigInt& other) const;
    BigInt operator%(const BigInt& other) const;
    
    BigInt& operator+=(const BigInt& other);
    BigInt& operator-=(const BigInt& other);
    BigInt& operator*=(const BigInt& other);
    BigInt& operator%=(const BigInt& other);
    
    // Сравнение
    bool operator==(const BigInt& other) const;
    bool operator!=(const BigInt& other) const;
    bool operator<(const BigInt& other) const;
    bool operator<=(const BigInt& other) const;
    bool operator>(const BigInt& other) const;
    bool operator>=(const BigInt& other) const;
    
    // Битвые операции
    BigInt operator<<(size_t shift) const;
    BigInt operator>>(size_t shift) const;
    BigInt operator&(const BigInt& other) const;
    BigInt operator|(const BigInt& other) const;
    
    // Унарные операции
    BigInt operator-() const;
    
    // Модульная арифметика
    BigInt modAdd(const BigInt& other, const BigInt& modulus) const;
    BigInt modSub(const BigInt& other, const BigInt& modulus) const;
    BigInt modMul(const BigInt& other, const BigInt& modulus) const;
    BigInt modInverse(const BigInt& modulus) const; // Обратный элемент по модулю
    BigInt modPow(const BigInt& exponent, const BigInt& modulus) const; // Возведение в степень
    
    // Вспомогательные функции
    bool isZero() const;
    bool isOne() const;
    bool isEven() const;
    size_t bitLength() const;
    size_t byteLength() const;
    
    // Конвертация
    std::vector<uint8_t> toBytes(size_t min_bytes = 0, bool little_endian = false) const;
    std::string toHex() const;
    std::string toDecimal() const;
    
    // Генерация случайного числа
    static BigInt random(size_t bit_length);
    static BigInt randomRange(const BigInt& min, const BigInt& max);
    
    // Константы
    static const BigInt ZERO;
    static const BigInt ONE;
    static const BigInt TWO;

private:
    std::vector<uint32_t> digits_; // Храним в base 2^32
    bool negative_;
    
    void normalize();
    void removeLeadingZeros();
    int compare(const BigInt& other) const;
    BigInt abs() const;
    
    // Внутренние операции
    void addDigits(const std::vector<uint32_t>& other);
    void subtractDigits(const std::vector<uint32_t>& other);
    std::vector<uint32_t> multiplyDigits(const std::vector<uint32_t>& other) const;
    std::pair<BigInt, BigInt> divideDigits(const BigInt& divisor) const;
    
    // Модульная арифметика
    BigInt montgomeryReduce(const BigInt& other, const BigInt& modulus, const BigInt& r_inv) const;
};

std::ostream& operator<<(std::ostream& os, const BigInt& bi);

} // namespace e2e

#endif // BIGINT_H

