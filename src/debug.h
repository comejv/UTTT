#ifndef DEBUG_H
#define DEBUG_H

#include <stdio.h>

int DEBUG = 0;

// Info macro with colors
#define INFO_LOG(fmt, ...)                                              \
    do                                                                  \
    {                                                                   \
        fprintf(stderr, "\033[0;32mINFO: %s:%d:%s(): " fmt "\033[0m\n", \
                __FILE__, __LINE__, __func__, ##__VA_ARGS__);           \
    } while (0)

// Debug macro with colors
#define DEBUG_LOG(fmt, ...)                                                  \
    do                                                                       \
    {                                                                        \
        if (DEBUG)                                                           \
        {                                                                    \
            fprintf(stderr, "\033[0;33mDEBUG: %s:%d:%s(): " fmt "\033[0m\n", \
                    __FILE__, __LINE__, __func__, ##__VA_ARGS__);            \
        }                                                                    \
    } while (0)

// Error macro with colors
#define ERROR_LOG(fmt, ...)                                              \
    do                                                                   \
    {                                                                    \
        fprintf(stderr, "\033[0;31mERROR: %s:%d:%s(): " fmt "\033[0m\n", \
                __FILE__, __LINE__, __func__, ##__VA_ARGS__);            \
    } while (0)

#endif // DEBUG_H