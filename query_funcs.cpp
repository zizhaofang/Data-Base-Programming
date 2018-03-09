#include "query_funcs.h"

void unifyStringForamt(string& s) {
  for(int i = 0 ; i < s.size(); i++) {
    if(s[i] == '\'') {
      s.insert(i, 1, s[i]);
      i++;
    }
  }

}

void add_player(connection *C, int team_id, int jersey_num, string first_name, string last_name,
                int mpg, int ppg, int rpg, int apg, double spg, double bpg)
{
    string sql = "INSERT INTO PLAYER ( PLAYER_ID, TEAM_ID, UNIFORM_NUM, FIRST_NAME, LAST_NAME, MPG, PPG, RPG, APG, SPG, BPG) ";
    vector<string> vec;
    vec.push_back(""); // unify with readfile
    vec.push_back( to_string(team_id) );
    vec.push_back( to_string( jersey_num )  );
    vec.push_back( first_name);
    vec.push_back(last_name);
    vec.push_back( to_string( mpg ) ) ;
    vec.push_back(to_string( ppg ));
    vec.push_back(to_string( rpg ));
    vec.push_back(to_string( apg ));
    vec.push_back(to_string( spg ));
    vec.push_back(to_string( spg ));
    sql += "VALUES ( " + string("DEFAULT") + "," + vec[1] + "," + vec[2] + ",'" + vec[3] + "','" + vec[4] + "'," + vec[5] + "," 
      + vec[6] + "," + vec[7] + "," + vec[8] + "," + vec[9] +","+ vec[10]  +");";
    try{
      work W = work(*C);
      W.exec(sql);
      W.commit();
    }catch (const pqxx::sql_error &e) {
      std::cerr << "SQL error: " << e.what() << std::endl;
      std::cerr << "Query was: " << e.query() << std::endl;
      exit(EXIT_FAILURE);
    } catch (const std::exception &e) {
      std::cerr << "Error: " << e.what() << std::endl;
      exit(EXIT_FAILURE);
  }
}


void add_team(connection *C, string name, int state_id, int color_id, int wins, int losses)
{
  string sql = "INSERT INTO TEAM (TEAM_ID, NAME, STATE_ID, COLOR_ID, WINS, LOSSES) ";
  vector<string> vec;
  vec.push_back("");
  unifyStringForamt(name);
  vec.push_back(name);
  vec.push_back(to_string(state_id));
  vec.push_back(to_string(color_id));
  vec.push_back(to_string(wins));
  vec.push_back((to_string(losses)));
  sql = sql + "VALUES ( " + "DEFAULT" + ",'" + vec[1] + "', "+ vec[2] 
      + "," + vec[3] + "," +vec[4] + "," + vec[5] + ");";
  try{
      work W = work(*C);
      W.exec(sql);
      W.commit();
    }catch (const pqxx::sql_error &e) {
      std::cerr << "SQL error: " << e.what() << std::endl;
      std::cerr << "Query was: " << e.query() << std::endl;
      exit(EXIT_FAILURE);
    } catch (const std::exception &e) {
      std::cerr << "Error: " << e.what() << std::endl;
      exit(EXIT_FAILURE);
  }
}


void add_state(connection *C, string name)
{
  string temp = name;
  unifyStringForamt(temp);
  string sql = "INSERT INTO STATE (STATE_ID, NAME) ";
  sql += "VALUES ( DEFAULT, '" + temp + "')";
  try{
      work W = work(*C);
      W.exec(sql);
      W.commit();
    }catch (const pqxx::sql_error &e) {
      std::cerr << "SQL error: " << e.what() << std::endl;
      std::cerr << "Query was: " << e.query() << std::endl;
      exit(EXIT_FAILURE);
    } catch (const std::exception &e) {
      std::cerr << "Error: " << e.what() << std::endl;
      exit(EXIT_FAILURE);
  }
}


void add_color(connection *C, string name)
{
  string temp = name;
  unifyStringForamt(temp);
  string sql = "INSERT INTO COLOR (COLOR_ID, NAME) ";
  sql += "VALUES ( DEFAULT, '" + temp + "')";
  try{
      work W = work(*C);
      W.exec(sql);
      W.commit();
    }catch (const pqxx::sql_error &e) {
      std::cerr << "SQL error: " << e.what() << std::endl;
      std::cerr << "Query was: " << e.query() << std::endl;
      exit(EXIT_FAILURE);
    } catch (const std::exception &e) {
      std::cerr << "Error: " << e.what() << std::endl;
      exit(EXIT_FAILURE);
  }
}


void query1(connection *C,
	    int use_mpg, int min_mpg, int max_mpg,
            int use_ppg, int min_ppg, int max_ppg,
            int use_rpg, int min_rpg, int max_rpg,
            int use_apg, int min_apg, int max_apg,
            int use_spg, double min_spg, double max_spg,
            int use_bpg, double min_bpg, double max_bpg
            )
{
  string sql = "SELECT * FROM PLAYER ";
  vector<string> instr;
  if(use_mpg == 1) {
    instr.push_back(" ( MPG BETWEEN "+ to_string( min_mpg )+ " AND " + to_string( max_mpg ) + " ) ");
  }
  if(use_ppg == 1) {
    instr.push_back(" ( PPG BETWEEN "+ to_string( min_ppg )+ " AND " + to_string( max_ppg ) + " ) ");
  }
  if(use_rpg == 1) {
    instr.push_back(" ( RPG BETWEEN "+ to_string(min_rpg) + " AND " + to_string(max_rpg) + " ) ");
  }
  if(use_apg == 1) {
    instr.push_back(" ( APG BETWEEN "+ to_string( min_apg )+ " AND " + to_string( max_apg ) + " ) ");
  }
  if(use_spg == 1) {
    instr.push_back(" ( SPG BETWEEN "+ to_string( min_spg )+ " AND " + to_string( max_spg ) + " ) ");
  }
  if(use_bpg == 1) {
    instr.push_back(" ( BPG BETWEEN "+ to_string( min_bpg )+ " AND " + to_string( max_bpg ) + " ) ");
  }
  if(instr.size() >= 0) {
    sql += "WHERE ";
    for(int i = 0 ; i < instr.size() ; i++) {
      sql += instr[i];
      if(i < instr.size() - 1) 
        sql += " AND ";
    }
  }
  sql += ";"
  try{
    work W = work(*C);
    result r = W.exec(sql);
    cout << "PLAYER_ID TEAM_ID UNIFORM_NUM FIRST_NAME LAST_NAME MPG PPG RPG APG SPG BPG" << endl;
    for(auto row:r) {
      for(auto field:row) {
        cout << field.c_str() << " ";
      }
      cout << endl;
    }
  }catch (const pqxx::sql_error &e) {
    std::cerr << "SQL error: " << e.what() << std::endl;
    std::cerr << "Query was: " << e.query() << std::endl;
    exit(EXIT_FAILURE);
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
    exit(EXIT_FAILURE);
  }
  
}


void query2(connection *C, string team_color)
{
}


void query3(connection *C, string team_name)
{
}


void query4(connection *C, string team_state, string team_color)
{
}


void query5(connection *C, int num_wins)
{
}
