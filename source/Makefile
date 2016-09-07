
-include $(RELEASE_BUILD)/CMS/Makefile.common


all: make_libraries make_programs


make_libraries:
	$(MAKE) -C $(RELEASE_BUILD)/source/libraries

make_programs:
	$(MAKE) -C $(RELEASE_BUILD)/source/programs

-include $(RELEASE_ROOT)/CMS/Makefile.common.rules

clean:
	@$(RM) -r $(RELEASE_BIN) $(RELEASE_LIB)
	@find . -name \*.o -exec $(RM) {} \;
	@find . -path \*$(OSNAME)\* -name \*.d -exec $(RM) {} \;
	@$(MAKE) -C $(RELEASE_BUILD)/source/programs clean
	@$(MAKE) -C $(RELEASE_BUILD)/source/libraries clean
