#include <iostream>
#include <cstring>
#include <vector>
using namespace std;
void xorBlock(const unsigned char *input, const unsigned char *key, unsigned char *output, int size) {
    for (int i = 0; i < size; ++i) {
        output[i] = input[i] ^ key[i];
    }
}
void simpleAES_Encrypt(const string &plaintext, const string &key, vector<unsigned char> &ciphertext) {
    int blockSize = key.size(); // Assume the key size determines the block size
    vector<unsigned char> block(blockSize);
    
    ciphertext.resize(plaintext.size());
    for (size_t i = 0; i < plaintext.size(); i += blockSize) {
        memcpy(block.data(), plaintext.c_str() + i, blockSize);
        xorBlock(block.data(), reinterpret_cast<const unsigned char *>(key.c_str()), ciphertext.data() + i, blockSize);
    }
}
void simpleAES_Decrypt(const vector<unsigned char> &ciphertext, const string &key, string &plaintext) {
    int blockSize = key.size(); // Assume the key size determines the block size
    vector<unsigned char> block(blockSize);
    
    plaintext.resize(ciphertext.size());
    for (size_t i = 0; i < ciphertext.size(); i += blockSize) {
        xorBlock(ciphertext.data() + i, reinterpret_cast<const unsigned char *>(key.c_str()), reinterpret_cast<unsigned char *>(&plaintext[i]), blockSize);
    }
}
int main() {
    string plaintext = "HelloWorld123456"; // Exactly 16 bytes
    string key = "ThisIsASecretKey";      // Exactly 16 bytes
    vector<unsigned char> ciphertext;
    string decryptedText;

    cout << "Plaintext: " << plaintext << endl;

    simpleAES_Encrypt(plaintext, key, ciphertext);
    cout << "Ciphertext: ";
    for (unsigned char c : ciphertext) {
        cout << hex << (int)c << " ";
    }
    cout << endl;

    simpleAES_Decrypt(ciphertext, key, decryptedText);
    cout << "Decrypted Text: " << decryptedText << endl;
    return 0;
}