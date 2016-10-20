#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

struct vertex{
	int x;
	int y;
};

struct Frontier{
	struct vertex v;
	struct Frontier* link;
};

bool** create_2d(int size);
//int* create_1d(int size);
void initialize(bool*** maze, int size);
void create_maze(bool*** maze, int maze_size);
struct vertex* create_vertices(int size);
struct Frontier* create_frontier(struct vertex a);
void push(struct Frontier** HEAD, struct vertex v);
void pop(struct Frontier** HEAD);
bool isEmpty(struct Frontier** HEAD);
struct vertex top(struct Frontier** HEAD);
bool* create_bool(int size);

int main(){
	srand(time(NULL));
	int maze_size;
	bool** maze;

	printf("Enter the size of Maze : \n");
	scanf("%d", &maze_size);

	maze = create_2d(maze_size);
	initialize(&maze, maze_size);
	create_maze(&maze, maze_size);
}

bool** create_2d(int size){
	bool** temp;
	temp = (bool**) malloc(sizeof(bool*)*size);

	int i;
	for(i=0; i<size; i++)
		temp[i] = (bool*)malloc(sizeof(bool)*size);

	return temp;
}

/*int* create_1d(int size){
	int* temp;
	temp = (int*)malloc(size*sizeof(int));
	return temp;
}*/

bool* create_bool(int size){
	bool* temp;
	temp = (bool*) malloc(size*sizeof(bool));
	int i;
	for(i=0; i<size; i++)
		temp[i] = false;
	return temp;
}

void initialize(bool*** maze, int size){
	int i;
	int j;
	for(i=0; i<size; i++)
		for(j=0; j<size; j++)
			(*maze)[i][j] = false;
}

struct vertex* create_vertices(int size){
	struct vertex* temp;
	temp = (struct vertex*) malloc(size*sizeof(struct vertex));
	return temp;
}

struct Frontier* create_frontier(struct vertex a){
	struct Frontier* temp;
	temp = (struct Frontier*) malloc(sizeof(struct Frontier));
	temp -> v = a;
	return temp;
}

bool isEmpty(struct Frontier** HEAD){
	return ((*HEAD) == NULL);
}

void push(struct Frontier** HEAD, struct vertex v){
	struct Frontier* temp;
	temp = create_frontier(v);
	temp -> link = (*HEAD);
	(*HEAD) = temp;
}

void pop(struct Frontier** HEAD){
	if((*HEAD) == NULL)
		return;
	struct Frontier* temp;
	temp = (*HEAD);
	(*HEAD) = (*HEAD)->link;
	free(temp);
 }

 struct vertex top(struct Frontier** HEAD){
 	return ((*HEAD)->v);
 }

void create_maze(bool*** maze, int maze_size){
	struct Frontier* FRONTIER = NULL;
	struct vertex* IN;
	struct vertex v;
	bool* is_in_IN;

	IN = create_vertices(maze_size);
	is_in_IN = create_bool(maze_size);

	int size = sqrt(maze_size);
	int random_x = rand()%size;
	int random_y = rand()%size;
	int i, j, k, x, y;
	int choice;
	int _choice[4];
	int _random[4];
	int temp;

	IN[0].x = random_x;
	IN[0].y = random_y;
	is_in_IN[IN[0].x*(size) + IN[0].y] = true;

	if(IN[0].x<size-1){
		v.x = IN[0].x + 1;
		v.y = IN[0].y;
		push(&FRONTIER, v);
	}

	if(IN[0].y<size-1){
		v.y = IN[0].y + 1;
		v.x = IN[0].x;
		push(&FRONTIER, v);
	}

	if(IN[0].y>0){
		v.y = IN[0].y - 1;
		v.x = IN[0].x;
		push(&FRONTIER, v);
	}

	if(IN[0].x>0){
		v.x = IN[0].x - 1;
		v.y = IN[0].y;
		push(&FRONTIER, v);
	}

	for(i=0; i<4; i++)
			_choice[i] = i;
	i=1;
	while(1){
		v = top(&FRONTIER);
		IN[i] = v;
		is_in_IN[IN[i].x*(size) + IN[i].y] = true;
		x = IN[i].x*(size) + IN[i].y;
		pop(&FRONTIER);

		for(k=0; k<4; k++)
			_random[k] = -1;

		k=0;
		if(v.x<size-1)
			_random[k] = (v.x+1)*size + v.y, k++;
		if(v.y<size-1)
			_random[k] = (v.x)*size + v.y + 1, k++;
		if(v.x>0)
			_random[k] = (v.x-1)*size + v.y, k++;
		if(v.y>0)
			_random[k] = (v.x)*size + v.y - 1, k++;

		for(k=0; k<4; k++){
			j = rand()%4;
			temp = _random[k];
			_random[k] = _random[j];
			_random[j] = temp;
		}

		k=0;
		while(1){
			if(_random[0]!=-1 && is_in_IN[_random[0]]){
				(*maze)[x][_random[k]] = true;
				(*maze)[_random[k]][x] = true;
				break;
			}
			if(_random[1]!=-1 && is_in_IN[_random[1]]){
				(*maze)[x][_random[1]] = true;
				(*maze)[_random[1]][x] = true;
				break;
			}
			if(_random[2]!=-1 && is_in_IN[_random[2]]){
				(*maze)[x][_random[2]] = true;
				(*maze)[_random[2]][x] = true;
				break;
			}
			if(_random[3]!=-1 && is_in_IN[_random[3]]){
				(*maze)[x][_random[3]] = true;
				(*maze)[_random[3]][x] = true;
				break;
			}

		}

		for(k=0; k<4; k++){
			j = rand()%4;
			choice = _choice[k];
			_choice[k] = _choice[j];
			_choice[j] = choice;
		}

		for(k=0; k<4; k++){
			choice = _choice[k];
			switch(choice){
				case 0:
					if(IN[i].x<size-1){
						v.x = IN[i].x + 1;
						v.y = IN[i].y;
						if(!is_in_IN[v.x*(size) + v.y])
							push(&FRONTIER, v);
					}
					break;
				case 1:
					if(IN[i].y<size-1){
						v.y = IN[i].y + 1;
						v.x = IN[i].x;
						if(!is_in_IN[v.x*(size) + v.y])
							push(&FRONTIER, v);
					}
					break;
				case 2:
					if(IN[i].y>0){
						v.y = IN[i].y - 1;
						v.x = IN[i].x;
						if(!is_in_IN[v.x*(size) + v.y])
							push(&FRONTIER, v);
					}
					break;
				case 3:
					if(IN[i].x>0){
						v.x = IN[i].x - 1;
						v.y = IN[i].y;
						if(!is_in_IN[v.x*(size) + v.y])
							push(&FRONTIER, v);
					}
					break;
			}
		}
		if(i==maze_size-1)
			break;
		i++;
	}

	for(i=0; i<maze_size; i++){
		for(j=0; j<maze_size; j++){
			if((*maze)[i][j])
				printf("1 ");
			else
				printf("0 ");
		}
		printf("\n");
	}
	for(i=0;i<maze_size;i++){
		for(j=0;j<maze_size;j++){
			if((*maze)[i][j])
				printf("%d %d 1\n",i,j);
		}
	}
}