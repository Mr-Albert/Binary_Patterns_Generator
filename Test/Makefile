MAIN_SRC_PATH=../src
CC=g++
CFLAGS=-c -Wall
#LDFLAGS=-lSDL -lSDL_gfx
INCL=-I $(SRC_PATH)include/
LDFLAGS = -std=c++1y -lpthread -fexceptions -g
EXE=testRun
TESTEXE=testDebugRun
debugFlag = -D _testMode



SRC=$(wildcard $(MAIN_SRC_PATH)/Binary_Pattern_Generator/*.cpp $(MAIN_SRC_PATH)/userInputClass/*.cpp )
EASYLOGGERSRC=$(wildcard $(MAIN_SRC_PATH)/easyLogger/*.cc )
TESTSRC=../src/test.cpp $(wildcard $(MAIN_SRC_PATH)/PatternTester/*.cpp)
TESTDEBUGSRC=../src/testDebug.cpp

OBJ=$(subst ../src, obj, $(SRC:.cpp=.o))
TESTOBJ=$(subst ../src, obj, $(TESTSRC:.cpp=.o))
TESTDEBUGOBJ=$(subst ../src, obj, $(TESTDEBUGSRC:.cpp=.o))
EASYLOGGEROBJ=$(subst ../src, obj, $(EASYLOGGERSRC:.cc=.o))

#DEBUGFLAG: debugFlag=-D _DebugMode
#DEBUGFLAG:
#	@echo defining  $(debugFlag) in compiler options
	
test: $(EASYLOGGERSRC) $(TESTSRC) $(SRC) $(EASYLOGGERSRC) $(EXE)
#	@mkdir -p obj
#	@mkdir -p obj/Binary_Pattern_Generator	
#	@echo $(TESTSRC)
#	@echo $(TESTOBJ)
#	@echo --------------------
#	@echo $(SRC)
#	@echo $(OBJ)
testDebug:debugFlag=-D _DebugMode
testDebug: $(EASYLOGGERSRC) $(TESTDEBUGSRC) $(SRC) $(EASYLOGGERSRC) $(TESTEXE)
#	@mkdir -p obj
#	@mkdir -p obj/Binary_Pattern_Generator	
#	@echo $(TESTSRC)
#	@echo $(TESTOBJ)
#	@echo --------------------
#	@echo $(SRC)
#	@echo $(OBJ)

$(EXE):  $(TESTOBJ) $(OBJ) $(EASYLOGGEROBJ)
	$(CC) $(LDFLAGS) $(TESTOBJ) $(EASYLOGGEROBJ) $(OBJ) -o $@ -lstdc++fs
	
$(TESTEXE): $(TESTDEBUGOBJ) $(OBJ) $(EASYLOGGEROBJ)
	$(CC)  $(LDFLAGS) $(EASYLOGGEROBJ) $(TESTDEBUGOBJ) $(OBJ)   -o $@ -lstdc++fs
obj/%.o: ../src/%.cpp
	@mkdir -p obj
	@mkdir -p obj/Binary_Pattern_Generator	
	@mkdir -p obj/easyLogger	
	@mkdir -p obj/PatternTester
	@mkdir -p obj/userInputClass
	
	$(CC) -fexceptions $(debugFlag) $(CFLAGS) $(INCL) -o $@ $<
obj/%.o: ../src/%.cc
	@mkdir -p obj
	@mkdir -p obj/Binary_Pattern_Generator	
	@mkdir -p obj/easyLogger	
	@mkdir -p obj/PatternTester	
	@mkdir -p obj/userInputClass	
	$(CC) -fexceptions $(debugFlag) $(CFLAGS) $(INCL) -o $@ $<
clean:
	rm -rf run $(EASYLOGGEROBJ) $(TESTOBJ) $(OBJ)