#include <iostream>
#include <pqxx/pqxx>

#include "exerciser.h"

using namespace std;
using namespace pqxx;


work* createTable(connection* C) {
  string sql;
  string dropT[4];
  dropT[0] = "DROP TABLE IF EXISTS PLAYER;";
  dropT[1] = "DROP TABLE IF EXISTS TEAM;";
  dropT[2] = "DROP TABLE IF EXISTS STATE;";
  dropT[3] = "DROP TABLE IF EXISTS COLOR;";

  string createT[4];
  createT[0] = "CREATE TABLE PLAYER ( "\
      "PLAYER_ID INT PRIMARY KEY NOT NULL, "\
      "TEAM_ID INT NOT NULL REFERENCES TEAM(TEAM_ID), "\
      "UNIFORM_NUM INT NOT NULL, "\
      "FIRST_NAME TEXT NOT NULL, "\
      "LAST_NAME TEXT NOT NULL, "\
      "MPG INT NOT NULL, "\
      "PPG INT NOT NULL, "\
      "RPG INT NOT NULL, "\
      "APG INT NOT NULL, "\
      "SPG NUMERIC(2,1) NOT NULL, "\
      "BPG NUMERIC(2,1) NOT NULL);";
  createT[1] = "CREATE TABLE TEAM ( "\
      "TEAM_ID INT PRIMARY KEY NOT NULL, "\
      "NAME TEXT NOT NULL, "\
      "STATE_ID INT NOT NULL REFERENCES STATE(STATE_ID), "\
      "COLOR_ID INT NOT NULL REFERENCES COLOR(COLOR_ID), "\
      "WINS INT NOT NULL, "\
      "LOSSES INT NOT NULL);";
  createT[2] = "CREATE TABLE STATE( "\
      "STATE_ID INT PRIMARY KEY NOT NULL, "\
      "NAME TEXT NOT NULL);";
  createT[3] = "CREATE TABLE COLOR( "\
      "COLOR_ID INT PRIMARY KEY NOT NULL, "\
      "NAME TEXT NOT NULL);";
  for(int i = 3; i >= 0 ; i++) {
    sql += dropT[i] + createT[i];
  }
	cerr << "try to work" << endl;
  work* W = new work(*C);
	cerr << "built work success"<<endl;
 // W->exec( sql );
//	cerr << "executed sql success" << endl;
 // W->commit();
//  cout << "Table created successfully" << endl;
  return W;
}

int main (int argc, char *argv[]) 
{

  //Allocate & initialize a Postgres connection object
  connection *C;

  try{
    //Establish a connection to the database
    //Parameters: database name, user name, user password
    C = new connection("dbname=acc_bball user=postgres password=passw0rd");
    if (C->is_open()) {
      cout << "Opened database successfully: " << C->dbname() << endl;
    } else {
      cout << "Can't open database" << endl;
      return 1;
    }
    work W(*C);
    //work* W = createTable(C);
  } catch (const std::exception &e){
    cerr << e.what() << std::endl;
    return 1;
  }
  cout << "Try to create table" <<endl;
  //TODO: create PLAYER, TEAM, STATE, and COLOR tables in the ACC_BBALL database
  //      load each table with rows from the provided source txt files
  /////////////////// Create table ///////////////////////////
  /*try{
    createTable(C);
  } catch (const std::exception &e){
    cerr << e.what() << std::endl;
    return 1;
  }*/

  exercise(C);


  //Close database connection
  C->disconnect();
  delete C;
  return 0;
}


