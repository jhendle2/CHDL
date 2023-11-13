#ifndef HDL_H
#define HDL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <stdbool.h>

typedef unsigned int uint;

#define QUOTE(X)  #X
#define CAT(A, B) A##B

#define LOW      0
#define HIGH     1
#define UNDEF    2
#define DONTCARE 3

typedef uint Bit_t;
#define NEW_BIT(NAME) Bit_t NAME: 2
typedef uint Nibl_t;
#define NEW_NIBL(NAME) Nibl_t NAME: 4
typedef uint Byte_t;
#define NEW_BYTE(NAME) Byte_t NAME: 8

static inline Bit_t assignBitFromUint(const uint U) {
    switch (U) {
        case 0 : return LOW;
        case 1 : return HIGH;
        default: return UNDEF;
    }
}
#define ASSIGN(A, B) A=assignBitFromUint(B)

typedef unsigned long long GateFields;
#define GATE_FIELDS GateFields _fields: 64

// typedef struct gate_s {
//     GATE_FIELDS;

//     void (*process)(struct gate_s* self);
//     void (*print  )(const struct gate_s* self);
// } Gate_t;

#define STRUCT_FIELDS(FIELD_LIST) \
    union {\
        GATE_FIELDS;\
        struct {\
            FIELD_LIST\
        };\
    }

// #define INPUT(NAME)  printf("input (%s)=%u\n", QUOTE(NAME), self->NAME)
// #define OUTPUT(NAME) printf("output(%s)=%u\n", QUOTE(NAME), self->NAME)
#define INPUT(NAME)  printf("<%s<\t%u\n", QUOTE(NAME), self->NAME)
#define OUTPUT(NAME) printf(">%s>\t%u\n", QUOTE(NAME), self->NAME)

#define NEW_GATE(NAME, GATE_FIELDS, INITS, FUNC_BODY, PRINT_LIST) \
    struct CAT(NAME, _s);\
    \
    static inline void CAT(process_,NAME)(struct CAT(NAME, _s)* self);\
    \
    typedef struct CAT(NAME,_s) {\
        STRUCT_FIELDS(\
            GATE_FIELDS\
        );\
        void (*process)(struct CAT(NAME,_s)* self);\
        void (*print  )(const struct CAT(NAME,_s)* self);\
    } CAT(NAME,_t);\
    \
    static inline void CAT(process_,NAME)(struct CAT(NAME, _s)* self) {FUNC_BODY}\
    \
    static inline void CAT(print_,NAME)(const CAT(NAME,_t)* self) {\
        printf("(%s)\n", QUOTE(NAME));\
        PRINT_LIST\
        printf("\n");\
    }\
    \
    static inline CAT(NAME,_t) NAME() {\
        CAT(NAME,_t) temp;\
        CAT(NAME,_t)* self=&temp;\
        self->process=CAT(process_,NAME);\
        self->print=CAT(print_,NAME);\
        INITS;\
        return temp;\
    }

#define NEW(GATE, NAME) CAT(GATE,_t) NAME = GATE()
#define STATIC(GATE, NAME) \
    static CAT(GATE,_t) NAME;\
    StaticFlag CAT(NAME,_init)=NOT_INITIALIZED;\
    if (CAT(NAME,_init)==NOT_INITIALIZED) {\
        NAME = GATE();\
        CAT(NAME,_init)=INITIALIZED;\
    }

        //     return (CAT(NAME,_t)){._fields=0xAAAAAAAAAAAAAAAA, .process=CAT(process_,NAME), .print=CAT(print_,NAME)};
        // /*return (CAT(NAME,_t)){._fields=0xFFFFFFFFFFFFFFFF, .process=CAT(process_,NAME), .print=CAT(print_,NAME)};*/

#define NAME(N)   N
#define FIELDS(F) F
#define BODY(B)   B
#define INIT(I)   I
#define LOG(L)    L

// #define INPUTS
// #define OUTPUTS

// #define PROCESS(G) process(&G)
#define PROCESS(G) G.process(&G)
/* #define PRINT(G)   {\
//     printf("%s ", QUOTE(G));\
//     print(&G);\
// } */
#define PRINT(G)   {\
    printf("%s ", QUOTE(G));\
    G.print(&G);\
}

static inline Bit_t NOT(const Bit_t bit) {
    switch (bit) {
        case LOW: return HIGH;
        case HIGH: return LOW;
        case DONTCARE: return DONTCARE;
        default: case UNDEF: return UNDEF;
    }
}
// #define NOT(X) (~(X))
// #define NOT(X) (!(X))

typedef enum InitFlag {
    NOT_INITIALIZED=0,
    INITIALIZED=1
} InitFlag;

#define StaticFlag static InitFlag 

#endif /* HDL_H */