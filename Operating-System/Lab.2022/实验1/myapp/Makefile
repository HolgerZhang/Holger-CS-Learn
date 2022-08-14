objects = myapp.o greeting.o
myapp: $(objects)
	gcc $(objects) -o myapp
greeting.o: greeting.h greeting.c
	gcc greeting.h greeting.c -c
myapp.o: greeting.h myapp.c
	gcc greeting.h myapp.c -c
clean: 
	rm myapp $(objects)
