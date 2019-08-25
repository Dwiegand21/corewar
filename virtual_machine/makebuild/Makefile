
include Config.make


all: $(BUILD_DIRS)
	make -C $(FT_DIR) build_static
	make -C . -f Build.make

debug:
	echo "undefine"

clean:
	make -C $(FT_DIR) clean
	rm -f $(OBJECT_FILES)

fclean: clean
	make -C $(FT_DIR) fclean
	rm -f $(TARGET)

re: fclean all


$(BUILD_DIRS):
	$(shell mkdir -p $(BUILD_DIRS))