Conversion.o: Conversion.c Conversion.h
	cc -c Conversion.c -o Conversion.o

TablasDeConversion.o: TablasDeConversion.c Conversion.h
	cc -c TablasDeConversion.c -o TablasDeConversion.o

ConversionTest.o: ConversionTest.c Conversion.h
	cc -c ConversionTest.c -o ConversionTest.o

Conversion: Conversion.o 
	cc Conversion.o -o Conversion

ConversionTest: ConversionTest.o Conversion.o 
	cc ConversionTest.o Conversion.o -o ConversionTest

TablasDeConversion: TablasDeConversion.o Conversion.o 
	cc TablasDeConversion.o Conversion.o -o TablasDeConversion

all: TablasDeConversion ConversionTest

tablas: TablasDeConversion
	./TablasDeConversion

test: ConversionTest
	./ConversionTest

todo: all
	@echo "Mostrando tablas..."
	./TablasDeConversion
	@echo ""
	@echo "Ejecutando tests..."
	./ConversionTest
	
clean:
	rm -f TablasDeConversion.o ConversionTest.o Conversion.o TablasDeConversion ConversionTest
