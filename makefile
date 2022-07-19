all : EXEC clean EXECUTION

algo.o : algo.c functions.h
	gcc -c -Wall algo.c


main.o : compression.c functions.h
	gcc -c -Wall compression.c

matrice.o : matrice.c functions.h
	gcc -c -Wall matrice.c

menu.o : menu.c functions.h
	gcc -c -Wall menu.c

main.o : main.c functions.h
	gcc -c -Wall main.c

EXEC : main.o menu.o matrice.o compression.o algo.o
	gcc -o EXEC -Wall main.o menu.o matrice.o compression.o algo.o -lm
        
clean:
	rm -rf *.o
	
EXECUTION :
	./EXEC
	
	
