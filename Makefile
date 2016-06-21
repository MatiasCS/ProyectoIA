#Macros

CC = g++
LIB = lib
INCLUDE = include
FLAGS = -c -Wall -I $(INCLUDE)
LIBFLAG = -L$(LIB)–levento

all: programa_o libreria programa 

programa_o:
	@echo Creando archivos .o
	@$(CC) $(FLAGS) tarea1.cpp utilities.cpp trip.cpp evo.cpp

libreria: programa_o
	@echo Creando bibliotecas
	@ar rvs $(LIB)/utilities.a utilities.o

programa: libreria
	@echo Creando el ejecutable
	@$(CC) tarea1.o utilities.o trip.o evo.o $(LIBFLAG) -o tarea1
	@echo Listo!
