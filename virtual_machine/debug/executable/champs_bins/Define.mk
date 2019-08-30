
export Path1 = "Hello!"

Path2 := $(DEP_PATH)
Path3 := $(shell cd `$(find ../corewar -name 'includes')` | pwd)
#Path3 := $(shell find ../corewar -name 'includes')