
  CFLAGS      += -ggdb -pg
  CXXFLAGS    += -ggdb -pg


SOURCE_DIRECTORIES = $(filter-out Makefile, $(wildcard *))

all: $(SOURCE_DIRECTORIES)

$(SOURCE_DIRECTORIES):
	if [ -d $@ ] ; then $(MAKE) $@.dir ; fi

clean:
	for dir in $(SOURCE_DIRECTORIES); \
	do $(MAKE) -C $$dir clean; \
	done

%.dir:
	$(MAKE) -C $*

help:
	@echo SOURCE_DIRECTORIES = $(SOURCE_DIRECTORIES)

.PHONY: $(SOURCE_DIRECTORIES)

