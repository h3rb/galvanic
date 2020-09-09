/******************************************************************
 __     __    _     _       __    _      _   __
/ /`_  / /\  | |   \ \  /  / /\  | |\ | | | / /`
\_\_/ /_/--\ |_|__  \_\/  /_/--\ |_| \| |_| \_\_,

 Copyright (c) 2020 H. Elwood Gilliland III
 This open source framework is available under the MIT License,
 see LICENSE file accompanying this file for more information
*******************************************************************/
#pragma once

#include "zerotypes.h"
#include "settings.h"
#include "db.h"

#define DEFAULT_ORM_TABLE  "ORM"

/* ORM (Object-relational model)
 * Expects a schema like:
 * ORM.ID     INT NOT NULL AUTO INCREMENT PRIMARY KEY
 * ORM.Keys   Defines "json vectors" to update keys from Data
 * ORM.Key0-9 INT NOT NULL INDEX
 * ORM.Search (a string containing searchable fragments)
 * ORM.Meta (a JSON block containing any app-defined meta data)
 * ORM.Data (a JSON block)
 * ORM.S3 (a JSON block describing an S3 location or location list)
 * ORM.URI (a JSON block describing related URLs)
 * ORM.Children
 * ORM.Parent
 * ORM.Membership (a JSON block describing group memberships)
 * ORM.Owner
 * ORM.Rules (a JSON block describing ACL rules)
 * ORM.Created (timestamp)
 * ORM.Deleted (bool)
 * ORM.Private (bool)
 * ORM.Flags0-9 (INT, value bitvec)
 */

ONE(ORMObject,{})
 Zint id;
 json data,s3,children,parent,membership,owner,rules;
 Zint created,flags;
 Zbool deleted,privacy;
 void fromRow( DBRow *in ) {
 }
 void Name( const char *s ) { this->name=s; }
 void ChildOf( ORMObject *o ) {
 }
 void ParentOf( ORMObject *o ) {
 }
 void MemberOf( ORMObject *o ) {
 }
 void SiblingOf( ORMObject *o ) {
 }
 void AddToGroup( const char *groupname ) {
 }
 void GetSameGroups( ORMObject *o, Strings &out ) {
 }
 bool isSameGroup( ORMObject *o ) {
 }
 bool FlagValue( int bin, int flagNumber )  {
 }
 int Key( int bin ) {
 }
 void SetKeyVector( int bin, const char *vector ) {
 }
 void SetKeyValue( int bin, int value ) {
 }
 void GetKey( const char *vector ) {
 }
MANY_(ORMObject,{})
DONE(ORMObject);

ONE(ORM,{ Set(&db); tableName=DEFAULT_ORM_TABLE; })
 Zstring tableName;
 ORM(DB *db) : ListItem() { Set(db); tableName=DEFAULT_ORM_TABLE; }
 Zp<DB> db;
MANY_(ORM,{})
DONE(ORM);
