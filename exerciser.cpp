#include "exerciser.h"

void exercise(connection *C)
{
  query1(C, 1, 35, 40,
	 1, 10, 20,
	 0, 0, 0,
	 0, 0, 0,
	 1, 1, 1.9,
	 0, 0, 0);
  query2(C,"Orange");
  query3(C,"Duke");
  query4(C,"NC","LightBlue");
  query5(C,5);

}
