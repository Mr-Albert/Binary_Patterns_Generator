MAIN_SRC_PATH=../src
CC=g++
CFLAGS=-c -Wall
#LDFLAGS=-lSDL -lSDL_gfx
#INCL=-I $(SRC_PATH)include/
EXE=testRun
TESTEXE=testDebugRun

SRC=$(wildcard $(MAIN_SRC_PATH)/Binary_Pattern_Generator/*.cpp $(MAIN_SRC_PATH)/easyLogger/*.cpp)
TESTSRC=../src/test.cpp $(wildcard $(MAIN_SRC_PATH)/PatternTester/*.cpp)
TESTDEBUGSRC=../src/testDebug.cpp
OBJ=$(subst ../src, obj, $(SRC:.cpp=.o))
TESTOBJ=$(subst ../src, obj, $(TESTSRC:.cpp=.o))
TESTDEBUGOBJ=$(subst ../src, obj, $(TESTDEBUGSRC:.cpp=.o))



test: $(TESTSRC) $(SRC) $(EXE)
#	@mkdir -p obj
#	@mkdir -p obj/Binary_Pattern_Generator	
#	@echo $(TESTSRC)
#	@echo $(TESTOBJ)
#	@echo --------------------
#	@echo $(SRC)
#	@echo $(OBJ)

testDebug: $(TESTDEBUGSRC) $(SRC) $(TESTEXE)
#	@mkdir -p obj
#	@mkdir -p obj/Binary_Pattern_Generator	
#	@echo $(TESTSRC)
#	@echo $(TESTOBJ)
#	@echo --------------------
#	@echo $(SRC)
#	@echo $(OBJ)

$(EXE): $(TESTOBJ) $(OBJ)
	$(CC) $(TESTOBJ) $(OBJ) -o $@
	
$(TESTEXE): $(TESTDEBUGOBJ) $(OBJ)
	$(CC) $(TESTDEBUGOBJ) $(OBJ) -o $@	
obj/%.o: ../src/%.cpp
	@mkdir -p obj
	@mkdir -p obj/Binary_Pattern_Generator	
	@mkdir -p obj/easyLogger	
	@mkdir -p obj/PatternTester	
	$(CC) $(CFLAGS) $(INCL) -o $@ $<
clean:
	rm -rf run $(TESTOBJ) $(OBJ)