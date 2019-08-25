
# By default: Static Library
DEFAULT_TARGETS				:= build_dll build_static build_so


include makebuild/SourceDefinitions.make

TARGET						:=
TARGET_NAME					:= ft
TARGET_PATH					?= $(PROJECT_MAIN_DIR)

CC							:= gcc
CFLAGS						:= -Wall -Wextra -Werror
LDFLAGS						:=
AR							:= ar
ARFLAGS						:= rcs

PROJECT_MAIN_DIR			:= $(__PROJECT_MAIN_DIR)
CONFIGS_DIR					:= $(__CONFIGS_DIR)
SOURCES_DIR					:= $(__SOURCES_DIR)
INCLUDES_DIR				:= $(__INCLUDES_DIR)
OBJECTS_DIR					:= $(__OBJECTS_DIR)
SHARED_OBJECTS_DIR			:= $(__SHARED_OBJECTS_DIR)
DEPENDENCY_DIR				:= $(__DEPENDENCY_DIR)

SOURCE_FILES				:= $(__SOURCE_FILES)
OBJECT_FILES				:= $(__OBJECT_FILES)
SHARED_OBJECT_FILES			:= $(__SHARED_OBJECT_FILES)

SOURCE_DIRECTORIES_PATHS 	:= $(__SOURCE_DIRECTORIES_PATHS)



build_so: TARGET			:= $(TARGET_PATH)/lib$(TARGET_NAME).so

build_so: CBUILD			:= gcc
build_so: CFLAGS			+= -fPIC
build_so: LDFLAGS			+= -shared
build_so: OBJECT_FILES		:= $(SHARED_OBJECT_FILES)
build_so: OBJECTS_DIR		:= $(SHARED_OBJECTS_DIR)



build_dll: TARGET			:= $(TARGET_PATH)/lib$(TARGET_NAME).dll

build_dll: CBUILD			:= gcc
build_dll: CFLAGS			+= -fPIC
build_dll: LDFLAGS			+= -shared
build_dll: OBJECT_FILES		:= $(SHARED_OBJECT_FILES)
build_dll: OBJECTS_DIR		:= $(SHARED_OBJECTS_DIR)



build_static: TARGET		:= $(TARGET_PATH)/lib$(TARGET_NAME).a



export TARGET
export CC
export CFLAGS
export LDFLAGS
export CBUILD
export PROJECT_MAIN_DIR
export INCLUDES_DIR
export OBJECTS_DIR
export SHARED_OBJECTS_DIR
export OBJECT_FILES
export SHARED_OBJECT_FILES
export SOURCE_DIRECTORIES_PATHS

unexport DEFAULT_TARGETS
unexport TARGET_NAME
unexport TARGET_PATH
unexport DEPENDENCY_DIR
unexport SOURCE_FILES
unexport CONFIGS_DIR
unexport SOURCES_DIR
