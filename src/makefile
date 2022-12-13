# compile macro
CC		= g++
CFLAGS	= -std=c++11 -Wall -g
INCX11 = /opt/homebrew/include
LIBX11 = /opt/homebrew/lib
# LDFLAGS	= -lm
INCLUDES= -I ../include/HMI  -I $(INCX11) 
LIBS = -L $(LIBX11) -lX11 -lpthread

# user modify: subdir, target and objects
VPATH 	= ./bestiole ./environment ./factory ./comportement ./capteur
EXENAME = main
OBJECTS	= Aquarium.o Milieu.o Bestiole.o main.o BestiolFactory.o Gragaire.o Peureuse.o Kamikaze.o Multiple.o Oreilles.o Yeux.o


# make target
all:${OBJECTS}
	${CC} ${CFLAGS} -o ${EXENAME} ${OBJECTS} ${INCLUDES} ${LIBS} 

# make clean
clean:
	rm -rf ${EXENAME} ${OBJECTS} 

# dependence	
%.o : %.cpp
	${CC} ${CFLAGS} ${INCLUDES} -c $<

