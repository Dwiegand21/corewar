

vpath
vpath %.c $(SOURCES_DIR)

.SUFFIXES:
.SUFFIXES: .c .o .h

all: $(TARGET)

$(TARGET): $(OBJECT_FILES)
	$(CC) $^ $(LFLAGS) -o $@

$(OBJECTS_DIR)/%.o: %.c
	$(CC) $(CFLAGS) $(IFLAGS) -o $@ -c $<
