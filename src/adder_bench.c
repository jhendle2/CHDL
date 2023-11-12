#include "chdl/gates.h"
#include "chdl/adders.h"

#include "adder_bench.h"

TEST_BENCH(full_adder_0_test_bench) {
    FULL_ADDER_t full_adder_0 = FULL_ADDER();

    RUN_LENGTH(max_run_length  , 64);
    NEW_SIM   (full_adder_0_sim, max_run_length, "A", "B", "Ci", "S", "Co");
    NEW_TRACE (full_adder_0_sim, max_run_length);

    SIMULATE(max_run_length) {
        LOAD(full_adder_0.a   , full_adder_0_sim_trace[0]);
        LOAD(full_adder_0.b   , full_adder_0_sim_trace[1]);
        LOAD(full_adder_0.c_in, full_adder_0_sim_trace[2]);

        PROCESS(full_adder_0);
        
        PLOT(full_adder_0_sim[0], full_adder_0.a    );
        PLOT(full_adder_0_sim[1], full_adder_0.b    );
        PLOT(full_adder_0_sim[2], full_adder_0.c_in );
        PLOT(full_adder_0_sim[3], full_adder_0.sum  );
        PLOT(full_adder_0_sim[4], full_adder_0.c_out);
    }

    GRAPH(full_adder_0_sim, max_run_length);
    // SAVE(full_adder_0_sim, max_run_length);
}
