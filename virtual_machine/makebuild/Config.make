
DEFAULT_TARGETS             ?= build_2018 build_old

include SourceDefinitions.make

TARGET_PATH					?= $(__PROJECT_MAIN_DIR)

TARGET						= $(__TARGET)
TARGET_NAME					:= corewar
__TARGET					:= $(shell echo "$(TARGET_PATH)/$(TARGET_NAME)" | sed 's/\/\//\//g')

TARGET_2					= $(__TARGET_2)
TARGET_NAME_2				:= corewar_old
__TARGET_2					:= $(shell echo "$(TARGET_PATH)/$(TARGET_NAME_2)" | sed 's/\/\//\//g')

CFLAGS						:= -Wall -Wextra -Werror
LFLAGS						= -L $(FT_DIR) -l ft
IFLAGS						= -I $(FT_DIR)/includes -I $(INCLUDES_DIR)


PROJECT_MAIN_DIR			:= $(__PROJECT_MAIN_DIR)
CONFIGS_DIR					:= $(__CONFIGS_DIR)
SOURCES_DIR					:= $(__SOURCES_DIR)
INCLUDES_DIR				:= $(__INCLUDES_DIR)
OBJECTS_DIR					:= $(__OBJECTS_DIR)
DEPENDENCY_DIR				:= $(__DEPENDENCY_DIR)
FT_DIR						:= $(__LIBRARIES_DIR)
BUILD_DIRS					:= $(__BUILD_DIRS)


SOURCE_FILES				:= $(__SOURCE_FILES)
OBJECT_FILES				:= $(__OBJECT_FILES)
OBJECT_FILES_2              := $(__OBJECT_FILES_2)


build_2018: CFLAGS          += -DCOREWAR_VERSION=2018

build_old: OBJECTS_DIR      := $(__OBJECTS_DIR_2)
build_old: OBJECT_FILES     := $(OBJECT_FILES_2)
build_old: TARGET           := $(TARGET_2)

export TARGET

export CFLAGS
export LFLAGS
export IFLAGS

export SOURCES_DIR
export OBJECTS_DIR
export OBJECT_FILES
