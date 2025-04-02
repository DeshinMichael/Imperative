gcc hashmap.c -shared -fPIC -O2 -fvisibility=hidden -D HASHMAP_EXPORTS -o hashmap.so

gcc -O2 -Wl,-rpath=. sample.c hashmap.so -o checked_solution