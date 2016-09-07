

all:
	$(MAKE) -C libsrc
	$(MAKE) -C libsrc++
	$(MAKE) -C mc_event
	$(MAKE) -C data_structure
	$(MAKE) -C config_manager
	$(MAKE) -C mapped_data
clean:
	rm -f #*# *.bak *~ core 
	$(MAKE) -C libsrc      clean
	$(MAKE) -C libsrc++    clean
	$(MAKE) -C mc_event    clean
	$(MAKE) -C data_structure clean
	$(MAKE) -C config_manager clean
	$(MAKE) -C mapped_data clean
