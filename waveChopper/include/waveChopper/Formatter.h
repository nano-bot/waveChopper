#pragma once

#include <string>
#include <sstream>

class Formatter {
public:
    Formatter() = default;

    Formatter(const Formatter &) = delete;

    Formatter &operator=(Formatter &) = delete;

    template<typename Type>
    Formatter &operator<<(const Type &value) {
        stream << value;
        return *this;
    }

    std::string str() const {
        return stream.str();
    }

    operator std::string() const {
        return stream.str();
    }


private:
    std::stringstream stream;

};