import os

os.chdir("/home/bulat/temporary_code/tmp")
os.system("gcc -fPIC -c impl1.c impl2.c")
os.system("gcc -shared -o libimpl1.so impl1.o")
os.system("gcc -shared -o libimpl2.so impl2.o")
os.system("gcc -o dl dl.c")