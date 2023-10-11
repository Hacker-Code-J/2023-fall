#CC=gcc				# (built-in variable) compling C programs
#CFLAGS=-g -Wall		# (built-in variable) extra flags to give to C
#OBJS=pubao_setup.o pubao_opr.o main.o
#TARGET=a.out
 
#all. $(TARGET)

#$(TARGET): $(OBJS)
#    $(CC) -o $@ $(OBJS)
# $@ : (automatic variables) current target name
    
#pubao_setup.o : pubao_setup.c
#	$(CC) -c -o pubao_setup.o pubao_setup.c
#    
#pubao_opr.o : pubao_opr.c
#	$(CC) -c -o pubao_opr.o pubao_opr.c
#    
#main.o : main.c
#	$(CC) -c -o main.o main.c
#    
#clean:
#	rm -f *.o
#	rm -f $(TARGET)

a.out : pubao_setup.o pubao_opr.o main.o
	gcc -o a.out pubao_setup.o pubao_opr.o main.o
    
pubao_setup.o : pubao_setup.c
	gcc -c -o pubao_setup.o pubao_setup.c
    
pubao_opr.o : pubao_opr.c
	gcc -c -o pubao_opr.o pubao_opr.c
    
main.o : main.c
	gcc -c -o main.o main.c    

clean:
	rm *.o a.out