#ifndef MLMSIM_H
# define MLMSIM_H


# include <stdlib.h>
# include <string.h>
#include <stdio.h>
#include <stdbool.h>


# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define BLUE "\033[1;34m"
# define NOCOLOR "\033[0m"

# define DOWNLINES_LIMIT 10
# define AGENTS_LIMIT 100


// Agent Tree : Forming a mlm structure use to calculate commissions and view agent's data
typedef struct s_Agent {
    int agent_id;
    int upline_id; // T^T I got to add this after every thing is finished just to be able to load_agent_from_csv()
    struct s_Agent *upline;
    struct s_Agent *downlines[DOWNLINES_LIMIT];
    int downlines_count;
    float personal_sales;
    float commission_earning;
    float self_commission_rate;
} t_Agent;

// Agent Hash Table : Helps searching for specific agent efficiently
typedef struct s_AgentHashTable {
    int agent_id;
    struct s_Agent *agent_node;
    struct s_AgentHashTable *next;
} t_AgentHashTable;


// MENUS
void manager_menu(t_AgentHashTable *agent_table[]);
void client_menu(t_AgentHashTable *agent_table[]);
void exit_menu(t_AgentHashTable *agent_table[]);

// UTILS_SAVE-LOAD-EXIT
void save_agents_to_csv(t_AgentHashTable *agent_table[]);
void load_agents_from_csv(t_AgentHashTable *agent_table[]);
void exit_mlmsim(t_AgentHashTable *agent_table[]);

// PAGE_MANAGER
// add agent
void add_agent(t_AgentHashTable *agent_table[]);
void add_downline(t_Agent *upline, t_Agent *new_agent);
void add_agent_to_table(t_AgentHashTable *agent_table[], t_Agent *agent);
// update agent's commission
void update_agent(t_AgentHashTable *agent_table[]);
// remove agent
void remove_agent(t_AgentHashTable *agent_table[]);
void remove_agent_connection(t_Agent *agent);
void remove_agent_from_hashtable(t_AgentHashTable *agent_table[], int agent_id);
// query agent
void query_agent(t_AgentHashTable *agent_table[]);
// print agent tree
void agent_tree(t_AgentHashTable *agent_table[]);
void print_tree_preorder(t_Agent *agent, int level);

// UTILS_MANAGER
int hash(int agent_id);
t_Agent* create_agent(int agent_id, float commission_rate);
t_Agent* find_agent(t_AgentHashTable *agent_table[], int agent_id);
bool validate_agent_id(t_AgentHashTable *agent_table[], int agent_id);
char *level_color(int level);

// PAGE_CLIENT
// payment
void client_payment_page(t_AgentHashTable *agent_table[]);
void client_payment(t_AgentHashTable *agent_table[], int agent_id, float pay_amount);

// UTILS_CLIENT
int easy_pow(int base, int pow);

#endif
