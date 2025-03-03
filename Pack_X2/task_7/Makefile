# Назначаем компилятор и флаги
CC = gcc

# Имя итогового исполняемого файла
TARGET = app

# Правило по умолчанию: собрать TARGET
all: $(TARGET)

# Линковка объектных файлов в исполняемый файл
$(TARGET): main.o primes.o
	$(CC) -o $(TARGET) main.o primes.o

# Компиляция main.c в объектный файл main.o
main.o: main.c
	$(CC) -c main.c

# Компиляция factorize.c в объектный файл factorize.o
primes.o: primes.c
	$(CC) -c primes.c

# Правило для очистки сгенерированных файлов
clean:
	rm -f *.o $(TARGET)