# Назначаем компилятор и флаги
CC = gcc

# Имя итогового исполняемого файла
TARGET = app

# Правило по умолчанию: собрать TARGET
all: $(TARGET)

# Линковка объектных файлов в исполняемый файл
$(TARGET): main.o factorize.o
	$(CC) -o $(TARGET) main.o factorize.o

# Компиляция main.c в объектный файл main.o
main.o: main.c
	$(CC) -c main.c

# Компиляция factorize.c в объектный файл factorize.o
factorize.o: factorize.c
	$(CC) -c factorize.c

# Правило для очистки сгенерированных файлов
clean:
	rm -f *.o $(TARGET)