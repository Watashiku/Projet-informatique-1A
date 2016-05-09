#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

int main()
{
    DB database=creation("graphe1.csv");
    lectureDB(database);
    return 0;
}
