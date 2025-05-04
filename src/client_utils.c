#include "mlmas.h"

int easy_pow(int base, int pow)
{
    int sum;

    if (base <= 1)
        return (base);
    sum = base;
    while (pow > 1)
    {
        sum *= base;
        pow--;
    }
    return (sum);
}

void client_payment(t_AgentHashTable *agent_table[])
{
    int agent_id;
    float pay_amount;
    float agent_commission;
    float upline_commission;
    float commission_rate;
    t_Agent *agent;
    t_Agent *upline_ptr;
    int upline_level;

    // Input : agent_id
    printf("Enter agent id to pay: ");
    scanf("%d", &agent_id);
    // Validate : agent_id
    if (!validate_agent_id(agent_table, agent_id))
        return ;
    // Input : pay_amount
    printf("Enter pay amount: ");
    scanf("%f", &pay_amount);
    // Validate : pay_amount
    if (pay_amount <= 0.0)
    {
        printf("Invalid amount, please try again\n");
        return ;
    }
    // Update agent's personal_sales and commission_earning
    agent = find_agent(agent_table, agent_id);
    upline_level = 0;
    commission_rate = agent->self_commission_rate;
    agent_commission = pay_amount * commission_rate / 100;
    agent->personal_sales += pay_amount;
    agent->commission_earning += agent_commission;
    printf("Pay amount: %.2f\n", pay_amount);
    printf("Level %d -> Agent %d recieved commssion %.2f%%: %.2f\n", upline_level, agent_id, commission_rate, agent_commission);
    commission_rate /= 2;
    // Update uplines commmission_earning up to 3 level of uplines
    upline_ptr = agent->upline;
    while (upline_ptr && ++upline_level <= 3)
    {
        upline_commission = pay_amount * commission_rate / 100;
        upline_ptr->commission_earning += upline_commission;
        printf("Level %d -> Agent %d recieved commssion %.2f%%: %.2f\n", upline_level, upline_ptr->agent_id, commission_rate, upline_commission);
        commission_rate /= 2;
        upline_ptr = upline_ptr->upline;
    }
}