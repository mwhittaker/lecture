.PHONY: all clean

all: cent centroid

%: %.c
	gcc -std=c99 -Wall -Wextra -O3 -o $@ $<

clean:
	rm centroid
	rm cent
