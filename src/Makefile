GCC=g++
FLAGS=--std=c++11

objects=headers/obj/elfheader.o headers/obj/utils.o headers/obj/programheader.o

all: headers tester

headerobjects:
	$(MAKE) -C headers

clean:
	$(MAKE) clean -C headers
	rm -f tester

tester: tester.cc headerobjects
	$(GCC) ${FLAGS} -o $@ $< ${objects}
