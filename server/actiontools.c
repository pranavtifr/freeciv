/**********************************************************************
 Freeciv - Copyright (C) 1996-2015 - Freeciv Development Team
   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
***********************************************************************/

#ifdef HAVE_CONFIG_H
#include <fc_config.h>
#endif

/* common */
#include "actions.h"

/* server */
#include "aiiface.h"
#include "actiontools.h"
#include "notify.h"
#include "plrhand.h"

/**************************************************************************
  After an action of a diplomat, maybe it will cause a diplomatic incident
  with the victim.
**************************************************************************/
static void maybe_cause_incident(const enum gen_action action,
                                 struct player *offender,
                                 struct player *victim_player,
                                 const struct tile *victim_tile,
                                 const char *victim_link)
{
  if (offender == victim_player) {
    /* The player is more than willing to forgive him self. */
    return;
  }

  if (!pplayers_at_war(offender, victim_player)) {
    switch (action) {
    case ACTION_SPY_BRIBE_UNIT:
      notify_player(offender, victim_tile,
                    E_DIPLOMATIC_INCIDENT, ftc_server,
                    _("You have caused an incident while bribing "
                      "the %s %s."),
                    nation_adjective_for_player(victim_player),
                    victim_link);
      notify_player(victim_player, victim_tile,
                    E_DIPLOMATIC_INCIDENT, ftc_server,
                    _("%s has caused an incident while bribing your %s."),
                    player_name(offender), victim_link);
      break;
    case ACTION_SPY_SABOTAGE_UNIT:
      notify_player(offender, victim_tile,
                    E_DIPLOMATIC_INCIDENT, ftc_server,
                    _("You have caused an incident while"
                      " sabotaging the %s %s."),
                    nation_adjective_for_player(victim_player),
                    victim_link);
      notify_player(victim_player, victim_tile,
                    E_DIPLOMATIC_INCIDENT, ftc_server,
                    _("The %s have caused an incident while"
                      " sabotaging your %s."),
                    nation_plural_for_player(offender),
                    victim_link);
      break;
    case ACTION_SPY_STEAL_TECH:
    case ACTION_SPY_TARGETED_STEAL_TECH:
      notify_player(offender, victim_tile,
                    E_DIPLOMATIC_INCIDENT, ftc_server,
                    _("You have caused an incident while attempting "
                      "to steal tech from %s."),
                    player_name(victim_player));
      notify_player(victim_player, victim_tile,
                    E_DIPLOMATIC_INCIDENT, ftc_server,
                    _("%s has caused an incident while attempting "
                      "to steal tech from you."), player_name(offender));
      break;
    case ACTION_SPY_INCITE_CITY:
      notify_player(offender, victim_tile,
                    E_DIPLOMATIC_INCIDENT, ftc_server,
                    _("You have caused an incident while inciting a "
                      "revolt in %s."), victim_link);
      notify_player(victim_player, victim_tile,
                    E_DIPLOMATIC_INCIDENT, ftc_server,
                    _("The %s have caused an incident while inciting a "
                      "revolt in %s."),
                    nation_plural_for_player(offender), victim_link);
      break;
    case ACTION_SPY_POISON:
      notify_player(offender, victim_tile,
                    E_DIPLOMATIC_INCIDENT, ftc_server,
                    _("You have caused an incident while poisoning %s."),
                    victim_link);
      notify_player(victim_player, victim_tile,
                    E_DIPLOMATIC_INCIDENT, ftc_server,
                    _("The %s have caused an incident while poisoning %s."),
                    nation_plural_for_player(offender), victim_link);
      break;
    case ACTION_SPY_SABOTAGE_CITY:
    case ACTION_SPY_TARGETED_SABOTAGE_CITY:
      notify_player(offender, victim_tile,
                    E_DIPLOMATIC_INCIDENT, ftc_server,
                    _("You have caused an incident while sabotaging %s."),
                    victim_link);
      notify_player(victim_player, victim_tile,
                    E_DIPLOMATIC_INCIDENT, ftc_server,
                    _("The %s have caused an incident while sabotaging %s."),
                    nation_plural_for_player(offender), victim_link);
      break;
    case ACTION_SPY_STEAL_GOLD:
      notify_player(offender, victim_tile,
                    E_DIPLOMATIC_INCIDENT, ftc_server,
                    _("You have caused an incident while"
                      " stealing gold from %s."),
                    victim_link);
      notify_player(victim_player, victim_tile,
                    E_DIPLOMATIC_INCIDENT, ftc_server,
                    _("The %s have caused an incident while"
                      " stealing gold from %s."),
                    nation_plural_for_player(offender), victim_link);
      break;
    case ACTION_COUNT:
    case ACTION_ESTABLISH_EMBASSY:
    case ACTION_SPY_INVESTIGATE_CITY:
    case ACTION_TRADE_ROUTE:
    case ACTION_MARKETPLACE:
    case ACTION_HELP_WONDER:
      return; /* These are not considered offences */
    }
    player_diplstate_get(victim_player, offender)->has_reason_to_cancel = 2;
    call_incident(INCIDENT_DIPLOMAT, offender, victim_player);
    player_update_last_war_action(offender);
    player_update_last_war_action(victim_player);
    send_player_all_c(offender, NULL);
    send_player_all_c(victim_player, NULL);
  }

  return;
}

/**************************************************************************
  Take care of any consequences (like casus belli) of getting caught while
  trying to perform the given action.
**************************************************************************/
void action_consequence_caught(const int act_id,
                               struct player *offender,
                               struct player *victim_player,
                               const struct tile *victim_tile,
                               const char *victim_link)
{
  maybe_cause_incident(act_id, offender,
                       victim_player, victim_tile, victim_link);
}

/**************************************************************************
  Take care of any consequences (like casus belli) of successfully
  performing the given action.
**************************************************************************/
void action_consequence_success(const int act_id,
                                struct player *offender,
                                struct player *victim_player,
                                const struct tile *victim_tile,
                                const char *victim_link)
{
  maybe_cause_incident(act_id, offender,
                       victim_player, victim_tile, victim_link);
}
