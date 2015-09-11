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

generate:
	cp ./cases/iris.data ./iris.data
	cp ./cases/iris.schema ./iris.schema

destroy:
	find -name "iris*" -exec rm {} \;

clean:	destroy
	find -name "*~" -exec rm -rf {} \;
	rm -rf $(BUILD)

compile-test: generate
	mkdir $(BUILD)
	$(COMPILER) $(SOURCE) -I $(INCLUDES) -o $(BUILD)$(OUTPUT) $(WARNING)

run-test:
	$(VALGRIND) $(BUILD)$(OUTPUT)

compile: generate
	mkdir $(BUILD)
	$(COMPILER) $(SOURCE) -I $(INCLUDES) -o $(BUILD)$(OUTPUT)

run:
	$(BUILD)$(OUTPUT)

