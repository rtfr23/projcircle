APP_NAME = geom
LIB_NAME = libgeom

CFLAGS = -Wall -Wextra -Werror
CPPFLAGS = -I src -MP -MMD
LDFLAGS =
LDLIBS =

BIN_DIR = bin
OBJ_DIR = obj
SRC_DIR = src
APP_PATH = $(BIN_DIR)/$(APP_NAME)
LIB_PATH = $(OBJ_DIR)/$(SRC_DIR)/$(LIB_NAME)/$(LIB_NAME).a
LIBOBJ_PATH = $(OBJ_DIR)/$(SRC_DIR)/$(LIB_NAME)
APPOBJ_PATH = $(OBJ_DIR)/$(SRC_DIR)/$(APP_NAME)

SRC_EXT = c

APP_SOURCES = $(wildcard $(SRC_DIR)/$(APP_NAME)/*.$(SRC_EXT))
APP_OBJECTS = $(patsubst $(SRC_DIR)/%.$(SRC_EXT), $(OBJ_DIR)/$(SRC_DIR)/%.o, $(APP_SOURCES))

LIB_SOURCES = $(wildcard $(SRC_DIR)/$(LIB_NAME)/*.$(SRC_EXT))
LIB_OBJECTS = $(patsubst $(SRC_DIR)/%.$(SRC_EXT), $(OBJ_DIR)/$(SRC_DIR)/%.o, $(LIB_SOURCES))

DEPS = $(APP_OBJECTS:.o=.d) $(LIB_OBJECTS:.o=.d)

.PHONY: all
all: $(APP_PATH)

-include $(DEPS)

$(APP_PATH): $(APP_OBJECTS) $(LIB_PATH)
	gcc $(CFLAGS) $(CPPFLAGS) $^ -o $@ $(LDFLAGS) $(LDLIBS)

$(LIB_PATH): $(LIB_OBJECTS)
	ar rcs $@ $^

$(OBJ_DIR)/%.o: %.c
	@if not exist "$(dir $@)" mkdir "$(dir $@)"
	gcc -c $(CFLAGS) $(CPPFLAGS) $< -o $@

.PHONY: clean
clean:
	powershell -Command "Remove-Item -Force -Path \"$(APP_PATH).exe\""
	powershell -Command "Remove-Item -Force -Path \"$(LIB_PATH)\""
	powershell -Command "Remove-Item -Force -Path \"$(LIBOBJ_PATH)\*.o""
	powershell -Command "Remove-Item -Force -Path \"$(LIBOBJ_PATH)\*.d""
	powershell -Command "Remove-Item -Force -Path \"$(APPOBJ_PATH)\*.d""
	powershell -Command "Remove-Item -Force -Path \"$(APPOBJ_PATH)\*.o""
