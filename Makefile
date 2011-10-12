
INCLUDES+=-Iinc

SOURCES+=$(wildcard src/*.c)

CFLAGS+=-Wall
TEST_LIBOPP_CFLAGS=-DTEST_OBJ_FACTORY_UTILS

BASE=$(basename $(notdir $(SOURCES)))
LIBOPP_OBJECTS=$(addprefix obj/, $(addsuffix .o,$(BASE)))
TARGETA=libopp.a
TARGETSO=libopp.so

all: obj_dir $(LIBOPP_TARGETA)  $(LIBOPP_TARGETSO)
	#export LD_LIBRARY_PATH=$(shell pwd)

test:
	$(MAKE) -C test

obj_dir:
	mkdir -p obj

ctags:
	ctags $(SOURCES)
	
obj/%.o: src/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

$(LIBOPP_TARGETA): $(LIBOPP_OBJECTS)
	ar crv $@ $(LIBOPP_OBJECTS)

$(LIBOPP_TARGETSO): $(LIBOPP_OBJECTS)
	$(CC) -shared -o $@ $(LIBOPP_OBJECTS)

install:

clean:
	rm -f $(LIBOPP_OBJECTS) $(LIBOPP_TARGETA) $(LIBOPP_TARGETSO)
	$(MAKE) -C test clean

.PHONY: all test clean ctags obj_dir install

