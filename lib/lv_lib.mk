CSRCS += lodepng.c

DEPPATH += --dep-path lib
VPATH += :lib

CFLAGS += "-I$(LVGL_DIR)/lib"
