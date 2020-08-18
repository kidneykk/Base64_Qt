#ifndef BASE64_H
#define BASE64_H

#include <unordered_map>
#include <string>

class base64
{
private:
    std::unordered_map<int, char> alph64;
    std::unordered_map<char, int> alph64_inv;

    unsigned int _blockSize{ 64U };

public:
    explicit base64();

    void setReadBlockSize(unsigned int size);

    std::string encode(const std::string& input_str);   // return encoded string
    std::string decode(const std::string& input_str);   // return decoded string
};

#endif // BASE64_H
