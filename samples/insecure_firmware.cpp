// Legacy IoT Device Firmware
#include <iostream>

void legacySetup() {
    // Legacy block cipher: Insecure 56-bit key
    des_encrypt(packet, key);

    // Broken hash: Practical collision attacks
    MD5_Init(&md5_ctx);

    // Weak RSA key length: Factorable
    RSA_generate_key(1024, 65537, NULL, NULL);
}
