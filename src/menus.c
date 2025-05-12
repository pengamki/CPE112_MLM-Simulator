#include "mlmsim.h"

void manager_menu(t_AgentHashTable *agent_table[])
{
    int choice;
    bool valid_scan;

    while(1)
    {
        printf("\n--- Manager menu ---\n");
        printf("1. Add an agent\n");
        printf("2. Edit an agent commission rate\n");
        printf("3. Remove an agent\n");
        printf("4. Query an agent\n");
        printf("5. View agent tree\n");
        printf("0. Return to main menu\n");

        printf("\nEnter your choice: ");
        valid_scan = scanf("%d", &choice);
        while(getchar() != '\n');  

        system("clear");
        if (!valid_scan)
        {
            printf("Numeric answer required, please try again.\n");
            continue;
        }
        switch (choice) {
            case 1:
                add_agent(agent_table);
                break;
            case 2:
                update_agent(agent_table);
                break;
            case 3:
                remove_agent(agent_table);
                break;
            case 4:
                query_agent(agent_table);
                break;
            case 5:
                agent_tree(agent_table);
                break;
            case 0:
                printf("Exiting manager menu.\n");
                return ;
            default:
                printf("Invalid choice, please try again.\n");
        }
    }
}

void client_menu(t_AgentHashTable *agent_table[])
{
    int choice;
    bool valid_scan;

    while(1)
    {
        printf("\n--- Client menu ---\n");
        printf("1. Make a payment\n");
        printf("0. Return to main menu\n");
        
        printf("\nEnter your choice: ");
        valid_scan = scanf("%d", &choice);
        while(getchar() != '\n');  

        system("clear");
        if (!valid_scan)
        {
            printf("Numeric answer required, please try again.\n");
            continue;
        }
        switch (choice)
        {
            case 1:
                client_payment_page(agent_table);
                break;
            case 0:
                printf("Exiting client menu.\n");
                return ;
            default:
                printf("Invalid choice, please try again.\n");
        }
    }
}

void exit_menu(t_AgentHashTable *agent_table[])
{
    int choice;
    bool valid_scan;
    
    while (1)
    {
        printf("\n--- Exit menu ---\n");
        printf("1. Exit\n");
        printf("2. Save and Exit\n");
        printf("0. Return to main menu\n");

        printf("\nEnter your choice: ");
        valid_scan = scanf("%d", &choice);
        while(getchar() != '\n');  

        system("clear");
        if (!valid_scan)
        {
            printf("Numeric answer required, please try again.\n");
            continue;
        }
        switch (choice)
        {
            case 1:
                exit_mlmsim(agent_table);
                break;
            case 2:
                save_agents_to_csv(agent_table);
                exit_mlmsim(agent_table);
                break;
            case 0:
                printf("Returning to main menu\n");
                return ;
            default:
                printf("Invalid choice, please try again.\n");
        }
    }
}

int main(void)
{
    t_AgentHashTable *agent_table[AGENTS_LIMIT] = {0};
    int choice;
    bool valid_scan;

    system("clear");
    load_agents_from_csv(agent_table);
    while (1)
    {
        printf("\n--- MLM commission calculator ---\n");
        printf("1. Manager menu: Manage agents\n");
        printf("2. Client menu: Simulate a payment\n");
        printf("0. Exit\n");

        printf("\nEnter your choice: ");
        valid_scan = scanf("%d", &choice);
        while(getchar() != '\n');  

        system("clear");
        if (!valid_scan)
        {
            printf("Numeric answer required, please try again.\n");
            continue;
        }
        switch (choice)
        {
            case 1:
                manager_menu(agent_table);
                break;
            case 2:
                client_menu(agent_table);
                break;
            case 0:
                exit_menu(agent_table);
                break;
            default:
                printf("Invalid choice, please try again.\n");
        }
    }
}