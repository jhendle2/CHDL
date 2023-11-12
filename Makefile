CC:=gcc
CFLAGS:=-g -Wall

SRC:=./src
OBJ:=./obj

SRCS:=$(wildcard $(SRC)/*.c)
OBJS:=$(patsubst $(SRC)/%.c,$(OBJ)/%.o,$(SRCS))
# HDRS:=$(wildcard $(SRC)*.h)
HDRS:=$(wildcard $(SRC)/chdl/*.h $(SRC)*.h)

INCLUDE:=-I$(SRC)

$(OBJ)/%.o: $(SRC)/%.c $(HDRS)
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<

hdl: $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDE)    -o $@ $(OBJS)

test: hdl
	./hdl