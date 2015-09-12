COMPILER=gcc
SOURCE=./source/*.c
INCLUDES=./includes
BUILD=./build/
OUTPUT=main
WARNING=-ansi -g -Wall
VALGRIND=valgrind --show-leak-kinds=all --leak-check=full --track-origins=yes
CASE=< teste.txt

all: test

done: destroy clean generate compile run

time: destroy clean generate compile time-run

test: destroy clean generate compile-test run-test

generate:
	cp ./cases/iris.data ./iris.data
	cp ./cases/iris.schema ./iris.schema

destroy:
	rm ./iris.data
	rm ./iris.schema
	find -name "*idx" -exec rm -rf {} \;

clean:
	find -name "*~" -exec rm -rf {} \;
	rm -rf $(BUILD)

compile-test:
	mkdir $(BUILD)
	$(COMPILER) $(SOURCE) -I $(INCLUDES) -o $(BUILD)$(OUTPUT) $(WARNING)

run-test:
	$(VALGRIND) $(BUILD)$(OUTPUT) $(CASE)

compile:
	mkdir $(BUILD)
	$(COMPILER) $(SOURCE) -I $(INCLUDES) -o $(BUILD)$(OUTPUT)

run:
	$(BUILD)$(OUTPUT)

time-run:
	time $(BUILD)$(OUTPUT) $(CASE)
