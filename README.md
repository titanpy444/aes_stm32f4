# aes_stm32f4
# STM32F4 AES Encryption Application

## Overview
This application implements AES encryption and decryption in CBC mode using zero padding on the STM32F4 microcontroller. It securely encrypts data and decrypts it back, ensuring robust communication and storage security for embedded systems.

## Key Features
- **AES-CBC Mode:** Encrypts data in 16-byte blocks using a key and IV.
- **Zero Padding:** Ensures plaintext is padded to align with AES block size.
- **Hex Conversion:** Outputs encrypted data as a hex string for easier handling.
- **Decryption Support:** Allows decryption of the hex string to retrieve original text.

## Components
- **`common.h`**: Header file containing helper functions (e.g., for hex conversion).
- **`main.c`**: Contains the main application logic, initialization, and encryption/decryption routines.

## Usage
1. **Encryption**:
   - Input plaintext data is encrypted using AES-CBC with zero padding.
   - The encrypted data is converted to a hexadecimal string.

2. **Decryption**:
   - The encrypted hexadecimal string is converted back to bytes.
   - The original plaintext is retrieved by decrypting the bytes.

### Example
The application encrypts the message:
The result is an encrypted hex string. After decryption, the original plaintext is restored.

## Functions
### `buffer_to_hex_string(const uint8_t* buffer, size_t buffer_len, char* hex_string)`
Converts a byte buffer to a hexadecimal string.

### `encrypt_large_text(const uint8_t* text, size_t text_len, char* encrypted_hex)`
Encrypts plaintext data using AES CBC mode with zero padding.

### `hex_string_to_buffer(const char* hex_string, uint8_t* buffer, size_t buffer_len)`
Converts a hexadecimal string to a byte buffer.

### `decrypt_large_text(const char* hex_encrypted, uint8_t* decrypted)`
Decrypts the encrypted hexadecimal string and retrieves the original plaintext.

## Prerequisites
- **Development Environment**:
  - STM32CubeIDE or equivalent.
  - STM32 HAL libraries.

- **Hardware**:
  - STM32F4 microcontroller.

## Building and Running
1. Open the project in STM32CubeIDE.
2. Build and flash the firmware onto the STM32F4 board.
3. Monitor the output through a serial terminal (e.g., PuTTY) to observe encrypted and decrypted text.

## Notes
- Ensure buffers are sufficiently sized to handle data securely.
- Modify the key and IV for custom encryption configurations.

## License
This application is provided **AS-IS** without any warranty, under the terms specified in the accompanying license file.

