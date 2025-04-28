# Kompilator C++
CXX = g++

# Ścieżka do folderu include biblioteki Ice
ICE_INCLUDE_DIR = /opt/homebrew/Cellar/ice/3.7.10/include

# Ścieżka do folderu lib biblioteki Ice
ICE_LIB_DIR = /opt/homebrew/Cellar/ice/3.7.10/lib

# Ścieżka do współdzielonych plików (np. generowanych przez Slice)
SHARED_DIR = ../shared

# Flagi kompilatora: standard C++20, dołączanie folderu includes projektu,
# dołączanie folderu includes Ice, dołączanie folderu shared, włączenie ostrzeżeń
CXXFLAGS = -std=c++20 -Iincludes -I$(ICE_INCLUDE_DIR) -I$(SHARED_DIR) -Wall

# Flagi linkera: wskazanie ścieżki do bibliotek Ice i linkowanie ich
LDFLAGS = -L$(ICE_LIB_DIR) -lIce -lIceUtil

# Nazwa pliku wykonywalnego (zgodnie z CMakeLists.txt)
TARGET = zadanie2

# Pliki źródłowe w folderze src bieżącego komponentu (system)
SRCS = $(wildcard src/*.cpp)

# Pliki źródłowe w folderze shared (zakładamy SIP.cpp)
SHARED_SRCS = $(wildcard $(SHARED_DIR)/*.cpp)

# Zamiana rozszerzeń .cpp na .o dla plików obiektowych lokalnych
OBJS = $(patsubst src/%.cpp, %.o, $(SRCS))

# Zamiana rozszerzeń .cpp na .o dla plików obiektowych współdzielonych
# Zakładamy, że pliki obiektowe dla shared lądują w bieżącym katalogu
SHARED_OBJS = $(patsubst $(SHARED_DIR)/%.cpp, %.o, $(SHARED_SRCS))

# Wszystkie pliki obiektowe
ALL_OBJS = $(OBJS) $(SHARED_OBJS)

# Domyślna reguła: budowanie aplikacji
all: $(TARGET)

# Reguła linkowania: tworzenie pliku wykonywalnego z plików obiektowych
# Używamy $(CXX), $(CXXFLAGS) i $(LDFLAGS) do linkowania
$(TARGET): $(ALL_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Reguła kompilacji dla lokalnych plików .cpp: tworzenie plików obiektowych (.o) z plików źródłowych (src/*.cpp)
# Zależności obejmują lokalne nagłówki i współdzielone nagłówki
%.o: src/%.cpp $(wildcard includes/*.h) $(wildcard $(SHARED_DIR)/*.h)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Reguła kompilacji dla współdzielonych plików .cpp: tworzenie plików obiektowych (.o) z plików źródłowych (shared/*.cpp)
# Zależności obejmują tylko współdzielone nagłówki (dla uproszczenia)
%.o: $(SHARED_DIR)/%.cpp $(wildcard $(SHARED_DIR)/*.h)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Reguła czyszczenia: usuwanie plików obiektowych i pliku wykonywalnego
clean:
	rm -f $(ALL_OBJS) $(TARGET)

# Oznaczenie reguł, które nie tworzą plików o tych nazwach
.PHONY: all clean