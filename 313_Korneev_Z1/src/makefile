CC = g++
FLAGS = -O2 -Wall -Werror -Wextra -pedantic -lsfml-graphics -lsfml-window -lsfml-system
TARGET = app
SOURCE = main.cpp
OBJECT_FILE = main.o

all: app

app: $(OBJECT_FILE)
	$(CC) $(OBJECT_FILE) -o $(TARGET) $(FLAGS)

$(OBJECT_FILE): $(SOURCE)
	$(CC) -c $(SOURCE)

clean:
	rm -rf $(OBJECT_FILE) $(TARGET)
