CC = gcc
TARGET = daft
SRCS = main.c fileHandler/reader.c fileHandler/writer.c utils.c dirHandler/curDirName.c dirHandler/listDir.c dirHandler/recursiveRmDir.c
OBJS = $(SRCS:.c=.o)
CURRENTDIR = $(CURDIR)
HELP_FILE = $(CURDIR)/help.txt
CFLAGS += -DHELP_PATH="\"$(HELP_FILE)\""
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
