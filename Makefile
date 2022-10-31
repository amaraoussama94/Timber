
Timber:Timber.o
	g++ Timber.o -o Timber -lsfml-graphics -lsfml-window -lsfml-system


Timber.o:Timber.cpp
	g++ -c Timber.cpp
clean: rm *.o


