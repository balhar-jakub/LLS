#include <stdio.h>
#include <stdlib.h>

#include "random.h"
#include "types.h"

floattype randLim(int limit) {
/* return a random number between 0 and limit inclusive.
 */

    floattype divisor = RAND_MAX/(limit+1);
    floattype retval;

    do { 
        retval = rand() / divisor;
    } while (retval > limit);

    return retval;
}
