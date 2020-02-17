#
# makefile for BCC++
#

SRC = main.c sub.c sub2.c 
OBJ = $(SRC:.c=.obj)
PROGRAM = main
CFLAGS = -w

all: $(PROGRAM)

$(PROGRAM): $(OBJ)
	$(CC) $(OBJ) -e$(PROGRAM)

.SUFFIXES: .c

.c.obj:
	$(CC) $(CFLAGS) -c $< 

clean:
	del *.obj 

