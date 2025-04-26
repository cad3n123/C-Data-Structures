# Makefile

%: %.c vector.c string.c
	gcc $^ -o $@

