#pragma once

enum class Chirality { R, L };

struct Damage {
    public:
        uint16_t amount;
        Chirality chirality;
};
