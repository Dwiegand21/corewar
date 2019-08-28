
default_target: all

.PHONY : default_target

.NOTPARALLEL:
.SUFFIXES:



all:
	make -C makebuild -f Makefile all

.PHONY : all

build_old:
	make -C makebuild -f Makefile build_old

.PHONY : build_old

build_2018:
	make -C makebuild -f Makefile build_2018

.PHONY : build_2018

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
