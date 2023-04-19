// Github link:
// https://github.com/catalinasirbu/ChangeOrderBits_computation.git

// Output:
// Ran in 873032 microseconds = 0.8 seconds

// CPU used: Intel(R) Core(TM) i7-6700HQ CPU @ 2.60GHz
// gcc (x86_64-posix-seh-rev2, Built by MinGW-W64 project) 12.2.0

#include <iostream>
#include <chrono>
#include <bitset>

#define VECTOR_SIZE (100*1000*1000UL)
uint32_t t[VECTOR_SIZE];

static inline void swapu32(uint32_t& u) {
    u = ((u & 0x55555555) << 1) | ((u & 0xAAAAAAAA) >> 1);
    u = ((u & 0x33333333) << 2) | ((u & 0xCCCCCCCC) >> 2);
    u = ((u & 0x0F0F0F0F) << 4) | ((u & 0xF0F0F0F0) >> 4);
    u = ((u & 0x00FF00FF) << 8) | ((u & 0xFF00FF00) >> 8);
    u = ((u & 0x0000FFFF) << 16) | ((u & 0xFFFF0000) >> 16);
}

void init() {
    for (uint32_t i = 0; i < VECTOR_SIZE; i++) {
        t[i] = rand();
    }
}

uint64_t getMilliseconds() {
    return std::chrono::duration_cast<std::chrono::microseconds>(
            std::chrono::high_resolution_clock::now().time_since_epoch())
            .count();
}

void init_lut8() {
    uint8_t lut8[256] = {0};
    for (int i = 0; i < 256; i++) {
        lut8[i] |= ((i & 0x01) << 7); // bit0
        lut8[i] |= ((i & 0x02) << 5); // bit1
        lut8[i] |= ((i & 0x04) << 3); // bit2
        lut8[i] |= ((i & 0x08) << 1); // bit3
        lut8[i] |= ((i & 0x10) >> 1); // bit4
        lut8[i] |= ((i & 0x20) >> 3); // bit5
        lut8[i] |= ((i & 0x40) >> 5); // bit6
        lut8[i] |= ((i & 0x80) >> 7); // bit7
    }
}

int main() {
    std::cout << "Started " << std::endl;
    init();
    std::cout << "Init done " << std::endl;

    t[0] = 3;
    std::bitset<32> bs1(t[0]);

    auto tstart = getMilliseconds();
    for (uint32_t i = 0; i < VECTOR_SIZE; i++) {
        swapu32(t[i]);
    }
    auto tstop = getMilliseconds();

    std::bitset<32> bs2(t[0]);
    std::cout << bs1 << std::endl;
    std::cout << bs2 << std::endl;

    std::cout << "Ran in " << (tstop - tstart) << " microseconds"  << std::endl;
    return 0;
}