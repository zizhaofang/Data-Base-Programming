#include "exerciser.h"

void exercise(connection *C)
{
    add_player(C, 1, 1, "NEW", "NEW", 4, 4, 4, 4, 3.33, 4.44);
    add_color(C,"NEW");
    add_state(C, "NEW");
    add_team(C, "NEW", 1, 1, 1, 1);
    cout << "q1\n" <<endl;
    query1(C, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,3,5);
    cout << "q2\n" <<endl;
    query2(C, "DarkBlue");
    cout << "q3\n" <<endl;
    query3(C, "Duke");
    cout << "q4\n" <<endl;
    query4(C, "NC", "DarkBlue");
    cout << "q5\n" <<endl;
    query5(C, 10);

}
