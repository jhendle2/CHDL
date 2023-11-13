#include <stdio.h>

// #include "chdl/latches.h"
#include "chdl/clock.h"
#include "chdl/sim.h"

NEW_GATE(
    NAME(XOR8),

    FIELDS(
        NEW_BYTE(a);
        NEW_BYTE(b);
        NEW_BYTE(q);
    ),
    
    INIT(
        self->a=0;
        self->b=0;
        self->q=0;
    ),

    BODY(
        self->q = self->a ^ self->b;
    ),

    LOG(
        INPUT(a);
        INPUT(b);
        OUTPUT(q);
    )
)

NEW_GATE(
    NAME(REG8),

    FIELDS(
        /* INPUTS */
        NEW_BYTE(data_in);
        NEW_BIT(enable);
        NEW_BIT(clk);
        
        /* OUTPUTS */
        NEW_BYTE(data_out);
    ),

    INIT(
        self->data_in  = 0x00;
        self->enable   = LOW;
        self->clk      = LOW;
        self->data_out = 0x00;
    ),

    BODY(
        if (self->clk == HIGH && self->enable == HIGH) {
            self->data_out = self->data_in;
        }
    ),

    LOG(
        INPUT(data_in);
        INPUT(enable);
        INPUT(clk);
        OUTPUT(data_out);
    )
)

TEST_BENCH(test_bench) {
    CLOCK_t clock = CLOCK();
    REG8_t  reg8  = REG8();
    REG8_t  clock2 = REG8();
    REG8_t  clock4 = REG8();

    RUN_LENGTH(max_cycles, 64 cycles);
    NEW_SIM(test_bench_sim, max_cycles, "Clk", "Clk2", "Clk4", "Data_in", "Enable", "Data_Out");
    NEW_TRACE(test_bench_sim, max_cycles);

    SIMULATE(16) {
        PROCESS(clock);
        
        LOAD(reg8.data_in, test_bench_sim_trace[0]);
        LOAD(reg8.enable , test_bench_sim_trace[1]);
        reg8.clk = clock.clock;
        PROCESS(reg8);

        clock2.data_in = clock.clock ^ clock2.data_out;
        clock2.enable  = clock.clock;
        clock2.clk     = clock.clock;
        PROCESS(clock2);        

        clock4.data_in = clock2.data_out ^ clock4.data_out;
        clock4.enable  = clock.clock;
        clock4.clk     = clock.clock;
        PROCESS(clock4);

        PLOT(test_bench_sim[0], clock.clock);
        PLOT(test_bench_sim[1], clock2.data_out);
        PLOT(test_bench_sim[2], clock4.data_out);
        PLOT(test_bench_sim[3], reg8.data_in);
        PLOT(test_bench_sim[4], reg8.enable);
        PLOT(test_bench_sim[5], reg8.data_out);
    }

    GRAPH(test_bench_sim, 16, "%02X", "", 2);
}

int main(int argc, char** argv) {

    test_bench("traces/reg8.txt");

    return 0;
}