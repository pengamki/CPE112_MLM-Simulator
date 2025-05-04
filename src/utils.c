#include "mlmas.h"

void exit_mlmsim(t_AgentHashTable *agent_table[])
{
    t_AgentHashTable *current;
    t_AgentHashTable *tmp;
    t_Agent *agents[AGENTS_LIMIT] = {0};
    int agent_count;

    agent_count = 0;
    for (int i = 0; i < AGENTS_LIMIT; i++)
    {
        current = agent_table[i];
        while (current)
        {
            tmp = current;
            current = current->next;
            agents[agent_count++] = tmp->agent_node;
            // Free the individual t_AgentHashTable node
            free(tmp);
        }
    }
    // Free each t_Agent node
    for (int i = 0; i < agent_count; i++)
        free(agents[i]);
    exit(0);
}

void save_agent_data(t_AgentHashTable *agent_table[])
{
    FILE *file;
    t_AgentHashTable *ptr;
    t_Agent *agent;

    system("mkdir -p ./data");
    file = fopen("./data/agents_data.csv", "w");
    if (!file)
    {
        printf("Error opening file for writing, going back\n");
        return ;
    }
    fprintf(file, "agent_id,commission_rate,personal_sales,commission_earning,upline_id\n");
    for (int i = 0; i < AGENTS_LIMIT; i++)
    {
        ptr = agent_table[i];
        while (ptr)
        {
            agent = ptr->agent_node;
            fprintf(file, "%d,%.2f,%.2f,%.2f,%d\n", agent->agent_id, agent->self_commission_rate, 
                    agent->personal_sales, agent->commission_earning, agent->upline_id);
            ptr = ptr->next;
        }
    }
    fclose(file);
    printf("Agent data saved to data/agents_data.csv\n");
}

void load_agents_from_csv(t_AgentHashTable *agent_table[])
{
    FILE *file;
    char line[256];
    int line_count;
    t_Agent *new_agent;
    int agent_id;
    int upline_id;
    float commission_rate;
    float personal_sales;
    float commission_earning;
    t_AgentHashTable *ptr;
    t_Agent *agent;
    t_Agent *upline;
    
    system("mkdir -p ./data");
    file = fopen("./data/agents_data.csv", "r");
    if (!file)
        return;
    line_count = 0;
    fgets(line, sizeof(line), file);
    // Create every agent before assign upline to prevent non-exist upline
    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%d,%f,%f,%f,%d", &agent_id, &commission_rate, 
                    &personal_sales, &commission_earning, &upline_id) != 5)
        {
            printf("Error parsing line %d\n", line_count);
            continue;
        }
        // Create the agent
        new_agent = create_agent(agent_id, commission_rate);
        new_agent->personal_sales = personal_sales;
        new_agent->commission_earning = commission_earning;
        new_agent->upline_id = upline_id;
        // Add agent to hash table
        add_agent_to_table(agent_table, new_agent);
    }
    // Assign upline
    for (int i = 0; i < AGENTS_LIMIT; i++)
    {
        ptr = agent_table[i];
        while (ptr)
        {
            agent = ptr->agent_node;
            if (agent && agent->upline_id != 0)
            {
                upline = find_agent(agent_table, agent->upline_id);
                if (upline)
                {
                    agent->upline = upline;
                    add_downline(upline, agent);
                }
            }
            ptr = ptr->next;
        }
    }
    fclose(file);
    printf("Agent data loaded from data/agents_data.csv\n");
}