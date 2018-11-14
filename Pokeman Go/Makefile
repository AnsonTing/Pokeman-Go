all: main.exe

main.exe: main.o arena.o kun.o move.o trainer.o
	g++ -o main.exe main.o arena.o kun.o move.o trainer.o

main.o: main.cpp arena.h container.h item.h kun.h move.h skill.h trainer.h
	g++ -c main.cpp

arena.o: arena.cpp arena.h trainer.h item.h container.h kun.h move.h
	g++ -c arena.cpp

kun.o: kun.cpp kun.h move.h item.h container.h
	g++ -c kun.cpp

move.o: move.cpp kun.h move.h item.h container.h
	g++ -c move.cpp

trainer.o: trainer.cpp trainer.h kun.h item.h container.h
	g++ -c trainer.cpp

clean:
	rm -rf *.o
	rm -rf *.exe
