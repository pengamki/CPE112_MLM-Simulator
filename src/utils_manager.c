#include "mlmsim.h"

int hash(int agent_id)
{
    return (agent_id % AGENTS_LIMIT);
}

t_Agent* create_agent(int agent_id, float commission_rate)
{
    t_Agent* new_agent;

    new_agent = (t_Agent *) malloc(sizeof(t_Agent));
    new_agent->agent_id = agent_id;
    new_agent->upline_id = 0;
    new_agent->self_commission_rate = commission_rate;
    new_agent->personal_sales = 0.0;
    new_agent->commission_earning = 0.0;
    new_agent->downlines_count = 0;
    new_agent->upline = NULL;
    return (new_agent);
}

t_Agent* find_agent(t_AgentHashTable *agent_table[], int agent_id)
{
    int index;
    t_AgentHashTable *current;
    
    // Return : found - t_Agent*, not found - NULL
    index = hash(agent_id);
    current = agent_table[index];
    while (current)
    {
        if (current->agent_id == agent_id)
            return (current->agent_node);
        current = current->next;
    }
    return (NULL);
}

bool validate_agent_id(t_AgentHashTable *agent_table[], int agent_id)
{
    t_Agent *agent;

    agent = find_agent(agent_table, agent_id);
    if (!agent)
    {
        printf("There's no agent with this id\n");
        return (false);
    }
    return (true);
}

// For tree viewing
char *level_color(int level)
{
    if (level % 4 == 0)
        return (BLUE);
    else if (level % 4 == 1)
        return (GREEN);
    else if (level % 4 == 2)
        return (RED);
    else if (level % 4 == 3)
        return (YELLOW);
    return (NOCOLOR);
}