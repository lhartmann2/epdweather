DIR_FONTS = ./Fonts
DIR_OBJ = ./obj
DIR_BIN = ./bin

OBJ_C = $(wildcard ${DIR_FONTS}/*.c ${DIR_OBJ}/*.c)
OBJ_O = $(patsubst %.c,${DIR_BIN}/%.o,$(notdir ${OBJ_C}))

TARGET = epd
#BIN_TARGET = ${DIR_BIN}/${TARGET}

CC = gcc

MSG = -g -O0 -Wall
DEBUG = -DUSE_DEBUG
# DEBUG =
CFLAGS += $(MSG) $(DEBUG) -I../bcm2835-1.68/src -I../c-weather/include

LIB = -L../bcm2835-1.68/src -L../c-weather/src -lbcm2835 -lcweather -lm

${TARGET}:${OBJ_O}
	$(CC) $(CFLAGS) $(OBJ_O) -o $@ $(LIB)

${DIR_BIN}/%.o : $(DIR_OBJ)/%.c
	$(CC) $(CFLAGS) -c  $< -o $@ $(LIB)

${DIR_BIN}/%.o:$(DIR_FONTS)/%.c
	$(CC) $(CFLAGS) -c  $< -o $@

clean:
	rm $(DIR_BIN)/*.*
	rm $(TARGET)
