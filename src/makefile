include  ../gs.mk

CLEANTARGET = clean

MODS = conn
MODSCLEAN =$(patsubst %, %.$(CLEANTARGET), $(MODS))

all: $(MODS)

.PHONY:  all  clean $(MODS) $(MODSCLEAN)

$(MODS):
	@echo "Begin to make gameserver module: '$@' ......"
	cd $@ && $(MAKE);
	@echo "Finish to  make gameserver module: '$@'"

$(MODSCLEAN):
	@echo "Begin to clean gameserver module: '$(patsubst %.$(CLEANTARGET),%, $@)' ......"
	cd $(patsubst %.$(CLEANTARGET),%, $@) && $(MAKE) $(CLEANTARGET);
	@echo "Finish to clean gameserver module: '$(patsubst %.$(CLEANTARGET),%, $@)'"

$(CLEANTARGET): $(MODSCLEAN)
