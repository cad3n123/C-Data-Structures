# Makefile

%: %.c vector.c string.c linked_list.c
	gcc $^ -o $@

