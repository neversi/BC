CC = gcc
FLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address
OUTPUT = my_bc
OFILE = main.o my_parser.o my_string.o my_bc.o

all: ${OUTPUT}

${OUTPUT}: ${OFILE}
	${CC} ${FLAGS} ${OFILE} -o ${OUTPUT}

%.o: %.c
	${CC} $^ -c

clean: 
	rm -rf *.o ${OUTPUT}

re: clean ${OUTPUT}