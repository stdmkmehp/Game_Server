include  gs.mk

CLEANTARGET = clean

MODS = src task
MODSCLEAN =$(patsubst %, %.$(CLEANTARGET), $(MODS))


all: $(MODS)

.PHONY:  all clean $(MODS) $(MODSCLEAN) 

$(MODS): 
	@echo "Begin to make  module: '$@' ......" 
	cd $@ && $(MAKE);
	@echo "Finish to  make  module: '$@'" 

$(MODSCLEAN):
	@echo "Begin to clean  module: '$(patsubst %.$(CLEANTARGET),%, $@)' ......" 
	cd $(patsubst %.$(CLEANTARGET),%, $@) && $(MAKE) $(CLEANTARGET);
	@echo "Finish to clean  module: '$(patsubst %.$(CLEANTARGET),%, $@)'" 

$(CLEANTARGET): $(MODSCLEAN)