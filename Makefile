CC = gcc
CFLAGS = -Wall
LDFLAGS = 

SRCS = main.c image.c
OBJS = $(SRCS:.c=.o)
EXECUTABLE = tad_imagens_ppm

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXECUTABLE)
