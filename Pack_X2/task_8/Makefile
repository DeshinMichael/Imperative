# Назначаем компилятор и флаги
CC = gcc

# Имя итогового исполняемого файла
TARGET = app

# Правило по умолчанию: собрать TARGET
all: $(TARGET)

# Линковка объектных файлов в исполняемый файл
$(TARGET): sample.o logger.o pack.o
	$(CC) -o $(TARGET) sample.o logger.o pack.o

sample.o: sample.c
	$(CC) -c sample.c

logger.o: logger.c
	$(CC) -c logger.c

pack.o: pack.c
	$(CC) -c pack.c

# Правило для очистки сгенерированных файлов
clean:
	rm -f *.o $(TARGET)