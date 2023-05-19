###
### CS475 Fall 17
### Makefile for CUDA PA5 matmult
### By Wim Bohm, and Waruna Ranasinghe
###

OPTIONS   :=  -O3 --ptxas-options -v --gpu-architecture=sm_61 --compiler-bindir /usr/local/gcc/6.5.0/bin  -std=c++11 
# Do I need this option?
#-I#Add the path to your cuda-patches/include directory here
EXECS :=  matmult00 matmult01 vecMax00 vecMax01 matmult02
all:$(EXECS)

clean:
	rm -f $(EXECS) *.o

timer.o : timer.cu timer.h
	nvcc $< -c -o $@ $(OPTIONS)

matmultKernel00.o : matmultKernel00.cu matmultKernel.h 
	nvcc $< -c -o $@ $(OPTIONS)

matmult00 : matmult.cu  matmultKernel.h matmultKernel00.o timer.o
	nvcc $< matmultKernel00.o -o $@ $(LIB) timer.o $(OPTIONS)

matmultKernel01.o : matmultKernel01.cu matmultKernel.h 
	nvcc $< -c -o $@ $(OPTIONS) -DFOOTPRINT_SIZE=32

matmult01 : matmult.cu  matmultKernel.h matmultKernel01.o timer.o
	nvcc $< matmultKernel01.o -o $@ $(LIB) timer.o $(OPTIONS) -DFOOTPRINT_SIZE=32

matmultKernel02.o : matmultKernel02.cu matmultKernel.h 
	nvcc $< -c -o $@ $(OPTIONS) -DFOOTPRINT_SIZE=48

matmult02 : matmult.cu  matmultKernel.h matmultKernel02.o timer.o
	nvcc $< matmultKernel02.o -o $@ $(LIB) timer.o $(OPTIONS) -DFOOTPRINT_SIZE=48

vecMaxKernel00.o : vecMaxKernel00.cu vecMaxKernel.h 
	nvcc $< -c -o $@ $(OPTIONS)

vecMax00 : vecMax.cu  vecMaxKernel.h vecMaxKernel00.o timer.o
	nvcc $< vecMaxKernel00.o -o $@ $(LIB) timer.o $(OPTIONS)

vecMaxKernel01.o : vecMaxKernel01.cu vecMaxKernel.h 
	nvcc $< -c -o $@ $(OPTIONS)

vecMax01 : vecMax.cu  vecMaxKernel.h vecMaxKernel01.o timer.o
	nvcc $< vecMaxKernel01.o -o $@ $(LIB) timer.o $(OPTIONS)

tar: matmultKernel00.cu matmultKernel01.cu matmultKernel.h matmult.cu Makefile vecMax.cu vecMaxKernel00.cu vecMaxKernel01.cu vecMaxKernel.h report.pdf
	tar cf PA4.tar  matmultKernel00.cu matmultKernel01.cu matmultKernel.h matmult.cu Makefile vecMax.cu vecMaxKernel00.cu vecMaxKernel01.cu vecMaxKernel.h report.pdf

