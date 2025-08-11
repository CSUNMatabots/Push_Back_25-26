#pragma once


// ===== Defaults & Internal Logic =====
#if !defined(BLACK_BOT) && !defined(RED_BOT)
    #define BLACK_BOT
#endif

#if defined(BLACK_BOT)
    #define BLACK_BOT
#elif defined(RED_BOT)
    #define RED_BOT
#else
    #error "One of BLACK_BOT or RED_BOT must be defined"
#endif
