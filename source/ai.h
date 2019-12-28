#ifndef __AI__
#define __AI__

// AIMain: the main function of ai program
int AIMain(int role, int * p_next_xx, int * p_next_yy);

// AIMainRandom: This ai placed a stone randomly.
int AIMainRandom(int * p_next_xx, int * p_next_yy);

// AIMainStupid: This ai placed a stone near the last stone.
int AIMainStupid(int * p_next_xx, int * p_next_yy);

#endif