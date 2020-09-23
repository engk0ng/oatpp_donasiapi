#include "enkripsi.hpp"
#include <iostream>

static Enkripsi *_instance = nullptr;

Enkripsi::Enkripsi()
{
    prng.GenerateBlock(key, key.size());
    prng.GenerateBlock(iv, sizeof (iv));

    encoded.clear();

    CryptoPP::HexEncoder *hexEncoder = new CryptoPP::HexEncoder(new CryptoPP::StringSink(encoded));
    CryptoPP::StringSource(key, key.size(), hexEncoder);

    encoded.clear();

    CryptoPP::HexEncoder *hexEncoder1 = new CryptoPP::HexEncoder(new CryptoPP::StringSink(encoded));
    CryptoPP::StringSource(iv, sizeof (iv), true, hexEncoder1);

    encoded.clear();
    CryptoPP::HexEncoder *hexEncoder2 = new CryptoPP::HexEncoder(new CryptoPP::StringSink(encoded));
    CryptoPP::StringSource(iv, sizeof (iv), true, hexEncoder2);
}

Enkripsi *Enkripsi::Instance() {
    if (_instance == nullptr) {
        _instance = new Enkripsi();
    }
    return _instance;
}

const std::string Enkripsi::encrypt(std::string_view plain) {
    encoded.clear();
    try {
        CryptoPP::CBC_Mode<CryptoPP::IDEA>::Encryption e;
        e.SetKeyWithIV(key, key.size(), iv);
        cipher.clear();
        CryptoPP::StringSource(plain.data(), true, new CryptoPP::StreamTransformationFilter(e, new CryptoPP::StringSink(cipher)));
    } catch (const CryptoPP::Exception &e) {
        std::cerr << e.what() << std::endl;
    }

    encoded.clear();
    CryptoPP::StringSource(cipher, true, new CryptoPP::HexEncoder(new CryptoPP::StringSink(encoded)));
    return encoded;
}

const std::string Enkripsi::decrypt(std::string_view enc) {
    cipher.clear();
    CryptoPP::StringSource(enc.data(), true, new CryptoPP::HexDecoder(new CryptoPP::StringSink(cipher)));
    try {
        CryptoPP::CBC_Mode<CryptoPP::IDEA>::Decryption d;
        d.SetKeyWithIV(key, key.size(), iv);
        recovered.clear();
        CryptoPP::StringSource(cipher, true, new CryptoPP::StreamTransformationFilter(d, new CryptoPP::StringSink(recovered)));
    } catch (const CryptoPP::Exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return recovered;
}
