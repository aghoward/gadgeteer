GCC=g++
FLAGS=--std=c++14 -I./headers -I./factories -L./headers/lib -L./factories/lib

objects=-lelfheader -lutils -lprogramheaderfactory -lsectionheaderfactory -lprogramheader -lsectionheader 

all: headerobjects factoryobjects tester

headerobjects:
	$(MAKE) -C headers

factoryobjects:
	$(MAKE) -C factories

clean:
	$(MAKE) clean -C headers
	$(MAKE) clean -C factories
	rm -f tester

tester: tester.cc headerobjects factoryobjects
	$(GCC) ${FLAGS} -o $@ $< ${objects}
