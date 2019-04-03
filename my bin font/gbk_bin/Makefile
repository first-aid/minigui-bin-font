
DIR_SRC=./src
DIR_OBJ=./obj
DIR_INC=./include

APPNAME=test

CC=gcc
OFLAGS=-o
CFLAGS=-c -I$(DIR_INC)
LDFLAGS=-lpthread
RM=rm

SRC_S=$(wildcard $(DIR_SRC)/*.c)
FILES=$(notdir $(SRC_S))
OBJS=$(patsubst %.c, $(DIR_OBJ)/%.o, $(FILES))

all:$(OBJS)
	$(CC) $(OFLAGS) $(APPNAME) $^ $(LDFLAGS)
	

$(DIR_OBJ)/%.o:$(DIR_SRC)/%.c
	$(CC) $(CFLAGS) $(OFLAGS) $@ $<	

clean:
	$(RM) -f $(OBJS) $(APPNAME)
	
