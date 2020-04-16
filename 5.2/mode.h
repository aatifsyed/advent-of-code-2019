#define POSITION_MODE  0
#define IMMEDIATE_MODE 1

#define CHECK_MODE(X) \
    switch (X) \
    { \
    case POSITION_MODE: \
    case IMMEDIATE_MODE: \
        break; \
    default: \
        printf("ERROR! Invalid Mode\n"); \
        break; \
    } 
