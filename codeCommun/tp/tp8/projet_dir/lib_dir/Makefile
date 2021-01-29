
PROJECTNAME=libcrazyrobot
INC=
ARFLAGS=-crs
AR=avr-ar
TRG=$(PROJECTNAME).a

include ../Ressources/Makefile.commun

$(TRG): $(OBJDEPS)
	$(AR) $(ARFLAGS) -o $@ $^

clean:
	$(REMOVE) $(TRG) $(TRG).map $(OBJDEPS) *.d

