MCU=atmega324pa
PRJSRC=$(wildcard *.cpp)
OPTLEVEL=s
CC=avr-gcc
REMOVE=rm -f
CFLAGS=-I. -MMD $(INC) -g -mmcu=$(MCU) -O$(OPTLEVEL) -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -DF_CPU=8000000
CXXFLAGS=-fno-exceptions
CFILES=$(filter %.c, $(PRJSRC))
CPPFILES=$(filter %.cpp, $(PRJSRC))
OBJDEPS=$(CFILES:.c=.o) $(CPPFILES:.cpp=.o)

.PHONY: all install clean

all: $(TRG)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

%.o: %.cpp
	$(CC) $(CFLAGS) $(CXXFLAGS) -c $<

-include *.d


