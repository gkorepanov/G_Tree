.PHONY: clean

TARGET = bin/G_Tree
FLAGS = -std=c++11 -Wall -g
OBJS = G_Main.o G_Lex/G_Lex.o
LEX = G_Lex/G_Lex.cpp
LEXL = $(LEX:.cpp=.l)
DEPS = $(OBJS:.o=.d)

tree: $(TARGET)

$(TARGET): $(OBJS)
	g++ -o $@ $^

-include $(DEPS)

%.o: %.cpp
	g++ $(FLAGS) -c -o $@ $<
	g++ $(FLAGS) -MM -o $(patsubst %.o, %.d, $@) $<


$(LEX): $(LEXL)
	flex -o $@ $<


