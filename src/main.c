#include <stdio.h>

// #include "adder_bench.h"
#include "chdl/latches.h"
#include "chdl/clock.h"
#include "chdl/sim.h"

// TEST_BENCH(sr_latch_bench) {
//     SR_LATCH_t sr_latch = SR_LATCH();

//     RUN_LENGTH(max_run_length  , 64);
//     NEW_SIM   (sr_latch_sim, max_run_length, "R", "S", "Q", "Q_inv");
//     NEW_TRACE (sr_latch_sim, max_run_length);

//     SIMULATE(64) {
//         LOAD(sr_latch.s, sr_latch_sim_trace[0]);
//         LOAD(sr_latch.r, sr_latch_sim_trace[1]);

//         PROCESS(sr_latch);
        
//         PLOT(sr_latch_sim[0], sr_latch.s);
//         PLOT(sr_latch_sim[1], sr_latch.r);
//         PLOT(sr_latch_sim[2], sr_latch.q);
//         PLOT(sr_latch_sim[3], sr_latch.q_inv);
//     }

//     GRAPH(sr_latch_sim, 64);
// }

TEST_BENCH(d_latch_bench) {
    D_LATCH_t d_latch = D_LATCH();

    RUN_LENGTH(max_run_length  , 64);
    NEW_SIM   (d_latch_sim, max_run_length, "Data", "Enable", "Q", "Q_inv");
    NEW_TRACE (d_latch_sim, max_run_length);

    SIMULATE(64) {
        LOAD(d_latch.data  , d_latch_sim_trace[0]);
        LOAD(d_latch.enable, d_latch_sim_trace[1]);

        PROCESS(d_latch);
        
        PLOT(d_latch_sim[0], d_latch.data);
        PLOT(d_latch_sim[1], d_latch.enable);
        PLOT(d_latch_sim[2], d_latch.q);
        PLOT(d_latch_sim[3], d_latch.q_inv);
    }

    GRAPH(d_latch_sim, 64);
    // SAVE(full_adder_0_sim, max_run_length);
}

TEST_BENCH(clock_bench) {
    CLOCK_t clock = CLOCK();

    RUN_LENGTH(max_run_length, 64);
    NEW_SIM(clock_sim, max_run_length, "Clock");

    SIMULATE(64) {
        PROCESS(clock);
        PLOT(clock_sim[0], clock.clock);
    }
    
    GRAPH(clock_sim, 64);
}

int main(int argc, char** argv) {
    
    // sr_latch_bench("traces/sr_latch.txt");
    d_latch_bench ("traces/d_latch.txt" );

    clock_bench(NULL);

    // full_adder_0_test_bench("traces/sim0.txt");
    // full_adder_0_test_bench("traces/sim1.txt");

    return 0;
}