ifeq ($(strip $(PVSNESLIB_HOME)),)
$(error "Please create an environment variable PVSNESLIB_HOME with path to its folder and restart application. (you can do it on windows with <setx PVSNESLIB_HOME "/c/snesdev">)")
endif

include snes_rules.mk
 
.PHONY: process all
 
#---------------------------------------------------------------------------------
# ROMNAME is used in snes_rules file
export ROMNAME := fighter

all: preProcess $(ROMNAME).sfc

preProcess:
	python python/gfx.py

clean: cleanBuildRes cleanRom cleanGfx
