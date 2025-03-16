# Numele fișierului sursă și al fișierului executabil
SRC = app.c
EXEC = app

# Directorul de includere pentru GLAD
GLAD_DIR = glad/include

# Directorul pentru sursa GLAD
GLAD_SRC = glad/src/glad.c

# Linker flags pentru biblioteci
LIBS = -lglfw -ldl -lm

# Căi de includere
INCLUDES = -I$(GLAD_DIR) -I/usr/include

# Compilatorul și opțiunile de compilare
CC = gcc
CFLAGS = -Wall -g

# Regula implicită pentru a construi aplicația
all: $(EXEC)

$(EXEC): $(SRC) $(GLAD_SRC)
	$(CC) $(CFLAGS) $(SRC) $(GLAD_SRC) -o $(EXEC) $(INCLUDES) $(LIBS)

# Regula pentru a curăța fișierele de compilare
clean:
	rm -f $(EXEC)

# Regula pentru a rula aplicația
run: $(EXEC)
	./$(EXEC)
