#include <sstream>
#include <vector>

#include "utils.hpp"

#define MMOV_ITER(x) std::make_move_iterator(x)

/*
Generate a vector of strings splitted on a delimiter string.
Effect should be very similar to 'split()' in Python.

If delim.size() > 1, recursively process each char in the string
starting from the start of the string, going towards the end of the string.

If delim.size() == 1, split the string using the single delim char.

If delim.size() == 0, don't do anything (need something to split on).

Example Usage:

    const auto msplits = splits("first:second:third:fourth", ":");

    for(const auto& i : msplits)
        std::cout << i << "\n";
    first
    second
    third
    fourth
*/
std::vector<std::string> splits(const std::string& str, const std::string& delim)
{
    if (delim.size() <= 0)
        return std::vector<std::string>();

    const auto dsplit = [&str](const auto c) {
        std::stringstream ss(str);
        std::vector<std::string> strings;

        while(ss)
        {
            std::string hldr;
            std::getline(ss, hldr, c);
            strings.emplace_back(std::move(hldr));
        }

        return std::vector<std::string>(MMOV_ITER(strings.begin()), MMOV_ITER(strings.end() - 1));
    };

    if(delim.size() == 1)
        return dsplit(delim.at(0));

    const auto join = [](const auto vec_strings) {
        std::stringstream ss;

        for(const auto& string : vec_strings)
            ss << string;

        return ss.str();
    };

    const auto& new_delim = std::string(delim.begin() + 1, delim.end());

    return splits(join(dsplit(delim.at(0))), new_delim);
}
