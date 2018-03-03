#include <iostream>
#include <pqxx/pqxx>
#include <vector>
#include <fstream>
#include <cstdlib>
#include "exerciser.h"

using namespace std;
using namespace pqxx;


void createTableSQL(string& sql) {
  sql += "DROP TABLE IF EXISTS PLAYER;";
  sql += "DROP TABLE IF EXISTS TEAM;";
  sql += "DROP TABLE IF EXISTS STATE;";
  sql += "DROP TABLE IF EXISTS COLOR;";
  
  sql += "CREATE TABLE COLOR( "\
    "COLOR_ID INT PRIMARY KEY NOT NULL, "\
    "NAME TEXT NOT NULL);";
  
  sql += "CREATE TABLE STATE( "\
    "STATE_ID INT PRIMARY KEY NOT NULL, "\
    "NAME TEXT NOT NULL);";
  sql += "CREATE TABLE TEAM ( "\
    "TEAM_ID INT PRIMARY KEY NOT NULL, "\
    "NAME TEXT NOT NULL, "\
    "STATE_ID INT NOT NULL REFERENCES STATE(STATE_ID), "\
    "COLOR_ID INT NOT NULL REFERENCES COLOR(COLOR_ID), "\
    "WINS INT NOT NULL, "\
    "LOSSES INT NOT NULL);";
  sql += "CREATE TABLE PLAYER ( "\
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
}

void readFileToVector(vector<vector<string> >& vec, string filename) {
  ifstream ifs;
  ifs.open(filename.c_str(), ifstream::in);
  if(!ifs.good()) {
    cerr << "Cannot open file." << endl;
    exit(EXIT_FAILURE);
  }
  while(!ifs.eof() ) {
    vector<string> vec_temp;
    string buffer;
    getline(ifs, buffer);
    buffer += " ";
    int l = 0, r = 0;
    while(l < buffer.size()) {
      if(buffer[l] == ' ') {
        vec_temp.push_back(buffer.substr( r, l - r));
        r = l + 1;
      }
      l++;
    }
    vec.push_back(vec_temp);
  }
  ifs.close();
}


void output(vector<vector<string> >& vec) {
  for(int i = 0 ; i < vec.size(); i++ ) {
    for(int j = 0 ; j < vec[i].size(); j++ ) {
      cout << vec[i][j] << " ";
    }
    cout << endl;
  }
}

void insertSQL(string& sql, vector<vector<string> >& color, vector<vector<string> >& state, vector<vector<string> >& team, vector<vector<string> >& player ) {
  string ins_arr[4] = {
    "INSERT INTO COLOR (COLOR_ID, NAME) ",
    "INSERT INTO STATE (STATE_ID, NAME) ",
    "INSERT INTO TEAM (TEAM_ID, NAME, STATE_ID, COLOR_ID, WINS, LOSSES) ",
    "INSERT INTO PLAYER (PLAYER_ID, TEAM_ID, UNIFORM_NUM, FIRST_NAME, LAST_NAME, MPG, PPG, RPG, APG, SPG, BPG) "
  };
  for(int i = 0 ; i < color.size() ; i++ ) {
    string temp = ins_arr[0] +
      "VALUES ( " + color[i][0] + ", '"+ color[i][1] + "');";
    sql += temp;
  }
  for(int i = 0 ; i < state.size(); i++ ){
    string temp = ins_arr[1] + 
      "VALUES ( " + state[i][0] + ", '" + color[i][1] + "');";
  }
  for (int i = 0; i < team.size(); i++ ) {
    string temp = ins_arr[2] + 
      "VALUES ( " + team[i][0] + ",'" + team[i][1] + "', "+ team[i][2] 
      + "," + team[i][3] + "," + team[i][4] + "," + team[i][5] + ");";
  }
  for(int i = 0 ; i < player.size() ; i++ ) {
    string temp = ins_arr[3] + 
      "VALUES ( " + player[i][0] + "," + player[i][1] + "," + player[i][2] + ",'" + player[i][3] + "','" + player[i][4] + "'," + player[i][5] + "," 
      + player[i][6] + "," + player[i][7] + "," + player[i][8] + "," + player[i][9] + player[i][10] + ");";
  }
}

int main (int argc, char *argv[]) 
{

  //Allocate & initialize a Postgres connection object
  connection *C;
  work *W;
  string sql;
  vector<vector<string> > color;
  vector<vector<string> > state;
  vector<vector<string> > team;
  vector<vector<string> > player;
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
/////////////////// Create table ///////////////////////////
    createTableSQL( sql );
////////////////////////// Read file ///////////////////////////  
    readFileToVector(color, "color.txt");
    readFileToVector(state, "state.txt");
    readFileToVector(team, "team.txt");
    readFileToVector(player, "player.txt");
///////////////////////////////////////////////////////////////
    insertSQL(sql, color, state, team, player);
    /*output(color);
    output(state);
    output(team);
    output(player);
*/
    W = new work(*C);
    cerr << "new work success"<<endl;
    W->exec(sql);
    W->commit();
  } catch (const std::exception &e){
    cerr << 
    e.what() << std::endl;
    return 1;
  }
  cout << "Try to create table" <<endl;
  //TODO: create PLAYER, TEAM, STATE, and COLOR tables in the ACC_BBALL database
  //      load each table with rows from the provided source txt files


  exercise(C);


  //Close database connection
  C->disconnect();
  delete C;
  delete W;
  return 0;
}