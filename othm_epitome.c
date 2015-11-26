#include "othm_epitome.h"
#include <stdio.h>
#include <stdlib.h>

struct othm_epitome *othm_epitome_new(struct othm_epitome *(*gen)(void),
				      struct othm_symbol_struct *symbol)
{
	struct othm_epitome *epitome;

	if (gen != NULL)
		epitome = gen();
	else
		epitome = malloc(sizeof(struct othm_epitome));

	epitome->symbol = symbol;
	epitome->to_be = othm_hashmap_new(NULL);
	epitome->not_to_be = othm_hashmap_new(NULL);

	return epitome;
}

void othm_epitome_add_opinion_to_be(struct othm_epitome *epitome,
				    struct othm_symbol_struct *keyword,
				    double value)
{
	struct othm_opinion *opinion;

	opinion = malloc(sizeof(struct othm_opinion));
	opinion->keyword = keyword;
	opinion->value = value;

	othm_hashmap_add(epitome->to_be, OTHMREQUEST(keyword), opinion);
}

void othm_epitome_add_opinion_not_to_be(struct othm_epitome *epitome,
					struct othm_symbol_struct *keyword,
					double value)
{
	struct othm_opinion *opinion;

	opinion = malloc(sizeof(struct othm_opinion));
	opinion->keyword = keyword;
	opinion->value = value;

	othm_hashmap_add(epitome->not_to_be, OTHMREQUEST(keyword), opinion);
}

void othm_epitome_print_hashmap(struct othm_hashmap *to_be)
{
	struct othm_hashbin *current_hashbin;
	unsigned int hashbin_num;
	unsigned int i;

	current_hashbin = to_be->hashbins;
	hashbin_num = to_be->hashbin_num;
	for (i = 0; i != hashbin_num; ++i) {
		struct othm_hashentry *current_hashentry;

		current_hashentry = current_hashbin->first;
		while (current_hashentry != NULL) {
			struct othm_opinion *opinion;

			printf("  ");
			opinion = current_hashentry->storage;
			othm_symbol_print(opinion->keyword);
			printf(" = %f\n", opinion->value);

			current_hashentry = current_hashentry->next;
		}
		++current_hashbin;
	}
}

double othm_fuzzy_and(double a, double b)
{
	return (a < b) ? a : b;
}

double othm_fuzzy_or(double a, double b)
{
	return (a > b) ? a : b;
}

struct othm_hashmap *othm_epitome_to_be_hashmap_and(struct othm_epitome *epitome,
						    struct othm_hashmap *a,
						    struct othm_hashmap *b)
{
	struct othm_hashbin *current_hashbin;
	unsigned int hashbin_num;
	unsigned int i;

	current_hashbin = a->hashbins;
	hashbin_num = a->hashbin_num;
	for (i = 0; i != hashbin_num; ++i) {
		struct othm_hashentry *current_hashentry;

		current_hashentry = current_hashbin->first;
		while (current_hashentry != NULL) {

			struct othm_opinion *opinion_a;
			struct othm_opinion *opinion_b;

			opinion_a = current_hashentry->storage;
			opinion_b = othm_hashmap_get(b, current_hashentry->key);

			if (opinion_b == NULL)
				goto othm_epitome_to_be_hashmap_and_next;


			othm_epitome_add_opinion_to_be
				(epitome, OTHMSYMBOLSTRUCT(current_hashentry->key),
				 othm_fuzzy_and(opinion_a->value, opinion_b->value));

		othm_epitome_to_be_hashmap_and_next:
			current_hashentry = current_hashentry->next;
		}
		++current_hashbin;
	}
}

struct othm_hashmap *othm_epitome_not_to_be_hashmap_and(struct othm_epitome *epitome,
							struct othm_hashmap *a,
							struct othm_hashmap *b)
{
	struct othm_hashbin *current_hashbin;
	unsigned int hashbin_num;
	unsigned int i;

	current_hashbin = a->hashbins;
	hashbin_num = a->hashbin_num;
	for (i = 0; i != hashbin_num; ++i) {
		struct othm_hashentry *current_hashentry;

		current_hashentry = current_hashbin->first;
		while (current_hashentry != NULL) {
			struct othm_opinion *opinion_a;
			struct othm_opinion *opinion_b;

			opinion_a = current_hashentry->storage;
			opinion_b = othm_hashmap_get(b, current_hashentry->key);

			if (opinion_b == NULL)
				goto othm_epitome_not_to_be_hashmap_and_next;

			othm_epitome_add_opinion_not_to_be
				(epitome, OTHMSYMBOLSTRUCT(current_hashentry->key),
				 othm_fuzzy_and(opinion_a->value, opinion_b->value));
		othm_epitome_not_to_be_hashmap_and_next:
			current_hashentry = current_hashentry->next;
		}
		++current_hashbin;
	}
}

void othm_epitome_and(struct othm_epitome *disjoint,
		      struct othm_epitome *a,
		      struct othm_epitome *b)
{
	othm_epitome_to_be_hashmap_and(disjoint, a->to_be, b->to_be);
	othm_epitome_not_to_be_hashmap_and(disjoint, a->not_to_be, b->not_to_be);
}

void othm_epitome_print(struct othm_epitome *epitome)
{
	printf("[ ");
	othm_symbol_print(epitome->symbol);
	printf(" ] {\n");
	/* printf("+++++++++++++++++++++\n"); */
	printf("-TO BE---------------\n");
	othm_epitome_print_hashmap(epitome->to_be);
	printf("-NOT TO BE-----------\n");
	othm_epitome_print_hashmap(epitome->not_to_be);
	/* printf("+++++++++++++++++++++\n"); */
	printf("}\n");
}
