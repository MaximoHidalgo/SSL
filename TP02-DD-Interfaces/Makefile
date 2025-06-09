run : TablasDeConversion
	./TablasDeConversion

test : ConversionTest
	./ConversionTest

Conversion.o : Conversion.c Conversion.h
	cc -c Conversion.c -o Conversion.o

ConversionTest : ConversionTest.o Conversion.o
	cc ConversionTest.o Conversion.o -o ConversionTest

ConversionTest.o : ConversionTest.c Conversion.h
	cc -c ConversionTest.c -o ConversionTest.o

clean :
	rm

TablasDeConversion : TablasDeConversion.o Conversion.o
	cc TablasDeConversion.o Conversion.o -o TablasDeConversion