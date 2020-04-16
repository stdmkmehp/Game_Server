include  ../gs.mk

CLEANTARGET = clean

MODS = echo_server
MODSCLEAN =$(patsubst %, %.$(CLEANTARGET), $(MODS))

all: $(MODS)

.PHONY:  all  clean $(MODS) $(MODSCLEAN)

$(MODS):
	@echo "Begin to make task: '$@' ......"
	cd $@ && $(MAKE);
	@echo "Finish to  make task: '$@'"

$(MODSCLEAN):
	@echo "Begin to clean task: '$(patsubst %.$(CLEANTARGET),%, $@)' ......"
	cd $(patsubst %.$(CLEANTARGET),%, $@) && $(MAKE) $(CLEANTARGET);
	@echo "Finish to clean task: '$(patsubst %.$(CLEANTARGET),%, $@)'"

$(CLEANTARGET): $(MODSCLEAN)
