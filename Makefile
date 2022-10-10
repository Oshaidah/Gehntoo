
CC = gcc
CFLAGS = -g -Wall -std=c89 -pedantic-errors
TARGET = p1_oshaidah_205
$(TARGET):$(TARGET).c
	$(CC) $(TARGET).c -o $(TARGET) $(CFLAGS)
clean:
	rm $(TARGET)
																								                            
