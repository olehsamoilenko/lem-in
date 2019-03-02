#include "lem-in.h"

void	show_node(t_node *node, t_lem *lem)
{
	if (lem->start == node)
		printf("START:");
	else if (lem->end == node)
		printf("END:");
	printf("\tname: %s,\t", node->name);
	if (node->bfs_prev == NULL)
		printf("prev: -,");
	else
		printf("prev: %s,", node->bfs_prev->name);
	printf("\tin_queue: %d,\tbfs_used: %d,\tlinks: ",
		node->bfs_in_queue, node->bfs_used);

	
	t_list_of_nodes *start = node->links;
	while (node->links)
	{
		printf("%s ", node->links->node->name);
		node->links = node->links->next;
	}
	node->links = start;
	printf("\n");
}

void	show_all_nodes(t_list_of_nodes *list, t_lem *lem)
{
	printf("ALL NODES:\n");
	t_list_of_nodes *start = list;
	while (list)
	{
		show_node(list->node, lem);
		list = list->next;
	}
	list = start;
	printf("\n");
}

void	show_path(t_list_of_nodes *path)
{
	if (path == NULL)
	{
		printf("Path is clear\n");
		return;
	}
	while (1)
	{
		printf("%s", path->node->name);
		if (path->next == NULL)
			break;
		else
			printf("->");
		path = path->next;
	}
	printf("\n");
}

void	show_all_pathes(t_list_of_pathes *list, t_lem *lem)
{
	printf("ALL PATHES (total_steps = %d):\n", total_steps(list, lem));
	t_list_of_pathes *start = list;
	while (list)
	{
		show_path(list->path);
		list = list->next;
	}
	list = start;
	printf("\n");
}