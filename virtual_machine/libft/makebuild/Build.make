
vpath %.c $(FT_SOURCE_DIRECTORIES_PATHS)

all: $(FT_OBJECTS_DIR) $(FT_TARGET)



%.a: $(FT_OBJECT_FILES)
	$(FT_AR) $(FT_ARFLAGS) $@ $^

%.dll: $(FT_OBJECT_FILES)
	$(FT_CC) $(FT_LDFLAGS) -o $@ $^

%.so: $(FT_OBJECT_FILES)
	$(FT_CC) $(FT_LDFLAGS) -o $@ $^


$(FT_OBJECTS_DIR)/%.o: %.c
	$(FT_CC) $(FT_CFLAGS) -I $(FT_INCLUDES_DIR) -o $@ -c $<

$(FT_OBJECTS_DIR):
	@$(shell mkdir $(FT_OBJECTS_DIR))