#ifndef ENKRIPSI_HPP
#define ENKRIPSI_HPP

#include "cryptopp/osrng.h"
#include "cryptopp/cryptlib.h"
#include "cryptopp/hex.h"
#include "cryptopp/filters.h"
#include "cryptopp/idea.h"
#include "cryptopp/modes.h"
#include "cryptopp/secblock.h"

class Enkripsi
{
public:
    Enkripsi();
    static Enkripsi *Instance();
    const std::string encrypt(std::string_view plain);
    const std::string decrypt(std::string_view enc);
private:
    CryptoPP::AutoSeededRandomPool prng;
    CryptoPP::SecByteBlock key{CryptoPP::IDEA::DEFAULT_KEYLENGTH};
    CryptoPP::byte iv[CryptoPP::IDEA::BLOCKSIZE];
    std::string plain;
    std::string cipher, encoded, recovered;
};

#endif // ENKRIPSI_HPP
