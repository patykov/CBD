Compilar:
g++ -I . -c *.cpp

Linkar:
g++ *.o -o main

Completo:
g++ -I . -c *.cpp && g++ *.o -o main && ./main

