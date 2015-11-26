all:
	gcc test.c othm_epitome.c -o test -lothm_base -lothm_hashmap -lothm_symbols
