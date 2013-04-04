# $(BIN) est la nom du binaire généré
TARGET = libstructs.a
TARGETDYN = libstructs.so

# Options de compilation
CC = gcc
CFLAGS = -pedantic -Wall -Wextra -fPIC -g
# INCLUDES
INC = ./include
# LIB DIR FINALE
LIBFIN = ../lib
# INCLUDES
LIBDIR = .
# SOURCES
SRC = ./src

# Pour la librairie statique
AR = ar rcs
# OBJET
DIR_OBJ = obj
## OBJECTS : liste des objets de la bibliothèque
OBJECTS = $(DIR_OBJ)/queue.o $(DIR_OBJ)/stack.o $(DIR_OBJ)/list.o $(DIR_OBJ)/doublelinkedlist.o

# all est la première règle à être exécutée car elle est la première
# dans le fichier Makefile. Notons que les dépendances peuvent être
# remplacées par une variable, ainsi que n'importe quel chaine de
# caractères des commandes
all: $(OBJECTS)
	@echo $(OBJECTS)
	$(CC) -L$(LIBDIR) $(LIBS) $(OBJECTS) -fPIC -shared -o $(LIBFIN)/$(TARGETDYN)

static: $(OBJECTS)
	@echo "**** PHASE DE LIEN ****"
	$(AR) $(LIBFIN)/$(TARGET) $(OBJECTS)

$(DIR_OBJ)/%.o: $(SRC)/%.c $(INC)/%.h
	@echo "**** $@ ****"
	$(CC) -I$(INC) $(FLAGS) -c $< -o $@
