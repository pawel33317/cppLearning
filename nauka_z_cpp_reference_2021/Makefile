#CEL: SKLADNIKI
#	KOMENDA
#< - aktualnie przetwarzany plik z listy składników (patrz przykład)
#@ - nazwa pliku docelowego
#^ - składniki
CXX=/usr/bin/g++-11
CXXFLAGS=-std=c++2a -Wall -O0
LFLAGS= #opcje linkera
LIBS = -lboost_system -lboost_filesystem -lm -lrt -lpthread -lstdc++
RELEASE_DIR=release
INCLUDES=./headers/

SRCS := $(wildcard *.cpp)

#OBJS := $(patsubst %.cpp,%.o,$(SRCS))
OBJS_RELEASE := $(patsubst %.cpp,$(RELEASE_DIR)/%.o,$(SRCS))

TARGET := app.bin

all: $(TARGET)
	./$(RELEASE_DIR)/app.bin


#linkowanie
$(TARGET): $(OBJS_RELEASE)
	#linkowanie zależy od kolejności, symbole powinny być najpierw requestowane
	#a później linkowane z biblioteki więc $(LIBS) jest za $^
	#w skrócie najpierw moduły używające biblioteki a później biblioteki

	#w przypadku cyklicznych zależności dana biblioteka powinna być dodana
	#wielokrotnie -la -lb -la -lc, można też użyć --start-group, --end-group
	$(CXX) $(LFLAGS) $^ $(LIBS) -o $(RELEASE_DIR)/$@

#kompilacja
$(RELEASE_DIR)/%.o: %.cpp
	@mkdir -p $(RELEASE_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@ -I$(INCLUDES)

clean:
	rm -rf $(TARGET) *.o $(RELEASE_DIR)
.PHONY: clean