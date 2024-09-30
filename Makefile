CC = g++
#HELPERSPATH = ../gr_helpers/
INCLPATH = ./includes/
SRCSPATH = ./srcs/
# $(HELPERSPATH)
CFLAGS = -g -std=c++2a -fsanitize=address $(foreach H, $(INCLPATH), -I$(H))
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

.PHONY: all clean fclean re run crun