/***********************************************************************
 Freeciv - Copyright (C) 1996 - A Kjeldberg, L Gregersen, P Unold
   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
***********************************************************************/
#ifndef FC__TRADEROUTES_H
#define FC__TRADEROUTES_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "support.h" /* bool */

struct city;
struct city_list;

/* What to do with previously established traderoutes that are now illegal.
 * Used in the network protocol. */
enum traderoute_illegal_cancelling
  {
    TRI_ACTIVE                        = 0, /* Keep them active */
    TRI_INACTIVE                      = 1, /* They are inactive */
    TRI_CANCEL                        = 2, /* Completely cancel them */
    TRI_LAST                          = 3
  };

/* Values used in the network protocol. */
enum trade_route_type {
  TRT_NATIONAL                        = 0,
  TRT_NATIONAL_IC                     = 1, /* Intercontinental */
  TRT_IN                              = 2,
  TRT_IN_IC                           = 3, /* International intercontinental */
  TRT_ALLY                            = 4,
  TRT_ALLY_IC                         = 5,
  TRT_ENEMY                           = 6,
  TRT_ENEMY_IC                        = 7,
  TRT_TEAM                            = 8,
  TRT_TEAM_IC                         = 9,
  TRT_LAST                            = 10
};

/* Values used in the network protocol. */
#define SPECENUM_NAME traderoute_bonus_type
#define SPECENUM_VALUE0 TBONUS_NONE
#define SPECENUM_VALUE0NAME "None"
#define SPECENUM_VALUE1 TBONUS_GOLD
#define SPECENUM_VALUE1NAME "Gold"
#define SPECENUM_VALUE2 TBONUS_SCIENCE
#define SPECENUM_VALUE2NAME "Science"
#define SPECENUM_VALUE3 TBONUS_BOTH
#define SPECENUM_VALUE3NAME "Both"
#include "specenum_gen.h"

struct trade_route_settings {
  int trade_pct;
  enum traderoute_illegal_cancelling cancelling;
  enum traderoute_bonus_type bonus_type;
};

int max_trade_routes(const struct city *pcity);
enum trade_route_type cities_trade_route_type(const struct city *pcity1,
                                              const struct city *pcity2);
int trade_route_type_trade_pct(enum trade_route_type type);

void trade_route_types_init(void);
const char *trade_route_type_name(enum trade_route_type type);
enum trade_route_type trade_route_type_by_name(const char *name);

const char *traderoute_cancelling_type_name(enum traderoute_illegal_cancelling type);
enum traderoute_illegal_cancelling traderoute_cancelling_type_by_name(const char *name);

struct trade_route_settings *
trade_route_settings_by_type(enum trade_route_type type);

bool can_cities_trade(const struct city *pc1, const struct city *pc2);
bool can_establish_trade_route(const struct city *pc1, const struct city *pc2);
bool have_cities_trade_route(const struct city *pc1, const struct city *pc2);
int trade_between_cities(const struct city *pc1, const struct city *pc2);
int city_num_trade_routes(const struct city *pcity);
int get_caravan_enter_city_trade_bonus(const struct city *pc1,
                                       const struct city *pc2,
                                       const bool establish_trade);
int city_trade_removable(const struct city *pcity,
                         struct city_list *would_remove);

#define trade_routes_iterate(c, t)                          \
do {                                                        \
  int _i##t;                                                \
  for (_i##t = 0 ; _i##t < MAX_TRADE_ROUTES ; _i##t++) {    \
    struct city *t = game_city_by_number(c->trade[_i##t]);  \
    if (t != NULL) {

#define trade_routes_iterate_end                            \
    }                                                       \
  }                                                         \
} while(FALSE)

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif  /* FC__TRADEROUTES_H */
