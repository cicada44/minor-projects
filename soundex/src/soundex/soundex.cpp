#include <soundex/soundex.hpp>

#include <algorithm>
#include <string>
#include <string_view>
#include <unordered_map>

#include <iostream>

namespace {

inline const std::unordered_map<char, char> letterToDigit{
    {'b', '1'}, {'f', '1'}, {'p', '1'}, {'v', '1'}, {'c', '2'}, {'g', '2'},
    {'j', '2'}, {'k', '2'}, {'q', '2'}, {'s', '2'}, {'x', '2'}, {'z', '2'},
    {'d', '3'}, {'t', '3'}, {'l', '4'}, {'m', '5'}, {'n', '5'}, {'r', '6'}};

bool isVowel(char c) {
    return (c == 'i' || c == 'a' || c == 'e' || c == 'o' || c == 'u' || c == 'y');
}

}  // namespace

uint32_t soundex_hash(std::string_view str) {
    std::string result(str);
    char firstLetter = str.at(0);
    result.erase(std::remove_if(std::next(result.begin()), result.end(),
                                [](char c) { return (c == 'h' || c == 'w'); }),
                 result.end());
    std::for_each(std::next(result.begin()), result.end(), [](char& c) {
        if (!isVowel(c) && !isdigit(c)) c = letterToDigit.at(c);
    });
    result.erase(
        std::unique(result.begin(), result.end(), [](char c, char d) { return c == d; }),
        result.end());
    result.erase(std::remove_if(std::next(result.begin()), result.end(),
                                [](char c) { return isVowel(c); }),
                 result.end());
    result.at(0) = std::toupper(firstLetter);
    result.reserve(5);
    while (result.size() < 4) result += '0';
    return *reinterpret_cast<const uint32_t*>(result.c_str());
}
