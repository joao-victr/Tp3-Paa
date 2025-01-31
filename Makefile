EXEC = main
COMPILER = gcc
OBJECTS = main.o input.o pattern_matching.o
input_file =music.txt
method = 1

all: $(OBJECTS)
	$(COMPILER) $(OBJECTS) -o $(EXEC)

main.o: main.c
	$(COMPILER) -c main.c

input.o: input.c
	$(COMPILER) -c input.c

pattern_matching.o: pattern_matching.c
	$(COMPILER) -c pattern_matching.c

clean: 
	rm -rf *.o $(EXEC)

run: $(EXEC)
	./$(EXEC) -a $(input_file) -b $(method)

val: $(EXEC)
	valgrind ./$(EXEC) -a $(input_file) -b $(method)