GCC=g++
AR=ar
FLAGS=--std=c++14 -I. -I./headers -I./factories -L./lib -L./headers/lib -L./factories/lib
AR_FLAGS=rcs
objdir=./obj
libdir=./lib

objects=-lelfheader -lutils -lprogramheaderfactory -lsectionheaderfactory -lprogramheader -lsectionheader 

all: ${objdir} ${libdir} ${libdir}/libutils.a headerobjects factoryobjects tester

${objdir}:
	if [[ ! -d ${objdir} ]]; then mkdir ${objdir}; fi;

${libdir}:
	if [[ ! -d ${libdir} ]]; then mkdir ${libdir}; fi;

${objdir}/%.o: %.cc %.h
	$(GCC) ${FLAGS} -c $< -o $@

${libdir}/lib%.a: ${objdir}/%.o
	$(AR) ${AR_FLAGS} $@ $<

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
