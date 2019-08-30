
# By default: Static Library
DEFAULT_TARGETS			    ?= build_static


include makebuild/SourceDefinitions.make

FT_TARGET					:=
FT_TARGET_NAME				:= ft
FT_TARGET_PATH				?= $(FT_PROJECT_MAIN_DIR)

FT_CC						:= gcc
FT_CFLAGS					:= -Wall -Wextra -Werror
FT_LDFLAGS					:=
FT_AR						:= ar
FT_ARFLAGS					:= rcs

FT_PROJECT_MAIN_DIR			:= $(__PROJECT_MAIN_DIR)
FT_CONFIGS_DIR				:= $(__CONFIGS_DIR)
FT_SOURCES_DIR				:= $(__SOURCES_DIR)
FT_INCLUDES_DIR				:= $(__INCLUDES_DIR)
FT_OBJECTS_DIR				:= $(__OBJECTS_DIR)
FT_SHARED_OBJECTS_DIR		:= $(__SHARED_OBJECTS_DIR)
FT_DEPENDENCY_DIR			:= $(__DEPENDENCY_DIR)

FT_SOURCE_FILES				:= $(__SOURCE_FILES)
FT_OBJECT_FILES				:= $(__OBJECT_FILES)
FT_SHARED_OBJECT_FILES		:= $(__SHARED_OBJECT_FILES)

FT_SOURCE_DIRECTORIES_PATHS	:= $(__SOURCE_DIRECTORIES_PATHS)



build_so: FT_TARGET			:= $(FT_TARGET_PATH)/lib$(FT_TARGET_NAME).so

build_so: FT_CBUILD			:= gcc
build_so: FT_CFLAGS			+= -fPIC
build_so: FT_LDFLAGS		+= -shared
build_so: FT_OBJECT_FILES	:= $(FT_SHARED_OBJECT_FILES)
build_so: FT_OBJECTS_DIR	:= $(FT_SHARED_OBJECTS_DIR)



build_dll: FT_TARGET		:= $(FT_TARGET_PATH)/lib$(FT_TARGET_NAME).dll

build_dll: FT_CBUILD		:= gcc
build_dll: FT_CFLAGS		+= -fPIC
build_dll: FT_LDFLAGS		+= -shared
build_dll: FT_OBJECT_FILES	:= $(FT_SHARED_OBJECT_FILES)
build_dll: FT_OBJECTS_DIR	:= $(FT_SHARED_OBJECTS_DIR)



build_static: FT_TARGET		:= $(FT_TARGET_PATH)/lib$(FT_TARGET_NAME).a



export FT_TARGET
export FT_CC
export FT_AR
export FT_ARFLAGS
export FT_CFLAGS
export FT_LDFLAGS
export FT_CBUILD
export FT_PROJECT_MAIN_DIR
export FT_INCLUDES_DIR
export FT_OBJECTS_DIR
export FT_SHARED_OBJECTS_DIR
export FT_OBJECT_FILES
export FT_SHARED_OBJECT_FILES
export FT_SOURCE_DIRECTORIES_PATHS

unexport FT_DEFAULT_TARGETS
unexport FT_TARGET_NAME
unexport FT_TARGET_PATH
unexport FT_DEPENDENCY_DIR
unexport FT_SOURCE_FILES
unexport FT_CONFIGS_DIR
unexport FT_SOURCES_DIR
