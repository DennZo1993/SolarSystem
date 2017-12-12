#pragma once

#include <stdexcept>


class TEngineException : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};


class TShaderException : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};