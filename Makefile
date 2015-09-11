COMPILER=gcc
SOURCE=./source/*.c
INCLUDES=./includes
BUILD=./build/
OUTPUT=main
WARNING=-ansi -g -Wall
VALGRIND=valgrind --show-leak-kinds=all --leak-check=full --track-origins=yes
CASE=< teste.txt

all: test

done: clean compile run

test: clean compile-test run-test

generate:
	cp ./cases/iris.data ./iris.data
	cp ./cases/iris.schema ./iris.schema

destroy:
	rm ./iris.data
	rm ./iris.schema
	rm ./iris-id.idx

clean:	destroy
	find -name "*~" -exec rm -rf {} \;
	rm -rf $(BUILD)

compile-test: generate
	mkdir $(BUILD)
	$(COMPILER) $(SOURCE) -I $(INCLUDES) -o $(BUILD)$(OUTPUT) $(WARNING)

run-test:
	$(VALGRIND) $(BUILD)$(OUTPUT) $(CASE)

compile: generate
	mkdir $(BUILD)
	$(COMPILER) $(SOURCE) -I $(INCLUDES) -o $(BUILD)$(OUTPUT)

run:
	$(BUILD)$(OUTPUT) $(CASE)
