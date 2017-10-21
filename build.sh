#! /bin/sh -e
cd "test"
gcc -Wall -Werror -Wextra -pedantic -O2 -fPIC  -c test-fail.c -o test-fail.o -I..
gcc -Wall -Werror -Wextra -pedantic -O2 -fPIC  -c test-whitespace.c -o test-whitespace.o -I..
gcc -Wall -Werror -Wextra -pedantic -O2 -fPIC  -c test.c -o test.o -I..
cd ".."
gcc -Wall -Werror -Wextra -pedantic -O2 -fPIC  -c genconfig.c -o genconfig.o
ar rcs libgenconfig.a genconfig.o
gcc -shared -o libgenconfig.so genconfig.o
cd "test"
gcc  -o test-fail.out test-fail.o ../libgenconfig.a
gcc  -o test-whitespace.out test-whitespace.o ../libgenconfig.a
gcc  -o test.out test.o ../libgenconfig.a
cd "../bin"
gcc -Wall -Werror -Wextra -pedantic -O2 -fPIC  -c prog_genconfig.c -o prog_genconfig.o -I..
gcc  -o prog_genconfig.out prog_genconfig.o ../libgenconfig.a
