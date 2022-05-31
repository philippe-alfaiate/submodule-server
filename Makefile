CC=gcc
CFLAGS=
INC=./
NAME=server
OBJ= main.o \



all: $(NAME)

fclean: clean
	rm -f $(NAME)

clean:
	rm -f *.o

%.o:%.c 
	$(CC) -c -o $@ $< $(CFLAGS)

$(NAME):$(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)


.PHONY: all fclean clean 