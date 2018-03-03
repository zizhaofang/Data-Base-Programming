#include "query_funcs.h"


void add_player(connection *C, int team_id, int jersey_num, string first_name, string last_name,
                int mpg, int ppg, int rpg, int apg, double spg, double bpg)
{
    string sql = "INSERT INTO PLAYER ( TEAM_ID, UNIFORM_NUM, FIRST_NAME, LAST_NAME, MPG, PPG, RPG, APG, SPG, BPG) ";
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
    vec.push_back(to_string( spg ).substr(0,3));
    vec.push_back(to_string( spg ).substr(0,3));
    sql += 
      "VALUES ( " + "DEFAULT" + "," + player[i][1] + "," + player[i][2] + ",'" + player[i][3] + "','" + player[i][4] + "'," + player[i][5] + "," 
      + player[i][6] + "," + player[i][7] + "," + player[i][8] + "," + player[i][9] +","+ player[i][10]  +");";
    work* W = new work(*C);
    W->exec(temp);
    W->commit();
}


void add_team(connection *C, string name, int state_id, int color_id, int wins, int losses)
{
}


void add_state(connection *C, string name)
{
}


void add_color(connection *C, string name)
{
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
