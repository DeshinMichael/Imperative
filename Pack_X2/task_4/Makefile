# Назначаем компилятор и флаги
CC = gcc

# Имя итогового исполняемого файла
TARGET = app

# Правило по умолчанию: собрать TARGET
all: $(TARGET)

# Линковка объектных файлов в исполняемый файл
$(TARGET): main.o sum.o query.o
	$(CC) -o $(TARGET) main.o sum.o query.o

main.o: main.c
	$(CC) -c main.c

sum.o: sum.c
	$(CC) -c sum.c

query.o: query.c
	$(CC) -c query.c

# Правило для очистки сгенерированных файлов
clean:
	rm -f *.o $(TARGET)