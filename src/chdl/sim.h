#ifndef SIM_H
#define SIM_H

#include "hdl.h"

typedef unsigned long long SimTime;
#define MAX_LABEL_SZ 16
#define NEW_SIM(NAME, LENGTH, ...)   uint NAME[64][LENGTH]; const char CAT(NAME,_labels)[MAX_LABEL_SZ][64] = {__VA_ARGS__, "\0"};

#define RUN_LENGTH(NAME, VALUE) const SimTime NAME = VALUE
#define SIMULATE(LENGTH) for (SimTime CLK = 0; CLK < LENGTH; CLK++)

static inline char simPrintChar(const uint sim_value) {
    switch (sim_value) {
        case DONTCARE: return 'X';
        case HIGH:     return '1';
        // case LOW:      return '.';
        case LOW:      return '_';
        default:
        case UNDEF:    return '?';
    }
}

static inline void simPrint(FILE* fp, const uint sim_value, const char* fmt, const char* delim, const size_t fmt_len) {
    // fprintf(fp, "%c", simPrintChar(sim_value));

    // if (sim_value == 0) fprintf(fp, "..|");
    // else fprintf(fp, "%02x|", sim_value);

    if (fmt_len == 1) {
        if (sim_value == 0) fprintf(fp, ".%s", delim);
        else                fprintf(fp, "%c%s", simPrintChar(sim_value), delim);
    }
    else {
        if (sim_value == 0) for (uint i = 0; i<fmt_len; i++) putc('.', fp);
        else fprintf(fp, fmt, sim_value);
        // fprintf(fp, fmt, sim_value);
        fprintf(fp, "%s", delim);
    }
}

#define OUTPLOT_HELPER(NAME, LENGTH, FP, FMT, DELIM, FMT_LEN) \
    fprintf(FP, "[%s]\n", TRACE_PATH);\
    for (uint _field_i = 0; _field_i < 64; _field_i++) {\
        if (CAT(NAME,_labels)[_field_i][0]==0) break;\
        fprintf(FP, "%-8s: ", CAT(NAME,_labels)[_field_i]);\
        for (SimTime CLK = 0; CLK<LENGTH; CLK++) {\
            simPrint(FP, NAME[_field_i][CLK], FMT, DELIM, FMT_LEN);\
        } fprintf(FP, "\n");\
    } fprintf(FP, "\n");

#define GRAPH(NAME, LENGTH, FMT, DELIM, FMT_LEN) OUTPLOT_HELPER(NAME, LENGTH, stdout, FMT, DELIM, FMT_LEN)

#define SAVE(NAME, LENGTH, FMT, DELIM, FMT_LEN) {\
    char save_path[128];\
    sprintf(save_path, "%s.stdout", TRACE_PATH);\
    FILE* save_fp = fopen(save_path, "w");\
    OUTPLOT_HELPER(NAME, LENGTH, save_fp, FMT, DELIM, FMT_LEN);\
    if (save_fp) fclose(save_fp);\
}

#define LOAD(ARG, VALUE) ARG = VALUE[CLK]
#define PLOT(ARG, VALUE) ARG[CLK] = VALUE

#define TEST_BENCH(NAME) void NAME(const char* TRACE_PATH)

#define BAD_TRACE_READ -1
#define NEW_TRACE(NAME, LENGTH)\
    uint CAT(NAME,_trace)[64][LENGTH];\
    SimTime status = load_from_trace(CAT(NAME,_trace), TRACE_PATH);\
    if (status == BAD_TRACE_READ) {\
        printf("[ERRO] Unable to simulate!\n");\
        return;\
    }

static inline SimTime load_from_trace(uint trace_array[64][64], const char* trace_path) {
    FILE* trace_fp = fopen(trace_path, "r");
    if (trace_fp == NULL) {
        printf("[ERRO] Trace path `%s` does not exist!\n", trace_path);
        return BAD_TRACE_READ;
    }

    SimTime clk = 0;
    char buf[256];
    fgets(buf, 128, trace_fp); /* Skips label row */

    while (fgets(buf, 128, trace_fp) != NULL) {
        const uint len = strlen(buf);
        if (buf[0] == '\n') continue; /* Ignores blank lines for spacing */
        if (buf[0] == '#')  continue; /* Ignores lines beginning with comment character */
        if (buf[len-1] == '\n') buf[len-1] = 0;
        char* tok = strtok(buf, ",");
        uint field_index = 0;
        while (tok) {
            if (tok[0]=='0' && tok[1]=='x') {
                trace_array[field_index++][clk] = strtol(tok+2, NULL, 16);
            }
            else {
                trace_array[field_index++][clk] = atoi(tok);
            }
            tok = strtok(NULL, ",");
        }
        clk++;
    }

    fclose(trace_fp);
    return clk;
}

#define cycles

#endif /* SIM_H */