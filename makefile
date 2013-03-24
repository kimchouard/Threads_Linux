CXX= gcc -g
CXXFLAGS=-W -Wall -ansi -pedantic 
LDFLAGS=  
EXEC= Thread
SRC= main.c lire.c factorisation.c factorisation_p4.c
OBJ= $(SRC:.cpp=.o)
LIBS= -lpthread
all: $(EXEC)

$(EXEC) : $(OBJ)
	$(CXX) -o $@ $^ $(LDFLAGS) $(LIBS)

%.o: %.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)

.PHONY: clean mrproper

clean:
	rm -rf *.o
	rm -rf $(EXEC)
	
mrproper: clean
	rm -rf $(EXEC)
