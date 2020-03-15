NRFX_SRC_DIR := external/nrfx/drivers/src

NRFX_SRCS := $(wildcard $(NRFX_SRC_DIR)/*.c)
NRFX_INC := -Iexternal/nrfx/drivers/include \
	    -Iexternal/nrfx \
	    -Iexternal/nrfx/mdk