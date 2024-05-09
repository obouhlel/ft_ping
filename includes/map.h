#ifndef MAP_H
#define MAP_H

#define MAP_SIZE 10

typedef void (*Function)(void);

typedef struct s_map {
	char		*key;
	Function	func;
}	t_map;

void		map_init(t_map *map);
void		map_insert(t_map *map, char *key, Function func);

#endif