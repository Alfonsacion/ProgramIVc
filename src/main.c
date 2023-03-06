#include <stdio.h>

typedef struct{
	int x;
	int y;
} Punto;

void escalar(Punto *p, int n)
{
	p->x += n;
	(*p).y += n;

}

int main(void)
{
	Punto punto = {4, 5};
	escalar(&punto, 10);
	printf("(%i, %i)", punto.x, punto.y);

	return 0;
}
