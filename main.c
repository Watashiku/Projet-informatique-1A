#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

int main()
{
    DB database=creation("metro.csv");
    lectureDB(database);
    cheminPlusCourt(database, 1, 100);
    return 0;
}
