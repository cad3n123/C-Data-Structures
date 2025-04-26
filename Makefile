# Makefile

%: %.c vector.c string.c linked_list.c binary_search_tree.c
	gcc $^ -o $@

