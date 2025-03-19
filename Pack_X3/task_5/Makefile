# Назначаем компилятор и флаги
CC = gcc

# Имя итогового исполняемого файла
TARGET = app

# Правило по умолчанию: собрать TARGET
all: $(TARGET)

# Линковка объектных файлов в исполняемый файл
$(TARGET): sample.o
	$(CC) -o $(TARGET) sample.o

# Компиляция sample.c в объектный файл sample.o
sample.o: sample.c
	$(CC) -c sample.c

# Правило для очистки сгенерированных файлов
clean:
	rm -f *.o $(TARGET)