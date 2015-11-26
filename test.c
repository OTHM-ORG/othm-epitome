#include "othm_epitome.h"
#include <stdlib.h>
#include <stdio.h>

OTHM_SYMBOL_INIT(Death);
OTHM_SYMBOL_INIT(Rats);

OTHM_SYMBOL_INIT(Death_Of_Rats);

OTHM_KEYWORD_INIT(Hooded);
OTHM_KEYWORD_INIT(Caring);
OTHM_KEYWORD_INIT(Meloncholy);
OTHM_KEYWORD_INIT(A_dog_person);

int main(int argc, char **args)
{
	struct othm_epitome *death;
	struct othm_epitome *rats;
	struct othm_epitome *death_of_rats;

	death = othm_epitome_new(NULL, OTHM_SYMBOL(Death));
	othm_epitome_add_opinion_to_be
		(death, OTHM_KEYWORD(Hooded), 1);
	othm_epitome_add_opinion_to_be
		(death, OTHM_KEYWORD(Caring), 0.75);
	othm_epitome_add_opinion_to_be
		(death, OTHM_KEYWORD(Meloncholy), 0.87);
	othm_epitome_add_opinion_not_to_be
		(death, OTHM_KEYWORD(A_dog_person), 0.25);
	othm_epitome_print(death);

	rats = othm_epitome_new(NULL, OTHM_SYMBOL(Rats));
	othm_epitome_add_opinion_to_be
		(rats, OTHM_KEYWORD(Caring), 0.03);
	othm_epitome_add_opinion_to_be
		(rats, OTHM_KEYWORD(Meloncholy), 0.44);
	othm_epitome_add_opinion_not_to_be
		(rats, OTHM_KEYWORD(A_dog_person), 1.0);
	othm_epitome_print(rats);

	death_of_rats = othm_epitome_new(NULL, OTHM_SYMBOL(Death_Of_Rats));
	othm_epitome_and(death_of_rats, death, rats);
	othm_epitome_print(death_of_rats);
}
