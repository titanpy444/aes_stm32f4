
#ifndef INC_COMMON_H_
#define INC_COMMON_H_

#include "main.h"
#include <stdint.h>
#include "aes.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Converts bytes to hex string.
void buffer_to_hex_string(const uint8_t* buffer, size_t buffer_len, char* hex_string);

// Encrypts text using AES CBC with zero padding.
int encrypt_large_text(const uint8_t* text, size_t text_len, char* encrypted_hex);

// Converts hex string to bytes.
int hex_string_to_buffer(const char* hex_string, uint8_t* buffer, size_t buffer_len);

// Decrypts hex string using AES CBC with zero padding.
int decrypt_large_text(const char* hex_encrypted, uint8_t* decrypted);



#endif /* INC_COMMON_H_ */
