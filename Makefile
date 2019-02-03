# having the option -DNDEBUG when compiling, means NO debugging occurs
# comment out the next line if you want debugging
# NO_DEBUGGING_STATEMENTS = -DNDEBUG
CXX = g++
VERSION = -std=c++14
CFLAGS = -pedantic -Wall -g -Wextra $(VERSION) $(NO_DEBUGGING_STATEMENTS)
LFLAGS = -Wall $(VERSION) 

INCS = LList.h
SRCS = LList.cpp\
	testLList.cpp
OBJS = $(SRCS:.cpp=.o)
EXEC = testLList

all: $(SRCS) $(EXEC)

# To make an object from source
#.cpp.o: 
%.o:%.cpp $(INCS)
	$(CXX) $(CFLAGS) -c $< -o $@

$(EXEC): $(OBJS) 
	$(CXX) $(LFLAGS) $(OBJS) -o $@

# for Windows
clean:
	del *.o  $(EXEC).exe
	@echo clean done

# for UNIX / Linux 
remove:
	\rm -f *.o  $(EXEC)
	@echo clean done
