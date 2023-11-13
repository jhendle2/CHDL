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

    GRAPH(d_latch_sim, 64, "%c", "", 1);
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
    
    GRAPH(clock_sim, 64, "%c", "", 1);
}

TEST_BENCH(debounced_clock_bench) {
    CLOCK_t   clock   = CLOCK();
    D_LATCH_t d_latch = D_LATCH();

    RUN_LENGTH(max_run_length, 64);
    NEW_SIM   (debounced_d_latch_sim, max_run_length, "Clock", "Data", "Enable", "Q", "Q_inv");

    SIMULATE(64) {
        PROCESS(clock);

        d_latch.data=clock.clock;
        d_latch.enable=clock.clock;

        PROCESS(d_latch);
        
        PLOT(debounced_d_latch_sim[0], clock.clock);
        PLOT(debounced_d_latch_sim[1], d_latch.data);
        PLOT(debounced_d_latch_sim[2], d_latch.enable);
        PLOT(debounced_d_latch_sim[3], d_latch.q);
        PLOT(debounced_d_latch_sim[4], d_latch.q_inv);
    }

    GRAPH(debounced_d_latch_sim, 64, "%c", "", 1);
    // SAVE(full_adder_0_sim, max_run_length);
}

TEST_BENCH(double_debounced_clock_bench) {
    CLOCK_t   clock     = CLOCK();
    D_LATCH_t d_latch_0 = D_LATCH();
    D_LATCH_t d_latch_1 = D_LATCH();

    RUN_LENGTH(max_run_length, 64);
    NEW_SIM   (double_debounced_d_latch_sim, max_run_length, "Clock", "Data0", "Enable0", "Q0", "Q_inv0", "Data1", "Enable1", "Q1", "Q_inv1");

    SIMULATE(64) {
        PROCESS(clock);

        d_latch_0.data  =clock.clock;
        d_latch_0.enable=clock.clock;

        d_latch_1.data  =d_latch_0.data;
        d_latch_1.enable=d_latch_0.enable;
        
        PROCESS(d_latch_0);
        PROCESS(d_latch_1);
        
        PLOT(double_debounced_d_latch_sim[0], clock.clock);

        PLOT(double_debounced_d_latch_sim[1], d_latch_0.data);
        PLOT(double_debounced_d_latch_sim[2], d_latch_0.enable);
        PLOT(double_debounced_d_latch_sim[3], d_latch_0.q);
        PLOT(double_debounced_d_latch_sim[4], d_latch_0.q_inv);
        
        PLOT(double_debounced_d_latch_sim[5], d_latch_1.data);
        PLOT(double_debounced_d_latch_sim[6], d_latch_1.enable);
        PLOT(double_debounced_d_latch_sim[7], d_latch_1.q);
        PLOT(double_debounced_d_latch_sim[8], d_latch_1.q_inv);
    }

    GRAPH(double_debounced_d_latch_sim, 64, "%c", "", 1);
    // SAVE(full_adder_0_sim, max_run_length);
}

TEST_BENCH(double_debounced_clock_bench_v2) {
    CLOCK_t   clock   = CLOCK();
    DOUBLE_D_LATCH_t dd_latch = DOUBLE_D_LATCH();

    RUN_LENGTH(max_run_length, 64);
    NEW_SIM   (debounced_dd_latch_sim, max_run_length, "Clock", "Data", "Enable", "Q", "Q_inv");

    SIMULATE(64) {
        PROCESS(clock);

        dd_latch.data=clock.clock;
        dd_latch.enable=clock.clock;

        PROCESS(dd_latch);
        
        PLOT(debounced_dd_latch_sim[0], clock.clock);
        PLOT(debounced_dd_latch_sim[1], dd_latch.data);
        PLOT(debounced_dd_latch_sim[2], dd_latch.enable);
        PLOT(debounced_dd_latch_sim[3], dd_latch.q);
        PLOT(debounced_dd_latch_sim[4], dd_latch.q_inv);
    }

    GRAPH(debounced_dd_latch_sim, 64, "%c", "", 1);
    // SAVE(full_adder_0_sim, max_run_length);
}

// int main(int argc, char** argv) {
    
//     // sr_latch_bench("traces/sr_latch.txt");
//     d_latch_bench ("traces/d_latch.txt" );
//     debounced_clock_bench(NULL);
//     double_debounced_clock_bench(NULL);
//     double_debounced_clock_bench_v2(NULL);

//     // clock_bench(NULL);

//     // full_adder_0_test_bench("traces/sim0.txt");
//     // full_adder_0_test_bench("traces/sim1.txt");

//     return 0;
// }