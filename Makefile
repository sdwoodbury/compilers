#Stuart Woodbury
#yr45570@umbc.edu
#february 2015
#cmsc431
#PROJ7
#top level makefile
#one make file to rule them all...

all:
	$(MAKE) -C src all
	
.PHONY: all tests clean

tests:
	mv PROJ7 src
	$(MAKE) -C tests all
	mv test.txt src
	$(MAKE) -C src assembly
	mv test.txt tests
	

.PHONY: stuff
stuff:
	cd src
	mv test.txt ../tests
	cd ..

.PHONY: all tests clean

clean:
	$(MAKE) -C src clean
	$(MAKE) -C tests clean
	rm -rf PROJ7
