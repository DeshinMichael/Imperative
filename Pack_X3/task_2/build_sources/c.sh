gcc -c zlib/*.c -I zlib
ar rcs zlib.a *.o

gcc -c zlib/minizip/unzip.c zlib/minizip/ioapi.c -I zlib -I zlib/minizip -DUSE_CRYPT
ar rcs minizip.a unzip.o ioapi.o

gcc test.c -I zlib -I zlib/minizip -L. minizip.a zlib.a -o checked_solution