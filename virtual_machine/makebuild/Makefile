
include Config.make


all: $(DEFAULT_TARGETS)

.PHONY : all

build_2018: $(BUILD_DIRS) ft
	@make -C . -f Build.make

.PHONY : build_2018

build_old: $(BUILD_DIRS) ft
	@make -C . -f Build.make

.PHONY : build_old

debug: ;

.PHONY : debug

ft:
	@make -C $(FT_DIR) build_static

.PHONY : ft

clean:
	@make -C $(FT_DIR) clean
	rm -f $(OBJECT_FILES)
	rm -f $(OBJECT_FILES_2)

.PHONY : clean

fclean: clean
	@make -C $(FT_DIR) fclean
	rm -f $(TARGET)
	rm -f $(TARGET)_old

.PHONY : fclean

re: fclean all

.PHONY : re

$(BUILD_DIRS):
	$(shell mkdir -p $(BUILD_DIRS))