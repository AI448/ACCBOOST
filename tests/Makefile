
COMPILER=

ifneq ($(strip $(COMPILER)), )
	include $(COMPILER).mk
endif

all:
	$(MAKE) -C META all
	$(MAKE) -C utility all
	
clean:
	$(MAKE) -C META clean
	$(MAKE) -C utility clean

