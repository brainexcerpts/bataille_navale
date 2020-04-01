#ifndef TYPE_H
#define TYPE_H

typedef enum{ MISS, TOUCH, SINK } Action;
typedef enum{ EASY, MEDIUM, HARD } Difficulty;
typedef enum{ PLAYER_START, IA_START, RAND_START } Start;
typedef enum{ SEA, BOAT, PORTE_AVION, CROISEUR, DESTROYER, VEDETTE  } TypeArea;
typedef enum{ VERTICAL, HORIZONTAL, NOLAYOUT } Layout;

typedef struct s_point
{
	unsigned int x;
	unsigned int y;
} Point;


#endif
