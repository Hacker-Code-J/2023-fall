CC = gcc
CFLAGS = -Wall -Wextra -g
OBJS = pubao_setup.o pubao_opr.o main.o

# Targets
a.out: $(OBJS)
	$(CC) -o $@ $^

pubao_setup.o: pubao_setup.c
	$(CC) $(CFLAGS) -c -o $@ $<

pubao_opr.o: pubao_opr.c
	$(CC) $(CFLAGS) -c -o $@ $<

main.o: main.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f *.o a.out

.PHONY: clean