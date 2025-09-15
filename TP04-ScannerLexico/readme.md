--------ESPECIFICACION DEL ESCANER LEXICO---------

Especificación en lenguaje regular:
Token Tipo: Es una palabra reservada que indica el tipo de la variable o de la función.


char x;
unsigned char x;	
short int x;
unsigned short int x;	
int x;
unsigned int x;
long int x;
unsigned long int x;	
float x;	
double x;
long double x;
void x;





Especificación autómata finito:

INICIAL -- 'i' --> I1 -- 'n' --> I2 -- 't' --> FIN: TOKEN_TYPE
INICIAL -- 'c' --> C1 -- 'h' --> C2 -- 'a' --> C3 -- 'r' --> FIN: TOKEN_TYPE
INICIAL -- 'f' --> F1 -- 'l' --> F2 -- 'o' --> F3 -- 'a' --> F4 -- 't' --> FIN: TOKEN_TYPE
INICIAL -- 'd' --> D1 -- 'o' --> D2 -- 'u' --> D3 -- 'b' --> D4 -- 'l' --> D5 -- 'e' --> FIN: TOKEN_TYPE
INICIAL -- 'v' --> V1 -- 'o' --> V2 -- 'i' --> V3 -- 'd' --> FIN: TOKEN_TYPE

