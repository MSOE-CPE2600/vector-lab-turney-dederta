CC=gcc
CFLAGS=-c -Wall
SOURCES=vector.c minimat.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=minimat

all: $(SOURCES) $(EXECUTABLE)

#pull in dependency infor for "existing" .o files
-include $(OBJECTS:.o=.d)

$(EXECUTABLE):$(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@
	$(CC) -MM $< > $*.d

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE) *.d