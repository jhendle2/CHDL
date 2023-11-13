#ifndef REGISTERS_H
#define REGISTERS_H

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

/**********************************************/
typedef Byte_t Addr8_t;

NEW_GATE(
    NAME(REGFILE_8x8),

    FIELDS(
        /* INPUTS */
        NEW_BYTE(read_addr_1);
        NEW_BYTE(read_addr_2);

        NEW_BYTE(write_addr);
        NEW_BYTE(write_data);
        NEW_BIT (write_enable);
        NEW_BIT (clock);

        /* SIGNALS */
        Byte_t byte_array[256];

        /* OUTPUTS */
        NEW_BYTE(read_data_1);
        NEW_BYTE(read_data_2);
    ),

    INIT(
        self->read_addr_1  = 0x00;
        self->read_addr_2  = 0x00;
        self->write_addr   = 0x00;
        self->write_data   = 0x00;
        self->write_enable = LOW;
        self->clock        = LOW;
        self->read_data_1  = 0x00;
        self->read_data_2  = 0x00;

        for (Addr8_t addr = 0x00; addr <= 0xFF; addr++) {
            self->byte_array[addr] = 0x00;
        }
    ),

    BODY(
        if (self->clock) {
            if (self->write_enable) {
                self->byte_array[self->write_addr] = self->write_data;
            }
        }

        /* Reads are asynchronous */
        self->read_data_1 = self->byte_array[self->read_addr_1];
        self->read_data_2 = self->byte_array[self->read_addr_2];
    ),

    LOG(
        printf("(RegFile)\n");
        printf("   | ");
        for (Addr8_t addr = 0x00; addr <= 0x0F; addr++)
            printf("%02X ", addr);
        printf("\n---+-");
        for (Addr8_t addr = 0x00; addr <= 0x0F; addr++)
            printf("---");
        
        for (Addr8_t addr = 0x00; addr <= 0xFF; addr++) {
            if (addr % 16 == 0) printf("\n%02X | ", addr & 0xF0);
            printf("%02X ", self->byte_array[addr]);
        }
        printf("\n(RegFile)\n");
    )
)

#endif /* REGISTERS_H */