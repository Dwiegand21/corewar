
vpath %.c $(SOURCE_DIRECTORIES_PATHS)

all: $(OBJECTS_DIR) $(TARGET)



%.a: $(OBJECT_FILES)
	$(AR) $(ARFLAGS) $@ $^

%.dll: $(OBJECT_FILES)
	$(CBUILD) $(LDFLAGS) -o $@ $^

%.so: $(OBJECT_FILES)
	$(CBUILD) $(LDFLAGS) -o $@ $^


$(OBJECTS_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -I $(INCLUDES_DIR) -o $@ -c $<

$(OBJECTS_DIR):
	@$(shell mkdir $(OBJECTS_DIR))