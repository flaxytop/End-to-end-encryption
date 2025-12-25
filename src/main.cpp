#include <iostream>
#include "ecc_keypair.h"
#include "ecc_encryption.h"
#include "ecdsa.h"
#include "utils.h"

using namespace e2e;

int main() {
    std::cout << "=== Сквозное шифрование на эллиптических кривых ===\n";
    std::cout << "Все алгоритмы реализованы самостоятельно\n\n";
    
    try {
        // Генерация ключей для Алисы
        std::cout << "Генерация ключей для Алисы...\n";
        ECCKeyPair alice_keys;
        std::string alice_public_hex = alice_keys.getPublicKeyHex();
        std::string alice_private_hex = alice_keys.getPrivateKeyHex();
        std::cout << "✓ Ключи Алисы сгенерированы\n";
        std::cout << "  Приватный ключ: " << alice_private_hex << "\n";
        std::cout << "  Публичный ключ: " << alice_public_hex << "\n\n";
        
        // Генерация ключей для Боба
        std::cout << "Генерация ключей для Боба...\n";
        ECCKeyPair bob_keys;
        std::string bob_public_hex = bob_keys.getPublicKeyHex();
        std::string bob_private_hex = bob_keys.getPrivateKeyHex();
        std::cout << "✓ Ключи Боба сгенерированы\n";
        std::cout << "  Приватный ключ: " << bob_private_hex << "\n";
        std::cout << "  Публичный ключ: " << bob_public_hex << "\n\n";
        
        // Алиса шифрует сообщение для Боба
        std::string message = "Привет, Боб! Это секретное сообщение.";
        std::cout << "Исходное сообщение: " << message << "\n\n";
        
        std::cout << "Алиса шифрует сообщение публичным ключом Боба...\n";
        std::string encrypted = ECCEncryption::encryptString(message, bob_keys.getPublicKey());
        std::cout << "✓ Сообщение зашифровано\n";
        std::cout << "Зашифрованные данные (Hex): " << encrypted << "\n\n";
        
        // Боб расшифровывает сообщение
        std::cout << "Боб расшифровывает сообщение своим приватным ключом...\n";
        std::string decrypted = ECCEncryption::decryptString(encrypted, bob_keys.getPrivateKey());
        std::cout << "✓ Сообщение расшифровано\n";
        std::cout << "Расшифрованное сообщение: " << decrypted << "\n\n";
        
        // Проверка цифровой подписи
        std::cout << "=== Проверка цифровой подписи ===\n";
        std::string data_to_sign = "Важные данные для подписи";
        std::cout << "Данные для подписи: " << data_to_sign << "\n";
        
        std::string signature = ECDSA::signString(data_to_sign, alice_keys.getPrivateKey());
        std::cout << "Подпись создана Алисой\n";
        std::cout << "Подпись (Hex): " << signature << "\n\n";
        
        bool is_valid = ECDSA::verifyString(data_to_sign, signature, alice_keys.getPublicKey());
        if (is_valid) {
            std::cout << "✓ Подпись валидна!\n";
        } else {
            std::cout << "✗ Подпись невалидна!\n";
        }
        
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}

