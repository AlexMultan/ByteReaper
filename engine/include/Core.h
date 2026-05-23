//
// Created by alex on 5/4/26.
//

#pragma once

// Windows Export/Import Macros
#ifdef _WIN32
    #ifdef ENGINE_BUILD_DLL
        #define ENGINE_API __declspec(dllexport)
    #elif defined(ENGINE_STATIC)
        #define ENGINE_API
    #else
        #define ENGINE_API __declspec(dllimport)
    #endif
// Linux/Mac Export Macros (GCC/Clang)
#elif defined(__linux__) || defined(__APPLE__)
    #ifdef ENGINE_BUILD_DLL
        #define ENGINE_API __attribute__((visibility("default")))
    #elif defined(ENGINE_STATIC)
        #define ENGINE_API
    #else
        #define ENGINE_API __attribute__((visibility("default")))
    #endif
#else
    #error "Unsupported platform. Only Windows and Linux are supported."
#endif
