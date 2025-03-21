# Numele fișierului sursă și al fișierului executabil
SRC = app.c src/shader.c src/stb_image.c
EXEC = app

# Directorul de includere pentru GLAD
GLAD_DIR = /home/cafea/Programare/C_Projects/Engine/glad/include

# Directorul pentru sursa GLAD
GLAD_SRC = /home/cafea/Programare/C_Projects/Engine/glad/src/glad.c

# Directorul pentru lib custom
LIB_DIR = /home/cafea/Programare/C_Projects/Engine/Triangle/lib

# Linker flags pentru biblioteci
LIBS = -lglfw -ldl -lm -lstdc++

# Căi de includere
INCLUDES = -I$(GLAD_DIR) -I/usr/include -I$(LIB_DIR)

# Compilatorul și opțiunile de compilare
CC = g++
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
 
