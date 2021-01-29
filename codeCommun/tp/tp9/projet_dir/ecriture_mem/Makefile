
PROJECTNAME=ecriture_mem
INC=-I ../lib_dir
LIBS=-l crazyrobot
AVRDUDE_PROGRAMMERID=usbasp
OBJCOPY=avr-objcopy
AVRDUDE=avrdude
HEXFORMAT=ihex
LDFLAGS=-L ../lib_dir -Wl,-Map,$(TRG).map -mmcu=$(MCU)
TRG=$(PROJECTNAME).out
HEXROMTRG=$(PROJECTNAME).hex
HEXTRG=$(HEXROMTRG) $(PROJECTNAME).ee.hex

include ../Ressources/Makefile

$(TRG): $(OBJDEPS)
	$(CC) $(LDFLAGS) -o $@ $^ -lm $(LIBS)


%.hex: %.out
	$(OBJCOPY) -j .text -j .data -O $(HEXFORMAT) $< $@

install: $(HEXROMTRG)
	$(AVRDUDE) -c $(AVRDUDE_PROGRAMMERID) -p $(MCU) -P -e -U flash:w:$(HEXROMTRG)

clean:
	$(REMOVE) $(TRG) $(TRG).map $(OBJDEPS) $(HEXTRG) *.d