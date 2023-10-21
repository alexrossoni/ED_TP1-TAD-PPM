CC = gcc
CFLAGS = -Wall
LDFLAGS = 

SRCS = main.c image.c
OBJS = $(SRCS:.c=.o)
EXECUTABLE = image_processing

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXECUTABLE)
