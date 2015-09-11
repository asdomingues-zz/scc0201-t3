COMPILER=gcc
SOURCE=./source/*.c
INCLUDES=./includes
BUILD=./build/
OUTPUT=main
WARNING=-ansi -g -Wall
VALGRIND=valgrind --show-leak-kinds=all --leak-check=full --track-origins=yes

all: test

done: clean compile run

test: clean compile-test run-test

clean:
	find -name "*~" -exec rm -rf {} \;
	rm -rf $(BUILD) 

compile-test:
	mkdir $(BUILD)
	$(COMPILER) $(SOURCE) -I $(INCLUDES) -o $(BUILD)$(OUTPUT) $(WARNING)

run-test:
	$(VALGRIND) $(BUILD)$(OUTPUT)

compile:
	mkdir $(BUILD)
	$(COMPILER) $(SOURCE) -I $(INCLUDES) -o $(BUILD)$(OUTPUT)

run:
	$(BUILD)$(OUTPUT)

