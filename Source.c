// math constants
#define _USE_MATH_DEFINES

// for Visual C++
#define _CRT_SECURE_NO_DEPRECATE

// arena
#define ARENA_W 120 // without border
#define ARENA_H 24 // without border

// symbols
#define P_MONSTER '+'
#define P_HUNTER 'H'

// macros for clearing console window and sleeping
#ifdef _WIN32
#include <windows.h>
#define CLEAR_SCREEN() system("cls")
#define SLEEP(sleepMs) Sleep(sleepMs)
#else
#include <unistd.h>
#define CLEAR_SCREEN() system("clear")
#define SLEEP(sleepMs) usleep(sleepMs * 1000)
#endif

// headers
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// function declarations
void print_arena(float x_H, float y_H, float x_M, float y_M, int a_H, int a_M);

void print_arena(float x_H, float y_H, float x_M, float y_M, int a_H, int a_M)
{
	CLEAR_SCREEN(); // clearing screen

	// inverting Y-axis for both hunter and monster
	y_H = ARENA_H - 1 - y_H;
	y_M = ARENA_H - 1 - y_M;

	int i, j, first_x, second_x;
	char first, second;
	for (i = 0; i < ARENA_H; i++)
	{
		// row contains both hunter and monster
		if (i == y_H && i == y_M)
		{
			// hunter is closer to the left side
			if (x_H < x_M)
			{
				first = P_HUNTER;
				second = P_MONSTER;
				first_x = x_H;
				second_x = x_M;
			}
			// monster is closer to the left side
			else
			{
				first = P_MONSTER;
				second = P_HUNTER;
				first_x = x_M;
				second_x = x_H;
			}

			if (first_x < 0 && (second_x >= 0 && second_x < ARENA_W))
			{
				// printing spaces
				for (j = 0; j < second_x; j++)
				{
					printf(" ");
				}
				// printing second character
				printf("%c", second);
			}


			if ((first_x >= 0 && first_x < ARENA_W) && (second_x >= 0 && second_x < ARENA_W))
			{
				// printing spaces
				for (j = 0; j < first_x; j++)
				{
					printf(" ");
				}
				// printing first character
				printf("%c", first);
				// printing spaces
				for (j = 0; j < abs(second_x - first_x) - 1; j++)
				{
					printf(" ");
				}
				// printing second character
				printf("%c", second);

			}

			if ((first_x >= 0 && first_x < ARENA_W) && second_x >= ARENA_W)
			{
				// printing spaces
				for (j = 0; j < first_x; j++)
				{
					printf(" ");
				}
				// printing first character
				printf("%c", first);
			}

		}
		// row contains only hunter
		else if (i == y_H)
		{
			if (x_H < ARENA_W && x_H >= 0)
			{
				// printing spaces
				for (j = 0; j < x_H; j++)
				{
					printf(" ");
				}
				// printing the hunter
				printf("%c", P_HUNTER);
			}
		}
		// row contains only monster
		else if (i == y_M)
		{
			if (x_M < ARENA_W && x_M >= 0)
			{
				// printing spaces
				for (j = 0; j < x_M; j++)
				{
					printf(" ");
				}
				// printing the monster
				printf("%c", P_MONSTER);
			}
		}
		printf("\n");
	}
	printf("________________________________________________________________________________________________________________________\n");
	printf("(%c) Hunter: (%.2f, %.2f, %ddgr)\n", P_HUNTER, x_H, y_H, a_H);
	printf("(%c) Monster: (%.2f, %.2f, %ddgr)\n", P_MONSTER, x_M, y_M, a_M);

}

float distance(float x_H, float y_H, float x_M, float y_M) {
	float dist;
	dist = sqrt((x_M - x_H)*(x_M - x_H) + (y_M - y_H)*(y_M - y_H));
	return dist;
}
int get_newX(float old_X, int angle, int move) {
	float newX;
	newX = old_X + move * cos(angle);
	if (newX > ARENA_W)
		newX = newX - ARENA_W;
	if (newX < 0)
		newX = newX + ARENA_W;
	return newX;
}
int get_newY(float old_Y, int angle, int move) {
	float newY;
	newY = old_Y + move * sin(angle);
	if (newY > ARENA_H)
		newY = newY - ARENA_H;
	if (newY < 0)
		newY = newY + ARENA_H;
	return newY;
}
int key_alpha(int angle, char t) {
	int alpha;

	if (t == 'a')
		alpha = angle + 30;
	if (t == 'w')
		alpha = angle;
	if (t == 'd')
		alpha = angle - 30;
	if (alpha < 0)
		alpha = alpha + 360;
	if (alpha > 360)
		alpha = alpha - 360;
	return alpha;
}


int main() {

	float x_H, y_H;
	float x_M, y_M;
	int x, a_H, a_M;
	char t;
	int moves = 0;


	srand(time(NULL));
	x_H = rand() % ARENA_W;
	y_H = rand() % ARENA_H;
	x_M = rand() % ARENA_W;
	y_M = rand() % ARENA_H;
	a_H = rand() % 361;
	a_M = rand() % 361;
	print_arena(x_H, y_H, x_M, y_M, a_H, a_M);


	while (distance(x_H, y_H, x_M, y_M) > 3) {

		printf("Distance: %.2f		Target:3\n", distance(x_H, y_H, x_M, y_M));
		scanf("%c", &t);
		while (t !='a' && t != 'w' && t != 'd')
			scanf("%c", &t);
		getchar();

		a_M = rand() % 360 + 1;
		a_H = key_alpha(a_H, t);

		x_H = get_newX(x_H, a_H, 5);
		y_H = get_newY(y_H, a_H, 5);
		x_M = get_newX(x_M, a_M, 2);
		y_M = get_newY(y_M, a_M, 2);

		print_arena(x_H, y_H, x_M, y_M, a_H, a_M);
		moves++;
	}
	printf("Distance: %.2f Congratulations, you catched The Monster (%d moves)", distance(x_H, y_H, x_M, y_M),moves);
	getchar();getchar();
}