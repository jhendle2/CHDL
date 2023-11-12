#ifndef LATCHES_H
#define LATCHES_H

#include "gates.h"

NEW_GATE(
    NAME(SR_LATCH),

    FIELDS(
        NEW_BIT(r);
        NEW_BIT(s);
        NEW_BIT(q);
        NEW_BIT(q_inv);
    ),

    INIT(
        self->r    =UNDEF;
        self->s    =UNDEF;
        self->q    =UNDEF;
        self->q_inv=UNDEF;
    ),

    BODY(
        /***************************/
        STATIC(XNOR, xnor_q);
        STATIC(XNOR, xnor_q_inv);
        
        /***************************/
        PROCESS(xnor_q_inv);
        ASSIGN(self->q, xnor_q.q);
        xnor_q.a = self->r;
        xnor_q.b = xnor_q_inv.q;

        PROCESS(xnor_q);
        ASSIGN(self->q_inv, xnor_q_inv.q);
        xnor_q_inv.a = self->s;
        xnor_q_inv.b = xnor_q.q;
    ),

    LOG(
        INPUT(r);
        INPUT(s);

        OUTPUT(q);
        OUTPUT(q_inv);
    )
)

NEW_GATE(
    NAME(D_LATCH),

    FIELDS(
        NEW_BIT(data);
        NEW_BIT(enable);
        NEW_BIT(q);
        NEW_BIT(q_inv);
    ),
    
    INIT(
        self->data  =UNDEF;
        self->enable=UNDEF;
        self->q     =UNDEF;
        self->q_inv =UNDEF;
    ),

    BODY(
        /***************************/
        NEW(AND, and_q);
        NEW(AND, and_q_inv);

        STATIC(XNOR, xnor_q);
        STATIC(XNOR, xnor_q_inv);

        /***************************/
        and_q.a = NOT(self->data);
        and_q.b =     self->enable;
        PROCESS(and_q);

        and_q_inv.a = self->enable;
        and_q_inv.b = self->data;
        PROCESS(and_q_inv);

        PROCESS(xnor_q_inv);
        ASSIGN(self->q, xnor_q.q);
        xnor_q.a = and_q.q;
        xnor_q.b = xnor_q_inv.q;

        PROCESS(xnor_q);
        ASSIGN(self->q_inv, xnor_q_inv.q);
        xnor_q_inv.a = and_q_inv.q;
        xnor_q_inv.b = xnor_q.q;
    ),

    LOG(
        INPUT(data);
        INPUT(enable);
        OUTPUT(q);
        OUTPUT(q_inv);
    )
)

NEW_GATE(
    NAME(DOUBLE_D_LATCH),

    FIELDS(
        NEW_BIT(data);
        NEW_BIT(enable);
        NEW_BIT(q);
        NEW_BIT(q_inv);
    ),
    
    INIT(
        self->data  =UNDEF;
        self->enable=UNDEF;
        self->q     =UNDEF;
        self->q_inv =UNDEF;
    ),

    BODY(
        /***************************/
        STATIC(D_LATCH, d_latch_0);
        STATIC(D_LATCH, d_latch_1);
        
        /***************************/
        d_latch_0.data   = self->data;
        d_latch_0.enable = self->enable;
        PROCESS(d_latch_0);

        // ASSIGN(self->q, xnor_q.q);
        d_latch_1.data   = d_latch_0.q;
        d_latch_1.enable = self->enable;
        PROCESS(d_latch_1);

        ASSIGN(self->q, d_latch_1.q);
        ASSIGN(self->q_inv, d_latch_1.q_inv);
    ),

    LOG(
        INPUT(data);
        INPUT(enable);
        OUTPUT(q);
        OUTPUT(q_inv);
    )
)

#endif /* LATCHES_H */