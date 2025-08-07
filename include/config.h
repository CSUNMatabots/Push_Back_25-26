#pragma once

// Always define one bot if neither is specified by build flags
#if !defined(BLACK_BOT) && !defined(RED_BOT)
    // Default to BLACK_BOT
    #define BLACK_BOT
#endif

// Internal logic used by the rest of the codebase
#if defined(BLACK_BOT)
    #define USE_BLACK_BOT
#elif defined(RED_BOT)
    #define USE_RED_BOT
#else
    #error "One of BLACK_BOT or RED_BOT must be defined"
#endif
