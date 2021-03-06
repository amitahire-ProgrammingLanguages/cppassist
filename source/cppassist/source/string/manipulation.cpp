
#include <cppassist/string/manipulation.h>

#include <algorithm>


namespace
{


static const char whitespace[] = " \t\n\r\f\v";


}


namespace cppassist
{
namespace string
{


std::string trimRight(const std::string & string)
{
    std::string out = string;

    out.erase(out.find_last_not_of(whitespace) + 1);

    return out;
}

std::string trimLeft(const std::string & string)
{
    std::string out = string;

    out.erase(0, out.find_first_not_of(whitespace));

    return out;
}

std::string trim(const std::string & string, bool removeAllWhitespace)
{
    if (removeAllWhitespace)
    {
        std::string out = string;

        for (unsigned int i = 0; i < 6; ++i)
        {
            out.erase(std::remove(out.begin(), out.end(), whitespace[i]), out.end());
        }

        return out;
    }

    else {
        return trimLeft(trimRight(string));
    }
}

std::string padLeft(const std::string & string, size_t length, char c)
{
    std::string padded = string;
    while (padded.size() < length) padded = c + padded;

    return padded;
}

std::string padRight(const std::string & string, size_t length, char c)
{
    std::string padded = string;
    while (padded.size() < length) padded = padded + c;

    return padded;
}

std::string stripped(const std::string & string, const std::set<char> & blacklist)
{
    auto result = string;
    result.erase(std::remove_if(result.begin(), result.end(), [&blacklist](char x) {
        return blacklist.count(x) > 0; }), result.end());

    return result;
}

std::vector<std::string> parseArray(const std::string & string, size_t size)
{
    std::vector<std::string> result;

    // Skip whitespace
    auto pos = string.find_first_not_of(whitespace);
    if (pos == std::string::npos)
        return result;

    // Expect '('
    if (string[pos] != '(')
        return result;

    // Position at the first element
    pos++;

    // Parse elements
    for (size_t i=0; i<size; i++)
    {
        // Abort if we read beyond the end of the string
        if (pos >= string.size())
            break;

        // Get position of next ',' or ')' for the last element
        auto rpos = ((i == size - 1) ? string.find(")", pos) : string.find(",", pos));
        if (rpos == std::string::npos)
            break;

        // Get substring
        std::string element = string.substr(pos, rpos - pos);
        result.push_back(trim(element));

        // Next element
        pos = rpos + 1;
    }

    return result;
}

std::vector<std::string> split(const std::string & input, char delimiter)
{
    std::vector<std::string> result;
    std::string line;
    std::stringstream ss(input);

    while(std::getline(ss, line, delimiter))
    {
        if (!line.empty())
        {
            result.push_back(line);
        }
    }

    return result;
}

bool contains(const std::string & string, const std::string & containsstring)
{
    return string.find(containsstring) != std::string::npos;
}

bool hasPrefix(const std::string & string, const std::string & prefix)
{
    return string.find(prefix) == 0;
}

bool hasSuffix(const std::string & string, const std::string & suffix)
{
    return string.size() >= suffix.size() && string.compare(string.size() - suffix.size(), suffix.size(), suffix) == 0;
}


} // namespace string
} // namespace cppassist
