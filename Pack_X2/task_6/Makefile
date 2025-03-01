# Назначаем компилятор и флаги
CC = gcc

# Имя итогового исполняемого файла
TARGET = app

# Правило по умолчанию: собрать TARGET
all: $(TARGET)

# Линковка объектных файлов в исполняемый файл
$(TARGET): main.o func.o
	$(CC) -o $(TARGET) main.o func.o

main.o: main.c
	$(CC) -c main.c

func.o: func.c
	$(CC) -c func.c

# Правило для очистки сгенерированных файлов
clean:
	rm -f *.o $(TARGET)