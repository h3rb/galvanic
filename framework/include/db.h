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

#include <cstdlib>
#include <iostream>

#include "mysql_connection.h"
#include "mysql_driver.h"
#include "cppconn/driver.h"
#include "cppconn/exception.h"
#include "cppconn/resultset.h"
#include "cppconn/statement.h"

#include "settings.h"

void mysql_connector_test();

class DB {
public:
  
  DB() {
   printErrors=true;
   ip="127.0.0.1";
   port="3306";
   driver=nullptr;
   con=nullptr;
   stmt=nullptr;
   res=nullptr;
  }
  
  Zstring ip,port;
  Zstring dbname;
  Zstring username;
  Zstring password;
  
  Zint lastErrorCode;
  Zstring lastErrorMessage;
  Zbool printErrors;
  Zint errorCount;
  
  sql::Driver *driver;
  sql::Connection *con;
  sql::Statement *stmt;
  sql::ResultSet *res;
  
  bool Connect( const char *ip, const char *port, const char *dbname, const char *username, const char *password ) {
    this->ip=ip;
    this->port=port;
    this->dbname=dbname;
    this->username=username;
    this->password=password;
    return Init();
  }
  
  bool Init() {
    Zstring url="tcp://";
    url+=ip;
    url+=":";
    url+=port;
    bool result=true;
    try {
        driver = sql::mysql::get_driver_instance();
        con = driver->connect(url.c_str(), username.c_str(), password.c_str());
        con->setSchema(dbname.c_str());
    } catch ( sql::SQLException &e ) {
      Error(e);
      result=false;
    }
    return result;
  }
  
  void Syntax( const char *statement ) {
    if ( stmt ) delete stmt;
    try {
     stmt = con->createStatement();          
    } catch ( sql::SQLException &e ) {
      Error(e);
      stmt=nullptr;
    }
  }
  
  sql::ResultSet *Execute( const char *statement ) {
    Syntax(statement);
    if ( res ) delete res;
    try {      
        res = stmt->executeQuery(statement);
    } catch ( sql::SQLException &e ) {
      Error(e);
      res=nullptr;
    }
    return res;
  }
  
  sql::ResultSet *GetResults() { return res; }

  void Error(sql::SQLException &e) {
    lastErrorCode=e.getErrorCode();
    lastErrorMessage=e.what();
    if ( lastErrorCode != 0 ) errorCount++;
    if ( printErrors && lastErrorCode != 0 ) {
       cout << "#db# ERR: SQLException: " << e.what() << endl;
       cout << " (MySQL error code: " << e.getErrorCode();
       cout << ", SQLState: " << e.getSQLState() << " )" << endl;
       cout << endl;
    }
  }
  
  void Shutdown() {
    cout << "Ending MySQL Session with " << errorCount.value << " errors" << endl;
    if ( res  ) delete res;
    if ( stmt ) delete stmt;
    if ( con  ) delete con;    
  }
  
  ~DB() {
  }
  
};

extern DB db;

ONE(DBRow,{})
 Strings values;
 void Print( Strings &fields ) {
  for ( int i=0; i<fields.count; i++ ) cout << "`" << fields.Get(i) << "`=`" << values.Get(i) << "`" << endl;
 }
MANY(DBRow,DBRowHandle,DBRowHandles,"DBRow",DBRows,{})
 void Print( Strings &fields ) {
  FOREACH(DBRow,row) {
    cout << "-----------------" << endl;
    row->Print(fields);
  }
  cout << "----------------- (end)" << endl;
 }
DONE(DBRow);

class DBResults {
public:
  Zstring table,query;
  DBRows rows;
  Zbool error;
  void Reset() {
    rows.Clear();
    error=false;
    table="";
  }
  void Print( Strings &fields ) {
    cout << "Results for table: " << table.c_str() << endl;
    if ( error ) cout << "ERROR: Query: ```" << query.value << "```" << endl;
    rows.Print(fields);
  }
};

class DBModel {
public:
  Strings fields;
  Zstring table;
  void Table( const char *tablename ) {
    table=tablename;
  }
  void Field( const char *fieldname ) {
    fields.Add(fieldname);
  }
  int FieldIndex( const char *fieldname ) {
    return fields.IndexOf(fieldname);
  }
  
  Zstring id_list;
  const char *ListToWhere( Strings &ids, const char *pad="" ) {
   id_list="";
   EACH(ids.first,String,s) {
    id_list+="ID=";
    id_list+=pad;
    id_list+=s->s.c_str();
    id_list+=pad;
    if ( s->next ) id_list+=" OR ";
   }
   return id_list.c_str();
  }
  
  void List( DBResults &out, Strings &ids, int limit=0 ) {
    out.table=table;
    out.query=StatementList(ids,limit);
    if ( db.Execute(out.query.c_str()) ) {
      while ( db.res->next() ) {
        DBRow *row = new DBRow;
        for ( int i=0; i<fields.count; i++ ) row->values.Add(db.res->getString(i+1));
        out.rows.Append(row);
      }
    } else out.error=true;
  }
  
  void Get( DBResults &out, const char *id ) {
    out.table=table;
    out.query=StatementGet(id);
    if ( db.Execute(out.query.c_str()) ) {
      while ( db.res->next() ) {
        DBRow *row = new DBRow;
        for ( int i=0; i<fields.count; i++ ) row->values.Add(db.res->getString(i+1));
        out.rows.Append(row);
      }      
    } else out.error=true;
  }
  
  void Select( DBResults &out, const char *where_order_limit="" ) {
    out.table=table;
    out.query=StatementSelect(where_order_limit);
    if ( db.Execute(out.query.c_str()) ) {
      while ( db.res->next() ) {
        DBRow *row = new DBRow;
        for ( int i=0; i<fields.count; i++ ) row->values.Add(db.res->getString(i+1));
        out.rows.Append(row);
      }      
    } else out.error=true;
  }
  
  void Insert( DBResults &out, Strings &fields, Strings &values, const char *pad="'" ) {
    out.table=table;
    out.query=StatementInsert(fields,values,pad);
    if ( db.Execute(out.query.c_str()) ) {
      while ( db.res->next() ) {
        DBRow *row = new DBRow;
        for ( int i=0; i<fields.count; i++ ) row->values.Add(db.res->getString(i+1));
        out.rows.Append(row);
      }      
    } else out.error=true;
  }
  
  void Update( DBResults &out, const char *where_order_limit, Strings &fields, Strings &values, const char *pad="'" ) {
    out.table=table;
    out.query=StatementUpdate(where_order_limit,fields,values,pad);
    if ( db.Execute(out.query.c_str()) ) { // Execute may throw a false-positive 0 error code 00000 state, see https://stackoverflow.com/questions/6903383/mysql-query-executes-but-throws-exception
      while ( db.res->next() ) {
        DBRow *row = new DBRow;
        for ( int i=0; i<fields.count; i++ ) row->values.Add(db.res->getString(i+1));
        out.rows.Append(row);
      }      
    } else out.error=true;
  }
  
  void Delete( DBResults &out, const char *where_order_limit ) {
    out.table=table;
    out.query=StatementDelete(where_order_limit);
    if ( db.Execute(out.query.c_str()) ) {
      while ( db.res->next() ) {
        DBRow *row = new DBRow;
        for ( int i=0; i<fields.count; i++ ) row->values.Add(db.res->getString(i+1));
        out.rows.Append(row);
      }      
    } else out.error=true;
  }
  
  Zstring SQL;
  const char *StatementList( Strings &ids, int limit=0 ) {
    SQL="SELECT ";
    EACH(fields.first,String,field) {
      SQL+=field->s.c_str();
      if (field->next) SQL+=",";
    }
    SQL+=" FROM ";
    SQL+=table;
    if ( ids.count > 0 ) {
      SQL+=" WHERE ";
      EACH(ids.first,String,id) {
        SQL+=id->s.c_str();
        if ( id->next ) SQL+=" OR ";
      }
    }
    if ( limit != 0 ) { SQL+=" LIMIT "; SQL+=limit; }
    DEBUG_LOG( { cout << "StatementList made: " << SQL.c_str() << endl; });
    return SQL.c_str();
  }
  
  const char *StatementGet( const char *id ) {
    SQL="SELECT ";
    EACH(fields.first,String,field) {
      SQL+=field->s.c_str();
      if (field->next) SQL+=",";
    }
    SQL+=" FROM ";
    SQL+=table;
    SQL+=" WHERE ID = ";
    SQL+=" LIMIT 1";
    DEBUG_LOG( { cout << "StatementGet made: " << SQL.c_str() << endl; });
    return SQL.c_str();
  }
  
  const char *StatementSelect( const char *where_order_limit="") {
    SQL="SELECT ";
    EACH(fields.first,String,field) {
      SQL+=field->s.c_str();
      if (field->next) SQL+=",";
    }
    SQL+=" FROM ";
    SQL+=table;
    if ( strlen(where_order_limit) > 0 ) {
     SQL+=" WHERE ";
     SQL+=where_order_limit;
    }
    DEBUG_LOG( { cout << "StatementSelect made: " << SQL.c_str() << endl; });
    return SQL.c_str();
  }
  
  Zstring escapeChars,escapeCharsReplace;
  const char *EscapeChars( const char *in, const char *pad="'" ) {
   if ( strlen(pad) == 0 ) return in;
   escapeCharsReplace="\\";
   escapeCharsReplace+=pad;
   escapeChars=in;
   escapeChars(pad,escapeCharsReplace.c_str());
   return escapeChars.c_str();
  }
  
  const char *StatementUpdate( const char *where_order_limit, Strings &fields, Strings &values, const char *pad="'" ) {
   SQL="UPDATE ";
   SQL+=table;
   SQL+=" SET ";
   for ( int i=0; i<fields.count; i++ ) {
    String *field=(String *)fields.Element(i);
    String *value=(String *)values.Element(i);
    SQL+=field->s;
    SQL+=" = ";
    SQL+=pad;
    SQL+=EscapeChars(value->s.c_str(),pad);
    SQL+=pad;
    if ( field->next ) SQL+=", ";
   }
   SQL+=" WHERE ";
   SQL+=where_order_limit;
   DEBUG_LOG( { cout << "StatementUpdate made: " << SQL.c_str() << endl; });
   return SQL.c_str();
  }
  
  const char *StatementInsert( Strings &fields, Strings &values, const char *pad="'" ) {
   SQL="INSERT INTO ";
   SQL+=table;
   SQL+="(";
   EACH(fields.first,String,field) {
    SQL+=field->s.c_str();
    if ( field->next ) SQL+=",";
   }
   SQL+=") VALUES (";
   EACH(values.first,String,value) {
    SQL+=pad;
    SQL+=EscapeChars(value->s.c_str(),pad);
    SQL+=pad;
    if ( value->next ) SQL+=",";
   }
   SQL+=")";
   DEBUG_LOG( { cout << "StatementInsert made: " << SQL.c_str() << endl; });
   return SQL.c_str();   
  }
  
  const char *StatementDelete( const char *where_order_limit ) {
   SQL="DELETE FROM ";
   SQL+=table;
   SQL+=" WHERE ";
   SQL+=where_order_limit;
   DEBUG_LOG( { cout << "StatementDelete made: " << SQL.c_str() << endl; });
   return SQL.c_str();
  }
};
