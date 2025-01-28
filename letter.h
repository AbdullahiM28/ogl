#ifndef LETTER.H
#define LETTER.H

#include <array>

class Letter {
    protected:
        std::array<int, 16> bitmap;
    public:
        Letter(std::array<int, 8> bitmap) : bitmap(bitmap) {}
        virtual std::array<int, 8> geBitMap() { return bitmap; }
        virtual ~Letter();
}

#endif