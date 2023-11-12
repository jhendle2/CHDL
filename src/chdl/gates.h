#ifndef GATES_H
#define GATES_H

#include "hdl.h"

NEW_GATE(
    NAME(AND),

    FIELDS(
        /* INPUTS */
        NEW_BIT(a);
        NEW_BIT(b);

        /* OUTPUTS */
        NEW_BIT(q);
    ),

    INIT(
        self->a=UNDEF;
        self->b=UNDEF;
        self->q=UNDEF;
    ),
    
    BODY(
        ASSIGN(self->q, self->a & self->b);
    ),

    LOG(
        INPUT(a);
        INPUT(b);
        OUTPUT(q);
    )
)

NEW_GATE(
    NAME(OR),

    FIELDS(
        /* INPUTS */
        NEW_BIT(a);
        NEW_BIT(b);

        /* OUTPUTS */
        NEW_BIT(q);
    ),

    INIT(
        self->a=UNDEF;
        self->b=UNDEF;
        self->q=UNDEF;
    ),
    
    BODY(
        ASSIGN(self->q, self->a | self->b);
    ),

    LOG(
        INPUT(a);
        INPUT(b);
        OUTPUT(q);
    )
)

NEW_GATE(
    NAME(XOR),

    FIELDS(
        /* INPUTS */
        NEW_BIT(a);
        NEW_BIT(b);

        /* OUTPUTS */
        NEW_BIT(q);
    ),

    INIT(
        self->a=UNDEF;
        self->b=UNDEF;
        self->q=UNDEF;
    ),
    
    BODY(
        ASSIGN(self->q, self->a ^ self->b);
    ),

    LOG(
        INPUT(a);
        INPUT(b);
        OUTPUT(q);
    )
)

/***********************************/


NEW_GATE(
    NAME(NAND),

    FIELDS(
        /* INPUTS */
        NEW_BIT(a);
        NEW_BIT(b);

        /* OUTPUTS */
        NEW_BIT(q);
    ),

    INIT(
        self->a=UNDEF;
        self->b=UNDEF;
        self->q=UNDEF;
    ),
    
    BODY(
        ASSIGN(self->q, NOT(self->a & self->b));
    ),

    LOG(
        INPUT(a);
        INPUT(b);
        OUTPUT(q);
    )
)

NEW_GATE(
    NAME(NOR),

    FIELDS(
        /* INPUTS */
        NEW_BIT(a);
        NEW_BIT(b);

        /* OUTPUTS */
        NEW_BIT(q);
    ),

    INIT(
        self->a=UNDEF;
        self->b=UNDEF;
        self->q=UNDEF;
    ),
    
    BODY(
        ASSIGN(self->q, NOT(self->a | self->b));
    ),

    LOG(
        INPUT(a);
        INPUT(b);
        OUTPUT(q);
    )
)

NEW_GATE(
    NAME(XNOR),

    FIELDS(
        /* INPUTS */
        NEW_BIT(a);
        NEW_BIT(b);

        /* OUTPUTS */
        NEW_BIT(q);
    ),
    
    INIT(
        self->a=UNDEF;
        self->b=UNDEF;
        self->q=UNDEF;
    ),

    BODY(
        ASSIGN(self->q, NOT(self->a ^ self->b));
    ),

    LOG(
        INPUT(a);
        INPUT(b);
        OUTPUT(q);
    )
)

#endif /* GATES_H */