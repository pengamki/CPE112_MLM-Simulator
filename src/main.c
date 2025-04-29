#include "../include/mlmas.h"
#include <stdio.h>
#include <stdbool.h>

typedef struct s_Agent {
  int agent_id;
  struct s_Agent *upline;
  struct s_Agent *downlines[DOWNLINES_LIMIT];
  int downlines_count;
  float personal_sales; // Total sales
  floar commission_earning; // Earning from commission
  float personal_commission_rate; // Percentage of commission earned from sales
  float downline_commission_rate; // Percentage of commission earced from downlines
} t_Agent;

typedef struct s_HashTable {
  int agent_id;
  t_Agent *agent_node;
  bool occupied;
} t_HashTable;

void init_table(t_HashTable table)
{
  for (int i = 0; i < AGENTS_LIMIT; i++)
  {
    table[i].occupied = true;
    table[i].agent_node = NULL;
  }
}

int main(void)
{
  t_Agent *you;
  t_HashTable agents_table[AGENTS_LIMIT];
  int running = 1;
  int choice;

  init_table(agents_table);
  while (running)
  {
    printf("[Welcome]");
    printf("1. -\n");
    printf("Enter choice: ");
    scanf("%d", &choice);
    switch (choice)
    {
      case 0:
        printf("option 0 selected\n");
        printf("[Exit]");
        running = 0;
        break;
      case 1:
        printf("option 1 selected\n");
        //
        break;
      default:
        printf("invalid option");
        break;
    }
  }
}
