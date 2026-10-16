// Simulated firmware module: sensor data pipeline
#include <iostream>

void encryptSensorReading(unsigned char* data, unsigned char* key) {
    AES256_encrypt(data, key);
}

void signFirmwareUpdate(unsigned char* update, unsigned char* privateKey) {
    RSA2048_sign(update, privateKey);
}

void hashSensorCalibration(unsigned char* calibrationData) {
    SHA256(calibrationData);
}
