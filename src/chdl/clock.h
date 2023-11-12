#ifndef CLOCK_H
#define CLOCK_H

#include "hdl.h"

NEW_GATE(
    NAME(CLOCK),

    FIELDS(
        NEW_BIT(clock);
    ),
    
    INIT(
        self->clock=LOW;
    ),

    BODY(
        ASSIGN(self->clock, (self->clock==HIGH) ? LOW : HIGH);
    ),

    LOG(
        OUTPUT(clock);
    )
)

#endif /* CLOCK_H */