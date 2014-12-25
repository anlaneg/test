//do nfa
#include <stdio.h>

#define INPUT_MAX_SIZE 64
#define STATE_MAX_SIZE 64
#define CHANGE_MAX_RULE_SIZE 64

typedef struct nfa_change_rule
{
	int current_state;
	int input;
	int next_state;
}nfa_change_rule_t;

typedef struct nfa
{
	int32_t input[INPUT_MAX_SIZE];
	int32_t rule[CHANGE_MAX_RULE_SIZE];
	int sstate;
	int state[STATE_MAX_SIZE];
	int tstate[STATE_MAX_SIZE];
}nfa_t;

int32_t nfa_to_dfa(nfa_t* nfa,nfa_t*dfa)
{
	
}
	
	
}
