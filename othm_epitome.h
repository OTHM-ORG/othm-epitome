#ifndef OTHM_EPITOME_H
#define OTHM_EPITOME_H

#include <othm_hashmap.h>
#include <othm_symbols.h>

struct othm_epitome {
	struct othm_symbol_struct *symbol;
	struct othm_hashmap *to_be;
	struct othm_hashmap *not_to_be;
};

struct othm_opinion {
	struct othm_symbol_struct *keyword;
	double value;
};

struct othm_epitome *othm_epitome_new(struct othm_epitome *(*gen)(void),
				      struct othm_symbol_struct *symbol);

void othm_epitome_add_opinion_to_be(struct othm_epitome *epitome,
				    struct othm_symbol_struct *keyword,
				    double value);

void othm_epitome_add_opinion_not_to_be(struct othm_epitome *epitome,
					struct othm_symbol_struct *keyword,
					double value);

void othm_epitome_print_hashmap(struct othm_hashmap *to_be);

void othm_epitome_print(struct othm_epitome *epitome);

void othm_epitome_and(struct othm_epitome *disjoint,
		      struct othm_epitome *a,
		      struct othm_epitome *b);

#endif
