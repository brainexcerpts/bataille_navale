#ifndef TYPE_H
#define TYPE_H

typedef enum{ MISS, TOUCH, SINK } Action;
typedef enum{ EASY, MEDIUM, HARD } Difficulty;
typedef enum{ PLAYER_START, IA_START, RAND_START } Start;
typedef enum{ SEA, PORTE_AVION, CROISEUR, DESTROYER, VEDETTE  } TypeArea;
typedef enum{ VERTICAL, HORIZONTAL, NOLAYOUT } Layout;

typedef struct s_point
{
	int x;
	int y;

} Point;


#endif
