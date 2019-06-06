#include "header/crypto.h"

cipher_t _b2b_cipher;
uint8_t _b2b_aes_key[AES_KEY_SIZE];

void crypto_init(void) {
    printf("AES Key: ");
    for(size_t i = 0; i < AES_KEY_SIZE; i++) {
        _b2b_aes_key[i] = ((i*5)<<2)*2;
        printf("%02X ", _b2b_aes_key[i]);
    }
    printf("\n");
    if(cipher_init(&_b2b_cipher, CIPHER_AES_128, _b2b_aes_key, AES_KEY_SIZE) < 0) {
        perror("Crypto init failed!\n");
        exit(-1);
    }
}

void crypto_encrypt(uint8_t* plain_data, uint8_t* cipher_data) {
    cipher_encrypt(&_b2b_cipher, plain_data, cipher_data);
}

void crypto_decrypt(uint8_t* cipher_data, uint8_t* plain_data) {
    cipher_decrypt(&_b2b_cipher, cipher_data, plain_data);
}
