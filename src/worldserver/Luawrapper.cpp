/*
** Lua binding: worldserver
** Generated automatically by tolua++-1.0.5 on Fri Oct 17 16:35:02 2008.
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int tolua_worldserver_open (lua_State* tolua_S);

#include "WorldServer.h"
#include "GameClient.h"
#include "Object.h"
#include "Common.h"
#include "WorldServer.h"
#include "Database.h"
#include "Console.h"
#include "CommandInterpreter.h"
#include "StringFun.h"
#include "version.h"
#include "Player.h"
#include "Affect.h"
#include "Vector.h"

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_WorldServer (lua_State* tolua_S)
{
 WorldServer* self = (WorldServer*) tolua_tousertype(tolua_S,1,0);
  self->DecRef();
 return 0;
}

static int tolua_collect_GameClient (lua_State* tolua_S)
{
 GameClient* self = (GameClient*) tolua_tousertype(tolua_S,1,0);
  delete self;
 return 0;
}

static int tolua_collect_time_t (lua_State* tolua_S)
{
 time_t* self = (time_t*) tolua_tousertype(tolua_S,1,0);
  delete self;
 return 0;
}

static int tolua_collect_ItemPrototype (lua_State* tolua_S)
{
 ItemPrototype* self = (ItemPrototype*) tolua_tousertype(tolua_S,1,0);
  delete self;
 return 0;
}

static int tolua_collect_NetworkPacket (lua_State* tolua_S)
{
 NetworkPacket* self = (NetworkPacket*) tolua_tousertype(tolua_S,1,0);
  self->DecRef();
 return 0;
}

static int tolua_collect_Modifier (lua_State* tolua_S)
{
 Modifier* self = (Modifier*) tolua_tousertype(tolua_S,1,0);
  delete self;
 return 0;
}

static int tolua_collect_Item (lua_State* tolua_S)
{
 Item* self = (Item*) tolua_tousertype(tolua_S,1,0);
  self->DecRef();
 return 0;
}

static int tolua_collect_Unit (lua_State* tolua_S)
{
 Unit* self = (Unit*) tolua_tousertype(tolua_S,1,0);
  delete self;
 return 0;
}

static int tolua_collect_Base (lua_State* tolua_S)
{
 Base* self = (Base*) tolua_tousertype(tolua_S,1,0);
  self->DecRef();
 return 0;
}

static int tolua_collect_Affect (lua_State* tolua_S)
{
 Affect* self = (Affect*) tolua_tousertype(tolua_S,1,0);
  delete self;
 return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"Database");
 tolua_usertype(tolua_S,"Socket");
 tolua_usertype(tolua_S,"GameClient");
 tolua_usertype(tolua_S,"DatabaseExecutor");
 tolua_usertype(tolua_S,"Item");
 tolua_usertype(tolua_S,"Modifier");
 tolua_usertype(tolua_S,"Client");
 tolua_usertype(tolua_S,"Base");
 tolua_usertype(tolua_S,"ObjectVector");
 tolua_usertype(tolua_S,"Spell");
 tolua_usertype(tolua_S,"time_t");
 tolua_usertype(tolua_S,"WorldServer");
 tolua_usertype(tolua_S,"ItemPrototype");
 tolua_usertype(tolua_S,"Unit");
 tolua_usertype(tolua_S,"Log");
 tolua_usertype(tolua_S,"Player");
 tolua_usertype(tolua_S,"NetworkPacket");
 tolua_usertype(tolua_S,"Object");
 tolua_usertype(tolua_S,"Timer");
 tolua_usertype(tolua_S,"SpellEntry");
 tolua_usertype(tolua_S,"Affect");
 tolua_usertype(tolua_S,"Server");
}

/* method: new of class  Base */
static int tolua_worldserver_Base_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"Base",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
 {
  Base* tolua_ret = (Base*)  new Base();
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"Base");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}

/* method: new_local of class  Base */
static int tolua_worldserver_Base_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"Base",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
 {
  Base* tolua_ret = (Base*)  new Base();
 tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"Base");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}

/* method: IncRef of class  Base */
static int tolua_worldserver_Base_IncRef00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Base",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  Base* self = (Base*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IncRef'",NULL);
#endif
 {
  self->IncRef();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IncRef'.",&tolua_err);
 return 0;
#endif
}

/* method: DecRef of class  Base */
static int tolua_worldserver_Base_DecRef00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Base",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  Base* self = (Base*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'DecRef'",NULL);
#endif
 {
  self->DecRef();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'DecRef'.",&tolua_err);
 return 0;
#endif
}

/* method: GetRefCount of class  Base */
static int tolua_worldserver_Base_GetRefCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Base",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  Base* self = (Base*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetRefCount'",NULL);
#endif
 {
  int tolua_ret = (int)  self->GetRefCount();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetRefCount'.",&tolua_err);
 return 0;
#endif
}

/* get function: length of class  NetworkPacket */
static int tolua_get_NetworkPacket_unsigned_length(lua_State* tolua_S)
{
  NetworkPacket* self = (NetworkPacket*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'length'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->length);
 return 1;
}

/* set function: length of class  NetworkPacket */
static int tolua_set_NetworkPacket_unsigned_length(lua_State* tolua_S)
{
  NetworkPacket* self = (NetworkPacket*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'length'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->length = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* method: new of class  NetworkPacket */
static int tolua_worldserver_NetworkPacket_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"NetworkPacket",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
 {
  NetworkPacket* tolua_ret = (NetworkPacket*)  new NetworkPacket();
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"NetworkPacket");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}

/* method: new_local of class  NetworkPacket */
static int tolua_worldserver_NetworkPacket_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"NetworkPacket",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
 {
  NetworkPacket* tolua_ret = (NetworkPacket*)  new NetworkPacket();
 tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"NetworkPacket");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}

/* method: new of class  NetworkPacket */
static int tolua_worldserver_NetworkPacket_new01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"NetworkPacket",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  unsigned int newlength = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
 {
  NetworkPacket* tolua_ret = (NetworkPacket*)  new NetworkPacket(newlength);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"NetworkPacket");
 }
 }
 return 1;
tolua_lerror:
 return tolua_worldserver_NetworkPacket_new00(tolua_S);
}

/* method: new_local of class  NetworkPacket */
static int tolua_worldserver_NetworkPacket_new01_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"NetworkPacket",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  unsigned int newlength = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
 {
  NetworkPacket* tolua_ret = (NetworkPacket*)  new NetworkPacket(newlength);
 tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"NetworkPacket");
 }
 }
 return 1;
tolua_lerror:
 return tolua_worldserver_NetworkPacket_new00_local(tolua_S);
}

/* method: SetLength of class  NetworkPacket */
static int tolua_worldserver_NetworkPacket_SetLength00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"NetworkPacket",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  NetworkPacket* self = (NetworkPacket*)  tolua_tousertype(tolua_S,1,0);
  unsigned int newlength = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetLength'",NULL);
#endif
 {
  self->SetLength(newlength);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetLength'.",&tolua_err);
 return 0;
#endif
}

/* method: Assemble of class  NetworkPacket */
static int tolua_worldserver_NetworkPacket_Assemble00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"NetworkPacket",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  NetworkPacket* self = (NetworkPacket*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Assemble'",NULL);
#endif
 {
  self->Assemble();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Assemble'.",&tolua_err);
 return 0;
#endif
}

/* method: Listen of class  Socket */
static int tolua_worldserver_Socket_Listen00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"Socket",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isusertype(tolua_S,3,"Log",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  int port = ((int)  tolua_tonumber(tolua_S,2,0));
  Log* iLogger = ((Log*)  tolua_tousertype(tolua_S,3,0));
 {
  Socket* tolua_ret = (Socket*)  Socket::Listen(port,iLogger);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"Socket");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Listen'.",&tolua_err);
 return 0;
#endif
}

/* method: Connect of class  Socket */
static int tolua_worldserver_Socket_Connect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"Socket",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isstring(tolua_S,3,0,&tolua_err) ||
 !tolua_isusertype(tolua_S,4,"Log",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  int port = ((int)  tolua_tonumber(tolua_S,2,0));
  char* host = ((char*)  tolua_tostring(tolua_S,3,0));
  Log* iLogger = ((Log*)  tolua_tousertype(tolua_S,4,0));
 {
  Socket* tolua_ret = (Socket*)  Socket::Connect(port,host,iLogger);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"Socket");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Connect'.",&tolua_err);
 return 0;
#endif
}

/* method: ErrorString of class  Socket */
static int tolua_worldserver_Socket_ErrorString00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"Socket",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  unsigned int code = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
 {
  char* tolua_ret = (char*)  Socket::ErrorString(code);
 tolua_pushstring(tolua_S,(const char*)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ErrorString'.",&tolua_err);
 return 0;
#endif
}

/* method: ReceiveData of class  Socket */
static int tolua_worldserver_Socket_ReceiveData00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Socket",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  Socket* self = (Socket*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ReceiveData'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->ReceiveData();
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ReceiveData'.",&tolua_err);
 return 0;
#endif
}

/* method: SendData of class  Socket */
static int tolua_worldserver_Socket_SendData00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Socket",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"NetworkPacket",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  Socket* self = (Socket*)  tolua_tousertype(tolua_S,1,0);
  NetworkPacket* data = ((NetworkPacket*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SendData'",NULL);
#endif
 {
  self->SendData(data);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SendData'.",&tolua_err);
 return 0;
#endif
}

/* method: SendData of class  Socket */
static int tolua_worldserver_Socket_SendData01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Socket",0,&tolua_err) ||
 !tolua_isuserdata(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  Socket* self = (Socket*)  tolua_tousertype(tolua_S,1,0);
  const void* data = ((const void*)  tolua_touserdata(tolua_S,2,0));
  unsigned int length = (( unsigned int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SendData'",NULL);
#endif
 {
  self->SendData(data,length);
 }
 }
 return 0;
tolua_lerror:
 return tolua_worldserver_Socket_SendData00(tolua_S);
}

/* method: SendPending of class  Socket */
static int tolua_worldserver_Socket_SendPending00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Socket",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  Socket* self = (Socket*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SendPending'",NULL);
#endif
 {
  self->SendPending();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SendPending'.",&tolua_err);
 return 0;
#endif
}

/* method: Accept of class  Socket */
static int tolua_worldserver_Socket_Accept00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Socket",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  Socket* self = (Socket*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Accept'",NULL);
#endif
 {
  Socket* tolua_ret = (Socket*)  self->Accept();
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"Socket");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Accept'.",&tolua_err);
 return 0;
#endif
}

/* method: InterestedEvents of class  Socket */
static int tolua_worldserver_Socket_InterestedEvents00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Socket",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  Socket* self = (Socket*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'InterestedEvents'",NULL);
#endif
 {
  unsigned int tolua_ret = ( unsigned int)  self->InterestedEvents();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'InterestedEvents'.",&tolua_err);
 return 0;
#endif
}

/* method: Connected of class  Socket */
static int tolua_worldserver_Socket_Connected00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const Socket",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const Socket* self = (const Socket*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Connected'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->Connected();
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Connected'.",&tolua_err);
 return 0;
#endif
}

/* method: GetIP of class  Socket */
static int tolua_worldserver_Socket_GetIP00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Socket",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  Socket* self = (Socket*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetIP'",NULL);
#endif
 {
  char* tolua_ret = (char*)  self->GetIP();
 tolua_pushstring(tolua_S,(const char*)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetIP'.",&tolua_err);
 return 0;
#endif
}

/* method: SetLogger of class  Socket */
static int tolua_worldserver_Socket_SetLogger00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Socket",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"Log",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  Socket* self = (Socket*)  tolua_tousertype(tolua_S,1,0);
  Log* iLogger = ((Log*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetLogger'",NULL);
#endif
 {
  self->SetLogger(iLogger);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetLogger'.",&tolua_err);
 return 0;
#endif
}

/* method: Rewind of class  Socket */
static int tolua_worldserver_Socket_Rewind00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Socket",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  Socket* self = (Socket*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Rewind'",NULL);
#endif
 {
  self->Rewind();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Rewind'.",&tolua_err);
 return 0;
#endif
}

/* method: Avail of class  Socket */
static int tolua_worldserver_Socket_Avail00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Socket",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  Socket* self = (Socket*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Avail'",NULL);
#endif
 {
  unsigned int tolua_ret = ( unsigned int)  self->Avail();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Avail'.",&tolua_err);
 return 0;
#endif
}

/* method: Chewed of class  Socket */
static int tolua_worldserver_Socket_Chewed00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Socket",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  Socket* self = (Socket*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Chewed'",NULL);
#endif
 {
  unsigned int tolua_ret = ( unsigned int)  self->Chewed();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Chewed'.",&tolua_err);
 return 0;
#endif
}

/* method: Swallow of class  Socket */
static int tolua_worldserver_Socket_Swallow00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Socket",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  Socket* self = (Socket*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Swallow'",NULL);
#endif
 {
  self->Swallow();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Swallow'.",&tolua_err);
 return 0;
#endif
}

/* method: Skip of class  Socket */
static int tolua_worldserver_Socket_Skip00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Socket",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  Socket* self = (Socket*)  tolua_tousertype(tolua_S,1,0);
  unsigned int iLength = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Skip'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->Skip(iLength);
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Skip'.",&tolua_err);
 return 0;
#endif
}

/* method: Get of class  Socket */
static int tolua_worldserver_Socket_Get00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Socket",0,&tolua_err) ||
 !tolua_isuserdata(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  Socket* self = (Socket*)  tolua_tousertype(tolua_S,1,0);
  void* oData = ((void*)  tolua_touserdata(tolua_S,2,0));
  unsigned int iDataSize = (( unsigned int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Get'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->Get(oData,iDataSize);
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Get'.",&tolua_err);
 return 0;
#endif
}

/* method: Get of class  Socket */
static int tolua_worldserver_Socket_Get01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Socket",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  Socket* self = (Socket*)  tolua_tousertype(tolua_S,1,0);
  unsigned char b = (( unsigned char)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Get'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->Get(b);
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 tolua_pushnumber(tolua_S,(lua_Number)b);
 }
 }
 return 2;
tolua_lerror:
 return tolua_worldserver_Socket_Get00(tolua_S);
}

/* method: GetLE of class  Socket */
static int tolua_worldserver_Socket_GetLE00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Socket",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  Socket* self = (Socket*)  tolua_tousertype(tolua_S,1,0);
  unsigned short w16 = (( unsigned short)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetLE'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->GetLE(w16);
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 tolua_pushnumber(tolua_S,(lua_Number)w16);
 }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetLE'.",&tolua_err);
 return 0;
#endif
}

/* method: GetLE of class  Socket */
static int tolua_worldserver_Socket_GetLE01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Socket",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  Socket* self = (Socket*)  tolua_tousertype(tolua_S,1,0);
  unsigned int w32 = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetLE'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->GetLE(w32);
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 tolua_pushnumber(tolua_S,(lua_Number)w32);
 }
 }
 return 2;
tolua_lerror:
 return tolua_worldserver_Socket_GetLE00(tolua_S);
}

/* method: GetLE of class  Socket */
static int tolua_worldserver_Socket_GetLE02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Socket",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  Socket* self = (Socket*)  tolua_tousertype(tolua_S,1,0);
  unsigned long long w64 = (( unsigned long long)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetLE'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->GetLE(w64);
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 tolua_pushnumber(tolua_S,(lua_Number)w64);
 }
 }
 return 2;
tolua_lerror:
 return tolua_worldserver_Socket_GetLE01(tolua_S);
}

/* method: GetLE of class  Socket */
static int tolua_worldserver_Socket_GetLE03(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Socket",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  Socket* self = (Socket*)  tolua_tousertype(tolua_S,1,0);
  float f32 = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetLE'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->GetLE(f32);
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 tolua_pushnumber(tolua_S,(lua_Number)f32);
 }
 }
 return 2;
tolua_lerror:
 return tolua_worldserver_Socket_GetLE02(tolua_S);
}

/* method: GetBE of class  Socket */
static int tolua_worldserver_Socket_GetBE00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Socket",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  Socket* self = (Socket*)  tolua_tousertype(tolua_S,1,0);
  unsigned short w16 = (( unsigned short)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetBE'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->GetBE(w16);
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 tolua_pushnumber(tolua_S,(lua_Number)w16);
 }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetBE'.",&tolua_err);
 return 0;
#endif
}

/* method: GetBE of class  Socket */
static int tolua_worldserver_Socket_GetBE01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Socket",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  Socket* self = (Socket*)  tolua_tousertype(tolua_S,1,0);
  unsigned int w32 = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetBE'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->GetBE(w32);
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 tolua_pushnumber(tolua_S,(lua_Number)w32);
 }
 }
 return 2;
tolua_lerror:
 return tolua_worldserver_Socket_GetBE00(tolua_S);
}

/* method: GetCStr of class  Socket */
static int tolua_worldserver_Socket_GetCStr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Socket",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  Socket* self = (Socket*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetCStr'",NULL);
#endif
 {
  char* tolua_ret = (char*)  self->GetCStr();
 tolua_pushstring(tolua_S,(const char*)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetCStr'.",&tolua_err);
 return 0;
#endif
}

/* get function: Logger of class  Database */
static int tolua_get_Database_Logger_ptr(lua_State* tolua_S)
{
  Database* self = (Database*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Logger'",NULL);
#endif
 tolua_pushusertype(tolua_S,(void*)self->Logger,"Log");
 return 1;
}

/* set function: Logger of class  Database */
static int tolua_set_Database_Logger_ptr(lua_State* tolua_S)
{
  Database* self = (Database*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Logger'",NULL);
 if (!tolua_isusertype(tolua_S,2,"Log",0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Logger = ((Log*)  tolua_tousertype(tolua_S,2,0));
 return 0;
}

/* method: Create of class  Database */
static int tolua_worldserver_Database_Create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"Database",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isstring(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  DatabaseType dbType = ((DatabaseType) (int)  tolua_tonumber(tolua_S,2,0));
  const char* dbAddress = ((const char*)  tolua_tostring(tolua_S,3,0));
 {
  Database* tolua_ret = (Database*)  Database::Create(dbType,dbAddress);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"Database");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Create'.",&tolua_err);
 return 0;
#endif
}

/* method: ParseType of class  Database */
static int tolua_worldserver_Database_ParseType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"Database",0,&tolua_err) ||
 !tolua_isstring(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const char* dbType = ((const char*)  tolua_tostring(tolua_S,2,0));
 {
  DatabaseType tolua_ret = (DatabaseType)  Database::ParseType(dbType);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ParseType'.",&tolua_err);
 return 0;
#endif
}

/* method: ErrorString of class  Database */
static int tolua_worldserver_Database_ErrorString00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"Database",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  DatabaseError err = ((DatabaseError) (int)  tolua_tonumber(tolua_S,2,0));
 {
  const char* tolua_ret = (const char*)  Database::ErrorString(err);
 tolua_pushstring(tolua_S,(const char*)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ErrorString'.",&tolua_err);
 return 0;
#endif
}

/* method: GetExecutor of class  Database */
static int tolua_worldserver_Database_GetExecutor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Database",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  Database* self = (Database*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetExecutor'",NULL);
#endif
 {
  DatabaseExecutor* tolua_ret = (DatabaseExecutor*)  self->GetExecutor();
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"DatabaseExecutor");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetExecutor'.",&tolua_err);
 return 0;
#endif
}

/* method: PutExecutor of class  Database */
static int tolua_worldserver_Database_PutExecutor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Database",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"DatabaseExecutor",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  Database* self = (Database*)  tolua_tousertype(tolua_S,1,0);
  DatabaseExecutor* dbEx = ((DatabaseExecutor*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'PutExecutor'",NULL);
#endif
 {
  self->PutExecutor(dbEx);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'PutExecutor'.",&tolua_err);
 return 0;
#endif
}

/* method: SetLogger of class  Database */
static int tolua_worldserver_Database_SetLogger00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Database",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"Log",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  Database* self = (Database*)  tolua_tousertype(tolua_S,1,0);
  Log* iLogger = ((Log*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetLogger'",NULL);
#endif
 {
  self->SetLogger(iLogger);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetLogger'.",&tolua_err);
 return 0;
#endif
}

/* method: GetParent of class  DatabaseExecutor */
static int tolua_worldserver_DatabaseExecutor_GetParent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"DatabaseExecutor",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  DatabaseExecutor* self = (DatabaseExecutor*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetParent'",NULL);
#endif
 {
  Database* tolua_ret = (Database*)  self->GetParent();
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"Database");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetParent'.",&tolua_err);
 return 0;
#endif
}

/* method: Ok of class  DatabaseExecutor */
static int tolua_worldserver_DatabaseExecutor_Ok00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"DatabaseExecutor",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  DatabaseExecutor* self = (DatabaseExecutor*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Ok'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->Ok();
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Ok'.",&tolua_err);
 return 0;
#endif
}

/* method: Free of class  DatabaseExecutor */
static int tolua_worldserver_DatabaseExecutor_Free00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"DatabaseExecutor",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  DatabaseExecutor* self = (DatabaseExecutor*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Free'",NULL);
#endif
 {
  self->Free();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Free'.",&tolua_err);
 return 0;
#endif
}

/* method: Execute of class  DatabaseExecutor */
static int tolua_worldserver_DatabaseExecutor_Execute00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"DatabaseExecutor",0,&tolua_err) ||
 !tolua_isstring(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  DatabaseExecutor* self = (DatabaseExecutor*)  tolua_tousertype(tolua_S,1,0);
  const char* Query = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Execute'",NULL);
#endif
 {
  DatabaseError tolua_ret = (DatabaseError)  self->Execute(Query);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Execute'.",&tolua_err);
 return 0;
#endif
}

/* method: NumFields of class  DatabaseExecutor */
static int tolua_worldserver_DatabaseExecutor_NumFields00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"DatabaseExecutor",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  DatabaseExecutor* self = (DatabaseExecutor*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'NumFields'",NULL);
#endif
 {
  int tolua_ret = (int)  self->NumFields();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NumFields'.",&tolua_err);
 return 0;
#endif
}

/* method: NumRows of class  DatabaseExecutor */
static int tolua_worldserver_DatabaseExecutor_NumRows00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"DatabaseExecutor",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  DatabaseExecutor* self = (DatabaseExecutor*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'NumRows'",NULL);
#endif
 {
  int tolua_ret = (int)  self->NumRows();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NumRows'.",&tolua_err);
 return 0;
#endif
}

/* method: NextRow of class  DatabaseExecutor */
static int tolua_worldserver_DatabaseExecutor_NextRow00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"DatabaseExecutor",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  DatabaseExecutor* self = (DatabaseExecutor*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'NextRow'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->NextRow();
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NextRow'.",&tolua_err);
 return 0;
#endif
}

/* method: Get of class  DatabaseExecutor */
static int tolua_worldserver_DatabaseExecutor_Get00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"DatabaseExecutor",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  DatabaseExecutor* self = (DatabaseExecutor*)  tolua_tousertype(tolua_S,1,0);
  unsigned int i = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Get'",NULL);
#endif
 {
  const char* tolua_ret = (const char*)  self->Get(i);
 tolua_pushstring(tolua_S,(const char*)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Get'.",&tolua_err);
 return 0;
#endif
}

/* method: GetLength of class  DatabaseExecutor */
static int tolua_worldserver_DatabaseExecutor_GetLength00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"DatabaseExecutor",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  DatabaseExecutor* self = (DatabaseExecutor*)  tolua_tousertype(tolua_S,1,0);
  unsigned int i = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetLength'",NULL);
#endif
 {
  unsigned int tolua_ret = ( unsigned int)  self->GetLength(i);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetLength'.",&tolua_err);
 return 0;
#endif
}

/* method: GetI32 of class  DatabaseExecutor */
static int tolua_worldserver_DatabaseExecutor_GetI3200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"DatabaseExecutor",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  DatabaseExecutor* self = (DatabaseExecutor*)  tolua_tousertype(tolua_S,1,0);
  unsigned int i = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetI32'",NULL);
#endif
 {
   int tolua_ret = (  int)  self->GetI32(i);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetI32'.",&tolua_err);
 return 0;
#endif
}

/* method: GetU32 of class  DatabaseExecutor */
static int tolua_worldserver_DatabaseExecutor_GetU3200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"DatabaseExecutor",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  DatabaseExecutor* self = (DatabaseExecutor*)  tolua_tousertype(tolua_S,1,0);
  unsigned int i = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetU32'",NULL);
#endif
 {
  unsigned int tolua_ret = ( unsigned int)  self->GetU32(i);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetU32'.",&tolua_err);
 return 0;
#endif
}

/* method: GetU64 of class  DatabaseExecutor */
static int tolua_worldserver_DatabaseExecutor_GetU6400(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"DatabaseExecutor",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  DatabaseExecutor* self = (DatabaseExecutor*)  tolua_tousertype(tolua_S,1,0);
  unsigned int i = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetU64'",NULL);
#endif
 {
  unsigned long long tolua_ret = ( unsigned long long)  self->GetU64(i);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetU64'.",&tolua_err);
 return 0;
#endif
}

/* method: GetFloat of class  DatabaseExecutor */
static int tolua_worldserver_DatabaseExecutor_GetFloat00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"DatabaseExecutor",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  DatabaseExecutor* self = (DatabaseExecutor*)  tolua_tousertype(tolua_S,1,0);
  unsigned int i = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetFloat'",NULL);
#endif
 {
  float tolua_ret = (float)  self->GetFloat(i);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetFloat'.",&tolua_err);
 return 0;
#endif
}

/* method: GetID of class  DatabaseExecutor */
static int tolua_worldserver_DatabaseExecutor_GetID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"DatabaseExecutor",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  DatabaseExecutor* self = (DatabaseExecutor*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetID'",NULL);
#endif
 {
  unsigned long long tolua_ret = ( unsigned long long)  self->GetID();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetID'.",&tolua_err);
 return 0;
#endif
}

/* method: GetAffectedRows of class  DatabaseExecutor */
static int tolua_worldserver_DatabaseExecutor_GetAffectedRows00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"DatabaseExecutor",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  DatabaseExecutor* self = (DatabaseExecutor*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetAffectedRows'",NULL);
#endif
 {
  unsigned int tolua_ret = ( unsigned int)  self->GetAffectedRows();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetAffectedRows'.",&tolua_err);
 return 0;
#endif
}

/* method: SocketEvent of class  Client */
static int tolua_worldserver_Client_SocketEvent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Client",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  Client* self = (Client*)  tolua_tousertype(tolua_S,1,0);
  unsigned int mask = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SocketEvent'",NULL);
#endif
 {
  self->SocketEvent(mask);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SocketEvent'.",&tolua_err);
 return 0;
#endif
}

/* get function: Login of class  GameClient */
static int tolua_get_GameClient_Login(lua_State* tolua_S)
{
  GameClient* self = (GameClient*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Login'",NULL);
#endif
 tolua_pushstring(tolua_S,(const char*)self->Login);
 return 1;
}

/* set function: Login of class  GameClient */
static int tolua_set_GameClient_Login(lua_State* tolua_S)
{
  GameClient* self = (GameClient*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Login'",NULL);
 if (!tolua_isstring(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Login = ((char*)  tolua_tostring(tolua_S,2,0));
 return 0;
}

/* get function: Character of class  GameClient */
static int tolua_get_GameClient_Character_ptr(lua_State* tolua_S)
{
  GameClient* self = (GameClient*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Character'",NULL);
#endif
 tolua_pushusertype(tolua_S,(void*)self->Character,"Player");
 return 1;
}

/* set function: Character of class  GameClient */
static int tolua_set_GameClient_Character_ptr(lua_State* tolua_S)
{
  GameClient* self = (GameClient*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Character'",NULL);
 if (!tolua_isusertype(tolua_S,2,"Player",0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Character = ((Player*)  tolua_tousertype(tolua_S,2,0));
 return 0;
}

/* method: new of class  GameClient */
static int tolua_worldserver_GameClient_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"GameClient",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"Socket",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  Socket* sock = ((Socket*)  tolua_tousertype(tolua_S,2,0));
 {
  GameClient* tolua_ret = (GameClient*)  new GameClient(sock);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"GameClient");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}

/* method: new_local of class  GameClient */
static int tolua_worldserver_GameClient_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"GameClient",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"Socket",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  Socket* sock = ((Socket*)  tolua_tousertype(tolua_S,2,0));
 {
  GameClient* tolua_ret = (GameClient*)  new GameClient(sock);
 tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"GameClient");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}

/* method: delete of class  GameClient */
static int tolua_worldserver_GameClient_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"GameClient",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  GameClient* self = (GameClient*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'",NULL);
#endif
   self->DecRef();
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}

/* method: SocketEvent of class  GameClient */
static int tolua_worldserver_GameClient_SocketEvent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"GameClient",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  GameClient* self = (GameClient*)  tolua_tousertype(tolua_S,1,0);
  unsigned int mask = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SocketEvent'",NULL);
#endif
 {
  self->SocketEvent(mask);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SocketEvent'.",&tolua_err);
 return 0;
#endif
}

/* method: Authenticated of class  GameClient */
static int tolua_worldserver_GameClient_Authenticated00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"GameClient",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  GameClient* self = (GameClient*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Authenticated'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->Authenticated();
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Authenticated'.",&tolua_err);
 return 0;
#endif
}

/* method: Send of class  GameClient */
static int tolua_worldserver_GameClient_Send00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"GameClient",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"NetworkPacket",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  GameClient* self = (GameClient*)  tolua_tousertype(tolua_S,1,0);
  NetworkPacket* packet = ((NetworkPacket*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Send'",NULL);
#endif
 {
  self->Send(packet);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Send'.",&tolua_err);
 return 0;
#endif
}

/* get function: Type of class  Modifier */
static int tolua_get_Modifier_unsigned_Type(lua_State* tolua_S)
{
  Modifier* self = (Modifier*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Type'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->Type);
 return 1;
}

/* set function: Type of class  Modifier */
static int tolua_set_Modifier_unsigned_Type(lua_State* tolua_S)
{
  Modifier* self = (Modifier*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Type'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Type = (( unsigned char)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: Amount of class  Modifier */
static int tolua_get_Modifier_Amount(lua_State* tolua_S)
{
  Modifier* self = (Modifier*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Amount'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->Amount);
 return 1;
}

/* set function: Amount of class  Modifier */
static int tolua_set_Modifier_Amount(lua_State* tolua_S)
{
  Modifier* self = (Modifier*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Amount'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Amount = ((  int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: MiscValue of class  Modifier */
static int tolua_get_Modifier_unsigned_MiscValue(lua_State* tolua_S)
{
  Modifier* self = (Modifier*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'MiscValue'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->MiscValue);
 return 1;
}

/* set function: MiscValue of class  Modifier */
static int tolua_set_Modifier_unsigned_MiscValue(lua_State* tolua_S)
{
  Modifier* self = (Modifier*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'MiscValue'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->MiscValue = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: MiscValue2 of class  Modifier */
static int tolua_get_Modifier_unsigned_MiscValue2(lua_State* tolua_S)
{
  Modifier* self = (Modifier*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'MiscValue2'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->MiscValue2);
 return 1;
}

/* set function: MiscValue2 of class  Modifier */
static int tolua_set_Modifier_unsigned_MiscValue2(lua_State* tolua_S)
{
  Modifier* self = (Modifier*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'MiscValue2'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->MiscValue2 = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* method: new of class  Modifier */
static int tolua_worldserver_Modifier_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"Modifier",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  unsigned char t = (( unsigned char)  tolua_tonumber(tolua_S,2,0));
   int a = ((  int)  tolua_tonumber(tolua_S,3,0));
  unsigned int mv1 = (( unsigned int)  tolua_tonumber(tolua_S,4,0));
  unsigned int mv2 = (( unsigned int)  tolua_tonumber(tolua_S,5,0));
 {
  Modifier* tolua_ret = (Modifier*)  new Modifier(t,a,mv1,mv2);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"Modifier");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}

/* method: new_local of class  Modifier */
static int tolua_worldserver_Modifier_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"Modifier",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  unsigned char t = (( unsigned char)  tolua_tonumber(tolua_S,2,0));
   int a = ((  int)  tolua_tonumber(tolua_S,3,0));
  unsigned int mv1 = (( unsigned int)  tolua_tonumber(tolua_S,4,0));
  unsigned int mv2 = (( unsigned int)  tolua_tonumber(tolua_S,5,0));
 {
  Modifier* tolua_ret = (Modifier*)  new Modifier(t,a,mv1,mv2);
 tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"Modifier");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}

/* get function: Duration of class  Affect */
static int tolua_get_Affect_Duration(lua_State* tolua_S)
{
  Affect* self = (Affect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Duration'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->Duration);
 return 1;
}

/* set function: Duration of class  Affect */
static int tolua_set_Affect_Duration(lua_State* tolua_S)
{
  Affect* self = (Affect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Duration'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Duration = ((  int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: CasterGUID of class  Affect */
static int tolua_get_Affect_unsigned_CasterGUID(lua_State* tolua_S)
{
  Affect* self = (Affect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'CasterGUID'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->CasterGUID);
 return 1;
}

/* set function: CasterGUID of class  Affect */
static int tolua_set_Affect_unsigned_CasterGUID(lua_State* tolua_S)
{
  Affect* self = (Affect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'CasterGUID'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->CasterGUID = (( unsigned long long)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: AuraSlot of class  Affect */
static int tolua_get_Affect_unsigned_AuraSlot(lua_State* tolua_S)
{
  Affect* self = (Affect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'AuraSlot'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->AuraSlot);
 return 1;
}

/* set function: AuraSlot of class  Affect */
static int tolua_set_Affect_unsigned_AuraSlot(lua_State* tolua_S)
{
  Affect* self = (Affect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'AuraSlot'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->AuraSlot = (( unsigned char)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: DamagePerTick of class  Affect */
static int tolua_get_Affect_unsigned_DamagePerTick(lua_State* tolua_S)
{
  Affect* self = (Affect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'DamagePerTick'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->DamagePerTick);
 return 1;
}

/* set function: DamagePerTick of class  Affect */
static int tolua_set_Affect_unsigned_DamagePerTick(lua_State* tolua_S)
{
  Affect* self = (Affect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'DamagePerTick'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->DamagePerTick = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: DamageTimer of class  Affect */
static int tolua_get_Affect_DamageTimer(lua_State* tolua_S)
{
  Affect* self = (Affect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'DamageTimer'",NULL);
#endif
 tolua_pushusertype(tolua_S,(void*)&self->DamageTimer,"Timer");
 return 1;
}

/* set function: DamageTimer of class  Affect */
static int tolua_set_Affect_DamageTimer(lua_State* tolua_S)
{
  Affect* self = (Affect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'DamageTimer'",NULL);
 if (!tolua_isusertype(tolua_S,2,"Timer",0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->DamageTimer = *((Timer*)  tolua_tousertype(tolua_S,2,0));
 return 0;
}

/* get function: SpellPerTick of class  Affect */
static int tolua_get_Affect_unsigned_SpellPerTick(lua_State* tolua_S)
{
  Affect* self = (Affect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'SpellPerTick'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->SpellPerTick);
 return 1;
}

/* set function: SpellPerTick of class  Affect */
static int tolua_set_Affect_unsigned_SpellPerTick(lua_State* tolua_S)
{
  Affect* self = (Affect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'SpellPerTick'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->SpellPerTick = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: SpellTimer of class  Affect */
static int tolua_get_Affect_SpellTimer(lua_State* tolua_S)
{
  Affect* self = (Affect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'SpellTimer'",NULL);
#endif
 tolua_pushusertype(tolua_S,(void*)&self->SpellTimer,"Timer");
 return 1;
}

/* set function: SpellTimer of class  Affect */
static int tolua_set_Affect_SpellTimer(lua_State* tolua_S)
{
  Affect* self = (Affect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'SpellTimer'",NULL);
 if (!tolua_isusertype(tolua_S,2,"Timer",0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->SpellTimer = *((Timer*)  tolua_tousertype(tolua_S,2,0));
 return 0;
}

/* get function: Positive of class  Affect */
static int tolua_get_Affect_Positive(lua_State* tolua_S)
{
  Affect* self = (Affect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Positive'",NULL);
#endif
 tolua_pushboolean(tolua_S,(bool)self->Positive);
 return 1;
}

/* set function: Positive of class  Affect */
static int tolua_set_Affect_Positive(lua_State* tolua_S)
{
  Affect* self = (Affect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Positive'",NULL);
 if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Positive = ((bool)  tolua_toboolean(tolua_S,2,0));
 return 0;
}

/* get function: CoAffect of class  Affect */
static int tolua_get_Affect_CoAffect_ptr(lua_State* tolua_S)
{
  Affect* self = (Affect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'CoAffect'",NULL);
#endif
 tolua_pushusertype(tolua_S,(void*)self->CoAffect,"Affect");
 return 1;
}

/* set function: CoAffect of class  Affect */
static int tolua_set_Affect_CoAffect_ptr(lua_State* tolua_S)
{
  Affect* self = (Affect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'CoAffect'",NULL);
 if (!tolua_isusertype(tolua_S,2,"Affect",0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->CoAffect = ((Affect*)  tolua_tousertype(tolua_S,2,0));
 return 0;
}

/* method: new of class  Affect */
static int tolua_worldserver_Affect_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"Affect",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"SpellEntry",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  SpellEntry* iProto = ((SpellEntry*)  tolua_tousertype(tolua_S,2,0));
   int iDuration = ((  int)  tolua_tonumber(tolua_S,3,0));
  unsigned long long iGuid = (( unsigned long long)  tolua_tonumber(tolua_S,4,0));
 {
  Affect* tolua_ret = (Affect*)  new Affect(iProto,iDuration,iGuid);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"Affect");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}

/* method: new_local of class  Affect */
static int tolua_worldserver_Affect_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"Affect",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"SpellEntry",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  SpellEntry* iProto = ((SpellEntry*)  tolua_tousertype(tolua_S,2,0));
   int iDuration = ((  int)  tolua_tonumber(tolua_S,3,0));
  unsigned long long iGuid = (( unsigned long long)  tolua_tonumber(tolua_S,4,0));
 {
  Affect* tolua_ret = (Affect*)  new Affect(iProto,iDuration,iGuid);
 tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"Affect");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}

/* method: AddMod of class  Affect */
static int tolua_worldserver_Affect_AddMod00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Affect",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  Affect* self = (Affect*)  tolua_tousertype(tolua_S,1,0);
  unsigned char t = (( unsigned char)  tolua_tonumber(tolua_S,2,0));
   int a = ((  int)  tolua_tonumber(tolua_S,3,0));
  unsigned int mv1 = (( unsigned int)  tolua_tonumber(tolua_S,4,0));
  unsigned int mv2 = (( unsigned int)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddMod'",NULL);
#endif
 {
  self->AddMod(t,a,mv1,mv2);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddMod'.",&tolua_err);
 return 0;
#endif
}

/* method: SetDamagePerTick of class  Affect */
static int tolua_worldserver_Affect_SetDamagePerTick00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Affect",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  Affect* self = (Affect*)  tolua_tousertype(tolua_S,1,0);
  unsigned int iDamage = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
  unsigned int iDeltaMs = (( unsigned int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetDamagePerTick'",NULL);
#endif
 {
  self->SetDamagePerTick(iDamage,iDeltaMs);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetDamagePerTick'.",&tolua_err);
 return 0;
#endif
}

/* method: SetPeriodicTriggerSpell of class  Affect */
static int tolua_worldserver_Affect_SetPeriodicTriggerSpell00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Affect",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  Affect* self = (Affect*)  tolua_tousertype(tolua_S,1,0);
  unsigned int iSpellId = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
  unsigned int iDeltaMs = (( unsigned int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetPeriodicTriggerSpell'",NULL);
#endif
 {
  self->SetPeriodicTriggerSpell(iSpellId,iDeltaMs);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetPeriodicTriggerSpell'.",&tolua_err);
 return 0;
#endif
}

/* method: Update of class  Affect */
static int tolua_worldserver_Affect_Update00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Affect",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  Affect* self = (Affect*)  tolua_tousertype(tolua_S,1,0);
  unsigned int iDeltaMs = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Update'",NULL);
#endif
 {
  unsigned char tolua_ret = ( unsigned char)  self->Update(iDeltaMs);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Update'.",&tolua_err);
 return 0;
#endif
}

/* method: delete of class  Unit */
static int tolua_worldserver_Unit_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Unit",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  Unit* self = (Unit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'",NULL);
#endif
   self->DecRef();
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}

/* method: Update of class  Unit */
static int tolua_worldserver_Unit_Update00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Unit",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  Unit* self = (Unit*)  tolua_tousertype(tolua_S,1,0);
  unsigned int iDeltaMs = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Update'",NULL);
#endif
 {
  self->Update(iDeltaMs);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Update'.",&tolua_err);
 return 0;
#endif
}

/* method: ApplyModifier of class  Unit */
static int tolua_worldserver_Unit_ApplyModifier00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Unit",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"Modifier",0,&tolua_err) ||
 !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
 !tolua_isusertype(tolua_S,4,"Affect",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  Unit* self = (Unit*)  tolua_tousertype(tolua_S,1,0);
  Modifier* iMod = ((Modifier*)  tolua_tousertype(tolua_S,2,0));
  bool iApply = ((bool)  tolua_toboolean(tolua_S,3,0));
  Affect* iParent = ((Affect*)  tolua_tousertype(tolua_S,4,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ApplyModifier'",NULL);
#endif
 {
  self->ApplyModifier(iMod,iApply,iParent);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ApplyModifier'.",&tolua_err);
 return 0;
#endif
}

/* method: ReceiveDamage of class  Unit */
static int tolua_worldserver_Unit_ReceiveDamage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Unit",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"Unit",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  Unit* self = (Unit*)  tolua_tousertype(tolua_S,1,0);
  Unit* iAttacker = ((Unit*)  tolua_tousertype(tolua_S,2,0));
  unsigned int iDamage = (( unsigned int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ReceiveDamage'",NULL);
#endif
 {
  self->ReceiveDamage(iAttacker,iDamage);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ReceiveDamage'.",&tolua_err);
 return 0;
#endif
}

/* method: GenerateLoot of class  Unit */
static int tolua_worldserver_Unit_GenerateLoot00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Unit",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  Unit* self = (Unit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GenerateLoot'",NULL);
#endif
 {
  self->GenerateLoot();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GenerateLoot'.",&tolua_err);
 return 0;
#endif
}

/* method: GiveXP of class  Unit */
static int tolua_worldserver_Unit_GiveXP00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Unit",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isusertype(tolua_S,3,"Unit",0,&tolua_err) ||
 !tolua_isboolean(tolua_S,4,1,&tolua_err) ||
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  Unit* self = (Unit*)  tolua_tousertype(tolua_S,1,0);
  unsigned int iXP = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
  Unit* iVictim = ((Unit*)  tolua_tousertype(tolua_S,3,0));
  bool iGroup = ((bool)  tolua_toboolean(tolua_S,4,true));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GiveXP'",NULL);
#endif
 {
  self->GiveXP(iXP,iVictim,iGroup);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GiveXP'.",&tolua_err);
 return 0;
#endif
}

/* method: RemoveInRangeObject of class  Unit */
static int tolua_worldserver_Unit_RemoveInRangeObject00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Unit",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"Object",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  Unit* self = (Unit*)  tolua_tousertype(tolua_S,1,0);
  Object* Obj = ((Object*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RemoveInRangeObject'",NULL);
#endif
 {
  self->RemoveInRangeObject(Obj);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RemoveInRangeObject'.",&tolua_err);
 return 0;
#endif
}

/* method: SetAttackTimer of class  Unit */
static int tolua_worldserver_Unit_SetAttackTimer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Unit",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  Unit* self = (Unit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetAttackTimer'",NULL);
#endif
 {
  self->SetAttackTimer();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetAttackTimer'.",&tolua_err);
 return 0;
#endif
}

/* method: IsAttackReady of class  Unit */
static int tolua_worldserver_Unit_IsAttackReady00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const Unit",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const Unit* self = (const Unit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsAttackReady'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->IsAttackReady();
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsAttackReady'.",&tolua_err);
 return 0;
#endif
}

/* method: CanReachWithAttack of class  Unit */
static int tolua_worldserver_Unit_CanReachWithAttack00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const Unit",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"Unit",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const Unit* self = (const Unit*)  tolua_tousertype(tolua_S,1,0);
  Unit* iVictim = ((Unit*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CanReachWithAttack'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->CanReachWithAttack(iVictim);
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CanReachWithAttack'.",&tolua_err);
 return 0;
#endif
}

/* method: RemoveAttacker of class  Unit */
static int tolua_worldserver_Unit_RemoveAttacker00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Unit",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"Unit",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  Unit* self = (Unit*)  tolua_tousertype(tolua_S,1,0);
  Unit* iAttacker = ((Unit*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RemoveAttacker'",NULL);
#endif
 {
  self->RemoveAttacker(iAttacker);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RemoveAttacker'.",&tolua_err);
 return 0;
#endif
}

/* method: GetLevel of class  Unit */
static int tolua_worldserver_Unit_GetLevel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Unit",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  Unit* self = (Unit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetLevel'",NULL);
#endif
 {
  unsigned char tolua_ret = ( unsigned char)  self->GetLevel();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetLevel'.",&tolua_err);
 return 0;
#endif
}

/* method: GetRace of class  Unit */
static int tolua_worldserver_Unit_GetRace00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Unit",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  Unit* self = (Unit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetRace'",NULL);
#endif
 {
  unsigned char tolua_ret = ( unsigned char)  self->GetRace();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetRace'.",&tolua_err);
 return 0;
#endif
}

/* method: GetClass of class  Unit */
static int tolua_worldserver_Unit_GetClass00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Unit",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  Unit* self = (Unit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetClass'",NULL);
#endif
 {
  unsigned char tolua_ret = ( unsigned char)  self->GetClass();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetClass'.",&tolua_err);
 return 0;
#endif
}

/* method: GetGender of class  Unit */
static int tolua_worldserver_Unit_GetGender00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Unit",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  Unit* self = (Unit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetGender'",NULL);
#endif
 {
  unsigned char tolua_ret = ( unsigned char)  self->GetGender();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetGender'.",&tolua_err);
 return 0;
#endif
}

/* method: DealDamage of class  Unit */
static int tolua_worldserver_Unit_DealDamage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Unit",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"Unit",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  Unit* self = (Unit*)  tolua_tousertype(tolua_S,1,0);
  Unit* iVictim = ((Unit*)  tolua_tousertype(tolua_S,2,0));
  unsigned int iDamage = (( unsigned int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'DealDamage'",NULL);
#endif
 {
  self->DealDamage(iVictim,iDamage);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'DealDamage'.",&tolua_err);
 return 0;
#endif
}

/* method: AttackerStateUpdate of class  Unit */
static int tolua_worldserver_Unit_AttackerStateUpdate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Unit",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"Unit",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isboolean(tolua_S,4,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  Unit* self = (Unit*)  tolua_tousertype(tolua_S,1,0);
  Unit* iVictim = ((Unit*)  tolua_tousertype(tolua_S,2,0));
  unsigned int iDamage = (( unsigned int)  tolua_tonumber(tolua_S,3,0));
  bool DoT = ((bool)  tolua_toboolean(tolua_S,4,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AttackerStateUpdate'",NULL);
#endif
 {
  self->AttackerStateUpdate(iVictim,iDamage,DoT);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AttackerStateUpdate'.",&tolua_err);
 return 0;
#endif
}

/* method: SpellNonMeleeDamageLog of class  Unit */
static int tolua_worldserver_Unit_SpellNonMeleeDamageLog00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Unit",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"Unit",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  Unit* self = (Unit*)  tolua_tousertype(tolua_S,1,0);
  Unit* iVictim = ((Unit*)  tolua_tousertype(tolua_S,2,0));
  unsigned int iSpellID = (( unsigned int)  tolua_tonumber(tolua_S,3,0));
  unsigned int iDamage = (( unsigned int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SpellNonMeleeDamageLog'",NULL);
#endif
 {
  self->SpellNonMeleeDamageLog(iVictim,iSpellID,iDamage);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SpellNonMeleeDamageLog'.",&tolua_err);
 return 0;
#endif
}

/* method: PeriodicAuraLog of class  Unit */
static int tolua_worldserver_Unit_PeriodicAuraLog00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Unit",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"Unit",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  Unit* self = (Unit*)  tolua_tousertype(tolua_S,1,0);
  Unit* iVictim = ((Unit*)  tolua_tousertype(tolua_S,2,0));
  unsigned int iSpellID = (( unsigned int)  tolua_tonumber(tolua_S,3,0));
  unsigned int iDamage = (( unsigned int)  tolua_tonumber(tolua_S,4,0));
  unsigned int iDamageType = (( unsigned int)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'PeriodicAuraLog'",NULL);
#endif
 {
  self->PeriodicAuraLog(iVictim,iSpellID,iDamage,iDamageType);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'PeriodicAuraLog'.",&tolua_err);
 return 0;
#endif
}

/* method: AttackStart of class  Unit */
static int tolua_worldserver_Unit_AttackStart00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Unit",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"Unit",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  Unit* self = (Unit*)  tolua_tousertype(tolua_S,1,0);
  Unit* iVictim = ((Unit*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AttackStart'",NULL);
#endif
 {
  self->AttackStart(iVictim);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AttackStart'.",&tolua_err);
 return 0;
#endif
}

/* method: AttackStop of class  Unit */
static int tolua_worldserver_Unit_AttackStop00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Unit",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  Unit* self = (Unit*)  tolua_tousertype(tolua_S,1,0);
  unsigned long long iVictimGuid = (( unsigned long long)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AttackStop'",NULL);
#endif
 {
  self->AttackStop(iVictimGuid);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AttackStop'.",&tolua_err);
 return 0;
#endif
}

/* method: IsAlive of class  Unit */
static int tolua_worldserver_Unit_IsAlive00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Unit",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  Unit* self = (Unit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsAlive'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->IsAlive();
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsAlive'.",&tolua_err);
 return 0;
#endif
}

/* method: IsDead of class  Unit */
static int tolua_worldserver_Unit_IsDead00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Unit",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  Unit* self = (Unit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsDead'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->IsDead();
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsDead'.",&tolua_err);
 return 0;
#endif
}

/* method: SetDeathState of class  Unit */
static int tolua_worldserver_Unit_SetDeathState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Unit",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  Unit* self = (Unit*)  tolua_tousertype(tolua_S,1,0);
  UnitDeathState iState = ((UnitDeathState) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetDeathState'",NULL);
#endif
 {
  self->SetDeathState(iState);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetDeathState'.",&tolua_err);
 return 0;
#endif
}

/* method: GetDeathState of class  Unit */
static int tolua_worldserver_Unit_GetDeathState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Unit",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  Unit* self = (Unit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetDeathState'",NULL);
#endif
 {
  UnitDeathState tolua_ret = (UnitDeathState)  self->GetDeathState();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetDeathState'.",&tolua_err);
 return 0;
#endif
}

/* method: AddAffect of class  Unit */
static int tolua_worldserver_Unit_AddAffect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Unit",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"Affect",0,&tolua_err) ||
 !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  Unit* self = (Unit*)  tolua_tousertype(tolua_S,1,0);
  Affect* iAff = ((Affect*)  tolua_tousertype(tolua_S,2,0));
  bool iUniq = ((bool)  tolua_toboolean(tolua_S,3,false));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddAffect'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->AddAffect(iAff,iUniq);
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddAffect'.",&tolua_err);
 return 0;
#endif
}

/* method: RemoveAffect of class  Unit */
static int tolua_worldserver_Unit_RemoveAffect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Unit",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"Affect",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  Unit* self = (Unit*)  tolua_tousertype(tolua_S,1,0);
  Affect* iAff = ((Affect*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RemoveAffect'",NULL);
#endif
 {
  self->RemoveAffect(iAff);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RemoveAffect'.",&tolua_err);
 return 0;
#endif
}

/* method: RemoveAffect of class  Unit */
static int tolua_worldserver_Unit_RemoveAffect01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Unit",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  Unit* self = (Unit*)  tolua_tousertype(tolua_S,1,0);
  unsigned int iType = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RemoveAffect'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->RemoveAffect(iType);
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
tolua_lerror:
 return tolua_worldserver_Unit_RemoveAffect00(tolua_S);
}

/* method: RemoveAffectById of class  Unit */
static int tolua_worldserver_Unit_RemoveAffectById00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Unit",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  Unit* self = (Unit*)  tolua_tousertype(tolua_S,1,0);
  unsigned int iSpellId = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RemoveAffectById'",NULL);
#endif
 {
  self->RemoveAffectById(iSpellId);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RemoveAffectById'.",&tolua_err);
 return 0;
#endif
}

/* method: RemoveAllAffects of class  Unit */
static int tolua_worldserver_Unit_RemoveAllAffects00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Unit",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  Unit* self = (Unit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RemoveAllAffects'",NULL);
#endif
 {
  self->RemoveAllAffects();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RemoveAllAffects'.",&tolua_err);
 return 0;
#endif
}

/* method: SetAura of class  Unit */
static int tolua_worldserver_Unit_SetAura00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Unit",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"Affect",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  Unit* self = (Unit*)  tolua_tousertype(tolua_S,1,0);
  Affect* iAff = ((Affect*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetAura'",NULL);
#endif
 {
  self->SetAura(iAff);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetAura'.",&tolua_err);
 return 0;
#endif
}

/* get function: ItemId of class  ItemPrototype */
static int tolua_get_ItemPrototype_unsigned_ItemId(lua_State* tolua_S)
{
  ItemPrototype* self = (ItemPrototype*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'ItemId'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->ItemId);
 return 1;
}

/* set function: ItemId of class  ItemPrototype */
static int tolua_set_ItemPrototype_unsigned_ItemId(lua_State* tolua_S)
{
  ItemPrototype* self = (ItemPrototype*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'ItemId'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->ItemId = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: Class of class  ItemPrototype */
static int tolua_get_ItemPrototype_unsigned_Class(lua_State* tolua_S)
{
  ItemPrototype* self = (ItemPrototype*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Class'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->Class);
 return 1;
}

/* set function: Class of class  ItemPrototype */
static int tolua_set_ItemPrototype_unsigned_Class(lua_State* tolua_S)
{
  ItemPrototype* self = (ItemPrototype*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Class'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Class = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: SubClass of class  ItemPrototype */
static int tolua_get_ItemPrototype_unsigned_SubClass(lua_State* tolua_S)
{
  ItemPrototype* self = (ItemPrototype*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'SubClass'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->SubClass);
 return 1;
}

/* set function: SubClass of class  ItemPrototype */
static int tolua_set_ItemPrototype_unsigned_SubClass(lua_State* tolua_S)
{
  ItemPrototype* self = (ItemPrototype*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'SubClass'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->SubClass = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: Name1 of class  ItemPrototype */
static int tolua_get_ItemPrototype_Name1(lua_State* tolua_S)
{
  ItemPrototype* self = (ItemPrototype*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Name1'",NULL);
#endif
 tolua_pushstring(tolua_S,(const char*)self->Name1);
 return 1;
}

/* set function: Name1 of class  ItemPrototype */
static int tolua_set_ItemPrototype_Name1(lua_State* tolua_S)
{
  ItemPrototype* self = (ItemPrototype*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Name1'",NULL);
 if (!tolua_isstring(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Name1 = ((char*)  tolua_tostring(tolua_S,2,0));
 return 0;
}

/* get function: Name2 of class  ItemPrototype */
static int tolua_get_ItemPrototype_Name2(lua_State* tolua_S)
{
  ItemPrototype* self = (ItemPrototype*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Name2'",NULL);
#endif
 tolua_pushstring(tolua_S,(const char*)self->Name2);
 return 1;
}

/* set function: Name2 of class  ItemPrototype */
static int tolua_set_ItemPrototype_Name2(lua_State* tolua_S)
{
  ItemPrototype* self = (ItemPrototype*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Name2'",NULL);
 if (!tolua_isstring(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Name2 = ((char*)  tolua_tostring(tolua_S,2,0));
 return 0;
}

/* get function: Name3 of class  ItemPrototype */
static int tolua_get_ItemPrototype_Name3(lua_State* tolua_S)
{
  ItemPrototype* self = (ItemPrototype*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Name3'",NULL);
#endif
 tolua_pushstring(tolua_S,(const char*)self->Name3);
 return 1;
}

/* set function: Name3 of class  ItemPrototype */
static int tolua_set_ItemPrototype_Name3(lua_State* tolua_S)
{
  ItemPrototype* self = (ItemPrototype*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Name3'",NULL);
 if (!tolua_isstring(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Name3 = ((char*)  tolua_tostring(tolua_S,2,0));
 return 0;
}

/* get function: Name4 of class  ItemPrototype */
static int tolua_get_ItemPrototype_Name4(lua_State* tolua_S)
{
  ItemPrototype* self = (ItemPrototype*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Name4'",NULL);
#endif
 tolua_pushstring(tolua_S,(const char*)self->Name4);
 return 1;
}

/* set function: Name4 of class  ItemPrototype */
static int tolua_set_ItemPrototype_Name4(lua_State* tolua_S)
{
  ItemPrototype* self = (ItemPrototype*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Name4'",NULL);
 if (!tolua_isstring(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Name4 = ((char*)  tolua_tostring(tolua_S,2,0));
 return 0;
}

/* get function: DisplayId of class  ItemPrototype */
static int tolua_get_ItemPrototype_unsigned_DisplayId(lua_State* tolua_S)
{
  ItemPrototype* self = (ItemPrototype*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'DisplayId'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->DisplayId);
 return 1;
}

/* set function: DisplayId of class  ItemPrototype */
static int tolua_set_ItemPrototype_unsigned_DisplayId(lua_State* tolua_S)
{
  ItemPrototype* self = (ItemPrototype*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'DisplayId'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->DisplayId = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: Quality of class  ItemPrototype */
static int tolua_get_ItemPrototype_unsigned_Quality(lua_State* tolua_S)
{
  ItemPrototype* self = (ItemPrototype*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Quality'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->Quality);
 return 1;
}

/* set function: Quality of class  ItemPrototype */
static int tolua_set_ItemPrototype_unsigned_Quality(lua_State* tolua_S)
{
  ItemPrototype* self = (ItemPrototype*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Quality'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Quality = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: Flags of class  ItemPrototype */
static int tolua_get_ItemPrototype_unsigned_Flags(lua_State* tolua_S)
{
  ItemPrototype* self = (ItemPrototype*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Flags'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->Flags);
 return 1;
}

/* set function: Flags of class  ItemPrototype */
static int tolua_set_ItemPrototype_unsigned_Flags(lua_State* tolua_S)
{
  ItemPrototype* self = (ItemPrototype*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Flags'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Flags = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: BuyPrice of class  ItemPrototype */
static int tolua_get_ItemPrototype_unsigned_BuyPrice(lua_State* tolua_S)
{
  ItemPrototype* self = (ItemPrototype*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'BuyPrice'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->BuyPrice);
 return 1;
}

/* set function: BuyPrice of class  ItemPrototype */
static int tolua_set_ItemPrototype_unsigned_BuyPrice(lua_State* tolua_S)
{
  ItemPrototype* self = (ItemPrototype*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'BuyPrice'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->BuyPrice = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: SellPrice of class  ItemPrototype */
static int tolua_get_ItemPrototype_unsigned_SellPrice(lua_State* tolua_S)
{
  ItemPrototype* self = (ItemPrototype*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'SellPrice'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->SellPrice);
 return 1;
}

/* set function: SellPrice of class  ItemPrototype */
static int tolua_set_ItemPrototype_unsigned_SellPrice(lua_State* tolua_S)
{
  ItemPrototype* self = (ItemPrototype*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'SellPrice'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->SellPrice = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: InventoryType of class  ItemPrototype */
static int tolua_get_ItemPrototype_unsigned_InventoryType(lua_State* tolua_S)
{
  ItemPrototype* self = (ItemPrototype*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'InventoryType'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->InventoryType);
 return 1;
}

/* set function: InventoryType of class  ItemPrototype */
static int tolua_set_ItemPrototype_unsigned_InventoryType(lua_State* tolua_S)
{
  ItemPrototype* self = (ItemPrototype*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'InventoryType'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->InventoryType = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: AllowableClass of class  ItemPrototype */
static int tolua_get_ItemPrototype_unsigned_AllowableClass(lua_State* tolua_S)
{
  ItemPrototype* self = (ItemPrototype*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'AllowableClass'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->AllowableClass);
 return 1;
}

/* set function: AllowableClass of class  ItemPrototype */
static int tolua_set_ItemPrototype_unsigned_AllowableClass(lua_State* tolua_S)
{
  ItemPrototype* self = (ItemPrototype*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'AllowableClass'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->AllowableClass = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: AllowableRace of class  ItemPrototype */
static int tolua_get_ItemPrototype_unsigned_AllowableRace(lua_State* tolua_S)
{
  ItemPrototype* self = (ItemPrototype*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'AllowableRace'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->AllowableRace);
 return 1;
}

/* set function: AllowableRace of class  ItemPrototype */
static int tolua_set_ItemPrototype_unsigned_AllowableRace(lua_State* tolua_S)
{
  ItemPrototype* self = (ItemPrototype*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'AllowableRace'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->AllowableRace = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: ItemLevel of class  ItemPrototype */
static int tolua_get_ItemPrototype_unsigned_ItemLevel(lua_State* tolua_S)
{
  ItemPrototype* self = (ItemPrototype*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'ItemLevel'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->ItemLevel);
 return 1;
}

/* set function: ItemLevel of class  ItemPrototype */
static int tolua_set_ItemPrototype_unsigned_ItemLevel(lua_State* tolua_S)
{
  ItemPrototype* self = (ItemPrototype*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'ItemLevel'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->ItemLevel = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: RequiredLevel of class  ItemPrototype */
static int tolua_get_ItemPrototype_unsigned_RequiredLevel(lua_State* tolua_S)
{
  ItemPrototype* self = (ItemPrototype*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'RequiredLevel'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->RequiredLevel);
 return 1;
}

/* set function: RequiredLevel of class  ItemPrototype */
static int tolua_set_ItemPrototype_unsigned_RequiredLevel(lua_State* tolua_S)
{
  ItemPrototype* self = (ItemPrototype*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'RequiredLevel'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->RequiredLevel = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: RequiredSkill of class  ItemPrototype */
static int tolua_get_ItemPrototype_unsigned_RequiredSkill(lua_State* tolua_S)
{
  ItemPrototype* self = (ItemPrototype*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'RequiredSkill'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->RequiredSkill);
 return 1;
}

/* set function: RequiredSkill of class  ItemPrototype */
static int tolua_set_ItemPrototype_unsigned_RequiredSkill(lua_State* tolua_S)
{
  ItemPrototype* self = (ItemPrototype*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'RequiredSkill'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->RequiredSkill = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: RequiredSkillRank of class  ItemPrototype */
static int tolua_get_ItemPrototype_unsigned_RequiredSkillRank(lua_State* tolua_S)
{
  ItemPrototype* self = (ItemPrototype*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'RequiredSkillRank'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->RequiredSkillRank);
 return 1;
}

/* set function: RequiredSkillRank of class  ItemPrototype */
static int tolua_set_ItemPrototype_unsigned_RequiredSkillRank(lua_State* tolua_S)
{
  ItemPrototype* self = (ItemPrototype*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'RequiredSkillRank'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->RequiredSkillRank = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: Field20 of class  ItemPrototype */
static int tolua_get_ItemPrototype_unsigned_Field20(lua_State* tolua_S)
{
  ItemPrototype* self = (ItemPrototype*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Field20'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->Field20);
 return 1;
}

/* set function: Field20 of class  ItemPrototype */
static int tolua_set_ItemPrototype_unsigned_Field20(lua_State* tolua_S)
{
  ItemPrototype* self = (ItemPrototype*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Field20'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Field20 = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: Field21 of class  ItemPrototype */
static int tolua_get_ItemPrototype_unsigned_Field21(lua_State* tolua_S)
{
  ItemPrototype* self = (ItemPrototype*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Field21'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->Field21);
 return 1;
}

/* set function: Field21 of class  ItemPrototype */
static int tolua_set_ItemPrototype_unsigned_Field21(lua_State* tolua_S)
{
  ItemPrototype* self = (ItemPrototype*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Field21'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Field21 = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: Field22 of class  ItemPrototype */
static int tolua_get_ItemPrototype_unsigned_Field22(lua_State* tolua_S)
{
  ItemPrototype* self = (ItemPrototype*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Field22'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->Field22);
 return 1;
}

/* set function: Field22 of class  ItemPrototype */
static int tolua_set_ItemPrototype_unsigned_Field22(lua_State* tolua_S)
{
  ItemPrototype* self = (ItemPrototype*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Field22'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Field22 = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: Field23 of class  ItemPrototype */
static int tolua_get_ItemPrototype_unsigned_Field23(lua_State* tolua_S)
{
  ItemPrototype* self = (ItemPrototype*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Field23'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->Field23);
 return 1;
}

/* set function: Field23 of class  ItemPrototype */
static int tolua_set_ItemPrototype_unsigned_Field23(lua_State* tolua_S)
{
  ItemPrototype* self = (ItemPrototype*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Field23'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Field23 = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: MaxCount of class  ItemPrototype */
static int tolua_get_ItemPrototype_unsigned_MaxCount(lua_State* tolua_S)
{
  ItemPrototype* self = (ItemPrototype*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'MaxCount'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->MaxCount);
 return 1;
}

/* set function: MaxCount of class  ItemPrototype */
static int tolua_set_ItemPrototype_unsigned_MaxCount(lua_State* tolua_S)
{
  ItemPrototype* self = (ItemPrototype*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'MaxCount'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->MaxCount = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: Field25 of class  ItemPrototype */
static int tolua_get_ItemPrototype_unsigned_Field25(lua_State* tolua_S)
{
  ItemPrototype* self = (ItemPrototype*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Field25'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->Field25);
 return 1;
}

/* set function: Field25 of class  ItemPrototype */
static int tolua_set_ItemPrototype_unsigned_Field25(lua_State* tolua_S)
{
  ItemPrototype* self = (ItemPrototype*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Field25'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Field25 = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: Armor of class  ItemPrototype */
static int tolua_get_ItemPrototype_unsigned_Armor(lua_State* tolua_S)
{
  ItemPrototype* self = (ItemPrototype*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Armor'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->Armor);
 return 1;
}

/* set function: Armor of class  ItemPrototype */
static int tolua_set_ItemPrototype_unsigned_Armor(lua_State* tolua_S)
{
  ItemPrototype* self = (ItemPrototype*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Armor'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Armor = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: Field62 of class  ItemPrototype */
static int tolua_get_ItemPrototype_unsigned_Field62(lua_State* tolua_S)
{
  ItemPrototype* self = (ItemPrototype*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Field62'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->Field62);
 return 1;
}

/* set function: Field62 of class  ItemPrototype */
static int tolua_set_ItemPrototype_unsigned_Field62(lua_State* tolua_S)
{
  ItemPrototype* self = (ItemPrototype*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Field62'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Field62 = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: FireRes of class  ItemPrototype */
static int tolua_get_ItemPrototype_unsigned_FireRes(lua_State* tolua_S)
{
  ItemPrototype* self = (ItemPrototype*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'FireRes'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->FireRes);
 return 1;
}

/* set function: FireRes of class  ItemPrototype */
static int tolua_set_ItemPrototype_unsigned_FireRes(lua_State* tolua_S)
{
  ItemPrototype* self = (ItemPrototype*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'FireRes'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->FireRes = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: NatureRes of class  ItemPrototype */
static int tolua_get_ItemPrototype_unsigned_NatureRes(lua_State* tolua_S)
{
  ItemPrototype* self = (ItemPrototype*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'NatureRes'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->NatureRes);
 return 1;
}

/* set function: NatureRes of class  ItemPrototype */
static int tolua_set_ItemPrototype_unsigned_NatureRes(lua_State* tolua_S)
{
  ItemPrototype* self = (ItemPrototype*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'NatureRes'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->NatureRes = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: FrostRes of class  ItemPrototype */
static int tolua_get_ItemPrototype_unsigned_FrostRes(lua_State* tolua_S)
{
  ItemPrototype* self = (ItemPrototype*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'FrostRes'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->FrostRes);
 return 1;
}

/* set function: FrostRes of class  ItemPrototype */
static int tolua_set_ItemPrototype_unsigned_FrostRes(lua_State* tolua_S)
{
  ItemPrototype* self = (ItemPrototype*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'FrostRes'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->FrostRes = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: ShadowRes of class  ItemPrototype */
static int tolua_get_ItemPrototype_unsigned_ShadowRes(lua_State* tolua_S)
{
  ItemPrototype* self = (ItemPrototype*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'ShadowRes'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->ShadowRes);
 return 1;
}

/* set function: ShadowRes of class  ItemPrototype */
static int tolua_set_ItemPrototype_unsigned_ShadowRes(lua_State* tolua_S)
{
  ItemPrototype* self = (ItemPrototype*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'ShadowRes'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->ShadowRes = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: ArcaneRes of class  ItemPrototype */
static int tolua_get_ItemPrototype_unsigned_ArcaneRes(lua_State* tolua_S)
{
  ItemPrototype* self = (ItemPrototype*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'ArcaneRes'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->ArcaneRes);
 return 1;
}

/* set function: ArcaneRes of class  ItemPrototype */
static int tolua_set_ItemPrototype_unsigned_ArcaneRes(lua_State* tolua_S)
{
  ItemPrototype* self = (ItemPrototype*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'ArcaneRes'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->ArcaneRes = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: Delay of class  ItemPrototype */
static int tolua_get_ItemPrototype_unsigned_Delay(lua_State* tolua_S)
{
  ItemPrototype* self = (ItemPrototype*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Delay'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->Delay);
 return 1;
}

/* set function: Delay of class  ItemPrototype */
static int tolua_set_ItemPrototype_unsigned_Delay(lua_State* tolua_S)
{
  ItemPrototype* self = (ItemPrototype*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Delay'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Delay = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: Field69 of class  ItemPrototype */
static int tolua_get_ItemPrototype_unsigned_Field69(lua_State* tolua_S)
{
  ItemPrototype* self = (ItemPrototype*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Field69'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->Field69);
 return 1;
}

/* set function: Field69 of class  ItemPrototype */
static int tolua_set_ItemPrototype_unsigned_Field69(lua_State* tolua_S)
{
  ItemPrototype* self = (ItemPrototype*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Field69'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Field69 = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: Bonding of class  ItemPrototype */
static int tolua_get_ItemPrototype_unsigned_Bonding(lua_State* tolua_S)
{
  ItemPrototype* self = (ItemPrototype*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Bonding'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->Bonding);
 return 1;
}

/* set function: Bonding of class  ItemPrototype */
static int tolua_set_ItemPrototype_unsigned_Bonding(lua_State* tolua_S)
{
  ItemPrototype* self = (ItemPrototype*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Bonding'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Bonding = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: Description of class  ItemPrototype */
static int tolua_get_ItemPrototype_Description(lua_State* tolua_S)
{
  ItemPrototype* self = (ItemPrototype*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Description'",NULL);
#endif
 tolua_pushstring(tolua_S,(const char*)self->Description);
 return 1;
}

/* set function: Description of class  ItemPrototype */
static int tolua_set_ItemPrototype_Description(lua_State* tolua_S)
{
  ItemPrototype* self = (ItemPrototype*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Description'",NULL);
 if (!tolua_isstring(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Description = ((char*)  tolua_tostring(tolua_S,2,0));
 return 0;
}

/* get function: Field102 of class  ItemPrototype */
static int tolua_get_ItemPrototype_unsigned_Field102(lua_State* tolua_S)
{
  ItemPrototype* self = (ItemPrototype*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Field102'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->Field102);
 return 1;
}

/* set function: Field102 of class  ItemPrototype */
static int tolua_set_ItemPrototype_unsigned_Field102(lua_State* tolua_S)
{
  ItemPrototype* self = (ItemPrototype*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Field102'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Field102 = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: Field103 of class  ItemPrototype */
static int tolua_get_ItemPrototype_unsigned_Field103(lua_State* tolua_S)
{
  ItemPrototype* self = (ItemPrototype*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Field103'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->Field103);
 return 1;
}

/* set function: Field103 of class  ItemPrototype */
static int tolua_set_ItemPrototype_unsigned_Field103(lua_State* tolua_S)
{
  ItemPrototype* self = (ItemPrototype*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Field103'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Field103 = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: Field104 of class  ItemPrototype */
static int tolua_get_ItemPrototype_unsigned_Field104(lua_State* tolua_S)
{
  ItemPrototype* self = (ItemPrototype*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Field104'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->Field104);
 return 1;
}

/* set function: Field104 of class  ItemPrototype */
static int tolua_set_ItemPrototype_unsigned_Field104(lua_State* tolua_S)
{
  ItemPrototype* self = (ItemPrototype*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Field104'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Field104 = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: Field105 of class  ItemPrototype */
static int tolua_get_ItemPrototype_unsigned_Field105(lua_State* tolua_S)
{
  ItemPrototype* self = (ItemPrototype*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Field105'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->Field105);
 return 1;
}

/* set function: Field105 of class  ItemPrototype */
static int tolua_set_ItemPrototype_unsigned_Field105(lua_State* tolua_S)
{
  ItemPrototype* self = (ItemPrototype*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Field105'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Field105 = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: Field106 of class  ItemPrototype */
static int tolua_get_ItemPrototype_unsigned_Field106(lua_State* tolua_S)
{
  ItemPrototype* self = (ItemPrototype*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Field106'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->Field106);
 return 1;
}

/* set function: Field106 of class  ItemPrototype */
static int tolua_set_ItemPrototype_unsigned_Field106(lua_State* tolua_S)
{
  ItemPrototype* self = (ItemPrototype*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Field106'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Field106 = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: Field107 of class  ItemPrototype */
static int tolua_get_ItemPrototype_unsigned_Field107(lua_State* tolua_S)
{
  ItemPrototype* self = (ItemPrototype*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Field107'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->Field107);
 return 1;
}

/* set function: Field107 of class  ItemPrototype */
static int tolua_set_ItemPrototype_unsigned_Field107(lua_State* tolua_S)
{
  ItemPrototype* self = (ItemPrototype*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Field107'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Field107 = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: Field108 of class  ItemPrototype */
static int tolua_get_ItemPrototype_unsigned_Field108(lua_State* tolua_S)
{
  ItemPrototype* self = (ItemPrototype*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Field108'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->Field108);
 return 1;
}

/* set function: Field108 of class  ItemPrototype */
static int tolua_set_ItemPrototype_unsigned_Field108(lua_State* tolua_S)
{
  ItemPrototype* self = (ItemPrototype*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Field108'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Field108 = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: Field109 of class  ItemPrototype */
static int tolua_get_ItemPrototype_unsigned_Field109(lua_State* tolua_S)
{
  ItemPrototype* self = (ItemPrototype*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Field109'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->Field109);
 return 1;
}

/* set function: Field109 of class  ItemPrototype */
static int tolua_set_ItemPrototype_unsigned_Field109(lua_State* tolua_S)
{
  ItemPrototype* self = (ItemPrototype*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Field109'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Field109 = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: Field110 of class  ItemPrototype */
static int tolua_get_ItemPrototype_unsigned_Field110(lua_State* tolua_S)
{
  ItemPrototype* self = (ItemPrototype*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Field110'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->Field110);
 return 1;
}

/* set function: Field110 of class  ItemPrototype */
static int tolua_set_ItemPrototype_unsigned_Field110(lua_State* tolua_S)
{
  ItemPrototype* self = (ItemPrototype*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Field110'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Field110 = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: Field111 of class  ItemPrototype */
static int tolua_get_ItemPrototype_unsigned_Field111(lua_State* tolua_S)
{
  ItemPrototype* self = (ItemPrototype*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Field111'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->Field111);
 return 1;
}

/* set function: Field111 of class  ItemPrototype */
static int tolua_set_ItemPrototype_unsigned_Field111(lua_State* tolua_S)
{
  ItemPrototype* self = (ItemPrototype*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Field111'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Field111 = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: MaxDurability of class  ItemPrototype */
static int tolua_get_ItemPrototype_unsigned_MaxDurability(lua_State* tolua_S)
{
  ItemPrototype* self = (ItemPrototype*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'MaxDurability'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->MaxDurability);
 return 1;
}

/* set function: MaxDurability of class  ItemPrototype */
static int tolua_set_ItemPrototype_unsigned_MaxDurability(lua_State* tolua_S)
{
  ItemPrototype* self = (ItemPrototype*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'MaxDurability'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->MaxDurability = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* method: delete of class  ItemPrototype */
static int tolua_worldserver_ItemPrototype_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"ItemPrototype",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  ItemPrototype* self = (ItemPrototype*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'",NULL);
#endif
  delete self;
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}

/* get function: Owner of class  Item */
static int tolua_get_Item_Owner_ptr(lua_State* tolua_S)
{
  Item* self = (Item*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Owner'",NULL);
#endif
 tolua_pushusertype(tolua_S,(void*)self->Owner,"Unit");
 return 1;
}

/* set function: Owner of class  Item */
static int tolua_set_Item_Owner_ptr(lua_State* tolua_S)
{
  Item* self = (Item*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Owner'",NULL);
 if (!tolua_isusertype(tolua_S,2,"Unit",0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Owner = ((Unit*)  tolua_tousertype(tolua_S,2,0));
 return 0;
}

/* method: new of class  Item */
static int tolua_worldserver_Item_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"Item",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
 {
  Item* tolua_ret = (Item*)  new Item();
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"Item");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}

/* method: new_local of class  Item */
static int tolua_worldserver_Item_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"Item",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
 {
  Item* tolua_ret = (Item*)  new Item();
 tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"Item");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}

/* method: Create of class  Item */
static int tolua_worldserver_Item_Create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Item",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isusertype(tolua_S,3,"Unit",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  Item* self = (Item*)  tolua_tousertype(tolua_S,1,0);
  unsigned int iItemId = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
  Unit* iOwner = ((Unit*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Create'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->Create(iItemId,iOwner);
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Create'.",&tolua_err);
 return 0;
#endif
}

/* method: Create of class  Item */
static int tolua_worldserver_Item_Create01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Item",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isusertype(tolua_S,4,"Unit",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  Item* self = (Item*)  tolua_tousertype(tolua_S,1,0);
  unsigned int iLowGuid = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
  unsigned int iItemId = (( unsigned int)  tolua_tonumber(tolua_S,3,0));
  Unit* iOwner = ((Unit*)  tolua_tousertype(tolua_S,4,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Create'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->Create(iLowGuid,iItemId,iOwner);
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
tolua_lerror:
 return tolua_worldserver_Item_Create00(tolua_S);
}

/* method: GetProto of class  Item */
static int tolua_worldserver_Item_GetProto00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Item",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  Item* self = (Item*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetProto'",NULL);
#endif
 {
  ItemPrototype* tolua_ret = (ItemPrototype*)  self->GetProto();
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"ItemPrototype");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetProto'.",&tolua_err);
 return 0;
#endif
}

/* method: FindProto of class  Item */
static int tolua_worldserver_Item_FindProto00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"Item",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  unsigned int iItemId = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
 {
  ItemPrototype* tolua_ret = (ItemPrototype*)  Item::FindProto(iItemId);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"ItemPrototype");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'FindProto'.",&tolua_err);
 return 0;
#endif
}

/* method: SaveToDB of class  Item */
static int tolua_worldserver_Item_SaveToDB00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Item",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  Item* self = (Item*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SaveToDB'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->SaveToDB();
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SaveToDB'.",&tolua_err);
 return 0;
#endif
}

/* method: LoadFromDB of class  Item */
static int tolua_worldserver_Item_LoadFromDB00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Item",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  Item* self = (Item*)  tolua_tousertype(tolua_S,1,0);
  unsigned int iLowGuid = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LoadFromDB'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->LoadFromDB(iLowGuid);
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LoadFromDB'.",&tolua_err);
 return 0;
#endif
}

/* method: DeleteFromDB of class  Item */
static int tolua_worldserver_Item_DeleteFromDB00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Item",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  Item* self = (Item*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'DeleteFromDB'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->DeleteFromDB();
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'DeleteFromDB'.",&tolua_err);
 return 0;
#endif
}

/* get function: Tick of class  Server */
static int tolua_get_Server_unsigned_Tick(lua_State* tolua_S)
{
  Server* self = (Server*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Tick'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->Tick);
 return 1;
}

/* set function: Tick of class  Server */
static int tolua_set_Server_unsigned_Tick(lua_State* tolua_S)
{
  Server* self = (Server*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Tick'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Tick = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: Logger of class  Server */
static int tolua_get_Server_Logger_ptr(lua_State* tolua_S)
{
  Server* self = (Server*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Logger'",NULL);
#endif
 tolua_pushusertype(tolua_S,(void*)self->Logger,"Log");
 return 1;
}

/* set function: Logger of class  Server */
static int tolua_set_Server_Logger_ptr(lua_State* tolua_S)
{
  Server* self = (Server*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Logger'",NULL);
 if (!tolua_isusertype(tolua_S,2,"Log",0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Logger = ((Log*)  tolua_tousertype(tolua_S,2,0));
 return 0;
}

/* method: Start of class  Server */
static int tolua_worldserver_Server_Start00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Server",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  Server* self = (Server*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Start'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->Start();
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Start'.",&tolua_err);
 return 0;
#endif
}

/* method: Stop of class  Server */
static int tolua_worldserver_Server_Stop00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Server",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  Server* self = (Server*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Stop'",NULL);
#endif
 {
  self->Stop();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Stop'.",&tolua_err);
 return 0;
#endif
}

/* method: IsRunning of class  Server */
static int tolua_worldserver_Server_IsRunning00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Server",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  Server* self = (Server*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsRunning'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->IsRunning();
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsRunning'.",&tolua_err);
 return 0;
#endif
}

/* method: AddClient of class  Server */
static int tolua_worldserver_Server_AddClient00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Server",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"Client",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  Server* self = (Server*)  tolua_tousertype(tolua_S,1,0);
  Client* client = ((Client*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddClient'",NULL);
#endif
 {
  self->AddClient(client);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddClient'.",&tolua_err);
 return 0;
#endif
}

/* method: SocketEvent of class  Server */
static int tolua_worldserver_Server_SocketEvent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Server",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  Server* self = (Server*)  tolua_tousertype(tolua_S,1,0);
  unsigned int mask = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SocketEvent'",NULL);
#endif
 {
  self->SocketEvent(mask);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SocketEvent'.",&tolua_err);
 return 0;
#endif
}

/* method: SetLogger of class  Server */
static int tolua_worldserver_Server_SetLogger00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Server",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"Log",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  Server* self = (Server*)  tolua_tousertype(tolua_S,1,0);
  Log* iLogger = ((Log*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetLogger'",NULL);
#endif
 {
  self->SetLogger(iLogger);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetLogger'.",&tolua_err);
 return 0;
#endif
}

/* get function: db of class  WorldServer */
static int tolua_get_WorldServer_db_ptr(lua_State* tolua_S)
{
  WorldServer* self = (WorldServer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'db'",NULL);
#endif
 tolua_pushusertype(tolua_S,(void*)self->db,"Database");
 return 1;
}

/* set function: db of class  WorldServer */
static int tolua_set_WorldServer_db_ptr(lua_State* tolua_S)
{
  WorldServer* self = (WorldServer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'db'",NULL);
 if (!tolua_isusertype(tolua_S,2,"Database",0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->db = ((Database*)  tolua_tousertype(tolua_S,2,0));
 return 0;
}

/* get function: rdb of class  WorldServer */
static int tolua_get_WorldServer_rdb_ptr(lua_State* tolua_S)
{
  WorldServer* self = (WorldServer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'rdb'",NULL);
#endif
 tolua_pushusertype(tolua_S,(void*)self->rdb,"Database");
 return 1;
}

/* set function: rdb of class  WorldServer */
static int tolua_set_WorldServer_rdb_ptr(lua_State* tolua_S)
{
  WorldServer* self = (WorldServer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'rdb'",NULL);
 if (!tolua_isusertype(tolua_S,2,"Database",0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->rdb = ((Database*)  tolua_tousertype(tolua_S,2,0));
 return 0;
}

/* get function: GameFeatures of class  WorldServer */
static int tolua_get_WorldServer_unsigned_GameFeatures(lua_State* tolua_S)
{
  WorldServer* self = (WorldServer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'GameFeatures'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->GameFeatures);
 return 1;
}

/* set function: GameFeatures of class  WorldServer */
static int tolua_set_WorldServer_unsigned_GameFeatures(lua_State* tolua_S)
{
  WorldServer* self = (WorldServer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'GameFeatures'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->GameFeatures = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* method: new of class  WorldServer */
static int tolua_worldserver_WorldServer_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"WorldServer",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isusertype(tolua_S,3,"Log",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  unsigned int iPort = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
  Log* iLogger = ((Log*)  tolua_tousertype(tolua_S,3,0));
 {
  WorldServer* tolua_ret = (WorldServer*)  new WorldServer(iPort,iLogger);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"WorldServer");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}

/* method: new_local of class  WorldServer */
static int tolua_worldserver_WorldServer_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"WorldServer",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isusertype(tolua_S,3,"Log",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  unsigned int iPort = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
  Log* iLogger = ((Log*)  tolua_tousertype(tolua_S,3,0));
 {
  WorldServer* tolua_ret = (WorldServer*)  new WorldServer(iPort,iLogger);
 tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"WorldServer");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}

/* method: UpdateRealm of class  WorldServer */
static int tolua_worldserver_WorldServer_UpdateRealm00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"WorldServer",0,&tolua_err) ||
 !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  WorldServer* self = (WorldServer*)  tolua_tousertype(tolua_S,1,0);
  bool Online = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'UpdateRealm'",NULL);
#endif
 {
  self->UpdateRealm(Online);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'UpdateRealm'.",&tolua_err);
 return 0;
#endif
}

/* method: SocketEvent of class  WorldServer */
static int tolua_worldserver_WorldServer_SocketEvent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"WorldServer",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  WorldServer* self = (WorldServer*)  tolua_tousertype(tolua_S,1,0);
  unsigned int mask = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SocketEvent'",NULL);
#endif
 {
  self->SocketEvent(mask);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SocketEvent'.",&tolua_err);
 return 0;
#endif
}

/* method: Start of class  WorldServer */
static int tolua_worldserver_WorldServer_Start00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"WorldServer",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  WorldServer* self = (WorldServer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Start'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->Start();
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Start'.",&tolua_err);
 return 0;
#endif
}

/* method: Stop of class  WorldServer */
static int tolua_worldserver_WorldServer_Stop00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"WorldServer",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  WorldServer* self = (WorldServer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Stop'",NULL);
#endif
 {
  self->Stop();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Stop'.",&tolua_err);
 return 0;
#endif
}

/* method: Update of class  WorldServer */
static int tolua_worldserver_WorldServer_Update00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"WorldServer",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  WorldServer* self = (WorldServer*)  tolua_tousertype(tolua_S,1,0);
  unsigned int DeltaMs = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Update'",NULL);
#endif
 {
  self->Update(DeltaMs);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Update'.",&tolua_err);
 return 0;
#endif
}

/* method: SetDatabase of class  WorldServer */
static int tolua_worldserver_WorldServer_SetDatabase00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"WorldServer",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"Database",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,3,"Database",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  WorldServer* self = (WorldServer*)  tolua_tousertype(tolua_S,1,0);
  Database* iwdb = ((Database*)  tolua_tousertype(tolua_S,2,0));
  Database* irdb = ((Database*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetDatabase'",NULL);
#endif
 {
  self->SetDatabase(iwdb,irdb);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetDatabase'.",&tolua_err);
 return 0;
#endif
}

/* method: GetRealmName of class  WorldServer */
static int tolua_worldserver_WorldServer_GetRealmName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"WorldServer",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  WorldServer* self = (WorldServer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetRealmName'",NULL);
#endif
 {
  const char* tolua_ret = (const char*)  self->GetRealmName();
 tolua_pushstring(tolua_S,(const char*)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetRealmName'.",&tolua_err);
 return 0;
#endif
}

/* method: SetRealmName of class  WorldServer */
static int tolua_worldserver_WorldServer_SetRealmName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"WorldServer",0,&tolua_err) ||
 !tolua_isstring(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  WorldServer* self = (WorldServer*)  tolua_tousertype(tolua_S,1,0);
  const char* iRealmName = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetRealmName'",NULL);
#endif
 {
  self->SetRealmName(iRealmName);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetRealmName'.",&tolua_err);
 return 0;
#endif
}

/* method: GetGameTime of class  WorldServer */
static int tolua_worldserver_WorldServer_GetGameTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"WorldServer",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  WorldServer* self = (WorldServer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetGameTime'",NULL);
#endif
 {
  time_t tolua_ret = (time_t)  self->GetGameTime();
 {
#ifdef __cplusplus
 void* tolua_obj = new time_t(tolua_ret);
 tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"time_t");
#else
 void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(time_t));
 tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"time_t");
#endif
 }
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetGameTime'.",&tolua_err);
 return 0;
#endif
}

/* method: GetClientLimit of class  WorldServer */
static int tolua_worldserver_WorldServer_GetClientLimit00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"WorldServer",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  WorldServer* self = (WorldServer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetClientLimit'",NULL);
#endif
 {
  unsigned int tolua_ret = ( unsigned int)  self->GetClientLimit();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetClientLimit'.",&tolua_err);
 return 0;
#endif
}

/* method: SetClientLimit of class  WorldServer */
static int tolua_worldserver_WorldServer_SetClientLimit00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"WorldServer",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  WorldServer* self = (WorldServer*)  tolua_tousertype(tolua_S,1,0);
  int Limit = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetClientLimit'",NULL);
#endif
 {
  self->SetClientLimit(Limit);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetClientLimit'.",&tolua_err);
 return 0;
#endif
}

/* method: GetStartZone of class  WorldServer */
static int tolua_worldserver_WorldServer_GetStartZone00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"WorldServer",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  WorldServer* self = (WorldServer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetStartZone'",NULL);
#endif
 {
  unsigned int tolua_ret = ( unsigned int)  self->GetStartZone();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetStartZone'.",&tolua_err);
 return 0;
#endif
}

/* method: SetStartZone of class  WorldServer */
static int tolua_worldserver_WorldServer_SetStartZone00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"WorldServer",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  WorldServer* self = (WorldServer*)  tolua_tousertype(tolua_S,1,0);
  int Zone = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetStartZone'",NULL);
#endif
 {
  self->SetStartZone(Zone);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetStartZone'.",&tolua_err);
 return 0;
#endif
}

/* method: GetCinematics of class  WorldServer */
static int tolua_worldserver_WorldServer_GetCinematics00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"WorldServer",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  WorldServer* self = (WorldServer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetCinematics'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->GetCinematics();
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetCinematics'.",&tolua_err);
 return 0;
#endif
}

/* method: SetCinematics of class  WorldServer */
static int tolua_worldserver_WorldServer_SetCinematics00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"WorldServer",0,&tolua_err) ||
 !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  WorldServer* self = (WorldServer*)  tolua_tousertype(tolua_S,1,0);
  bool Enable = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetCinematics'",NULL);
#endif
 {
  self->SetCinematics(Enable);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetCinematics'.",&tolua_err);
 return 0;
#endif
}

/* method: SetMotd of class  WorldServer */
static int tolua_worldserver_WorldServer_SetMotd00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"WorldServer",0,&tolua_err) ||
 !tolua_isstring(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  WorldServer* self = (WorldServer*)  tolua_tousertype(tolua_S,1,0);
  const char* motd = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetMotd'",NULL);
#endif
 {
  self->SetMotd(motd);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetMotd'.",&tolua_err);
 return 0;
#endif
}

/* method: GetMotd of class  WorldServer */
static int tolua_worldserver_WorldServer_GetMotd00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"WorldServer",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  WorldServer* self = (WorldServer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMotd'",NULL);
#endif
 {
  const char* tolua_ret = (const char*)  self->GetMotd();
 tolua_pushstring(tolua_S,(const char*)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMotd'.",&tolua_err);
 return 0;
#endif
}

/* method: GetClientsConnected of class  WorldServer */
static int tolua_worldserver_WorldServer_GetClientsConnected00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"WorldServer",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  WorldServer* self = (WorldServer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetClientsConnected'",NULL);
#endif
 {
  unsigned int tolua_ret = ( unsigned int)  self->GetClientsConnected();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetClientsConnected'.",&tolua_err);
 return 0;
#endif
}

/* method: SendGlobalPacket of class  WorldServer */
static int tolua_worldserver_WorldServer_SendGlobalPacket00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"WorldServer",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"NetworkPacket",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,3,"GameClient",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  WorldServer* self = (WorldServer*)  tolua_tousertype(tolua_S,1,0);
  NetworkPacket* data = ((NetworkPacket*)  tolua_tousertype(tolua_S,2,0));
  GameClient* Self = ((GameClient*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SendGlobalPacket'",NULL);
#endif
 {
  self->SendGlobalPacket(data,Self);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SendGlobalPacket'.",&tolua_err);
 return 0;
#endif
}

/* method: SendGlobalMessage of class  WorldServer */
static int tolua_worldserver_WorldServer_SendGlobalMessage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"WorldServer",0,&tolua_err) ||
 !tolua_isstring(tolua_S,2,0,&tolua_err) ||
 !tolua_isusertype(tolua_S,3,"GameClient",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  WorldServer* self = (WorldServer*)  tolua_tousertype(tolua_S,1,0);
  const char* iText = ((const char*)  tolua_tostring(tolua_S,2,0));
  GameClient* Self = ((GameClient*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SendGlobalMessage'",NULL);
#endif
 {
  self->SendGlobalMessage(iText,Self);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SendGlobalMessage'.",&tolua_err);
 return 0;
#endif
}

/* method: GenerateGUID of class  WorldServer */
static int tolua_worldserver_WorldServer_GenerateGUID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"WorldServer",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  WorldServer* self = (WorldServer*)  tolua_tousertype(tolua_S,1,0);
  unsigned int GuidHigh = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GenerateGUID'",NULL);
#endif
 {
  unsigned long long tolua_ret = ( unsigned long long)  self->GenerateGUID(GuidHigh);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GenerateGUID'.",&tolua_err);
 return 0;
#endif
}

/* Open function */
TOLUA_API int tolua_worldserver_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
#ifdef __cplusplus
 tolua_cclass(tolua_S,"Base","Base","",tolua_collect_Base);
#else
 tolua_cclass(tolua_S,"Base","Base","",NULL);
#endif
 tolua_beginmodule(tolua_S,"Base");
 tolua_function(tolua_S,"new",tolua_worldserver_Base_new00);
 tolua_function(tolua_S,"new_local",tolua_worldserver_Base_new00_local);
 tolua_set_call_event(tolua_S,tolua_worldserver_Base_new00_local, "Base");
 tolua_function(tolua_S,"IncRef",tolua_worldserver_Base_IncRef00);
 tolua_function(tolua_S,"DecRef",tolua_worldserver_Base_DecRef00);
 tolua_function(tolua_S,"GetRefCount",tolua_worldserver_Base_GetRefCount00);
 tolua_endmodule(tolua_S);
#ifdef __cplusplus
 tolua_cclass(tolua_S,"NetworkPacket","NetworkPacket","Base",tolua_collect_NetworkPacket);
#else
 tolua_cclass(tolua_S,"NetworkPacket","NetworkPacket","Base",NULL);
#endif
 tolua_beginmodule(tolua_S,"NetworkPacket");
 tolua_variable(tolua_S,"length",tolua_get_NetworkPacket_unsigned_length,tolua_set_NetworkPacket_unsigned_length);
 tolua_function(tolua_S,"new",tolua_worldserver_NetworkPacket_new00);
 tolua_function(tolua_S,"new_local",tolua_worldserver_NetworkPacket_new00_local);
 tolua_set_call_event(tolua_S,tolua_worldserver_NetworkPacket_new00_local, "NetworkPacket");
 tolua_function(tolua_S,"new",tolua_worldserver_NetworkPacket_new01);
 tolua_function(tolua_S,"new_local",tolua_worldserver_NetworkPacket_new01_local);
 tolua_set_call_event(tolua_S,tolua_worldserver_NetworkPacket_new01_local, "NetworkPacket");
 tolua_function(tolua_S,"SetLength",tolua_worldserver_NetworkPacket_SetLength00);
 tolua_function(tolua_S,"Assemble",tolua_worldserver_NetworkPacket_Assemble00);
 tolua_endmodule(tolua_S);
 tolua_constant(tolua_S,"RECVB_SIZE",RECVB_SIZE);
 tolua_constant(tolua_S,"RECVB_MASK",RECVB_MASK);
 tolua_constant(tolua_S,"SENDB_SIZE",SENDB_SIZE);
 tolua_constant(tolua_S,"SENDB_MASK",SENDB_MASK);
 tolua_constant(tolua_S,"PF_READ",PF_READ);
 tolua_constant(tolua_S,"PF_WRITE",PF_WRITE);
 tolua_constant(tolua_S,"PF_EXCEPT",PF_EXCEPT);
 tolua_cclass(tolua_S,"Socket","Socket","Base",NULL);
 tolua_beginmodule(tolua_S,"Socket");
 tolua_function(tolua_S,"Listen",tolua_worldserver_Socket_Listen00);
 tolua_function(tolua_S,"Connect",tolua_worldserver_Socket_Connect00);
 tolua_function(tolua_S,"ErrorString",tolua_worldserver_Socket_ErrorString00);
 tolua_function(tolua_S,"ReceiveData",tolua_worldserver_Socket_ReceiveData00);
 tolua_function(tolua_S,"SendData",tolua_worldserver_Socket_SendData00);
 tolua_function(tolua_S,"SendData",tolua_worldserver_Socket_SendData01);
 tolua_function(tolua_S,"SendPending",tolua_worldserver_Socket_SendPending00);
 tolua_function(tolua_S,"Accept",tolua_worldserver_Socket_Accept00);
 tolua_function(tolua_S,"InterestedEvents",tolua_worldserver_Socket_InterestedEvents00);
 tolua_function(tolua_S,"Connected",tolua_worldserver_Socket_Connected00);
 tolua_function(tolua_S,"GetIP",tolua_worldserver_Socket_GetIP00);
 tolua_function(tolua_S,"SetLogger",tolua_worldserver_Socket_SetLogger00);
 tolua_function(tolua_S,"Rewind",tolua_worldserver_Socket_Rewind00);
 tolua_function(tolua_S,"Avail",tolua_worldserver_Socket_Avail00);
 tolua_function(tolua_S,"Chewed",tolua_worldserver_Socket_Chewed00);
 tolua_function(tolua_S,"Swallow",tolua_worldserver_Socket_Swallow00);
 tolua_function(tolua_S,"Skip",tolua_worldserver_Socket_Skip00);
 tolua_function(tolua_S,"Get",tolua_worldserver_Socket_Get00);
 tolua_function(tolua_S,"Get",tolua_worldserver_Socket_Get01);
 tolua_function(tolua_S,"GetLE",tolua_worldserver_Socket_GetLE00);
 tolua_function(tolua_S,"GetLE",tolua_worldserver_Socket_GetLE01);
 tolua_function(tolua_S,"GetLE",tolua_worldserver_Socket_GetLE02);
 tolua_function(tolua_S,"GetLE",tolua_worldserver_Socket_GetLE03);
 tolua_function(tolua_S,"GetBE",tolua_worldserver_Socket_GetBE00);
 tolua_function(tolua_S,"GetBE",tolua_worldserver_Socket_GetBE01);
 tolua_function(tolua_S,"GetCStr",tolua_worldserver_Socket_GetCStr00);
 tolua_endmodule(tolua_S);
 tolua_constant(tolua_S,"dbeOk",dbeOk);
 tolua_constant(tolua_S,"dbeBadArguments",dbeBadArguments);
 tolua_constant(tolua_S,"dbeConnectionFailed",dbeConnectionFailed);
 tolua_constant(tolua_S,"dbeWrongCredentials",dbeWrongCredentials);
 tolua_constant(tolua_S,"dbeConnectionLost",dbeConnectionLost);
 tolua_constant(tolua_S,"dbeInvalidQuery",dbeInvalidQuery);
 tolua_constant(tolua_S,"dbUnknown",dbUnknown);
 tolua_constant(tolua_S,"dbMySQL",dbMySQL);
 tolua_cclass(tolua_S,"DatabaseExecutor","DatabaseExecutor","",NULL);
 tolua_beginmodule(tolua_S,"DatabaseExecutor");
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"Log","Log","",NULL);
 tolua_beginmodule(tolua_S,"Log");
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"Database","Database","Base",NULL);
 tolua_beginmodule(tolua_S,"Database");
 tolua_variable(tolua_S,"Logger",tolua_get_Database_Logger_ptr,tolua_set_Database_Logger_ptr);
 tolua_function(tolua_S,"Create",tolua_worldserver_Database_Create00);
 tolua_function(tolua_S,"ParseType",tolua_worldserver_Database_ParseType00);
 tolua_function(tolua_S,"ErrorString",tolua_worldserver_Database_ErrorString00);
 tolua_function(tolua_S,"GetExecutor",tolua_worldserver_Database_GetExecutor00);
 tolua_function(tolua_S,"PutExecutor",tolua_worldserver_Database_PutExecutor00);
 tolua_function(tolua_S,"SetLogger",tolua_worldserver_Database_SetLogger00);
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"DatabaseExecutor","DatabaseExecutor","Base",NULL);
 tolua_beginmodule(tolua_S,"DatabaseExecutor");
 tolua_function(tolua_S,"GetParent",tolua_worldserver_DatabaseExecutor_GetParent00);
 tolua_function(tolua_S,"Ok",tolua_worldserver_DatabaseExecutor_Ok00);
 tolua_function(tolua_S,"Free",tolua_worldserver_DatabaseExecutor_Free00);
 tolua_function(tolua_S,"Execute",tolua_worldserver_DatabaseExecutor_Execute00);
 tolua_function(tolua_S,"NumFields",tolua_worldserver_DatabaseExecutor_NumFields00);
 tolua_function(tolua_S,"NumRows",tolua_worldserver_DatabaseExecutor_NumRows00);
 tolua_function(tolua_S,"NextRow",tolua_worldserver_DatabaseExecutor_NextRow00);
 tolua_function(tolua_S,"Get",tolua_worldserver_DatabaseExecutor_Get00);
 tolua_function(tolua_S,"GetLength",tolua_worldserver_DatabaseExecutor_GetLength00);
 tolua_function(tolua_S,"GetI32",tolua_worldserver_DatabaseExecutor_GetI3200);
 tolua_function(tolua_S,"GetU32",tolua_worldserver_DatabaseExecutor_GetU3200);
 tolua_function(tolua_S,"GetU64",tolua_worldserver_DatabaseExecutor_GetU6400);
 tolua_function(tolua_S,"GetFloat",tolua_worldserver_DatabaseExecutor_GetFloat00);
 tolua_function(tolua_S,"GetID",tolua_worldserver_DatabaseExecutor_GetID00);
 tolua_function(tolua_S,"GetAffectedRows",tolua_worldserver_DatabaseExecutor_GetAffectedRows00);
 tolua_endmodule(tolua_S);
 tolua_constant(tolua_S,"HIGHGUID_PLAYER",HIGHGUID_PLAYER);
 tolua_constant(tolua_S,"HIGHGUID_THING",HIGHGUID_THING);
 tolua_constant(tolua_S,"HIGHGUID_UNIT",HIGHGUID_UNIT);
 tolua_constant(tolua_S,"HIGHGUID_GAMEOBJECT",HIGHGUID_GAMEOBJECT);
 tolua_constant(tolua_S,"HIGHGUID_DYNAMICOBJECT",HIGHGUID_DYNAMICOBJECT);
 tolua_constant(tolua_S,"TYPE_OBJECT",TYPE_OBJECT);
 tolua_constant(tolua_S,"TYPE_ITEM",TYPE_ITEM);
 tolua_constant(tolua_S,"TYPE_CONTAINER",TYPE_CONTAINER);
 tolua_constant(tolua_S,"TYPE_UNIT",TYPE_UNIT);
 tolua_constant(tolua_S,"TYPE_PLAYER",TYPE_PLAYER);
 tolua_constant(tolua_S,"TYPE_GAMEOBJECT",TYPE_GAMEOBJECT);
 tolua_constant(tolua_S,"TYPE_DYNAMICOBJECT",TYPE_DYNAMICOBJECT);
 tolua_constant(tolua_S,"TYPE_CORPSE",TYPE_CORPSE);
 tolua_constant(tolua_S,"TYPE_AIGROUP",TYPE_AIGROUP);
 tolua_constant(tolua_S,"TYPE_AREATRIGGER",TYPE_AREATRIGGER);
 tolua_constant(tolua_S,"UPDATE_VALUES",UPDATE_VALUES);
 tolua_constant(tolua_S,"UPDATE_MOVEMENT",UPDATE_MOVEMENT);
 tolua_constant(tolua_S,"UPDATE_CREATE_OBJECT",UPDATE_CREATE_OBJECT);
 tolua_constant(tolua_S,"UPDATE_OUT_OF_RANGE_OBJECTS",UPDATE_OUT_OF_RANGE_OBJECTS);
 tolua_constant(tolua_S,"UPDATE_NEAR_OBJECTS",UPDATE_NEAR_OBJECTS);
 tolua_cclass(tolua_S,"Database","Database","",NULL);
 tolua_beginmodule(tolua_S,"Database");
 tolua_endmodule(tolua_S);
#ifdef __cplusplus
 tolua_cclass(tolua_S,"GameClient","GameClient","",tolua_collect_GameClient);
#else
 tolua_cclass(tolua_S,"GameClient","GameClient","",NULL);
#endif
 tolua_beginmodule(tolua_S,"GameClient");
 tolua_endmodule(tolua_S);
#ifdef __cplusplus
 tolua_cclass(tolua_S,"NetworkPacket","NetworkPacket","",tolua_collect_NetworkPacket);
#else
 tolua_cclass(tolua_S,"NetworkPacket","NetworkPacket","",NULL);
#endif
 tolua_beginmodule(tolua_S,"NetworkPacket");
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"ObjectVector","ObjectVector","",NULL);
 tolua_beginmodule(tolua_S,"ObjectVector");
 tolua_endmodule(tolua_S);
#ifdef __cplusplus
 tolua_cclass(tolua_S,"NetworkPacket","NetworkPacket","",tolua_collect_NetworkPacket);
#else
 tolua_cclass(tolua_S,"NetworkPacket","NetworkPacket","",NULL);
#endif
 tolua_beginmodule(tolua_S,"NetworkPacket");
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"Object","Object","Base",NULL);
 tolua_beginmodule(tolua_S,"Object");
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"Server","Server","",NULL);
 tolua_beginmodule(tolua_S,"Server");
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"Client","Client","Base",NULL);
 tolua_beginmodule(tolua_S,"Client");
 tolua_function(tolua_S,"SocketEvent",tolua_worldserver_Client_SocketEvent00);
 tolua_endmodule(tolua_S);
 tolua_constant(tolua_S,"CAPS_MAKEITEMS",CAPS_MAKEITEMS);
 tolua_constant(tolua_S,"CAPS_MAKECREATURES",CAPS_MAKECREATURES);
 tolua_cclass(tolua_S,"Player","Player","",NULL);
 tolua_beginmodule(tolua_S,"Player");
 tolua_endmodule(tolua_S);
#ifdef __cplusplus
 tolua_cclass(tolua_S,"GameClient","GameClient","Client",tolua_collect_GameClient);
#else
 tolua_cclass(tolua_S,"GameClient","GameClient","Client",NULL);
#endif
 tolua_beginmodule(tolua_S,"GameClient");
 tolua_variable(tolua_S,"Login",tolua_get_GameClient_Login,tolua_set_GameClient_Login);
 tolua_variable(tolua_S,"Character",tolua_get_GameClient_Character_ptr,tolua_set_GameClient_Character_ptr);
 tolua_function(tolua_S,"new",tolua_worldserver_GameClient_new00);
 tolua_function(tolua_S,"new_local",tolua_worldserver_GameClient_new00_local);
 tolua_set_call_event(tolua_S,tolua_worldserver_GameClient_new00_local, "GameClient");
 tolua_function(tolua_S,"delete",tolua_worldserver_GameClient_delete00);
 tolua_function(tolua_S,"SocketEvent",tolua_worldserver_GameClient_SocketEvent00);
 tolua_function(tolua_S,"Authenticated",tolua_worldserver_GameClient_Authenticated00);
 tolua_function(tolua_S,"Send",tolua_worldserver_GameClient_Send00);
 tolua_endmodule(tolua_S);
 tolua_constant(tolua_S,"MAX_POSITIVE_AURAS",MAX_POSITIVE_AURAS);
 tolua_constant(tolua_S,"MAX_AURAS",MAX_AURAS);
 tolua_constant(tolua_S,"AFLAG_EMPTY",AFLAG_EMPTY);
 tolua_constant(tolua_S,"AFLAG_SET",AFLAG_SET);
 tolua_constant(tolua_S,"SPELL_AURA_NONE",SPELL_AURA_NONE);
 tolua_constant(tolua_S,"SPELL_AURA_BIND_SIGHT",SPELL_AURA_BIND_SIGHT);
 tolua_constant(tolua_S,"SPELL_AURA_MOD_POSSESS",SPELL_AURA_MOD_POSSESS);
 tolua_constant(tolua_S,"SPELL_AURA_PERIODIC_DAMAGE",SPELL_AURA_PERIODIC_DAMAGE);
 tolua_constant(tolua_S,"SPELL_AURA_MOD_CONFUSE",SPELL_AURA_MOD_CONFUSE);
 tolua_constant(tolua_S,"SPELL_AURA_MOD_CHARM",SPELL_AURA_MOD_CHARM);
 tolua_constant(tolua_S,"SPELL_AURA_MOD_FEAR",SPELL_AURA_MOD_FEAR);
 tolua_constant(tolua_S,"SPELL_AURA_PERIODIC_HEAL",SPELL_AURA_PERIODIC_HEAL);
 tolua_constant(tolua_S,"SPELL_AURA_MOD_ATTACKSPEED",SPELL_AURA_MOD_ATTACKSPEED);
 tolua_constant(tolua_S,"SPELL_AURA_MOD_THREAT",SPELL_AURA_MOD_THREAT);
 tolua_constant(tolua_S,"SPELL_AURA_MOD_TAUNT",SPELL_AURA_MOD_TAUNT);
 tolua_constant(tolua_S,"SPELL_AURA_MOD_STUN",SPELL_AURA_MOD_STUN);
 tolua_constant(tolua_S,"SPELL_AURA_MOD_DAMAGE_DONE",SPELL_AURA_MOD_DAMAGE_DONE);
 tolua_constant(tolua_S,"SPELL_AURA_MOD_DAMAGE_TAKEN",SPELL_AURA_MOD_DAMAGE_TAKEN);
 tolua_constant(tolua_S,"SPELL_AURA_DAMAGE_SHIELD",SPELL_AURA_DAMAGE_SHIELD);
 tolua_constant(tolua_S,"SPELL_AURA_MOD_STEALTH",SPELL_AURA_MOD_STEALTH);
 tolua_constant(tolua_S,"SPELL_AURA_MOD_DETECT",SPELL_AURA_MOD_DETECT);
 tolua_constant(tolua_S,"SPELL_AURA_MOD_INVISIBILITY",SPELL_AURA_MOD_INVISIBILITY);
 tolua_constant(tolua_S,"SPELL_AURA_MOD_INVISIBILITY_DETECTION",SPELL_AURA_MOD_INVISIBILITY_DETECTION);
 tolua_constant(tolua_S,"SPELL_AURA_MOD_RESISTANCE",SPELL_AURA_MOD_RESISTANCE);
 tolua_constant(tolua_S,"SPELL_AURA_PERIODIC_TRIGGER_SPELL",SPELL_AURA_PERIODIC_TRIGGER_SPELL);
 tolua_constant(tolua_S,"SPELL_AURA_PERIODIC_ENERGIZE",SPELL_AURA_PERIODIC_ENERGIZE);
 tolua_constant(tolua_S,"SPELL_AURA_MOD_PACIFY",SPELL_AURA_MOD_PACIFY);
 tolua_constant(tolua_S,"SPELL_AURA_MOD_ROOT",SPELL_AURA_MOD_ROOT);
 tolua_constant(tolua_S,"SPELL_AURA_MOD_SILENCE",SPELL_AURA_MOD_SILENCE);
 tolua_constant(tolua_S,"SPELL_AURA_REFLECT_SPELLS",SPELL_AURA_REFLECT_SPELLS);
 tolua_constant(tolua_S,"SPELL_AURA_MOD_STAT",SPELL_AURA_MOD_STAT);
 tolua_constant(tolua_S,"SPELL_AURA_MOD_SKILL",SPELL_AURA_MOD_SKILL);
 tolua_constant(tolua_S,"SPELL_AURA_MOD_INCREASE_SPEED",SPELL_AURA_MOD_INCREASE_SPEED);
 tolua_constant(tolua_S,"SPELL_AURA_MOD_INCREASE_MOUNTED_SPEED",SPELL_AURA_MOD_INCREASE_MOUNTED_SPEED);
 tolua_constant(tolua_S,"SPELL_AURA_MOD_DECREASE_SPEED",SPELL_AURA_MOD_DECREASE_SPEED);
 tolua_constant(tolua_S,"SPELL_AURA_MOD_INCREASE_HEALTH",SPELL_AURA_MOD_INCREASE_HEALTH);
 tolua_constant(tolua_S,"SPELL_AURA_MOD_INCREASE_ENERGY",SPELL_AURA_MOD_INCREASE_ENERGY);
 tolua_constant(tolua_S,"SPELL_AURA_MOD_SHAPESHIFT",SPELL_AURA_MOD_SHAPESHIFT);
 tolua_constant(tolua_S,"SPELL_AURA_EFFECT_IMMUNITY",SPELL_AURA_EFFECT_IMMUNITY);
 tolua_constant(tolua_S,"SPELL_AURA_STATE_IMMUNITY",SPELL_AURA_STATE_IMMUNITY);
 tolua_constant(tolua_S,"SPELL_AURA_SCHOOL_IMMUNITY",SPELL_AURA_SCHOOL_IMMUNITY);
 tolua_constant(tolua_S,"SPELL_AURA_DAMAGE_IMMUNITY",SPELL_AURA_DAMAGE_IMMUNITY);
 tolua_constant(tolua_S,"SPELL_AURA_DISPEL_IMMUNITY",SPELL_AURA_DISPEL_IMMUNITY);
 tolua_constant(tolua_S,"SPELL_AURA_PROC_TRIGGER_SPELL",SPELL_AURA_PROC_TRIGGER_SPELL);
 tolua_constant(tolua_S,"SPELL_AURA_PROC_TRIGGER_DAMAGE",SPELL_AURA_PROC_TRIGGER_DAMAGE);
 tolua_constant(tolua_S,"SPELL_AURA_TRACK_CREATURES",SPELL_AURA_TRACK_CREATURES);
 tolua_constant(tolua_S,"SPELL_AURA_TRACK_RESOURCES",SPELL_AURA_TRACK_RESOURCES);
 tolua_constant(tolua_S,"SPELL_AURA_MOD_PARRY_SKILL",SPELL_AURA_MOD_PARRY_SKILL);
 tolua_constant(tolua_S,"SPELL_AURA_MOD_PARRY_PERCENT",SPELL_AURA_MOD_PARRY_PERCENT);
 tolua_constant(tolua_S,"SPELL_AURA_MOD_DODGE_SKILL",SPELL_AURA_MOD_DODGE_SKILL);
 tolua_constant(tolua_S,"SPELL_AURA_MOD_DODGE_PERCENT",SPELL_AURA_MOD_DODGE_PERCENT);
 tolua_constant(tolua_S,"SPELL_AURA_MOD_BLOCK_SKILL",SPELL_AURA_MOD_BLOCK_SKILL);
 tolua_constant(tolua_S,"SPELL_AURA_MOD_BLOCK_PERCENT",SPELL_AURA_MOD_BLOCK_PERCENT);
 tolua_constant(tolua_S,"SPELL_AURA_MOD_CRIT_PERCENT",SPELL_AURA_MOD_CRIT_PERCENT);
 tolua_constant(tolua_S,"SPELL_AURA_PERIODIC_LEECH",SPELL_AURA_PERIODIC_LEECH);
 tolua_constant(tolua_S,"SPELL_AURA_MOD_HIT_CHANCE",SPELL_AURA_MOD_HIT_CHANCE);
 tolua_constant(tolua_S,"SPELL_AURA_MOD_SPELL_HIT_CHANCE",SPELL_AURA_MOD_SPELL_HIT_CHANCE);
 tolua_constant(tolua_S,"SPELL_AURA_TRANSFORM",SPELL_AURA_TRANSFORM);
 tolua_constant(tolua_S,"SPELL_AURA_MOD_SPELL_CRIT_CHANCE",SPELL_AURA_MOD_SPELL_CRIT_CHANCE);
 tolua_constant(tolua_S,"SPELL_AURA_MOD_INCREASE_SWIM_SPEED",SPELL_AURA_MOD_INCREASE_SWIM_SPEED);
 tolua_constant(tolua_S,"SPELL_AURA_MOD_DAMAGE_DONE_CREATURE",SPELL_AURA_MOD_DAMAGE_DONE_CREATURE);
 tolua_constant(tolua_S,"SPELL_AURA_MOD_PACIFY_SILENCE",SPELL_AURA_MOD_PACIFY_SILENCE);
 tolua_constant(tolua_S,"SPELL_AURA_MOD_SCALE",SPELL_AURA_MOD_SCALE);
 tolua_constant(tolua_S,"SPELL_AURA_PERIODIC_HEALTH_FUNNEL",SPELL_AURA_PERIODIC_HEALTH_FUNNEL);
 tolua_constant(tolua_S,"SPELL_AURA_PERIODIC_MANA_FUNNEL",SPELL_AURA_PERIODIC_MANA_FUNNEL);
 tolua_constant(tolua_S,"SPELL_AURA_PERIODIC_MANA_LEECH",SPELL_AURA_PERIODIC_MANA_LEECH);
 tolua_constant(tolua_S,"SPELL_AURA_MOD_CASTING_SPEED",SPELL_AURA_MOD_CASTING_SPEED);
 tolua_constant(tolua_S,"SPELL_AURA_FEIGN_DEATH",SPELL_AURA_FEIGN_DEATH);
 tolua_constant(tolua_S,"SPELL_AURA_MOD_DISARM",SPELL_AURA_MOD_DISARM);
 tolua_constant(tolua_S,"SPELL_AURA_MOD_STALKED",SPELL_AURA_MOD_STALKED);
 tolua_constant(tolua_S,"SPELL_AURA_SCHOOL_ABSORB",SPELL_AURA_SCHOOL_ABSORB);
 tolua_constant(tolua_S,"SPELL_AURA_EXTRA_ATTACKS",SPELL_AURA_EXTRA_ATTACKS);
 tolua_constant(tolua_S,"SPELL_AURA_MOD_SPELL_CRIT_CHANCE_SCHOOL",SPELL_AURA_MOD_SPELL_CRIT_CHANCE_SCHOOL);
 tolua_constant(tolua_S,"SPELL_AURA_MOD_POWER_COST",SPELL_AURA_MOD_POWER_COST);
 tolua_constant(tolua_S,"SPELL_AURA_MOD_POWER_COST_SCHOOL",SPELL_AURA_MOD_POWER_COST_SCHOOL);
 tolua_constant(tolua_S,"SPELL_AURA_REFLECT_SPELLS_SCHOOL",SPELL_AURA_REFLECT_SPELLS_SCHOOL);
 tolua_constant(tolua_S,"SPELL_AURA_MOD_LANGUAGE",SPELL_AURA_MOD_LANGUAGE);
 tolua_constant(tolua_S,"SPELL_AURA_FAR_SIGHT",SPELL_AURA_FAR_SIGHT);
 tolua_constant(tolua_S,"SPELL_AURA_MECHANIC_IMMUNITY",SPELL_AURA_MECHANIC_IMMUNITY);
 tolua_constant(tolua_S,"SPELL_AURA_MOUNTED",SPELL_AURA_MOUNTED);
 tolua_constant(tolua_S,"SPELL_AURA_MOD_DAMAGE_PERCENT_DONE",SPELL_AURA_MOD_DAMAGE_PERCENT_DONE);
 tolua_constant(tolua_S,"SPELL_AURA_MOD_PERCENT_STAT",SPELL_AURA_MOD_PERCENT_STAT);
 tolua_constant(tolua_S,"SPELL_AURA_SPLIT_DAMAGE",SPELL_AURA_SPLIT_DAMAGE);
 tolua_constant(tolua_S,"SPELL_AURA_WATER_BREATHING",SPELL_AURA_WATER_BREATHING);
 tolua_constant(tolua_S,"SPELL_AURA_MOD_BASE_RESISTANCE",SPELL_AURA_MOD_BASE_RESISTANCE);
 tolua_constant(tolua_S,"SPELL_AURA_MOD_REGEN",SPELL_AURA_MOD_REGEN);
 tolua_constant(tolua_S,"SPELL_AURA_MOD_POWER_REGEN",SPELL_AURA_MOD_POWER_REGEN);
 tolua_constant(tolua_S,"SPELL_AURA_CHANNEL_DEATH_ITEM",SPELL_AURA_CHANNEL_DEATH_ITEM);
 tolua_constant(tolua_S,"SPELL_AURA_MOD_DAMAGE_PERCENT_TAKEN",SPELL_AURA_MOD_DAMAGE_PERCENT_TAKEN);
 tolua_constant(tolua_S,"SPELL_AURA_MOD_PERCENT_REGEN",SPELL_AURA_MOD_PERCENT_REGEN);
 tolua_constant(tolua_S,"SPELL_AURA_PERIODIC_DAMAGE_PERCENT",SPELL_AURA_PERIODIC_DAMAGE_PERCENT);
 tolua_constant(tolua_S,"SPELL_AURA_MOD_RESIST_CHANCE",SPELL_AURA_MOD_RESIST_CHANCE);
 tolua_constant(tolua_S,"SPELL_AURA_MOD_DETECT_RANGE",SPELL_AURA_MOD_DETECT_RANGE);
 tolua_constant(tolua_S,"SPELL_AURA_PREVENTS_FLEEING",SPELL_AURA_PREVENTS_FLEEING);
 tolua_constant(tolua_S,"SPELL_AURA_MOD_UNATTACKABLE",SPELL_AURA_MOD_UNATTACKABLE);
 tolua_constant(tolua_S,"SPELL_AURA_INTERRUPT_REGEN",SPELL_AURA_INTERRUPT_REGEN);
 tolua_constant(tolua_S,"SPELL_AURA_GHOST",SPELL_AURA_GHOST);
 tolua_constant(tolua_S,"SPELL_AURA_SPELL_MAGNET",SPELL_AURA_SPELL_MAGNET);
 tolua_constant(tolua_S,"SPELL_AURA_MANA_SHIELD",SPELL_AURA_MANA_SHIELD);
 tolua_constant(tolua_S,"SPELL_AURA_MOD_SKILL_TALENT",SPELL_AURA_MOD_SKILL_TALENT);
 tolua_constant(tolua_S,"SPELL_AURA_MOD_ATTACK_POWER",SPELL_AURA_MOD_ATTACK_POWER);
 tolua_constant(tolua_S,"SPELL_AURA_AURAS_VISIBLE",SPELL_AURA_AURAS_VISIBLE);
 tolua_constant(tolua_S,"SPELL_AURA_MOD_RESISTANCE_PCT",SPELL_AURA_MOD_RESISTANCE_PCT);
 tolua_constant(tolua_S,"SPELL_AURA_MOD_CREATURE_ATTACK_POWER",SPELL_AURA_MOD_CREATURE_ATTACK_POWER);
 tolua_constant(tolua_S,"SPELL_AURA_MOD_TOTAL_THREAT",SPELL_AURA_MOD_TOTAL_THREAT);
 tolua_constant(tolua_S,"SPELL_AURA_WATER_WALK",SPELL_AURA_WATER_WALK);
 tolua_constant(tolua_S,"SPELL_AURA_FEATHER_FALL",SPELL_AURA_FEATHER_FALL);
 tolua_constant(tolua_S,"SPELL_AURA_HOVER",SPELL_AURA_HOVER);
 tolua_constant(tolua_S,"SPELL_AURA_ADD_FLAT_MODIFIER",SPELL_AURA_ADD_FLAT_MODIFIER);
 tolua_constant(tolua_S,"SPELL_AURA_ADD_PCT_MODIFIER",SPELL_AURA_ADD_PCT_MODIFIER);
 tolua_constant(tolua_S,"SPELL_AURA_ADD_TARGET_TRIGGER",SPELL_AURA_ADD_TARGET_TRIGGER);
 tolua_constant(tolua_S,"SPELL_AURA_MOD_POWER_REGEN_PERCENT",SPELL_AURA_MOD_POWER_REGEN_PERCENT);
 tolua_constant(tolua_S,"SPELL_AURA_ADD_CASTER_HIT_TRIGGER",SPELL_AURA_ADD_CASTER_HIT_TRIGGER);
 tolua_constant(tolua_S,"SPELL_AURA_OVERRIDE_CLASS_SCRIPTS",SPELL_AURA_OVERRIDE_CLASS_SCRIPTS);
 tolua_constant(tolua_S,"SPELL_AURA_MOD_RANGED_DAMAGE_TAKEN",SPELL_AURA_MOD_RANGED_DAMAGE_TAKEN);
 tolua_constant(tolua_S,"SPELL_AURA_MOD_RANGED_DAMAGE_TAKEN_PCT",SPELL_AURA_MOD_RANGED_DAMAGE_TAKEN_PCT);
 tolua_constant(tolua_S,"SPELL_AURA_MOD_HEALING",SPELL_AURA_MOD_HEALING);
 tolua_constant(tolua_S,"SPELL_AURA_IGNORE_REGEN_INTERRUPT",SPELL_AURA_IGNORE_REGEN_INTERRUPT);
 tolua_constant(tolua_S,"SPELL_AURA_MOD_MECHANIC_RESISTANCE",SPELL_AURA_MOD_MECHANIC_RESISTANCE);
 tolua_constant(tolua_S,"SPELL_AURA_MOD_HEALING_PCT",SPELL_AURA_MOD_HEALING_PCT);
 tolua_constant(tolua_S,"SPELL_AURA_SHARE_PET_TRACKING",SPELL_AURA_SHARE_PET_TRACKING);
 tolua_constant(tolua_S,"SPELL_AURA_UNTRACKABLE",SPELL_AURA_UNTRACKABLE);
 tolua_constant(tolua_S,"SPELL_AURA_EMPATHY",SPELL_AURA_EMPATHY);
 tolua_constant(tolua_S,"SPELL_AURA_MOD_OFFHAND_DAMAGE_PCT",SPELL_AURA_MOD_OFFHAND_DAMAGE_PCT);
 tolua_constant(tolua_S,"SPELL_AURA_MOD_POWER_COST_PCT",SPELL_AURA_MOD_POWER_COST_PCT);
 tolua_constant(tolua_S,"SPELL_AURA_MOD_RANGED_ATTACK_POWER",SPELL_AURA_MOD_RANGED_ATTACK_POWER);
 tolua_constant(tolua_S,"SPELL_AURA_MOD_MELEE_DAMAGE_TAKEN",SPELL_AURA_MOD_MELEE_DAMAGE_TAKEN);
 tolua_constant(tolua_S,"SPELL_AURA_MOD_MELEE_DAMAGE_TAKEN_PCT",SPELL_AURA_MOD_MELEE_DAMAGE_TAKEN_PCT);
 tolua_constant(tolua_S,"SPELL_AURA_RANGED_ATTACK_POWER_ATTACKER_BONUS",SPELL_AURA_RANGED_ATTACK_POWER_ATTACKER_BONUS);
 tolua_constant(tolua_S,"SPELL_AURA_MOD_POSSESS_PET",SPELL_AURA_MOD_POSSESS_PET);
 tolua_constant(tolua_S,"SPELL_AURA_MOD_INCREASE_SPEED_ALWAYS",SPELL_AURA_MOD_INCREASE_SPEED_ALWAYS);
 tolua_constant(tolua_S,"SPELL_AURA_MOD_MOUNTED_SPEED_ALWAYS",SPELL_AURA_MOD_MOUNTED_SPEED_ALWAYS);
 tolua_constant(tolua_S,"SPELL_AURA_MOD_CREATURE_RANGED_ATTACK_POWER",SPELL_AURA_MOD_CREATURE_RANGED_ATTACK_POWER);
 tolua_constant(tolua_S,"SPELL_AURA_MOD_INCREASE_ENERGY_PERCENT",SPELL_AURA_MOD_INCREASE_ENERGY_PERCENT);
 tolua_constant(tolua_S,"SPELL_AURA_MOD_INCREASE_HEALTH_PERCENT",SPELL_AURA_MOD_INCREASE_HEALTH_PERCENT);
 tolua_constant(tolua_S,"SPELL_AURA_MOD_MANA_REGEN_INTERRUPT",SPELL_AURA_MOD_MANA_REGEN_INTERRUPT);
 tolua_constant(tolua_S,"SPELL_AURA_MOD_HEALING_DONE",SPELL_AURA_MOD_HEALING_DONE);
 tolua_constant(tolua_S,"SPELL_AURA_MOD_HEALING_DONE_PERCENT",SPELL_AURA_MOD_HEALING_DONE_PERCENT);
 tolua_constant(tolua_S,"SPELL_AURA_MOD_TOTAL_STAT_PERCENTAGE",SPELL_AURA_MOD_TOTAL_STAT_PERCENTAGE);
 tolua_constant(tolua_S,"SPELL_AURA_MOD_HASTE",SPELL_AURA_MOD_HASTE);
 tolua_constant(tolua_S,"SPELL_AURA_FORCE_REACTION",SPELL_AURA_FORCE_REACTION);
 tolua_constant(tolua_S,"SPELL_AURA_MOD_RANGED_HASTE",SPELL_AURA_MOD_RANGED_HASTE);
 tolua_constant(tolua_S,"SPELL_AURA_MOD_RANGED_AMMO_HASTE",SPELL_AURA_MOD_RANGED_AMMO_HASTE);
 tolua_constant(tolua_S,"SPELL_AURA_MOD_BASE_RESISTANCE_PCT",SPELL_AURA_MOD_BASE_RESISTANCE_PCT);
 tolua_constant(tolua_S,"SPELL_AURA_MOD_RESISTANCE_EXCLUSIVE",SPELL_AURA_MOD_RESISTANCE_EXCLUSIVE);
 tolua_constant(tolua_S,"SPELL_AURA_SAFE_FALL",SPELL_AURA_SAFE_FALL);
 tolua_constant(tolua_S,"SPELL_AURA_CHARISMA",SPELL_AURA_CHARISMA);
 tolua_constant(tolua_S,"SPELL_AURA_PERSUADED",SPELL_AURA_PERSUADED);
 tolua_constant(tolua_S,"SPELL_AURA_ADD_CREATURE_IMMUNITY",SPELL_AURA_ADD_CREATURE_IMMUNITY);
 tolua_constant(tolua_S,"SPELL_AURA_RETAIN_COMBO_POINTS",SPELL_AURA_RETAIN_COMBO_POINTS);
 tolua_cclass(tolua_S,"SpellEntry","SpellEntry","",NULL);
 tolua_beginmodule(tolua_S,"SpellEntry");
 tolua_endmodule(tolua_S);
#ifdef __cplusplus
 tolua_cclass(tolua_S,"Modifier","Modifier","",tolua_collect_Modifier);
#else
 tolua_cclass(tolua_S,"Modifier","Modifier","",NULL);
#endif
 tolua_beginmodule(tolua_S,"Modifier");
 tolua_variable(tolua_S,"Type",tolua_get_Modifier_unsigned_Type,tolua_set_Modifier_unsigned_Type);
 tolua_variable(tolua_S,"Amount",tolua_get_Modifier_Amount,tolua_set_Modifier_Amount);
 tolua_variable(tolua_S,"MiscValue",tolua_get_Modifier_unsigned_MiscValue,tolua_set_Modifier_unsigned_MiscValue);
 tolua_variable(tolua_S,"MiscValue2",tolua_get_Modifier_unsigned_MiscValue2,tolua_set_Modifier_unsigned_MiscValue2);
 tolua_function(tolua_S,"new",tolua_worldserver_Modifier_new00);
 tolua_function(tolua_S,"new_local",tolua_worldserver_Modifier_new00_local);
 tolua_set_call_event(tolua_S,tolua_worldserver_Modifier_new00_local, "Modifier");
 tolua_endmodule(tolua_S);
#ifdef __cplusplus
 tolua_cclass(tolua_S,"Affect","Affect","",tolua_collect_Affect);
#else
 tolua_cclass(tolua_S,"Affect","Affect","",NULL);
#endif
 tolua_beginmodule(tolua_S,"Affect");
 tolua_variable(tolua_S,"Duration",tolua_get_Affect_Duration,tolua_set_Affect_Duration);
 tolua_variable(tolua_S,"CasterGUID",tolua_get_Affect_unsigned_CasterGUID,tolua_set_Affect_unsigned_CasterGUID);
 tolua_variable(tolua_S,"AuraSlot",tolua_get_Affect_unsigned_AuraSlot,tolua_set_Affect_unsigned_AuraSlot);
 tolua_variable(tolua_S,"DamagePerTick",tolua_get_Affect_unsigned_DamagePerTick,tolua_set_Affect_unsigned_DamagePerTick);
 tolua_variable(tolua_S,"DamageTimer",tolua_get_Affect_DamageTimer,tolua_set_Affect_DamageTimer);
 tolua_variable(tolua_S,"SpellPerTick",tolua_get_Affect_unsigned_SpellPerTick,tolua_set_Affect_unsigned_SpellPerTick);
 tolua_variable(tolua_S,"SpellTimer",tolua_get_Affect_SpellTimer,tolua_set_Affect_SpellTimer);
 tolua_variable(tolua_S,"Positive",tolua_get_Affect_Positive,tolua_set_Affect_Positive);
 tolua_variable(tolua_S,"CoAffect",tolua_get_Affect_CoAffect_ptr,tolua_set_Affect_CoAffect_ptr);
 tolua_function(tolua_S,"new",tolua_worldserver_Affect_new00);
 tolua_function(tolua_S,"new_local",tolua_worldserver_Affect_new00_local);
 tolua_set_call_event(tolua_S,tolua_worldserver_Affect_new00_local, "Affect");
 tolua_function(tolua_S,"AddMod",tolua_worldserver_Affect_AddMod00);
 tolua_function(tolua_S,"SetDamagePerTick",tolua_worldserver_Affect_SetDamagePerTick00);
 tolua_function(tolua_S,"SetPeriodicTriggerSpell",tolua_worldserver_Affect_SetPeriodicTriggerSpell00);
 tolua_function(tolua_S,"Update",tolua_worldserver_Affect_Update00);
 tolua_endmodule(tolua_S);
#ifdef __cplusplus
 tolua_cclass(tolua_S,"Affect","Affect","",tolua_collect_Affect);
#else
 tolua_cclass(tolua_S,"Affect","Affect","",NULL);
#endif
 tolua_beginmodule(tolua_S,"Affect");
 tolua_endmodule(tolua_S);
#ifdef __cplusplus
 tolua_cclass(tolua_S,"Modifier","Modifier","",tolua_collect_Modifier);
#else
 tolua_cclass(tolua_S,"Modifier","Modifier","",NULL);
#endif
 tolua_beginmodule(tolua_S,"Modifier");
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"Spell","Spell","",NULL);
 tolua_beginmodule(tolua_S,"Spell");
 tolua_endmodule(tolua_S);
 tolua_constant(tolua_S,"ALIVE",ALIVE);
 tolua_constant(tolua_S,"JUST_DIED",JUST_DIED);
 tolua_constant(tolua_S,"CORPSE",CORPSE);
 tolua_constant(tolua_S,"DEAD",DEAD);
 tolua_constant(tolua_S,"UFF_GOSSIP",UFF_GOSSIP);
 tolua_constant(tolua_S,"UFF_LOCKED_MOVE",UFF_LOCKED_MOVE);
 tolua_constant(tolua_S,"UFF_PLAYER_CONTROLLED",UFF_PLAYER_CONTROLLED);
 tolua_constant(tolua_S,"UFF_PLUS_MOB",UFF_PLUS_MOB);
 tolua_constant(tolua_S,"UFF_ALLIANCE",UFF_ALLIANCE);
 tolua_constant(tolua_S,"UFF_MOUNTED",UFF_MOUNTED);
 tolua_constant(tolua_S,"UFF_DEAD",UFF_DEAD);
 tolua_constant(tolua_S,"UFF_NO_ROTATION",UFF_NO_ROTATION);
 tolua_constant(tolua_S,"UFF_IN_COMBAT",UFF_IN_COMBAT);
 tolua_constant(tolua_S,"UFF_SKINNABLE",UFF_SKINNABLE);
 tolua_constant(tolua_S,"UFF_SHEATHED",UFF_SHEATHED);
 tolua_constant(tolua_S,"UDF_LOOTABLE",UDF_LOOTABLE);
 tolua_constant(tolua_S,"UDF_TAPPED_OTHER",UDF_TAPPED_OTHER);
 tolua_constant(tolua_S,"UDF_TAPPED_YOU",UDF_TAPPED_YOU);
 tolua_constant(tolua_S,"UDF_SHOW_INFO",UDF_SHOW_INFO);
 tolua_constant(tolua_S,"CFF_CLAIMED",CFF_CLAIMED);
#ifdef __cplusplus
 tolua_cclass(tolua_S,"Unit","Unit","Object",tolua_collect_Unit);
#else
 tolua_cclass(tolua_S,"Unit","Unit","Object",NULL);
#endif
 tolua_beginmodule(tolua_S,"Unit");
 tolua_function(tolua_S,"delete",tolua_worldserver_Unit_delete00);
 tolua_function(tolua_S,"Update",tolua_worldserver_Unit_Update00);
 tolua_function(tolua_S,"ApplyModifier",tolua_worldserver_Unit_ApplyModifier00);
 tolua_function(tolua_S,"ReceiveDamage",tolua_worldserver_Unit_ReceiveDamage00);
 tolua_function(tolua_S,"GenerateLoot",tolua_worldserver_Unit_GenerateLoot00);
 tolua_function(tolua_S,"GiveXP",tolua_worldserver_Unit_GiveXP00);
 tolua_function(tolua_S,"RemoveInRangeObject",tolua_worldserver_Unit_RemoveInRangeObject00);
 tolua_function(tolua_S,"SetAttackTimer",tolua_worldserver_Unit_SetAttackTimer00);
 tolua_function(tolua_S,"IsAttackReady",tolua_worldserver_Unit_IsAttackReady00);
 tolua_function(tolua_S,"CanReachWithAttack",tolua_worldserver_Unit_CanReachWithAttack00);
 tolua_function(tolua_S,"RemoveAttacker",tolua_worldserver_Unit_RemoveAttacker00);
 tolua_function(tolua_S,"GetLevel",tolua_worldserver_Unit_GetLevel00);
 tolua_function(tolua_S,"GetRace",tolua_worldserver_Unit_GetRace00);
 tolua_function(tolua_S,"GetClass",tolua_worldserver_Unit_GetClass00);
 tolua_function(tolua_S,"GetGender",tolua_worldserver_Unit_GetGender00);
 tolua_function(tolua_S,"DealDamage",tolua_worldserver_Unit_DealDamage00);
 tolua_function(tolua_S,"AttackerStateUpdate",tolua_worldserver_Unit_AttackerStateUpdate00);
 tolua_function(tolua_S,"SpellNonMeleeDamageLog",tolua_worldserver_Unit_SpellNonMeleeDamageLog00);
 tolua_function(tolua_S,"PeriodicAuraLog",tolua_worldserver_Unit_PeriodicAuraLog00);
 tolua_function(tolua_S,"AttackStart",tolua_worldserver_Unit_AttackStart00);
 tolua_function(tolua_S,"AttackStop",tolua_worldserver_Unit_AttackStop00);
 tolua_function(tolua_S,"IsAlive",tolua_worldserver_Unit_IsAlive00);
 tolua_function(tolua_S,"IsDead",tolua_worldserver_Unit_IsDead00);
 tolua_function(tolua_S,"SetDeathState",tolua_worldserver_Unit_SetDeathState00);
 tolua_function(tolua_S,"GetDeathState",tolua_worldserver_Unit_GetDeathState00);
 tolua_function(tolua_S,"AddAffect",tolua_worldserver_Unit_AddAffect00);
 tolua_function(tolua_S,"RemoveAffect",tolua_worldserver_Unit_RemoveAffect00);
 tolua_function(tolua_S,"RemoveAffect",tolua_worldserver_Unit_RemoveAffect01);
 tolua_function(tolua_S,"RemoveAffectById",tolua_worldserver_Unit_RemoveAffectById00);
 tolua_function(tolua_S,"RemoveAllAffects",tolua_worldserver_Unit_RemoveAllAffects00);
 tolua_function(tolua_S,"SetAura",tolua_worldserver_Unit_SetAura00);
 tolua_endmodule(tolua_S);
 tolua_constant(tolua_S,"HEALTH",HEALTH);
 tolua_constant(tolua_S,"UNKNOWN",UNKNOWN);
 tolua_constant(tolua_S,"AGILITY",AGILITY);
 tolua_constant(tolua_S,"STRENGHT",STRENGHT);
 tolua_constant(tolua_S,"INTELLECT",INTELLECT);
 tolua_constant(tolua_S,"SPIRIT",SPIRIT);
 tolua_constant(tolua_S,"STAMINA",STAMINA);
 tolua_constant(tolua_S,"NORMAL_DAMAGE",NORMAL_DAMAGE);
 tolua_constant(tolua_S,"HOLY_DAMAGE",HOLY_DAMAGE);
 tolua_constant(tolua_S,"FIRE_DAMAGE",FIRE_DAMAGE);
 tolua_constant(tolua_S,"NATURE_DAMAGE",NATURE_DAMAGE);
 tolua_constant(tolua_S,"FROST_DAMAGE",FROST_DAMAGE);
 tolua_constant(tolua_S,"SHADOW_DAMAGE",SHADOW_DAMAGE);
 tolua_constant(tolua_S,"ARCANE_DAMAGE",ARCANE_DAMAGE);
 tolua_constant(tolua_S,"USE",USE);
 tolua_constant(tolua_S,"ON_EQUIP",ON_EQUIP);
 tolua_constant(tolua_S,"CHANCE_ON_HIT",CHANCE_ON_HIT);
 tolua_constant(tolua_S,"SOULSTONE",SOULSTONE);
 tolua_constant(tolua_S,"ITEM_QUALITY_POOR_GREY",ITEM_QUALITY_POOR_GREY);
 tolua_constant(tolua_S,"ITEM_QUALITY_NORMAL_WHITE",ITEM_QUALITY_NORMAL_WHITE);
 tolua_constant(tolua_S,"ITEM_QUALITY_UNCOMMON_GREEN",ITEM_QUALITY_UNCOMMON_GREEN);
 tolua_constant(tolua_S,"ITEM_QUALITY_RARE_BLUE",ITEM_QUALITY_RARE_BLUE);
 tolua_constant(tolua_S,"ITEM_QUALITY_EPIC_PURPLE",ITEM_QUALITY_EPIC_PURPLE);
 tolua_constant(tolua_S,"ITEM_QUALITY_LEGENDARY_ORANGE",ITEM_QUALITY_LEGENDARY_ORANGE);
 tolua_constant(tolua_S,"ITEM_QUALITY_ARTIFACT_LIGHT_YELLOW",ITEM_QUALITY_ARTIFACT_LIGHT_YELLOW);
 tolua_constant(tolua_S,"NO_BIND",NO_BIND);
 tolua_constant(tolua_S,"BIND_WHEN_PICKED_UP",BIND_WHEN_PICKED_UP);
 tolua_constant(tolua_S,"BIND_WHEN_EQUIPED",BIND_WHEN_EQUIPED);
 tolua_constant(tolua_S,"INVTYPE_NON_EQUIP",INVTYPE_NON_EQUIP);
 tolua_constant(tolua_S,"INVTYPE_HEAD",INVTYPE_HEAD);
 tolua_constant(tolua_S,"INVTYPE_NECK",INVTYPE_NECK);
 tolua_constant(tolua_S,"INVTYPE_SHOULDERS",INVTYPE_SHOULDERS);
 tolua_constant(tolua_S,"INVTYPE_BODY",INVTYPE_BODY);
 tolua_constant(tolua_S,"INVTYPE_CHEST",INVTYPE_CHEST);
 tolua_constant(tolua_S,"INVTYPE_WAIST",INVTYPE_WAIST);
 tolua_constant(tolua_S,"INVTYPE_LEGS",INVTYPE_LEGS);
 tolua_constant(tolua_S,"INVTYPE_FEET",INVTYPE_FEET);
 tolua_constant(tolua_S,"INVTYPE_WRISTS",INVTYPE_WRISTS);
 tolua_constant(tolua_S,"INVTYPE_HANDS",INVTYPE_HANDS);
 tolua_constant(tolua_S,"INVTYPE_FINGER",INVTYPE_FINGER);
 tolua_constant(tolua_S,"INVTYPE_TRINKET",INVTYPE_TRINKET);
 tolua_constant(tolua_S,"INVTYPE_WEAPON",INVTYPE_WEAPON);
 tolua_constant(tolua_S,"INVTYPE_SHIELD",INVTYPE_SHIELD);
 tolua_constant(tolua_S,"INVTYPE_RANGED",INVTYPE_RANGED);
 tolua_constant(tolua_S,"INVTYPE_CLOAK",INVTYPE_CLOAK);
 tolua_constant(tolua_S,"INVTYPE_2HWEAPON",INVTYPE_2HWEAPON);
 tolua_constant(tolua_S,"INVTYPE_BAG",INVTYPE_BAG);
 tolua_constant(tolua_S,"INVTYPE_TABARD",INVTYPE_TABARD);
 tolua_constant(tolua_S,"INVTYPE_ROBE",INVTYPE_ROBE);
 tolua_constant(tolua_S,"INVTYPE_WEAPONMAINHAND",INVTYPE_WEAPONMAINHAND);
 tolua_constant(tolua_S,"INVTYPE_WEAPONOFFHAND",INVTYPE_WEAPONOFFHAND);
 tolua_constant(tolua_S,"INVTYPE_HOLDABLE",INVTYPE_HOLDABLE);
 tolua_constant(tolua_S,"INVTYPE_AMMO",INVTYPE_AMMO);
 tolua_constant(tolua_S,"INVTYPE_THROWN",INVTYPE_THROWN);
 tolua_constant(tolua_S,"INVTYPE_RANGEDRIGHT",INVTYPE_RANGEDRIGHT);
 tolua_constant(tolua_S,"NUM_INVENTORY_TYPES",NUM_INVENTORY_TYPES);
 tolua_constant(tolua_S,"ITEM_CLASS_CONSUMABLE",ITEM_CLASS_CONSUMABLE);
 tolua_constant(tolua_S,"ITEM_CLASS_CONTAINER",ITEM_CLASS_CONTAINER);
 tolua_constant(tolua_S,"ITEM_CLASS_WEAPON",ITEM_CLASS_WEAPON);
 tolua_constant(tolua_S,"ITEM_CLASS_ARMOR",ITEM_CLASS_ARMOR);
 tolua_constant(tolua_S,"ITEM_CLASS_REAGENT",ITEM_CLASS_REAGENT);
 tolua_constant(tolua_S,"ITEM_CLASS_PROJECTILE",ITEM_CLASS_PROJECTILE);
 tolua_constant(tolua_S,"ITEM_CLASS_TRADE_GOODS",ITEM_CLASS_TRADE_GOODS);
 tolua_constant(tolua_S,"ITEM_CLASS_RECIPE",ITEM_CLASS_RECIPE);
 tolua_constant(tolua_S,"ITEM_CLASS_QUIVER",ITEM_CLASS_QUIVER);
 tolua_constant(tolua_S,"ITEM_CLASS_QUEST",ITEM_CLASS_QUEST);
 tolua_constant(tolua_S,"ITEM_CLASS_KEY",ITEM_CLASS_KEY);
 tolua_constant(tolua_S,"ITEM_CLASS_MISC",ITEM_CLASS_MISC);
#ifdef __cplusplus
 tolua_cclass(tolua_S,"ItemPrototype","ItemPrototype","",tolua_collect_ItemPrototype);
#else
 tolua_cclass(tolua_S,"ItemPrototype","ItemPrototype","",NULL);
#endif
 tolua_beginmodule(tolua_S,"ItemPrototype");
 tolua_variable(tolua_S,"ItemId",tolua_get_ItemPrototype_unsigned_ItemId,tolua_set_ItemPrototype_unsigned_ItemId);
 tolua_variable(tolua_S,"Class",tolua_get_ItemPrototype_unsigned_Class,tolua_set_ItemPrototype_unsigned_Class);
 tolua_variable(tolua_S,"SubClass",tolua_get_ItemPrototype_unsigned_SubClass,tolua_set_ItemPrototype_unsigned_SubClass);
 tolua_variable(tolua_S,"Name1",tolua_get_ItemPrototype_Name1,tolua_set_ItemPrototype_Name1);
 tolua_variable(tolua_S,"Name2",tolua_get_ItemPrototype_Name2,tolua_set_ItemPrototype_Name2);
 tolua_variable(tolua_S,"Name3",tolua_get_ItemPrototype_Name3,tolua_set_ItemPrototype_Name3);
 tolua_variable(tolua_S,"Name4",tolua_get_ItemPrototype_Name4,tolua_set_ItemPrototype_Name4);
 tolua_variable(tolua_S,"DisplayId",tolua_get_ItemPrototype_unsigned_DisplayId,tolua_set_ItemPrototype_unsigned_DisplayId);
 tolua_variable(tolua_S,"Quality",tolua_get_ItemPrototype_unsigned_Quality,tolua_set_ItemPrototype_unsigned_Quality);
 tolua_variable(tolua_S,"Flags",tolua_get_ItemPrototype_unsigned_Flags,tolua_set_ItemPrototype_unsigned_Flags);
 tolua_variable(tolua_S,"BuyPrice",tolua_get_ItemPrototype_unsigned_BuyPrice,tolua_set_ItemPrototype_unsigned_BuyPrice);
 tolua_variable(tolua_S,"SellPrice",tolua_get_ItemPrototype_unsigned_SellPrice,tolua_set_ItemPrototype_unsigned_SellPrice);
 tolua_variable(tolua_S,"InventoryType",tolua_get_ItemPrototype_unsigned_InventoryType,tolua_set_ItemPrototype_unsigned_InventoryType);
 tolua_variable(tolua_S,"AllowableClass",tolua_get_ItemPrototype_unsigned_AllowableClass,tolua_set_ItemPrototype_unsigned_AllowableClass);
 tolua_variable(tolua_S,"AllowableRace",tolua_get_ItemPrototype_unsigned_AllowableRace,tolua_set_ItemPrototype_unsigned_AllowableRace);
 tolua_variable(tolua_S,"ItemLevel",tolua_get_ItemPrototype_unsigned_ItemLevel,tolua_set_ItemPrototype_unsigned_ItemLevel);
 tolua_variable(tolua_S,"RequiredLevel",tolua_get_ItemPrototype_unsigned_RequiredLevel,tolua_set_ItemPrototype_unsigned_RequiredLevel);
 tolua_variable(tolua_S,"RequiredSkill",tolua_get_ItemPrototype_unsigned_RequiredSkill,tolua_set_ItemPrototype_unsigned_RequiredSkill);
 tolua_variable(tolua_S,"RequiredSkillRank",tolua_get_ItemPrototype_unsigned_RequiredSkillRank,tolua_set_ItemPrototype_unsigned_RequiredSkillRank);
 tolua_variable(tolua_S,"Field20",tolua_get_ItemPrototype_unsigned_Field20,tolua_set_ItemPrototype_unsigned_Field20);
 tolua_variable(tolua_S,"Field21",tolua_get_ItemPrototype_unsigned_Field21,tolua_set_ItemPrototype_unsigned_Field21);
 tolua_variable(tolua_S,"Field22",tolua_get_ItemPrototype_unsigned_Field22,tolua_set_ItemPrototype_unsigned_Field22);
 tolua_variable(tolua_S,"Field23",tolua_get_ItemPrototype_unsigned_Field23,tolua_set_ItemPrototype_unsigned_Field23);
 tolua_variable(tolua_S,"MaxCount",tolua_get_ItemPrototype_unsigned_MaxCount,tolua_set_ItemPrototype_unsigned_MaxCount);
 tolua_variable(tolua_S,"Field25",tolua_get_ItemPrototype_unsigned_Field25,tolua_set_ItemPrototype_unsigned_Field25);
 tolua_variable(tolua_S,"Armor",tolua_get_ItemPrototype_unsigned_Armor,tolua_set_ItemPrototype_unsigned_Armor);
 tolua_variable(tolua_S,"Field62",tolua_get_ItemPrototype_unsigned_Field62,tolua_set_ItemPrototype_unsigned_Field62);
 tolua_variable(tolua_S,"FireRes",tolua_get_ItemPrototype_unsigned_FireRes,tolua_set_ItemPrototype_unsigned_FireRes);
 tolua_variable(tolua_S,"NatureRes",tolua_get_ItemPrototype_unsigned_NatureRes,tolua_set_ItemPrototype_unsigned_NatureRes);
 tolua_variable(tolua_S,"FrostRes",tolua_get_ItemPrototype_unsigned_FrostRes,tolua_set_ItemPrototype_unsigned_FrostRes);
 tolua_variable(tolua_S,"ShadowRes",tolua_get_ItemPrototype_unsigned_ShadowRes,tolua_set_ItemPrototype_unsigned_ShadowRes);
 tolua_variable(tolua_S,"ArcaneRes",tolua_get_ItemPrototype_unsigned_ArcaneRes,tolua_set_ItemPrototype_unsigned_ArcaneRes);
 tolua_variable(tolua_S,"Delay",tolua_get_ItemPrototype_unsigned_Delay,tolua_set_ItemPrototype_unsigned_Delay);
 tolua_variable(tolua_S,"Field69",tolua_get_ItemPrototype_unsigned_Field69,tolua_set_ItemPrototype_unsigned_Field69);
 tolua_variable(tolua_S,"Bonding",tolua_get_ItemPrototype_unsigned_Bonding,tolua_set_ItemPrototype_unsigned_Bonding);
 tolua_variable(tolua_S,"Description",tolua_get_ItemPrototype_Description,tolua_set_ItemPrototype_Description);
 tolua_variable(tolua_S,"Field102",tolua_get_ItemPrototype_unsigned_Field102,tolua_set_ItemPrototype_unsigned_Field102);
 tolua_variable(tolua_S,"Field103",tolua_get_ItemPrototype_unsigned_Field103,tolua_set_ItemPrototype_unsigned_Field103);
 tolua_variable(tolua_S,"Field104",tolua_get_ItemPrototype_unsigned_Field104,tolua_set_ItemPrototype_unsigned_Field104);
 tolua_variable(tolua_S,"Field105",tolua_get_ItemPrototype_unsigned_Field105,tolua_set_ItemPrototype_unsigned_Field105);
 tolua_variable(tolua_S,"Field106",tolua_get_ItemPrototype_unsigned_Field106,tolua_set_ItemPrototype_unsigned_Field106);
 tolua_variable(tolua_S,"Field107",tolua_get_ItemPrototype_unsigned_Field107,tolua_set_ItemPrototype_unsigned_Field107);
 tolua_variable(tolua_S,"Field108",tolua_get_ItemPrototype_unsigned_Field108,tolua_set_ItemPrototype_unsigned_Field108);
 tolua_variable(tolua_S,"Field109",tolua_get_ItemPrototype_unsigned_Field109,tolua_set_ItemPrototype_unsigned_Field109);
 tolua_variable(tolua_S,"Field110",tolua_get_ItemPrototype_unsigned_Field110,tolua_set_ItemPrototype_unsigned_Field110);
 tolua_variable(tolua_S,"Field111",tolua_get_ItemPrototype_unsigned_Field111,tolua_set_ItemPrototype_unsigned_Field111);
 tolua_variable(tolua_S,"MaxDurability",tolua_get_ItemPrototype_unsigned_MaxDurability,tolua_set_ItemPrototype_unsigned_MaxDurability);
 tolua_function(tolua_S,"delete",tolua_worldserver_ItemPrototype_delete00);
 tolua_endmodule(tolua_S);
#ifdef __cplusplus
 tolua_cclass(tolua_S,"Unit","Unit","",tolua_collect_Unit);
#else
 tolua_cclass(tolua_S,"Unit","Unit","",NULL);
#endif
 tolua_beginmodule(tolua_S,"Unit");
 tolua_endmodule(tolua_S);
#ifdef __cplusplus
 tolua_cclass(tolua_S,"Item","Item","Object",tolua_collect_Item);
#else
 tolua_cclass(tolua_S,"Item","Item","Object",NULL);
#endif
 tolua_beginmodule(tolua_S,"Item");
 tolua_variable(tolua_S,"Owner",tolua_get_Item_Owner_ptr,tolua_set_Item_Owner_ptr);
 tolua_function(tolua_S,"new",tolua_worldserver_Item_new00);
 tolua_function(tolua_S,"new_local",tolua_worldserver_Item_new00_local);
 tolua_set_call_event(tolua_S,tolua_worldserver_Item_new00_local, "Item");
 tolua_function(tolua_S,"Create",tolua_worldserver_Item_Create00);
 tolua_function(tolua_S,"Create",tolua_worldserver_Item_Create01);
 tolua_function(tolua_S,"GetProto",tolua_worldserver_Item_GetProto00);
 tolua_function(tolua_S,"FindProto",tolua_worldserver_Item_FindProto00);
 tolua_function(tolua_S,"SaveToDB",tolua_worldserver_Item_SaveToDB00);
 tolua_function(tolua_S,"LoadFromDB",tolua_worldserver_Item_LoadFromDB00);
 tolua_function(tolua_S,"DeleteFromDB",tolua_worldserver_Item_DeleteFromDB00);
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"Server","Server","Client",NULL);
 tolua_beginmodule(tolua_S,"Server");
 tolua_variable(tolua_S,"Tick",tolua_get_Server_unsigned_Tick,tolua_set_Server_unsigned_Tick);
 tolua_variable(tolua_S,"Logger",tolua_get_Server_Logger_ptr,tolua_set_Server_Logger_ptr);
 tolua_function(tolua_S,"Start",tolua_worldserver_Server_Start00);
 tolua_function(tolua_S,"Stop",tolua_worldserver_Server_Stop00);
 tolua_function(tolua_S,"IsRunning",tolua_worldserver_Server_IsRunning00);
 tolua_function(tolua_S,"AddClient",tolua_worldserver_Server_AddClient00);
 tolua_function(tolua_S,"SocketEvent",tolua_worldserver_Server_SocketEvent00);
 tolua_function(tolua_S,"SetLogger",tolua_worldserver_Server_SetLogger00);
 tolua_endmodule(tolua_S);
 tolua_constant(tolua_S,"GF_PLAYER_AUTOATTACK",GF_PLAYER_AUTOATTACK);
 tolua_cclass(tolua_S,"Database","Database","",NULL);
 tolua_beginmodule(tolua_S,"Database");
 tolua_endmodule(tolua_S);
#ifdef __cplusplus
 tolua_cclass(tolua_S,"GameClient","GameClient","",tolua_collect_GameClient);
#else
 tolua_cclass(tolua_S,"GameClient","GameClient","",NULL);
#endif
 tolua_beginmodule(tolua_S,"GameClient");
 tolua_endmodule(tolua_S);
#ifdef __cplusplus
 tolua_cclass(tolua_S,"WorldServer","WorldServer","Server",tolua_collect_WorldServer);
#else
 tolua_cclass(tolua_S,"WorldServer","WorldServer","Server",NULL);
#endif
 tolua_beginmodule(tolua_S,"WorldServer");
 tolua_variable(tolua_S,"db",tolua_get_WorldServer_db_ptr,tolua_set_WorldServer_db_ptr);
 tolua_variable(tolua_S,"rdb",tolua_get_WorldServer_rdb_ptr,tolua_set_WorldServer_rdb_ptr);
 tolua_variable(tolua_S,"GameFeatures",tolua_get_WorldServer_unsigned_GameFeatures,tolua_set_WorldServer_unsigned_GameFeatures);
 tolua_function(tolua_S,"new",tolua_worldserver_WorldServer_new00);
 tolua_function(tolua_S,"new_local",tolua_worldserver_WorldServer_new00_local);
 tolua_set_call_event(tolua_S,tolua_worldserver_WorldServer_new00_local, "WorldServer");
 tolua_function(tolua_S,"UpdateRealm",tolua_worldserver_WorldServer_UpdateRealm00);
 tolua_function(tolua_S,"SocketEvent",tolua_worldserver_WorldServer_SocketEvent00);
 tolua_function(tolua_S,"Start",tolua_worldserver_WorldServer_Start00);
 tolua_function(tolua_S,"Stop",tolua_worldserver_WorldServer_Stop00);
 tolua_function(tolua_S,"Update",tolua_worldserver_WorldServer_Update00);
 tolua_function(tolua_S,"SetDatabase",tolua_worldserver_WorldServer_SetDatabase00);
 tolua_function(tolua_S,"GetRealmName",tolua_worldserver_WorldServer_GetRealmName00);
 tolua_function(tolua_S,"SetRealmName",tolua_worldserver_WorldServer_SetRealmName00);
 tolua_function(tolua_S,"GetGameTime",tolua_worldserver_WorldServer_GetGameTime00);
 tolua_function(tolua_S,"GetClientLimit",tolua_worldserver_WorldServer_GetClientLimit00);
 tolua_function(tolua_S,"SetClientLimit",tolua_worldserver_WorldServer_SetClientLimit00);
 tolua_function(tolua_S,"GetStartZone",tolua_worldserver_WorldServer_GetStartZone00);
 tolua_function(tolua_S,"SetStartZone",tolua_worldserver_WorldServer_SetStartZone00);
 tolua_function(tolua_S,"GetCinematics",tolua_worldserver_WorldServer_GetCinematics00);
 tolua_function(tolua_S,"SetCinematics",tolua_worldserver_WorldServer_SetCinematics00);
 tolua_function(tolua_S,"SetMotd",tolua_worldserver_WorldServer_SetMotd00);
 tolua_function(tolua_S,"GetMotd",tolua_worldserver_WorldServer_GetMotd00);
 tolua_function(tolua_S,"GetClientsConnected",tolua_worldserver_WorldServer_GetClientsConnected00);
 tolua_function(tolua_S,"SendGlobalPacket",tolua_worldserver_WorldServer_SendGlobalPacket00);
 tolua_function(tolua_S,"SendGlobalMessage",tolua_worldserver_WorldServer_SendGlobalMessage00);
 tolua_function(tolua_S,"GenerateGUID",tolua_worldserver_WorldServer_GenerateGUID00);
 tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}
