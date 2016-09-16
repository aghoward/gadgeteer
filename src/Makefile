GCC=g++
AR=ar
FLAGS=--std=c++14 -I. -I./errorhandlers -I./headers -I./factories -I./results -L./lib -L./errorhandlers/lib -L./headers/lib -L./factories/lib -L./results/lib
AR_FLAGS=rcs
objdir=./obj
libdir=./lib

objects=-lerrorhandler -lelfheader -lfileparser -lgadgetfinder -lelfheaderfactory -lprogramheaderfactory -lsectionheaderfactory -lprogramheader -lsectionheader -lbinaryfile -lresultfactory -lresult -lutils

all: ${objdir} ${libdir} ${libdir}/libutils.a ${libdir}/libbinaryfile.a ${libdir}/libfileparser.a ${libdir}/libgadgetfinder.a errorhandlerobjects headerobjects factoryobjects resultobjects tester

${objdir}:
	if [[ ! -d ${objdir} ]]; then mkdir ${objdir}; fi;

${libdir}:
	if [[ ! -d ${libdir} ]]; then mkdir ${libdir}; fi;

${objdir}/%.o: %.cc %.h
	$(GCC) ${FLAGS} -c $< -o $@

${libdir}/lib%.a: ${objdir}/%.o
	$(AR) ${AR_FLAGS} $@ $<

errorhandlerobjects:
	$(MAKE) -C errorhandlers

headerobjects:
	$(MAKE) -C headers

factoryobjects:
	$(MAKE) -C factories

resultobjects:
	$(MAKE) -C results

clean:
	$(MAKE) clean -C headers
	$(MAKE) clean -C factories
	$(MAKE) clean -C results
	$(MAKE) clean -C errorhandlers
	rm -f tester

tester: tester.cc errorhandlerobjects headerobjects factoryobjects
	$(GCC) ${FLAGS} -o $@ $< ${objects}
