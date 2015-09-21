.PHONY: test

CFLAGS = --std=c99

test: workq
	./workq 4

workq: workq.o
	$(CC) $(CFLAGS) -o $@ $^ -lpthread -lm

%.o: %.c
	$(CC) $(CFLAGS) -c -O3 $<

clean:
	rm -f *.o workq
