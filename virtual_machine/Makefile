
default_target: all

.PHONY : default_target

.NOTPARALLEL:
.SUFFIXES:



all:
	make -C makebuild -f Makefile all

.PHONY : all

debug:
	make -C makebuild -f Makefile debug

.PHONY : debug

test: ;

.PHONY : test

clean:
	make -C makebuild -f Makefile clean

.PHONY : clean

fclean: clean
	make -C makebuild -f Makefile fclean

.PHONY : fclean

re: fclean all
	make -C makebuild -f Makefile re

.PHONY : re
