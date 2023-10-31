#------------------------------------------------------------------------------
#  Makefile for Dictionary ADT
#
#  make                makes all
#  make all            makes all
#  make WordFrequency  makes WordFrequency binary
#  make Order          makes Order binary
#  make DictionaryTest makes DictionaryTest binary
#  make clean          removes binary files and object files
#------------------------------------------------------------------------------

CC = g++
CFLAGS = -std=c++17 -Wall -Ofast

.PHONY: all clean

all: Order WordFrequency DictionaryTest

Order: Order.o Dictionary.o 
	$(CC) $(CFLAGS) -o Order Order.o Dictionary.o

WordFrequency: WordFrequency.o Dictionary.o
	$(CC) $(CFLAGS) -o WordFrequency WordFrequency.o Dictionary.o

DictionaryTest: DictionaryTest.o Dictionary.o
	$(CC) $(CFLAGS) -o DictionaryTest DictionaryTest.o Dictionary.o 

DictionaryClient: DictionaryClient.o Dictionary.o
	$(CC) $(CFLAGS) -o DictionaryClient DictionaryClient.o Dictionary.o 

%.o : %.cpp
	$(CC) $(CFLAGS) -c -g $<

clean: 
	rm -f WordFrequency Order DictionaryTest *.o