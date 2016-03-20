//A Special Judge For IOI'07 Aliens (user version)
//Author : yuscvscv

#ifndef _aliens_
#define _aliens_

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>

namespace _aliens
{
	int N, M;
	int CX, CY;
	int ask;
	int dir[13][2] =
	{
		{2, 2}, {2, 0}, {2, -2},
		{1, 1}, {1, -1},
		{0, 2}, {0, 0}, {0, -2},
		{-1, 1}, {-1, -1},
		{-2, 2}, {-2, 0}, {-2, -2}
	};

	inline long long abs(long long t)
	{
		return t > 0 ? t : -t;
	}

	inline void error(int opt)
	{
		switch(opt)
		{
			case 0:
				puts("Error 0 : Read Input Error.");
				break;
			case 1:
				puts("Error 1 : N does not satisfy the constraints.");
				break;
			case 2:
				puts("Error 2 : M is not an odd integer greater than or equal to 3.");
				break;
			case 3:
				puts("Error 3 : The crop formation does not fit in the meadow.");
				break;
			case 4:
				puts("Error 4 : The grass in cell (X0, Y0) is not flattened.");
				break;
			case 5:
				puts("Error 5 : The coordinates(X, Y) are not inside the meadow.");
				break;
			case 6:
				puts("Error 6 : You use this facility more than 300 times.");
				break;
			case 7:
				puts("Error 7 : Wrong Answer.");
				break;
			default:
				puts("Unknown Error.");
		}
		exit(0);
	}

}

void Init(int *UserN, int *UserX, int *UserY);
void Solution(int X, int Y);
bool Examine(int X, int Y);


void Init(int *UserN, int *UserX, int *UserY)
{
    freopen("test.in", "r", stdin);

	int t, n, m, cx, cy, ux, uy;
	long long int lt;

	t = scanf("%d %d", &n, &m);

	if(t != 2)
		_aliens::error(0);

	if(!(15 <= n && n <= 2000000000))
		_aliens::error(1);

	if(!(m >= 3 && m % 2 == 1))
		_aliens::error(2);

	_aliens::N = n;
	_aliens::M = m;

	t = scanf("%d %d", &ux, &uy);
	if(t != 2)
		_aliens::error(0);


	t = scanf("%d %d", &cx, &cy);
	if(t != 2)
		_aliens::error(0);

	lt = 2LL*m + m/2;
	if(!(1 <= cx-lt && cx+lt <= n && 1 <= cy-lt && cy+lt <= n))
		_aliens::error(3);

	_aliens::CX = cx;
	_aliens::CY = cy;

	_aliens::ask = 0;
	if(!Examine(ux, uy))
		_aliens::error(4);

	_aliens::ask = 0;
	*UserN = n;
	*UserX = ux;
	*UserY = uy;

	printf("Initialize.\n");
}


void Solution(int X, int Y)
{
	printf("Correct answer is (%d, %d).\n",
		_aliens::CX,
		_aliens::CY);

	printf("Your answer is (%d, %d).\n", X, Y);

	if(_aliens::CX != X ||
		_aliens::CY != Y)
		_aliens::error(7);

	exit(0);
}

bool Examine(int X, int Y)
{
	if (X < 1 || Y < 1 ||
		X > _aliens::N ||
		Y > _aliens::N)
		_aliens::error(5);

	long long tx, ty, cx, cy, m, tm;

	cx = _aliens::CX;
	cy = _aliens::CY;

	m = _aliens::M;
	tm = m/2;

	_aliens::ask += 1;
	if(_aliens::ask > 300)
		_aliens::error(6);

	for(int i=0;i<13;i++)
	{
		tx = cx + _aliens::dir[i][0] * m;
		ty = cy + _aliens::dir[i][1] * m;

		if (_aliens::abs(X - tx) <= tm &&
			_aliens::abs(Y - ty) <= tm)
			return 1;
	}
	return 0;
}

#endif

