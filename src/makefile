# compile macro
CC		= g++
CFLAGS	= -Wall -std=c++11
INCX11 = /opt/homebrew/include
LIBX11 = /opt/homebrew/lib
# LDFLAGS	= -lm
INCLUDES= -I ../include/HMI -lX11 -lpthread . -I $(INCX11) -L $(LIBX11)

# user modify: subdir, target and objects
VPATH 	= ./bestiole ./environment
EXENAME = main
OBJECTS	= Aquarium.o Milieu.o Bestiole.o main.o

# make target
all:${OBJECTS}
	${CC} ${CFLAGS} -o ${EXENAME} ${OBJECTS} ${INCLUDES}
	
# make clean
clean:
	rm -rf ${EXENAME} ${OBJECTS} 

# dependence	
%.o : %.cpp
	${CC} ${CFLAGS} ${INCLUDES} -c $< -o $@

