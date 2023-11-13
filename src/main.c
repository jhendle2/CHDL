#include <stdio.h>

#include "chdl/clock.h"
#include "chdl/sim.h"
#include "chdl/registers.h"

TEST_BENCH(regfile_bench) {
    CLOCK_t clock = CLOCK();
    REGFILE_8x8_t regfile = REGFILE_8x8();

    RUN_LENGTH(max_cycles, 64 cycles);
    NEW_SIM(regfile_bench_sim, max_cycles, "Clk", "Write", "Waddr", "Data", "Addr1", "Read1", "Addr2", "Read2");
    NEW_TRACE(regfile_bench_sim, max_cycles);

    SIMULATE(32) {
        PROCESS(clock);
        // PRINT(regfile);
        regfile.clock = clock.clock;

        LOAD(regfile.write_enable, regfile_bench_sim_trace[0]);
        LOAD(regfile.write_addr  , regfile_bench_sim_trace[1]);
        LOAD(regfile.write_data  , regfile_bench_sim_trace[2]);
        LOAD(regfile.read_addr_1 , regfile_bench_sim_trace[3]);
        LOAD(regfile.read_addr_2 , regfile_bench_sim_trace[4]);
        PROCESS(regfile);

        PLOT(regfile_bench_sim[0], clock.clock);
        PLOT(regfile_bench_sim[1], regfile.write_enable);
        PLOT(regfile_bench_sim[2], regfile.write_addr);
        PLOT(regfile_bench_sim[3], regfile.write_data);
        PLOT(regfile_bench_sim[4], regfile.read_addr_1);
        PLOT(regfile_bench_sim[5], regfile.read_data_1);
        PLOT(regfile_bench_sim[6], regfile.read_addr_2);
        PLOT(regfile_bench_sim[7], regfile.read_data_2);
    }

    GRAPH(regfile_bench_sim, 32, "%02x", "", 2);
    PRINT(regfile);
}

int main(int argc, char** argv) {

    // test_bench("traces/reg8.txt");
    regfile_bench("traces/regfile_trace.txt");

    return 0;
}