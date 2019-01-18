/*****************************************************************************
 Freeciv - Copyright (C) 2005 - The Freeciv Project
   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
*****************************************************************************/

#ifndef FC__API_CLIENT_BASE_H
#define FC__API_CLIENT_BASE_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* common/scriptcore */
#include "luascript_types.h"

struct lua_State;

Player *api_client_player(lua_State *L);
void api_client_chat_base(lua_State *L, const char *msg);
void api_client_unit_airlift(lua_State *L, Unit *punit, City *pcity);
void api_client_unit_load(lua_State *L, Unit *pcargo, Unit *ptransport);
void api_client_unit_move(lua_State *L, Unit *punit, Tile *ptile);
void api_client_unit_upgrade(lua_State *L, Unit *punit);
void api_client_diplomat_action(lua_State *L, Unit *pdiplo, int target_id,
                                int value, int action);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* FC__API_CLIENT_BASE_H */

