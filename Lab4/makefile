CC = gcc
CFLAGS = -Wall -Wextra

LIB_DIR = /usr/local/lib

dl_main: impl1 impl2
	$(CC) $(CFLAGS) -o dl_main.out dl_main.c -ldl -pedantic

st_main_impl1: impl1
	$(CC) $(CFLAGS) -o st_main1.out st_main.c impl1.o -lm -pedantic

st_main_impl2: impl2
	$(CC) $(CFLAGS) -o st_main2.out st_main.c impl2.o -lm -pedantic

impl1: lib1
	$(CC) $(CFLAGS) -shared -o libimpl1.so impl1.o -lm -pedantic

impl2: lib2
	$(CC) $(CFLAGS) -shared -o libimpl2.so impl2.o -lm -pedantic

lib1:
	$(CC) $(CFLAGS) -c impl1.c -fPIC

lib2:
	$(CC) $(CFLAGS) -c impl2.c -fPIC

clear:
	rm -f *.out *.so *.o