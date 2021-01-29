#include "value_to_interval.h"


/***************************************************************************************************************
* @brief Retourne l'intervalle de distance selon la valeur reçue par le capteur gauche en mode Diagnostic.
* @param uint16_t input, la valeur reçue par le capteur.
* @return Interval_diagnostic, l'intervalle de distance dans laquelle se situe la distance captée par le capteur
****************************************************************************************************************/
Interval_diagnostic value_to_interval_diagnostic_left(uint16_t input)
{
	Interval_diagnostic interval;
	if (347 <= input)
		interval = LESS_15;
	else if (234 <= input && input < 347)
		interval = IN_15_25;
	else if (176 <= input && input < 234)
		interval = IN_25_35;
	else if (153 <= input && input < 176)
		interval = IN_35_45;
	else if (130 <= input && input < 153)
		interval = IN_45_55;
	else if (121 <= input && input < 130)
		interval = IN_55_65;
	else if (90<= input && input < 121)
		interval = IN_65_75;
	else if (input < 90)
		interval = MORE_75;
	else
		{}

	return interval;
}

/***************************************************************************************************************
* @brief Retourne l'intervalle de distance selon la valeur reçue par le capteur droit en mode Diagnostic.
* @param uint16_t input, la valeur reçue par le capteur.
* @return Interval_diagnostic, l'intervalle de distance dans laquelle se situe la distance captée par le capteur
****************************************************************************************************************/
Interval_diagnostic value_to_interval_diagnostic_right(uint16_t input)
{
	Interval_diagnostic interval;
	if (340 <= input)
		interval = LESS_15;
	else if (234 <= input && input < 340)
		interval = IN_15_25;
	else if (180 <= input && input < 234)
		interval = IN_25_35;
	else if (150 <= input && input < 180)
		interval = IN_35_45;
	else if (127 <= input && input < 150)
		interval = IN_45_55;
	else if (118 <= input && input < 127)
		interval = IN_55_65;
	else if (103 <= input && input < 118)
		interval = IN_65_75;
	else if (input < 103)
		interval = MORE_75;
	else
		{}

	return interval;
}

/***************************************************************************************************************
* @brief Retourne l'intervalle de distance selon la valeur reçue par le capteur droit en mode Parcours.
* @param uint16_t input, la valeur reçue par le capteur.
* @return Interval_diagnostic, l'intervalle de distance dans laquelle se situe la distance captée par le capteur
****************************************************************************************************************/
Interval_parcours value_to_interval_parcours_right(uint16_t input)
{
	Interval_parcours interval;
	if (507 < input)
		interval = LESS_100;
	else if(412 < input && input <= 507)
		interval = IN_100_125;
		
	else if(340 < input && input <= 412)
		interval = IN_125_150;
		
	else if (303 < input && input <= 340)
		interval = IN_150_175;
		
	else if (279 < input && input <= 303)
		interval = IN_175_200;
		
	else if (262 < input && input <= 279)
		interval = IN_200_225; 
		
	else if (234 < input && input <= 262)
		interval = IN_225_250;
		
	else if (224 < input && input <= 234)
		interval = IN_250_275;
		
	else if (209 < input && input <= 224)
		interval = IN_275_300;

	else if (input <= 209)
		interval = IN_300_600;


	return interval;
}

/***************************************************************************************************************
* @brief Retourne l'intervalle de distance selon la valeur reçue par le capteur gauche en mode Parcours.
* @param uint16_t input, la valeur reçue par le capteur.
* @return Interval_diagnostic, l'intervalle de distance dans laquelle se situe la distance captée par le capteur
****************************************************************************************************************/
Interval_parcours value_to_interval_parcours_left(uint16_t input)
{
	Interval_parcours interval;
	if (505 < input)
		interval = LESS_100;
	else if(428 < input && input <= 505)
		interval = IN_100_125;
		
	else if(347 < input && input <= 428)
		interval = IN_125_150;
		
	else if (317 < input && input <= 347)
		interval = IN_150_175;
		
	else if (280 < input && input <= 317)
		interval = IN_175_200;
		
	else if (246 < input && input <= 280)
		interval = IN_200_225; 
		
	else if (234 < input && input <= 246)
		interval = IN_225_250;
		
	else if (227 < input && input <= 234)
		interval = IN_250_275;
		
	else if (207 < input && input <= 227)
		interval = IN_275_300;

	else if (input <= 207)
		interval = IN_300_600;

	return interval;
}

