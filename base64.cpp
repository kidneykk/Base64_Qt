#include "base64.h"

base64::base64() {
    // maps initialization
    int i = 0;
    for (char ch = 'A'; ch <= 'Z'; ++ch) { alph64[i] = ch; alph64_inv[ch] = i++; }
    for (char ch = 'a'; ch <= 'z'; ++ch) { alph64[i] = ch; alph64_inv[ch] = i++; }
    for (char ch = '0'; ch <= '9'; ++ch) { alph64[i] = ch; alph64_inv[ch] = i++; }
    alph64[i] = '+'; alph64_inv['+'] = i++;
    alph64[i] = '/'; alph64_inv['/'] = i;
}

void base64::setReadBlockSize(unsigned int size)
{
    _blockSize = size;
}

std::string base64::encode(const std::string& input_str)
{
    if (input_str.empty()) return "";

    using u8 = unsigned char;

    char ch = 0;    // current 6-bit char
    char rem = 0;   // 'remainder'

    std::string encoded;
    for (int i = 0; i < input_str.size(); ++i) {
        switch (i % 3) {
        case 0:
            if (i > 0) encoded += alph64[rem];
            ch = ((u8)input_str[i] >> 2);
            rem = ((u8)input_str[i] << 4) & 0x30;		// 00xx0000
            break;

        case 1:
            ch = ((u8)input_str[i] >> 4) | rem;
            rem = ((u8)input_str[i] << 2) & 0x3C;		// 00xxxx00
            break;

        case 2:
            ch = ((u8)input_str[i] >> 6) | rem;
            rem = (u8)input_str[i] & 0x3F;				// 00xxxxxx
            break;
        }
        encoded += alph64[ch];
    }
    encoded += alph64[rem];
         if (input_str.size() % 3 == 1) encoded += "==";
    else if (input_str.size() % 3 == 2) encoded += '=';

    return encoded;
}

std::string base64::decode(const std::string& encoded)
{
    if (encoded.empty()) return "";

    char ch;    // current char
    char rem;   // 'remainder' - part of next char

    int k = 0;
    std::string decoded;
    for (int i = 0; i < encoded.size() - 1; ++i) {
        switch (k % 3) {
        case 0:
            ch = alph64_inv[encoded[i]] << 2;
            rem = alph64_inv[encoded[i + 1]] >> 4;			// 0000 00xx
            break;

        case 1:
            ch = alph64_inv[encoded[i]] << 4;
            rem = alph64_inv[encoded[i + 1]] >> 2;			// 0000 xxxx
            break;

        case 2:
            ch = alph64_inv[encoded[i]] << 6;
            rem = alph64_inv[encoded[i + 1]];				// 00xx xxxx
            i++;
            break;
        }
        decoded += static_cast<char>(ch | rem);
        k++;
    }

    return decoded;
}
