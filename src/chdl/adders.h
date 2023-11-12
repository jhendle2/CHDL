#ifndef ADDERS_H
#define ADDERS_H

#include "gates.h"

NEW_GATE(
    NAME(HALF_ADDER),

    FIELDS(
        NEW_BIT(a);
        NEW_BIT(b);
        NEW_BIT(sum);
        NEW_BIT(c_out);
    ),

    INIT(

    ),
    
    BODY(
        AND_t c_out = AND();
        c_out.a = self->a;
        c_out.b = self->b;
        PROCESS(c_out);

        XOR_t sum = XOR();
        sum.a = self->a;
        sum.b = self->b;
        PROCESS(sum);

        ASSIGN(self->sum  , sum.q);
        ASSIGN(self->c_out, c_out.q);
    ),

    LOG(
        INPUT(a);
        INPUT(b);
        OUTPUT(sum);
        OUTPUT(c_out);
    )
)

NEW_GATE(
    NAME(FULL_ADDER),

    FIELDS(
        /* INPUTS */
        NEW_BIT(a);
        NEW_BIT(b);
        NEW_BIT(c_in);
        
        /* OUTPUTS */
        NEW_BIT(sum);
        NEW_BIT(c_out);
    ),

    INIT(

    ),

    BODY(
        HALF_ADDER_t partial_sum = HALF_ADDER();
        HALF_ADDER_t full_sum    = HALF_ADDER();
        OR_t c_out = OR();

        partial_sum.a = self->a;
        partial_sum.b = self->b;
        PROCESS(partial_sum);

        full_sum.a = self->c_in;
        full_sum.b = partial_sum.sum;
        PROCESS(full_sum);

        c_out.a = full_sum.c_out;
        c_out.b = partial_sum.c_out;
        PROCESS(c_out);

        ASSIGN(self->sum, full_sum.sum);
        ASSIGN(self->c_out, c_out.q);
    ),

    LOG(
        INPUT(a);
        INPUT(b);
        INPUT(c_in);
        OUTPUT(sum);
        OUTPUT(c_out);
    )
)

#endif /* ADDERS_H */