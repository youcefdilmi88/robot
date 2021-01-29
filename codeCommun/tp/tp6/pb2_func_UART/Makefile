
MCU=atmega324pa
PROJECTNAME=libcrazyrobot
PRJSRC=main.cpp
INC=
LIBS=
OPTLEVEL=s
CC=avr-gcc
REMOVE=rm -f
CFLAGS=-I. -MMD $(INC) -g -mmcu=$(MCU) -O$(OPTLEVEL) -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Werror=all
CXXFLAGS=-fno-exceptions
LDFLAGS=-Wl,-Map,$(TRG).map -mmcu=$(MCU)
ARFLAGS=-crs
AR=avr-ar
TRG=$(PROJECTNAME).a
CFILES=$(filter %.c, $(PRJSRC))
CPPFILES=$(filter %.cpp, $(PRJSRC))
OBJDEPS=$(CFILES:.c=.o) $(CPPFILES:.cpp=.o)

.PHONY: all install clean

all: $(TRG)

$(TRG): $(OBJDEPS)
	$(AR) $(ARFLAGS) $(LDFLAGS) -o $(TRG) $(OBJDEPS) -lm $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

%.o: %.cpp
	$(CC) $(CFLAGS) $(CXXFLAGS) -c $<

-include *.d

clean:
	$(REMOVE) $(TRG) $(TRG).map $(OBJDEPS) *.d

