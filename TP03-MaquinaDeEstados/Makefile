CC = gcc
CFLAGS = -Wall -Wextra -std=c2x

OUT1 = RemoveComments_impl1
OUT2 = RemoveComments_impl2
OUT1_CLEAN = NoComments_impl1.c
OUT2_CLEAN = NoComments_impl2.c

BENCH_REP=1000
#usa sh por defecto
SHELL := /bin/bash

.PHONY: all clean benchmark nocomments1 nocomments2

all: $(OUT1) $(OUT2) nocomments1 nocomments2

$(OUT1): RemoveComments.c
	$(CC) $(CFLAGS) -DIMPLEMENTACION_1 RemoveComments.c -o $(OUT1)

$(OUT2): RemoveComments.c
	$(CC) $(CFLAGS) RemoveComments.c -o $(OUT2)

clean:
	rm -f $(OUT1) $(OUT2) salida1.c salida2.c NoComments_impl1.c NoComments_impl2.c

#desecho salidas poniendolas en dev/null para que se vea bien la dif de tiempo entre implementaciones
benchmark: $(OUT1) $(OUT2)
	@echo "Benchmark implementación 1 (repeticiones $(BENCH_REP))"
	@time for i in $(shell seq 1 $(BENCH_REP)); do ./$(OUT1) < Test.c > /dev/null; done
	@echo "Benchmark implementación 2 (repeticiones $(BENCH_REP))"
	@time for i in $(shell seq 1 $(BENCH_REP)); do ./$(OUT2) < Test.c > /dev/null; done
	@echo "Comparacion de salidas"
	@./$(OUT1) < Test.c > $(OUT1_CLEAN)
	@./$(OUT2) < Test.c > $(OUT2_CLEAN)
	@diff NoComments_impl1.c NoComments_impl2.c && echo "Los archivos son idénticos" || echo "Los archivos difieren"

nocomments1: $(OUT1) Test.c
	./$(OUT1) < Test.c > $(OUT1_CLEAN)

nocomments2: $(OUT2) Test.c
	./$(OUT2) < Test.c > $(OUT2_CLEAN)