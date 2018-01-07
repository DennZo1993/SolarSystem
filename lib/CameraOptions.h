#pragma once

#include "Option.incl"


struct TCameraOptions {
    using TSelf = TCameraOptions;

    OPTION_DEFAULT(float, FOV, 45.0f);
    OPTION(size_t, ResolutionX);
    OPTION(size_t, ResolutionY);
    OPTION(float,  ZNear);
    OPTION(float,  ZFar);
};


#undef OPTION