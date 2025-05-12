#include "mlmsim.h"

void client_payment(t_AgentHashTable *agent_table[], int agent_id, float pay_amount)
{
    t_Agent *agent;
    float agent_commission;
    float upline_commission;
    float commission_rate;
    t_Agent *upline_ptr;
    int upline_level;

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

void client_payment_page(t_AgentHashTable *agent_table[])
{
    int agent_id;
    float pay_amount;
    bool valid_scan;

    // Input : agent_id
    printf("Enter agent id to pay: ");
    valid_scan = scanf("%d", &agent_id);
    while(getchar() != '\n');
    if (!valid_scan)
    {
        printf("Numeric answer required, please try again.\n");
        return;
    }
    // Validate : agent_id
    if (!validate_agent_id(agent_table, agent_id))
        return ;
    // Input : pay_amount
    printf("Enter pay amount: ");
    valid_scan = scanf("%f", &pay_amount);
    while(getchar() != '\n');
    if (!valid_scan)
    {
        printf("Numeric answer required, please try again.");
        return;
    }
    // Validate : pay_amount
    if (pay_amount <= 0.0)
    {
        printf("Invalid amount, please try again\n");
        return ;
    }
    // Update agent's personal_sales and commission_earning
    client_payment(agent_table, agent_id, pay_amount);
}