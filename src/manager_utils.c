#include "mlmas.h"

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

void add_downline(t_Agent *upline, t_Agent *new_agent)
{
    upline->downlines[(upline->downlines_count)++] = new_agent;
    new_agent->upline = upline;
    new_agent->upline_id = new_agent->upline->agent_id;
}

void add_agent_to_table(t_AgentHashTable *agent_table[], t_Agent *agent)
{
    int index;
    t_AgentHashTable *new_node;
    t_AgentHashTable *ptr;

    // Create t_AgenthashTable node
    index = hash(agent->agent_id);
    new_node = (t_AgentHashTable *) malloc(sizeof(t_AgentHashTable));
    new_node->agent_node = agent;
    new_node->agent_id = agent->agent_id;
    new_node->next = NULL;
    // Chain to table
    if (!agent_table[index])
        agent_table[index] = new_node;
    else
    {
        ptr = agent_table[index];
        while (ptr->next)
            ptr = ptr->next;
        ptr->next = new_node;
    }
}

void add_agent(t_AgentHashTable *agent_table[])
{
    int upline_id;
    int agent_id;
    float commission_rate;
    t_Agent *unavailable;
    t_Agent *upline;
    t_Agent *new_agent;

    // Input : upline_id
    printf("Enter recruiter id (0 if no upline): ");
    scanf("%d", &upline_id);
    // Validate : upline_id
    if (upline_id)
    {
        upline = find_agent(agent_table, upline_id);
        // is exist
        if (!upline)
        {
            printf("Recruiter wth this id not found, please try again\n");
            return ;
        }
        // is not full
        if (upline->downlines_count == DOWNLINES_LIMIT)
        {
            printf("This agent can't recruit any more person\n");
            return ;
        }
    }
    // Input : agent_id
    printf("Enter agent id: ");
    scanf("%d", &agent_id);
    // Validate : agent_id - not taken
    unavailable = find_agent(agent_table, agent_id);
    if (unavailable)
    {
        printf("Sorry, this id is unavailable, please try again\n");
        return ;
    }
    // Input : commission_rate
    printf("Enter commission rate: ");
    scanf("%f", &commission_rate);
    // Validate : commission_rate - (0 <= comminssion_rate <= 10)
    if (commission_rate < 0.0)
    {
        printf("Commission rate couldn't go below zero, please try again\n");
        return ;
    }
    if (commission_rate > 10.0)
    {
        printf("We limit our commission rate ceiling at 10 percent, please try again\n");
        return ;
    }
    // Create agent
    new_agent = create_agent(agent_id, commission_rate);
    if (upline_id != 0)
        add_downline(upline, new_agent);
    add_agent_to_table(agent_table, new_agent);
    printf("Agent %d added successfully\n", agent_id);
    return ;
}

void query_agent(t_AgentHashTable *agent_table[])
{
    int agent_id;
    t_Agent *agent;

    // Input : agent_id
    printf("Enter agent id: ");
    scanf("%d", &agent_id);
    // Validate : agent_id
    if (!validate_agent_id(agent_table, agent_id))
        return ;
    // Print agent's info
    agent = find_agent(agent_table, agent_id);
    printf("Agent id: %d\n", agent->agent_id);
    if (agent->upline)
        printf("Upline: %d\n", agent->upline->agent_id);
    else
        printf("No upline\n");
    printf("Downline amount: %d person\n", agent->downlines_count);
    printf("Downline list: ");
    if (agent->downlines_count > 0)
    {
        for (int i = 0; i < agent->downlines_count; i++)
            printf("%d ", agent->downlines[i]->agent_id);
        printf("\n");
    }
    else
        printf("None\n");
    printf("Personal sale: %.2f\n", agent->personal_sales);
    printf("Commission earned: %.2f\n", agent->commission_earning);
    printf("Current commission rate: %.1f\n", agent->self_commission_rate);
}

void agent_tree(t_AgentHashTable *agent_table[])
{
    bool has_agents;
    t_AgentHashTable *ptr;

    // Validate : has_agents
    has_agents = false;
    for (int i = 0; i < AGENTS_LIMIT; i++)
    {
        if (agent_table[i])
        {
            has_agents = true;
            break;
        }
    }
    if (!has_agents)
    {
        printf("No agent in the system\n");
        return ;
    }
    // Print agent tree
    printf("Agent tree:\n\n");
    for (int i = 0; i < AGENTS_LIMIT; i++)
    {
        ptr = agent_table[i];
        while (ptr)
        {
            if (!ptr->agent_node->upline_id)
            {
                print_tree_preorder(ptr->agent_node, 0);
                printf("\n");
            }
            ptr = ptr->next;
        }
    }
}

void print_tree_preorder(t_Agent *agent, int level)
{
    // Indentation represent parent-child relationship
    for (int i = 0; i < level - 1; i++)
        printf("|  ");
    if (level)
        printf("|--");
    // Print agent's data
    printf("Agent ID: %d {Commission rate: %.1f%%, Personal sales: %.2f, Commission earned: %.2f}\n",
        agent->agent_id, agent->self_commission_rate, agent->personal_sales, agent->commission_earning
    );
    // Pre-order traverse downlines
    for (int i = 0; i < agent->downlines_count; i++)
        print_tree_preorder(agent->downlines[i], level + 1);
}

void update_agent(t_AgentHashTable *agent_table[])
{
    int agent_id;
    float commission_rate;
    t_Agent *agent;

    // Input : agent_id
    printf("Enter agent id to edit: ");
    scanf("%d", &agent_id);
    // Validate : agent_id
    if (!validate_agent_id(agent_table, agent_id))
        return ;
    // Input : new_commission_rate
    printf("Enter new commission rate for this agent: ");
    scanf("%f", &commission_rate);
    // Validate : new_commission_rate
    if (commission_rate < 0.0)
    {
        printf("Commission rate couldn't go below zero, please try again\n");
        return ;
    }
    if (commission_rate > 10.0)
    {
        printf("We limit our commission rate ceiling at 10 percent, please try again\n");
        return ;
    }
    // Update agent's commission
    agent = find_agent(agent_table, agent_id);
    printf("Updating Agent ID: %d commission from %.1f to %.1f\n", agent->agent_id, agent->self_commission_rate, commission_rate);
    agent->self_commission_rate = commission_rate;
}

void remove_agent(t_AgentHashTable *agent_table[])
{
    int agent_id;
    t_Agent *agent;

    // Input : agent_id
    printf("Enter agent id to remove: ");
    scanf("%d", &agent_id);
    // Validate : agent_id
    if (!validate_agent_id(agent_table, agent_id))
        return ;
    // Remove agent - from tree and hash table
    agent = find_agent(agent_table, agent_id);
    remove_agent_connection(agent); // from tree - remove upline's downline & downlines' upline
    remove_agent_from_hashtable(agent_table, agent_id); // from hash table
    free(agent);
    printf("Agent %d removed successfully\n", agent_id);
}

void remove_agent_connection(t_Agent *agent)
{
    t_Agent *upline;

    // Remove upline's downline
    upline = agent->upline;
    if (upline)
    {
        // search of agent in upline's downline
        for (int i = 0; i < upline->downlines_count; i++)
        {
            if (upline->downlines[i] == agent)
            {
                // remove agent from downlines[] by shifting
                for (int j = i; j < upline->downlines_count; j++)
                    upline->downlines[j] = upline->downlines[j + 1];
                upline->downlines_count--;
                break;
            }
        }
    }
    agent->upline = NULL;
    // Remove downlines' upline
    for (int i = 0; i < agent->downlines_count; i++)
    {
        agent->downlines[i]->upline_id = 0;
        agent->downlines[i]->upline = NULL;
    }
}

void remove_agent_from_hashtable(t_AgentHashTable *agent_table[], int agent_id)
{
    int index;
    t_AgentHashTable *current;
    t_AgentHashTable *previous;

    index = hash(agent_id);
    current = agent_table[index];
    previous = NULL;
    // Find agent
    while (current)
    {
        if (current->agent_id == agent_id)
        {
            if (!previous)
                agent_table[index] = current->next;
            else
                previous->next = current->next;
            free(current);
            return ;
        }
        previous = current;
        current = current->next;
    }
}