# Variables
CC     = gcc
DEBUG  = -g -DDEBUG
CFLAGS = -ansi -Wall -c -std=c99 -g
LFLAGS = -Wall

DEPS = FileIO.h DIPs.h Image.h ImageList.h Movie.h Constants.h
OBJS = MovieLab.o FileIO.o DIPs.o Image.o ImageList.o Movie.o

 # Default target
all: MovieLab

 ######################### Generate object files #######################
 # Target for MovieLab.o
MovieLab.o: MovieLab.c $(DEPS)
        $(CC) $(CFLAGS) MovieLab.c -o MovieLab.o

 # Target for FileIO.o
FileIO.o: FileIO.c $(DEPS)
        $(CC) $(CFLAGS) FileIO.c -o FileIO.o

#Target for DIPs.o
DIPs.o: DIPs.c $(DEPS)
        $(CC) $(CFLAGS) DIPs.c -o DIPs.o

# Target for Image.o
Image.o: Image.c $(DEPS)
        $(CC) $(CFLAGS) Image.c -o Image.o

#Target for ImageList.o
ImageList.o: ImageList.c $(DEPS)
        $(CC) $(CFLAGS) ImageList.c -o ImageList.o

     # Target for Movie.o
Movie.o: Movie.c $(DEPS)
        $(CC) $(CFLAGS) Movie.c -o Movie.o

######################### Generate the executable #####################
#Target for MovieLab
MovieLab: $(OBJS)
        $(CC) $(LFLAGS) $(OBJS) -o MovieLab

###############################  others  ##############################
#Target for clean-up
clean:
        rm -f *.o MovieLab
