#ifndef MODE_H
#define MODE_H

#define POSITION_MODE  0
#define IMMEDIATE_MODE 1
#define RELATIVE_MODE  2

#define CHECK_MODE(X) \
    switch (X) \
    { \
    case POSITION_MODE:  \
    case IMMEDIATE_MODE: \
    case RELATIVE_MODE:  \
        break; \
    default: \
        printf("ERROR! Invalid Mode\n"); \
        break; \
    } 

#endif