gcc main.c matrixsqr.c -o checked_solution libopenblas.so -lpthread

gcc myblas.c -shared -fPIC -O2 -o myblas.so