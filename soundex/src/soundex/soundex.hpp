#pragma once

#include <string_view>

#include <iostream>

union hash {
    char s[5] = {};
    uint32_t n;
};

uint32_t soundex_hash(std::string_view str);
