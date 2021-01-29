#ifndef VALUE_TO_INTERVAL_H
#define VALUE_TO_INTERVAL_H

#include <avr/io.h>

enum Interval_diagnostic {LESS_15 = 10, IN_15_25 = 20, IN_25_35 = 30, IN_35_45 = 40, IN_45_55 = 50, IN_55_65 = 60, IN_65_75 = 70, MORE_75 = 80};
Interval_diagnostic value_to_interval_diagnostic_left(uint16_t input);
Interval_diagnostic value_to_interval_diagnostic_right(uint16_t input);


enum Interval_parcours {LESS_100, IN_100_125, IN_125_150, IN_150_175, IN_175_200, IN_200_225, IN_225_250, IN_250_275, IN_275_300, IN_300_600};
Interval_parcours value_to_interval_parcours_left(uint16_t input);
Interval_parcours value_to_interval_parcours_right(uint16_t input);


#endif /* VALUE_TO_INTERVAL_H */
