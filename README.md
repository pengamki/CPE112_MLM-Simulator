# Sales agent Assistant [CoreDumpUseGarnier]

## Group members
1. **Team Leader + System Architect** | Peeranat Ngamkiatkajorn 67070503429
2. **Quality Assurance** | Paemika Yongwittayakul 67070503469
3. **C Developer* | Khongpop Manowanna 67070503488

## Problem Statement
Sales representative agents want to recruit other agents as their downlines. Each agentearn commision not only from their own sale but also from the sales of their downlines. Wewant to implement a tree data structure to efficiently calculate commisions at different level.Sales representative agents want to recruit other agents as their downlines. Each agentearn commision not only from their own sale but also from the sales of their downlines. Wewant to implement a tree data structure to efficiently calculate commisions at different level.Sales representative agents want to recruit other agents as their downlines. Each agentearn commision not only from their own sale but also from the sales of their downlines. Wewant to implement a tree data structure to efficiently calculate commisions at different level.

## Functionality
- Each agent has a unique ID and may have their downlines (Forming a tree).
- Each agent recieve commission from their downlines.
- Commission will divides upward through tree, with each agent passinga portion of theirsales to their upline.
- Specify commission earned from agents, compute the total earning for all agent in thesystem.

## Technology Stack
1. **Tree** - Represent a Multi Level Marketing (MLM) structure.
2. **Linked List** - Store each agent's downline dynamically, contains their AgentID, Sales, Downlines (Child nodes).
3. **Queue** - Process comission updates level by level with Breath First Search (BFS) which starts from agent who earned sales first.
