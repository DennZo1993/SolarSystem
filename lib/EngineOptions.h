#pragma once

#include "Option.incl"


// Window options.
struct TWindowOptions {
    using TSelf = TWindowOptions;

    OPTION(size_t,      Height);
    OPTION(size_t,      Width);
    OPTION(std::string, Caption);
};


// Engine options.
struct TEngineOptions {
};


#undef OPTION