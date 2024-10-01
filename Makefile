CC = g++
#HELPERSPATH = ../gr_helpers/
INCLPATH = ./includes/
SRCSPATH = ./srcs/
# $(HELPERSPATH)-fsanitize=address
CFLAGS = -g -std=c++2a  $(foreach H, $(INCLPATH), -I$(H))
MAIN = $(SRCSPATH)main.cpp
EXEC = ./a.out
#HELPERS = $(HELPERSPATH)*.cpp

all: $(EXEC)
#$(HELPERS)
$(EXEC) : $(MAIN)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f *.o

fclean: clean
	rm -f $(EXEC)

re : fclean all

run: $(EXEC)
	./$^

crun: $(EXEC)
	clear
	./$^

leaks:
	valgrind --leak-check=full --show-leak-kinds=all ./$(EXEC)

.PHONY: all clean fclean re run crun leaks
