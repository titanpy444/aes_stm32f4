#include "common.h"

/******************************************************************************
 * @brief Converts a buffer of bytes to a hexadecimal string
 * @param buffer: Input byte buffer
 * @param buffer_len: Length of the buffer
 * @param hex_string: Output buffer for the hex string (must be at least 2*buffer_len+1)
 * @retval None
 *****************************************************************************/
void buffer_to_hex_string(const uint8_t* buffer, size_t buffer_len, char* hex_string) {
    for (size_t i = 0; i < buffer_len; i++) {
        sprintf(hex_string + (i * 2), "%02X", buffer[i]);
    }
    hex_string[buffer_len * 2] = '\0';
}

/******************************************************************************
 * @brief Encrypts input text using AES CBC with zero padding
 * @param text: Input text to encrypt
 * @param text_len: Length of input text
 * @param encrypted_hex: Output buffer for hex result (must be large enough)
 * @retval Number of bytes in encrypted result (before hex conversion)
 *****************************************************************************/
int encrypt_large_text(const uint8_t* text, size_t text_len, char* encrypted_hex) {
    uint8_t key[16] = "0123456789abcdef";
    uint8_t iv[16]  = "abcdef9876543210";
    struct AES_ctx ctx;

    const size_t block_size = 16;
    size_t padded_len = text_len;

    // Calculate required padding
    if (text_len % block_size != 0) {
        padded_len = text_len + (block_size - (text_len % block_size));
    }

    // Create padded buffer
    uint8_t* padded_text = (uint8_t*)malloc(padded_len);
    if (!padded_text) return -1;

    memcpy(padded_text, text, text_len);
    if (padded_len > text_len) {
        memset(padded_text + text_len, 0, padded_len - text_len);
    }

    // Print padded blocks (for debugging)
    printf("Padded blocks before encryption:\n");
    for (size_t i = 0; i < padded_len; i += block_size) {
        for (size_t j = 0; j < block_size; j++) {
            if (i + j < padded_len) {
                if (padded_text[i + j] != 0) {
                    printf("%c", padded_text[i + j]);
                } else {
                    printf("\\0");  // Display null bytes as \0
                }
            }
        }
        printf("\n");
    }

    // Initialize and encrypt
    AES_init_ctx_iv(&ctx, key, iv);
    AES_CBC_encrypt_buffer(&ctx, padded_text, padded_len);

    // Convert to hex string
    buffer_to_hex_string(padded_text, padded_len, encrypted_hex);

    free(padded_text);
    return padded_len;
}

/******************************************************************************
 * @brief Converts a hexadecimal string to a byte buffer
 * @param hex_string: Input hexadecimal string
 * @param buffer: Output buffer for the converted bytes
 * @param buffer_len: Length of the output buffer
 * @retval Number of bytes written to the buffer
 *****************************************************************************/
int hex_string_to_buffer(const char* hex_string, uint8_t* buffer, size_t buffer_len) {
    size_t hex_len = strlen(hex_string);
    if (hex_len % 2 != 0 || hex_len / 2 > buffer_len) {
        return -1;  // Invalid hex string or buffer too small
    }

    for (size_t i = 0; i < hex_len; i += 2) {
        char hex_byte[3] = {hex_string[i], hex_string[i+1], '\0'};
        buffer[i/2] = (uint8_t)strtol(hex_byte, NULL, 16);
    }

    return hex_len / 2;
}

/******************************************************************************
 * @brief Decrypts the input hexadecimal string using AES CBC mode with zero padding
 * @param hex_encrypted: Hexadecimal string of encrypted data
 * @param decrypted: Output buffer for decrypted data (must be large enough)
 * @retval Number of bytes written to the decrypted buffer
 *****************************************************************************/
int decrypt_large_text(const char* hex_encrypted, uint8_t* decrypted) {
    uint8_t key[16] = "0123456789abcdef";
    uint8_t iv[16]  = "abcdef9876543210";
    struct AES_ctx ctx;

    // Convert hex string to bytes
    uint8_t encrypted_data[512];  // Adjust size as needed
    int encrypted_len = hex_string_to_buffer(hex_encrypted, encrypted_data, sizeof(encrypted_data));
    if (encrypted_len < 0) {
        return -1;
    }

    // Initialize AES context
    AES_init_ctx_iv(&ctx, key, iv);

    // Decrypt the data (will include padding zeros)
    AES_CBC_decrypt_buffer(&ctx, encrypted_data, encrypted_len);

    // Copy to output buffer
    memcpy(decrypted, encrypted_data, encrypted_len);

    return encrypted_len;
}
