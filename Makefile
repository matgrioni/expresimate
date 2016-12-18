CC := g++
CFLAGS := -std=c++0x -Wall
INC := -I include
SRCDIR := src
BUILDDIR := build
TARGET := bin/main

SRCEXT := cpp
SRCS := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJS := $(patsubst $(SRCDIR)/%, $(BUILDDIR)/%, $(SRCS:.$(SRCEXT)=.o))

$(TARGET): $(OBJS)
	@echo "Linking..."
	@echo "$(CC) $^ -o $(TARGET)"
	$(CC) $^ -o $(TARGET)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@echo "$(CC) $(CFLAGS) -c -o $@ $<"
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean:
	@echo "Cleaning..."
	@echo "$(RM) $(OBJS) $(TARGET)"
	$(RM) $(OBJS) $(TARGET)

.PHONY: clean
