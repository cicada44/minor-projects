#include <soundex/soundex.hpp>

#include <csv.hpp>
#include <pugixml.hpp>

#include <map>
#include <set>

#include <iostream>

namespace {

using HashToStrs = std::map<std::string, std::set<std::string>>;

[[maybe_unused]] void outputHashes(const HashToStrs &strs) {
    for (const auto &[hash, names] : strs) {
        std::cout << hash << '\n';
        for (const auto &name : names) {
            std::cout << '\t' << name << '\n';
        }
        std::cout << '\n';
    }
}

}  // namespace

int main() {
    csv::CSVReader csv_file = csv::CSVReader("names2020.csv");
    std::string name;

    HashToStrs hashNames;

    for (auto &row : csv_file) {
        name = row["name"];
        name = name.substr(name.find_first_of(' ') + 1);
        hash h{.n = soundex_hash(name)};
        hashNames[h.s].insert(name);
    }

    // outputHashes(hashNames);

    pugi::xml_document doc;
    pugi::xml_node node = doc.append_child("soundex");
    for (const auto &[hashStr, names] : hashNames) {
        pugi::xml_node namesNode = node.append_child("names");
        namesNode.append_attribute("hash") = hashStr.c_str();
        for (const auto &name : names) {
            pugi::xml_node nameNode = namesNode.append_child("name");
            nameNode.append_child(pugi::node_pcdata).set_value(name.c_str());
        }
    }

    doc.print(std::cout);
}
