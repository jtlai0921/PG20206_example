#
# makefile
#

SRC = main.c sub.c sub2.c 
OBJ = $(SRC:.c=.obj)
PROGRAM = main
CFLAGS = /Wall

all: $(PROGRAM)

$(PROGRAM): $(OBJ)
	$(CC) $(OBJ) /Fe$(PROGRAM)

.SUFFIXES: .c

.c.obj:
	$(CC) $(CFLAGS) /c $< 

clean:
	del *.obj 

