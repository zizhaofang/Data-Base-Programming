#include "exerciser.h"

void exercise(connection *C)
{
    add_player(C, 1, 1, "NEW", "NEW", 4, 4, 4, 4, 3.33, 4.44);
    add_color(C,"NEW");
    add_state(C, "NEW");
    add_team(C, "NEW", 1, 1, 1, 1);
    query1(C, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,3,5);
    query2(C, "DarkBlue");
    query3(C, "Duke");
    query4(C, "NC", "Red");
    query5(C, 10);

}
