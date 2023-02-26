#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include<io.h>
#include <string.h>//!!
using namespace std;
enum Color {
	Black, Blue, Green, Cyan, Red,
	Magenta, Brown, LightGray, DarkGray, LightBlue, LightGreen, LightCyan,
	LightRed, LightMagenta, Yellow, White
};

enum Direction { Up = 72, Left = 75, Right = 77, Down = 80, Enter = 13, esc = 27, Space = 32 };
HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);//�������� ���������� ��������� ����
void SetCursor(int x, int y)
{
	COORD myCoords = { x,y };
	SetConsoleCursorPosition(hStdOut, myCoords);
}
void SetColor(Color text, Color background)
{
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}
int const SizeAria = 10;//������ �������� ����
int const MaxSizeShip = 4;
double CountOfShip = ((1 + MaxSizeShip) / 2.0) * MaxSizeShip; //���������� ��������

//�������� ���� ��������� ��������
struct Ship
{
	int Size = MaxSizeShip;//������
	int Direct;//����������� 0 - �������������, 1 -�����������
	int PointX;//���������� � ��������� ����� 
	int PointY;//���������� � ��������� �����
	int Namber;//����� ������� ������ �������
	int Live;//1- �����, 0 - ����
	int CountLive;
};
// �������� ��������� ��������
void setShip(Ship& boat)
{
	boat.Size = MaxSizeShip;
	boat.Direct = 0;
	boat.PointX = 0;
	boat.PointY = 0;
	boat.Namber = 1;
	boat.Live = 2;
	boat.CountLive = 1;
}
//�������� ������� ��������
void setShip(Ship* boat, int length)
{
	int CountMax = MaxSizeShip,
		CountBoat = 1,
		n = 0;
	for (size_t i = 0; i < length; i++)
	{
		setShip(boat[i]);
		boat[i].Size = CountMax;
		boat[i].Namber = CountBoat;
		boat[i].CountLive = CountMax;
		CountBoat--;
		if (CountBoat == 0)
		{
			n++;
			CountMax = MaxSizeShip - n;
			CountBoat = n + 1;
		}
	}
}
//����� ������� ��������
void ShowMasShip(Ship* mas)
{
	cout << "Size\tNam\tDir\tPointX\tPointY\t\Live\tCountLive\n";
	for (size_t i = 0; i < CountOfShip; i++)
	{
		cout << mas[i].Size << "\t" << mas[i].Namber << "\t" << mas[i].Direct <<
			"\t" << mas[i].PointX << "\t" << mas[i].PointY << "\t"
			<< mas[i].Live << "\t" << mas[i].CountLive << "\n";
	}
}
//����������� �������
void CopyMas(int** MasSource, int** MasCopy, int row, int col)
{
	for (size_t i = 0; i < row; i++)
	{
		for (size_t j = 0; j < col; j++)
		{

			MasCopy[i][j] = MasSource[i][j];
		}
	}
}

//����� ��������
int SumShip(Ship* mas)
{
	int sum = 0;
	for (size_t i = 0; i < CountOfShip; i++)
	{
		if (mas[i].Live > 0)
			sum++;
	}
	return sum;
}
//������ ���������� 0
void setMas0(int** mas, int row, int col)
{
	for (size_t i = 0; i < row; i++)
	{
		for (size_t j = 0; j < col; j++)
		{
			mas[i][j] = 0;
		}
	}
}

//����������� ������� � ��������� ������� � ������ ��� �������
void setRandomMasShip(Ship& boat, int** masAria, int CountShip, int lenghtAria)
{
	int key = 0, key1 = 0;
	int X, Y, EndX, EndY;//���������� ��� �������� ������
	do
	{
		boat.Direct = rand() % 2;
		key = 0;
		if (boat.Direct == 0) {
			boat.PointX = rand() % (lenghtAria - boat.Size);
			boat.PointY = rand() % lenghtAria;
			X = boat.PointX;
			Y = boat.PointY;
			EndX = lenghtAria - boat.Size - 1;
			EndY = lenghtAria - 1;
		}
		else
		{
			boat.PointX = rand() % lenghtAria;
			boat.PointY = rand() % (lenghtAria - boat.Size);
			X = boat.PointX;
			Y = boat.PointY;
			EndX = lenghtAria - 1;
			EndY = lenghtAria - boat.Size - 1;
		}
		if (boat.Direct == 0) //�������� ���� ������� �������������
		{
			if (X > 0 && X < EndX && Y>0 && Y < EndY) //�������� ���� �� ������
			{
				for (size_t t = Y - 1; t < Y + 2; t++)
				{
					for (size_t j = X - 1; j < X + boat.Size + 2; j++)
					{
						if (masAria[t][j] > 0)
						{
							key++;
						}
					}
				}
			}
			else if (X == 0 && Y == 0)// �������� ���� ����� ����
			{
				for (size_t t = Y; t < Y + 2; t++)
				{
					for (size_t j = X; j < X + boat.Size + 2; j++)
					{
						if (masAria[t][j] > 0)
						{
							key++;
						}
					}
				}
			}
			else if (X == 0 && Y == EndY)// �������� ���� ����� ���
			{
				for (size_t t = Y - 1; t < Y + 1; t++)
				{
					for (size_t j = X; j < X + boat.Size + 2; j++)
					{
						if (masAria[t][j] > 0)
						{
							key++;
						}
					}
				}
			}
			else if (X == EndX && Y == 0)// �������� ���� ������ ����
			{
				for (size_t t = Y; t < Y + 2; t++)
				{
					for (size_t j = X - 1; j < X + boat.Size + 1; j++)
					{
						if (masAria[t][j] > 0)
						{
							key++;
						}
					}
				}
			}
			else if (X == EndX && Y == EndY)// �������� ���� ������ ���
			{
				for (size_t t = Y - 1; t < Y + 1; t++)
				{
					for (size_t j = X - 1; j < X + boat.Size + 1; j++)
					{
						if (masAria[t][j] > 0)
						{
							key++;
						}
					}
				}
			}
			else if (X == 0 && X < EndX && Y>0 && Y < EndY)// �������� ���� �����
			{
				for (size_t t = Y - 1; t < Y + 2; t++)
				{
					for (size_t j = X; j < X + boat.Size + 2; j++)
					{
						if (masAria[t][j] > 0)
						{
							key++;
						}
					}
				}
			}
			else if (X > 0 && X == EndX && Y > 0 && Y < EndY)// �������� ���� ������
			{
				for (size_t t = Y - 1; t < Y + 2; t++)
				{
					for (size_t j = X - 1; j < X + boat.Size + 1; j++)
					{
						if (masAria[t][j] > 0)
						{
							key++;
						}
					}
				}
			}
			else if (X > 0 && X < EndX && Y == 0 && Y < EndY) //�������� ���� ������
			{
				for (size_t t = Y; t < Y + 2; t++)
				{
					for (size_t j = X - 1; j < X + boat.Size + 2; j++)
					{
						if (masAria[t][j] > 0)
						{
							key++;
						}
					}
				}
			}
			else //�������� ���� �����
			{
				for (size_t t = Y - 1; t < Y + 1; t++)
				{
					for (size_t j = X - 1; j < X + boat.Size + 2; j++)
					{
						if (masAria[t][j] > 0)
						{
							key++;
						}
					}
				}
			}
		}
		if (boat.Direct == 1) //�������� ���� ������� �����������
		{
			if (X > 0 && X < EndX && Y>0 && Y < EndY) //�������� ���� �� ������
			{
				for (size_t t = Y - 1; t < Y + boat.Size + 2; t++)
				{
					for (size_t j = X - 1; j < X + 2; j++)
					{
						if (masAria[t][j] > 0)
						{
							key++;
						}
					}
				}
			}
			else if (X == 0 && Y == 0)// �������� ���� ����� ����
			{
				for (size_t t = Y; t < Y + boat.Size + 2; t++)
				{
					for (size_t j = X; j < X + 2; j++)
					{
						if (masAria[t][j] > 0)
						{
							key++;
						}
					}
				}
			}
			else if (X == 0 && Y == EndY)// �������� ���� ����� ���
			{
				for (size_t t = Y - 1; t < Y + boat.Size + 1; t++)
				{
					for (size_t j = X; j < X + 2; j++)
					{
						if (masAria[t][j] > 0)
						{
							key++;
						}
					}
				}
			}
			else if (X == EndX && Y == 0)// �������� ���� ������ ����
			{
				for (size_t t = Y; t < Y + boat.Size + 1; t++)
				{
					for (size_t j = X - 1; j < X + 2; j++)
					{
						if (masAria[t][j] > 0)
						{
							key++;
						}
					}
				}
			}
			else if (X == EndX && Y == EndY)// �������� ���� ������ ���
			{
				for (size_t t = Y - 1; t < Y + boat.Size + 1; t++)
				{
					for (size_t j = X - 1; j < X + 1; j++)
					{
						if (masAria[t][j] > 0)
						{
							key++;
						}
					}
				}
			}
			else if (X == 0 && X < EndX && Y>0 && Y < EndY)// �������� ���� �����
			{
				for (size_t t = Y - 1; t < Y + boat.Size + 2; t++)
				{
					for (size_t j = X; j < X + 2; j++)
					{
						if (masAria[t][j] > 0)
						{
							key++;
						}
					}
				}
			}
			else if (X > 0 && X == EndX && Y > 0 && Y < EndY)// �������� ���� ������
			{
				for (size_t t = Y - 1; t < Y + boat.Size + 2; t++)
				{
					for (size_t j = X - 1; j < X + 1; j++)
					{
						if (masAria[t][j] > 0)
						{
							key++;
						}
					}
				}
			}
			else if (X > 0 && X < EndX && Y == 0 && Y < EndY) //�������� ���� ������
			{
				for (size_t t = Y; t < Y + boat.Size + 2; t++)
				{
					for (size_t j = X - 1; j < X + 2; j++)
					{
						if (masAria[t][j] > 0)
						{
							key++;
						}
					};
				}
			}
			else //�������� ���� �����
			{
				for (size_t t = Y - 1; t < Y + boat.Size + 1; t++)
				{
					for (size_t j = X - 1; j < X + 2; j++)
					{
						if (masAria[t][j] > 0)
						{
							key++;
						}
					}
				}
			}
		}
		if (key == 0)
		{
			boat.PointX = X;
			boat.PointY = Y;
			if (boat.Direct == 0)
			{
				for (size_t h = 0; h < (boat.Size); h++)
				{
					masAria[Y][(X + h)] = boat.Size * 10 + boat.Namber;
				}
			}
			else
			{
				for (size_t h = 0; h < (boat.Size); h++)
				{
					masAria[(Y + h)][X] = boat.Size * 10 + boat.Namber;
				}
			}
		}key1++;
	} while (key > 0);
}
//����������� ��������������� �������� �� ���� � ��������� �������
void setRandomMasShip(Ship* boat, int** masAria, int CountShip, int lenghtAria)
{
	setMas0(masAria, lenghtAria, lenghtAria);
	for (size_t i = 0; i < CountShip; i++)
	{
		setRandomMasShip(boat[i], masAria, CountShip, lenghtAria);
	}
}

void ShowMas(int** mas, int row, int col)
{
	for (size_t i = 0; i < row; i++)
	{
		for (size_t j = 0; j < col; j++)
		{
			cout << mas[i][j] /*<<"\t"*/;
		}
		cout << "\n";
	}
}
//������� ��������� ���� ����
//������� ��������� �������� �������
int SquareH = 2, SquareW = 4;//������ ������� �������� ����
void SquareCursor(int x, int y, Color color)
{
	SetCursor(x, y);
	SetColor(color, color);
	for (size_t i = 0; i < SquareH; i++)
	{
		SetCursor(x, y + i);
		for (size_t i = 0; i < SquareW; i++)
		{
			cout << "*";
		}
	}
	SetColor(White, Black);
}

//������� �������� ������� ���� ���
void SetMasBattle(int** masBattle)
{
	setMas0(masBattle, SizeAria * 3 + 1, SizeAria * 6 + 2);
	for (size_t i = 0; i < SizeAria * 3 + 1; i++)
	{
		for (size_t j = 0; j < SizeAria * 6 + 2; j++)
		{
			if (i % 3 == 0 || j % 6 == 0 || j % 6 == 1)
				masBattle[i][j] = -1;
		}
	}
}
//������� ������� �������� �� �������
void CopyAriaBattle(int i, int j, int** masBattle, int num)
{
	for (size_t k = 0; k < 2; k++)
	{
		for (size_t n = 0; n < 4; n++)
		{
			masBattle[i * 3 + 1 + k][j * 6 + 2 + n] = num;
		}
	}
}
//������� ���������� ������� ���� ��� ����������� ��������
void SetMasBattle(int** masAria, int** masBattle)
{
	for (size_t i = 0; i < SizeAria; i++)
	{
		for (size_t j = 0; j < SizeAria; j++)
		{
			if (masAria[i][j] == 0)
			{
				CopyAriaBattle(i, j, masBattle, 0);
			}
			else if (masAria[i][j] > 0)
			{
				CopyAriaBattle(i, j, masBattle, masAria[i][j]);
			}
		}
	}
}
//�������� ���������� ������� ���� ��� � ����������� ��������
// � ������������ �� ������������
void SetMasBattle(int** masAria, int** masBattle, int** masCopy)
{
	for (size_t i = 0; i < SizeAria; i++)
	{
		for (size_t j = 0; j < SizeAria; j++)
		{
			if (masCopy[i][j] == 0)
			{
				CopyAriaBattle(i, j, masBattle, 0);
				if (masAria[i][j] > 10)
				{
					CopyAriaBattle(i, j, masBattle, masAria[i][j]);
				}
			}
			else if (masCopy[i][j] > 0)
			{
				CopyAriaBattle(i, j, masBattle, masCopy[i][j]);
			}
		}
	}
}
//������� ��������� ���� ����
void BattleField(int StartPointX, int StartPointY, Color fild, Color Square, int** masBattle)
{
	for (size_t i = 0; i < SizeAria * 3 + 1; i++)
	{
		SetCursor(StartPointX, StartPointY + i);
		for (size_t j = 0; j < SizeAria * 6 + 2; j++)
		{
			if (masBattle[i][j] == -1)//�������
			{
				SetColor(fild, fild);
			}
			else if (masBattle[i][j] == 0)//�� �������� ��������
			{
				SetColor(Square, Square);
			}
			else if (masBattle[i][j] == 1)//������
			{
				SetColor(LightGray, LightGray);
			}
			else if (masBattle[i][j] == 3)// ����
			{
				SetColor(Red, Red);
			}
			else if (masBattle[i][j] == 2)// �����
			{
				SetColor(Brown, Brown);
			}
			else if (masBattle[i][j] > 10)//������������� �������
			{
				SetColor(DarkGray, DarkGray);
			}
			cout << "*";
			SetColor(White, Black);
		}
	}SetColor(White, Black);
}
//�������� ��������
int CheckFire(int X, int Y, int** masCopy, int** masAria, Ship* boat)
{
	int key = 0, num = 0;
	int s, n, EndX, EndY;
	if (masCopy[Y][X] > 0 && masCopy[Y][X] < 10)//��������� � �������� �������
	{
		key = 1;
	}
	else if (masAria[Y][X] == 0)//������
	{
		masCopy[Y][X] = 1;
		key = 0;
	}

	else if (masAria[Y][X] > 10)
	{
		key = 2;//���������
		for (size_t i = 0; i < CountOfShip; i++)
		{
			s = masAria[Y][X] / 10;
			n = masAria[Y][X] % 10;
			if (boat[i].Size == masAria[Y][X] / 10 && boat[i].Namber == masAria[Y][X] % 10)//���������� ���������� �������
			{
				num = i;
			}
		}
		boat[num].CountLive--;
		if (boat[num].CountLive > 0)
		{
			boat[num].Live = 1;
			masCopy[Y][X] = 2;
		}
		else {
			boat[num].Live = 0;
			key = 3;//����
			X = boat[num].PointX;
			Y = boat[num].PointY;
			if (boat[num].Direct == 0)
			{
				EndX = SizeAria - boat[num].Size;
				EndY = SizeAria - 1;
				if (X > 0 && X < EndX && Y>0 && Y < EndY) //�������� ���� �� ������
				{
					for (size_t t = Y - 1; t < Y + 2; t++)
					{
						for (size_t j = X - 1; j < X + boat[num].Size + 1; j++)
						{
							masCopy[t][j] = 1;
						}
					}
				}
				else if (X == 0 && Y == 0)// �������� ���� ����� ����
				{
					for (size_t t = Y; t < Y + 2; t++)
					{
						for (size_t j = X; j < X + boat[num].Size + 1; j++)
						{
							masCopy[t][j] = 1;
						}
					}
				}
				else if (X == 0 && Y == EndY)// �������� ���� ����� ���
				{
					for (size_t t = Y - 1; t < Y + 1; t++)
					{
						for (size_t j = X; j < X + boat[num].Size + 2; j++)
						{
							masCopy[t][j] = 1;
						}
					}
				}
				else if (X == EndX && Y == 0)// �������� ���� ������ ����
				{
					for (size_t t = Y; t < Y + 2; t++)
					{
						for (size_t j = X - 1; j < X + boat[num].Size + 1; j++)
						{
							masCopy[t][j] = 1;
						}
					}
				}
				else if (X == EndX && Y == EndY)// �������� ���� ������ ���
				{
					for (size_t t = Y - 1; t < Y + 1; t++)
					{
						for (size_t j = X - 1; j < X + boat[num].Size + 1; j++)
						{
							masCopy[t][j] = 1;
						}
					}
				}
				else if (X == 0 && X < EndX && Y>0 && Y < EndY)// �������� ���� �����
				{
					for (size_t t = Y - 1; t < Y + 2; t++)
					{
						for (size_t j = X; j < X + boat[num].Size + 1; j++)
						{
							masCopy[t][j] = 1;
						}
					}
				}
				else if (X > 0 && X == EndX && Y > 0 && Y < EndY)// �������� ���� ������
				{
					for (size_t t = Y - 1; t < Y + 2; t++)
					{
						for (size_t j = X - 1; j < X + boat[num].Size + 1; j++)
						{
							masCopy[t][j] = 1;
						}
					}
				}
				else if (X > 0 && X < EndX && Y == 0 && Y < EndY) //�������� ���� ������
				{
					for (size_t t = Y; t < Y + 2; t++)
					{
						for (size_t j = X - 1; j < X + boat[num].Size + 1; j++)
						{
							masCopy[t][j] = 1;
						}
					}
				}
				else //�������� ���� �����
				{
					for (size_t t = Y - 1; t < Y + 1; t++)
					{
						for (size_t j = X - 1; j < X + boat[num].Size + 1; j++)
						{
							masCopy[t][j] = 1;
						}
					}
				}
				for (size_t i = 0; i < boat[num].Size; i++)
				{
					masCopy[Y][X + i] = 3;
				}
			}

			if (boat[num].Direct == 1) {
				EndX = SizeAria - 1;
				EndY = SizeAria - boat[num].Size;
				if (X > 0 && X < EndX && Y>0 && Y < EndY) //�������� ���� �� ������
				{
					for (size_t t = Y - 1; t < Y + boat[num].Size + 1; t++)
					{
						for (size_t j = X - 1; j < X + 2; j++)
						{
							masCopy[t][j] = 1;
						}
					}
				}
				else if (X == 0 && Y == 0)// �������� ���� ����� ����
				{
					for (size_t t = Y; t < Y + boat[num].Size + 1; t++)
					{
						for (size_t j = X; j < X + 2; j++)
						{
							masCopy[t][j] = 1;
						}
					}
				}
				else if (X == 0 && Y == EndY)// �������� ���� ����� ���
				{
					for (size_t t = Y - 1; t < Y + boat[num].Size; t++)
					{
						for (size_t j = X; j < X + 2; j++)
						{
							masCopy[t][j] = 1;
						}
					}
				}
				else if (X == EndX && Y == 0)// �������� ���� ������ ����
				{
					for (size_t t = Y; t < Y + boat[num].Size + 1; t++)
					{
						for (size_t j = X - 1; j < X + 2; j++)
						{
							masCopy[t][j] = 1;
						}
					}
				}
				else if (X == EndX && Y == EndY)// �������� ���� ������ ���
				{
					for (size_t t = Y - 1; t < Y + boat[num].Size; t++)
					{
						for (size_t j = X - 1; j < X + 1; j++)
						{
							masCopy[t][j] = 1;
						}
					}
				}
				else if (X == 0 && X < EndX && Y>0 && Y < EndY)// �������� ���� �����
				{
					for (size_t t = Y - 1; t < Y + boat[num].Size + 1; t++)
					{
						for (size_t j = X; j < X + 2; j++)
						{
							masCopy[t][j] = 1;
						}
					}
				}
				else if (X > 0 && X == EndX && Y > 0 && Y < EndY)// �������� ���� ������
				{
					for (size_t t = Y - 1; t < Y + boat[num].Size + 1; t++)
					{
						for (size_t j = X - 1; j < X + 1; j++)
						{
							masCopy[t][j] = 1;
						}
					}
				}
				else if (X > 0 && X < EndX && Y == 0 && Y < EndY) //�������� ���� ������
				{
					for (size_t t = Y; t < Y + boat[num].Size + 1; t++)
					{
						for (size_t j = X - 1; j < X + 2; j++)
						{
							masCopy[t][j] = 1;
						}
					}
				}
				else //�������� ���� �����
				{
					for (size_t t = Y - 1; t < Y + boat[num].Size; t++)
					{
						for (size_t j = X - 1; j < X + 2; j++)
						{
							masCopy[t][j] = 1;
						}
					}
				}
				for (size_t i = 0; i < boat[num].Size; i++)
				{
					masCopy[Y + i][X] = 3;
				}
			}
		}
	}
	return key;
}
struct Shoot
{
	int xhit;//x ����� ������� ���������
	int yhit;//� ����� ������� ���������
	int DirectHit;//0 �� ����������, 1 �������������, 2 ����������� 
	int Napravl;//���������� �������� 1 ��� -1
	int keyEnemyShoot;//����������� ��� ������� ��� ��� ���
}hit;
//�������� �������� ����������
int EnemyShut(int X, int Y, int**& masBattle, int**& masCopy, int**& masAria,
	Ship* boat, Shoot& hit)
{
	int key = 0, x = 0, y = 0;
	bool xy = true;
	SetMasBattle(masAria, masBattle, masCopy);
	BattleField(X, Y, Green, LightGreen, masBattle);
	do {
		xy = false;
		x = rand() % SizeAria;
		y = rand() % SizeAria;
		if (masCopy[y][x] == 0)
		{
			xy = true;
		}
	} while (xy == false);
	key = CheckFire(x, y, masCopy, masAria, boat);
	if (key == 2)
	{
		hit.xhit = x;
		hit.yhit = y;
		hit.keyEnemyShoot = 2;
	}
	SetMasBattle(masAria, masBattle, masCopy);
	BattleField(X, Y, Green, LightGreen, masBattle);
	return key;
}

int Hitmen(int X, int Y, int**& masBattle, int**& masCopy, int**& masAria,
	Ship* boat, Shoot& hit)
{
	int key, step;
	bool xy;
	int X1 = hit.xhit, Y1 = hit.yhit;
	do
	{
		if (hit.DirectHit == 0) {
			do {
				xy = false;
				X1 = -1 + rand() % 3 + hit.xhit;
				Y1 = -1 + rand() % 3 + hit.yhit;
				if ((X1 > -1 && X1 < SizeAria) && (Y1 > -1 && Y1 < SizeAria)) {
					if ((X1 == hit.xhit && Y1 == hit.yhit + 1) || (X1 == hit.xhit && Y1 == hit.yhit - 1)
						|| (X1 == hit.xhit + 1 && Y1 == hit.yhit) || (X1 == hit.xhit - 1 && Y1 == hit.yhit))
					{
						if (masCopy[Y1][X1] == 0)
						{
							xy = true;
							if (masAria[Y1][X1] != 0)
							{
								if (Y1 == hit.yhit)hit.DirectHit = 1;//�������������
								if (X1 == hit.xhit)hit.DirectHit = 2;//�����������
							}
						}
					}
				}
			} while (xy == false);
			key = CheckFire(X1, Y1, masCopy, masAria, boat);
			SetMasBattle(masAria, masBattle, masCopy);
			BattleField(X, Y, Green, LightGreen, masBattle);
			if (key == 2)
				hit.keyEnemyShoot = 2;
			if (key == 3)
			{
				hit.keyEnemyShoot = 0;
				hit.DirectHit = 0;
				hit.Napravl = 0;
				break;
			}
		}
		else if (hit.DirectHit == 1)
		{
			step = 0;
			do {
				xy = false;
				if (hit.Napravl == 0)
				{
					do
					{
						hit.Napravl = -1 + rand() % 3;
					} while (hit.Napravl == 0);
				}
				X1 = hit.Napravl * step + hit.xhit;
				if (X1 > -1 && X1 < SizeAria) {
					if (masCopy[Y1][X1] == 0)
					{
						xy = true;
						if (masAria[Y1][X1] == 0)
						{
							hit.Napravl *= -1;
							step = 0;
						}
						else if (masAria[Y1][X1] != 0)
						{
							step++;
						}
					}
					else if (masCopy[Y1][X1] == 1)
					{
						hit.Napravl *= -1;
						step = 0;
					}
					else step++;
				}
				else if (X1 < 0 && X1 >= SizeAria) {
					hit.Napravl *= -1;
					step = 0;
				}
			} while (xy == false);
			key = CheckFire(X1, Y1, masCopy, masAria, boat);
			SetMasBattle(masAria, masBattle, masCopy);
			BattleField(X, Y, Green, LightGreen, masBattle);
			if (key == 3)
			{
				hit.keyEnemyShoot = 0;
				hit.DirectHit = 0;
				hit.Napravl = 0;
				break;
			}
			else hit.keyEnemyShoot = 2;
		}
		else if (hit.DirectHit == 2)
		{
			step = 0;
			do {
				xy = false;
				if (hit.Napravl == 0)
				{
					do
					{
						hit.Napravl = -1 + rand() % 3;
					} while (hit.Napravl == 0);
				}
				Y1 = hit.Napravl * step + hit.yhit;
				if (Y1 > -1 && Y1 < SizeAria) {
					if (masCopy[Y1][X1] == 0)
					{
						xy = true;
						if (masAria[Y1][X1] == 0)
						{
							hit.Napravl *= -1;
							step = 0;
						}
						else if (masAria[Y1][X1] != 0)
						{
							step++;
						}
					}
					else if (masCopy[Y1][X1] == 1)
					{
						hit.Napravl *= -1;
						step = 0;
					}
					else step++;
				}
				else if (Y1 < 0 && Y1 >= SizeAria) {
					hit.Napravl *= -1;
					step = 0;
				}
			} while (xy == false);
			key = CheckFire(X1, Y1, masCopy, masAria, boat);
			SetMasBattle(masAria, masBattle, masCopy);
			BattleField(X, Y, Green, LightGreen, masBattle);
			if (key == 3)
			{
				hit.keyEnemyShoot = 0;
				hit.DirectHit = 0;
				hit.Napravl = 0;
				break;
			}
			else hit.DirectHit = 2;
		}
	} while (key != 0);
	return key;
}
const int strLogin = 15, strPass = 15;
struct User
{
	char login[strLogin];
	char pass[strPass];
	int progress = 0;
};
int memory(FILE* f, User*& mas)
{
	int length = 0;
	errno_t err = fopen_s(&f, "user.txt", "r");
	if (f != nullptr)
	{
		//����� �������� ��� ������� ���� ������ ���� ������ �� ������
		length = _filelength(_fileno(f)) / sizeof(User);
		//cout << "\nsize = " << length << "\n";
		if (length > 0)
		{
			mas = new User[length];
			for (size_t i = 0; i < length; i++)
			{
				fread(&mas[i], sizeof(User), 1, f);
			}
		}
		fclose(f);
	}
	return length;
}
void showMenu(char mas[][30], int row, int punct)
{
	for (size_t i = 0; i < row; i++)
	{
		SetCursor(60, 15 + i);
		if (i == punct)
		{
			SetColor(LightBlue, Black);
		}
		else
			SetColor(White, Black);
		cout << mas[i];
	}
	SetColor(White, Black);
}
void showMenuResult(char mas[][30], int row, int punct)
{
	for (size_t i = 0; i < row; i++)
	{
		SetCursor(60, 15 + i);
		if (i == punct)
		{
			SetColor(LightBlue, LightGray);
		}
		else
			SetColor(Black, LightGray);
		cout << mas[i];
	}
	SetColor(White, Black);
}
int ActivePunctResult(char mas[][30], int row)
{
	int number = 0, key;
	do
	{
		showMenuResult(mas, row, number);
		key = _getch();
		switch (key)
		{
		case Up:
			if (number >= 1)
				number--;
			break;
		case Down:
			if (number < row)
				number++;
			break;
		case Enter:
			return number;
			break;
		}
	} while (key != esc);
	return -1;
}
int ActivePunct(char mas[][30], int row)
{
	int number = 0, key;
	do
	{
		showMenu(mas, row, number);
		key = _getch();
		switch (key)
		{
		case Up:
			if (number >= 1)
				number--;
			break;
		case Down:
			if (number < row)
				number++;
			break;
		case Enter:
			return number;
			break;
		}
	} while (key != esc);
	return -1;
}
//������� ��������� ������ �������� ����������
void menuResult(int row, int col, int X, int Y)
{
	for (size_t i = 0; i < row; i++)
	{
		SetCursor(X, Y + i);
		for (size_t j = 0; j < col; j++)
		{
			SetColor(LightGray, LightGray);
			cout << " ";
			SetColor(White, Black);
		}cout << "\n";
	}
}
void seabattle(Color color) 
{
	SetColor(color, Black);
	cout << "     zzzzzzzzz   zzzzzzzzzzzz       zz       zzzzzzzzzz         zz       zzzzzzzzzzzz  zzzzzzzzzzzz  zzz           zzzzzzzzzzzz\n";
	cout << "   zzzzzzzzzzzz  zzzzzzzzzzzz      zzzz      zzzzzzzzzzz       zzzz      zzzzzzzzzzzz  zzzzzzzzzzzz  zzz           zzzzzzzzzzzz\n";
	cout << "   zzz      zzz  zzz              zzzzzz     zzz     zzz      zzzzzz          zz            zz       zzz           zzz\n";
	cout << "     zzz         zzz             zzz  zzz    zzz     zzz     zzz  zzz         zz            zz       zzz           zzz\n";
	cout << "       zzz       zzzzzzzzz      zzz    zzz   zzzzzzzzzz     zzz    zzz        zz            zz       zzz           zzzzzzzzzz\n";
	cout << "         zzz     zzzzzzzzz     zzz      zzz  zzzzzzzzzzz   zzz      zzz       zz            zz       zzz           zzzzzzzzzz\n";
	cout << "           zzz   zzz           zzzzzzzzzzzz  zzz      zzz  zzzzzzzzzzzz       zz            zz       zzz           zzz\n";
	cout << "   zz       zzz  zzz           zzzzzzzzzzzz  zzz      zzz  zzzzzzzzzzzz       zz            zz       zzz           zzz\n";
	cout << "   zzzzzzzzzzzz  zzzzzzzzzzzz  zzz      zzz  zzzzzzzzzzzz  zzz      zzz       zz            zz       zzzzzzzzzzzz  zzzzzzzzzzzz\n";
	cout << "    zzzzzzzzzz   zzzzzzzzzzzz  zzz      zzz  zzzzzzzzzzz   zzz      zzz       zz            zz       zzzzzzzzzzzz  zzzzzzzzzzzz\n";
	SetColor(White, Black);

};
int main()
{
	setlocale(LC_ALL, "rus");
	srand(time(NULL));
	User u;
	User temp;
	int key, size;
	bool enter = false;
	FILE* f;
	User* mas = nullptr;
	seabattle(Red);
	char menuLogin[3][30] = { "������������������" ,"����������������","�����" };
	int punktLogin = 0;
	do
	{
		punktLogin = ActivePunct(menuLogin, 3);
		if (punktLogin == 0)
		{
			system("cls");
			seabattle(Red);
			SetCursor(60, 15);
			cout << "������� Login ";
			errno_t err = fopen_s(&f, "user.txt", "r");
			gets_s(u.login, strLogin);
			if (err == 0)
			{
				enter = false;
				while (!feof(f))
				{
					fread(&temp, sizeof(User), 1, f);
					if (!_stricmp(u.login, temp.login))
					{
						system("cls");
						seabattle(Red);
						enter = true;
						SetCursor(30, 15);
						cout << "����� ������������ ��� ����������, ������� ������ ���.";
						fclose(f);
						break;
					}
				}
				if (enter == false)
				{
					fclose(f);
					err = fopen_s(&f, "user.txt", "a");
					SetCursor(60, 16);
					cout << "������: ";
					gets_s(u.pass, strPass);
					fwrite(&u, sizeof(User), 1, f);
					SetCursor(55, 17);
					cout << "�� ������� ����������������";
					fclose(f);
					Sleep(1500);
					system("cls");
					break;
				}
			}
			else
			{
				fopen_s(&f, "user.txt", "w");//������� ����
				fclose(f);
			}
			Sleep(1500);
			system("cls");
		}
		else if (punktLogin == 1)
		{
			system("cls");
			seabattle(Red);
			SetCursor(60, 15);
			cout << "������� Login:\t ";
			errno_t err = fopen_s(&f, "user.txt", "r");
			gets_s(u.login, strLogin);
			if (err == 0)
			{
				enter = false;
				while (!feof(f))
				{
					fread(&temp, sizeof(User), 1, f);
					if (_stricmp(u.login, temp.login) == 0)
					{
						enter = true;
						fclose(f);
						break;
					}
				}fclose(f);
			}
			if (enter == true)
			{
				SetCursor(60, 16);
				cout << "������� ������:\t ";
				gets_s(u.pass, strPass);
				if (_stricmp(u.pass, temp.pass) == 0)
				{
					SetCursor(60, 17);
					cout << "�� ����� ���������� ������";
					u = temp;
					SetCursor(60, 18);
					cout << "���-�� �����" << u.progress;
					Sleep(1000);
					system("cls");
					break;
				}
				else
				{
					SetCursor(60, 17);
					cout << "�� ����� �� ���������� ������!!!";
					Sleep(1000);
					system("cls");
				}
			}
			else {
				SetCursor(30, 16);
				cout << "����� ������������ �� ����������, ������� ������ ��� ��� �����������������";
				Sleep(1000);
				system("cls");
			}
		}
		else if (punktLogin == 2)
		{
			system("cls");
			break;
		}
	} while (punktLogin != -1);
	if (punktLogin == 0 || punktLogin == 1) {
		errno_t err = fopen_s(&f, "user.txt", "r");

		size = memory(f, mas);
		fclose(f);

		int contin = 0;
		do {
			Ship* boatSelf = new Ship[CountOfShip];//�������� ������ ��� ������ ����� ��������
			setShip(boatSelf, CountOfShip);//�������������� ��������� ������ ����� ��������
			Ship* boatEnemy = new Ship[CountOfShip];//�������� ������ ��� ������ ����� ��������
			setShip(boatEnemy, CountOfShip);//�������������� ��������� ������ ����� ��������

			//�������� ������ ��� ������ ����������� ����� ��������
			int** masAriaSelf = new int* [SizeAria];
			for (size_t i = 0; i < SizeAria; i++)
			{
				masAriaSelf[i] = new int[SizeAria];
			}
			//�������� ������ ��� ������� ������ �� ����� �����
			int** masAriaSelfCopy = new int* [SizeAria];
			for (size_t i = 0; i < SizeAria; i++)
			{
				masAriaSelfCopy[i] = new int[SizeAria];
			}
			setMas0(masAriaSelfCopy, SizeAria, SizeAria);
			//�������� ������ ��� ������ ����������� �������� ����������
			int** masAriaEnemy = new int* [SizeAria];//�������� ������ 
			for (size_t i = 0; i < SizeAria; i++)
			{
				masAriaEnemy[i] = new int[SizeAria];
			}
			setMas0(masAriaEnemy, SizeAria, SizeAria);
			//�������� ������ ��� ������� ������ �� ����� ����������
			int** masAriaEnemyCopy = new int* [SizeAria];
			for (size_t i = 0; i < SizeAria; i++)
			{
				masAriaEnemyCopy[i] = new int[SizeAria];
			}
			setMas0(masAriaEnemyCopy, SizeAria, SizeAria);
			//���� ����������� ��������
			seabattle(Red);
			char menuSet[2][30] = { "��������� �����������" ,"������ �����������" };
			int punktSet = 0;
			SetCursor(55, 14);
			cout << "�������� ��� ����������� ��������";
			do
			{
				punktSet = ActivePunct(menuSet, 2);
				//����������� ���� ������� � ��������� �������
				if (punktSet == 0)
				{
					setRandomMasShip(boatSelf, masAriaSelf, CountOfShip, SizeAria);
					system("cls");
					break;
				}
				else;
			} while (punktSet != -1);

			//���� ���������
			seabattle(Red);
			int difficult = 0;
			char menuDifficult[2][30] = { "�������" ,"�������" };
			int punktDifficult = 0;
			SetCursor(50, 14);
			cout << "�������� ��� ��������� ����";
			do
			{
				punktDifficult = ActivePunct(menuDifficult, 2);
				if (punktDifficult == 0)
				{
					difficult = 0;
					system("cls");
					break;
				}
				else
				{
					difficult = 1;
					system("cls");
					break;
				}
			} while (punktDifficult != -1);


			//����������� ������� ���������� � ��������� �������
			setRandomMasShip(boatEnemy, masAriaEnemy, CountOfShip, SizeAria);

			SetCursor(SizeAria * 5, 1);
			cout << "��� " << u.login << "\t���-�� �����   \t" << u.progress;
			//�������� ������ ��� ����������� ����� ��������
			int** masBattleFildSelf = new int* [SizeAria * 3 + 1];
			for (size_t i = 0; i < SizeAria * 3 + 1; i++)
			{
				masBattleFildSelf[i] = new int[SizeAria * 6 + 2];
			}
			//�������� ������ ��� ������� ������� ����
			int** masBattleFildEnemy = new int* [SizeAria * 3 + 1];
			for (size_t i = 0; i < SizeAria * 3 + 1; i++)
			{
				masBattleFildEnemy[i] = new int[SizeAria * 6 + 2];
			}
			int* masEnemyHit = new int[5];
			int FirstPointEnemyX = 1, FirstPointEnemyY = 5;
			int FirstpointSelfX = SizeAria * 7, FirstpointSelfY = 5;
			SetMasBattle(masBattleFildSelf);
			SetMasBattle(masBattleFildEnemy);
			SetMasBattle(masAriaSelfCopy, masBattleFildSelf);
			SetMasBattle(masAriaEnemyCopy, masBattleFildEnemy);
			int click; //���������� ������� ������ �� ����������
			//��������� ��������� ����� 
			SetMasBattle(masAriaEnemyCopy, masBattleFildEnemy);
			BattleField(FirstPointEnemyX, FirstPointEnemyY, Blue, Cyan, masBattleFildEnemy);
			SetMasBattle(masAriaSelf, masBattleFildSelf, masAriaSelfCopy);
			BattleField(FirstpointSelfX, FirstpointSelfY, Green, LightGreen, masBattleFildSelf);
			int x = 0, y = 0;
			int SumShipSelf = SumShip(boatSelf), SumShipEnemy = SumShip(boatEnemy);
			SetCursor(16, SizeAria * 4 - 2);
			cout << "����������� ����� ��������: " << SumShipEnemy;
			SetCursor(SizeAria * 7 + 15, SizeAria * 4 - 2);
			cout << "����������� ����� ��������: " << SumShipSelf;
			SetCursor(24, 3);
			cout << "������� ����������";
			SetCursor(SizeAria * 7 + 26, 3);
			cout << "���� �������";

			int keySelf = 0, keyEnemy = 0; //���� �������� ��������
			Shoot Hit = { 0,0,0,0,0 };
			do
			{

				SetMasBattle(masAriaEnemyCopy, masBattleFildEnemy);
				BattleField(1, 5, Blue, Cyan, masBattleFildEnemy);
				SquareCursor(FirstPointEnemyX + 2 + x, FirstPointEnemyY + 1 + y, LightGreen);
				click = _getch();
				switch (click)
				{
				case Up:
					if (y > 2) y -= 3;
					break;
				case Left:
					if (x > 5)x -= 6;
					break;
				case Right:
					if (x < SizeAria * 6 - 9)x += 6;
					break;
				case Down:
					if (y < SizeAria * 3 - 4)y += 3;
					break;
				case Enter:
					keySelf = CheckFire(x / 6, y / 3, masAriaEnemyCopy, masAriaEnemy, boatEnemy);
					if (keySelf == 0)
					{
						do {
							if (difficult == 0) {
								keyEnemy = EnemyShut(FirstpointSelfX, FirstPointEnemyY,
									masBattleFildSelf, masAriaSelfCopy, masAriaSelf, boatSelf, Hit);
							}
							else {
								if ((keyEnemy < 2 || keyEnemy == 3) && Hit.keyEnemyShoot == 0) {
									keyEnemy = EnemyShut(FirstpointSelfX, FirstPointEnemyY,
										masBattleFildSelf, masAriaSelfCopy, masAriaSelf, boatSelf, Hit);
								}
								if (keyEnemy == 2 || Hit.keyEnemyShoot == 2)
								{
									keyEnemy = Hitmen(FirstpointSelfX, FirstPointEnemyY, masBattleFildSelf,
										masAriaSelfCopy, masAriaSelf, boatSelf, Hit);
								}
							}
							if (SumShip(boatSelf) == 0)break;
						} while (keyEnemy > 1);
					}
					SumShipSelf = SumShip(boatSelf); SumShipEnemy = SumShip(boatEnemy);
					SetCursor(16, SizeAria * 4 - 2);
					cout << "                                     ";
					SetCursor(16, SizeAria * 4 - 2);
					cout << "����������� ����� ��������: " << SumShipEnemy;
					SetCursor(SizeAria * 7 + 15, SizeAria * 4 - 2);
					cout << "                                     ";
					SetCursor(SizeAria * 7 + 15, SizeAria * 4 - 2);
					cout << "����������� ����� ��������: " << SumShipSelf;
					break;
				}
				if (SumShipSelf == 0 || SumShipEnemy == 0) break;
			} while (click != esc);
			menuResult(8, 30, 51, 10);
			if (SumShip(boatSelf))
			{
				SetCursor(SizeAria * 6, 12);
				SetColor(Black, LightGray);
				cout << "�� ��������!!!";
				if (difficult == 0) u.progress += 10;
				else u.progress += 100;
			}
			if (SumShip(boatEnemy))
			{
				SetCursor(SizeAria * 6, 12);
				SetColor(Black, LightGray);
				cout << "�� ���������!!!";
			}
			char menuContin[2][30] = { "����� ����" ,"�����" };
			int punktContin = 0;
			SetCursor(55, 14);
			SetColor(Black, LightGray);
			cout << "������� ������� �����?";
			do
			{
				punktContin = ActivePunctResult(menuContin, 2);
				if (punktContin == 0)
				{
					contin = 0;
					system("cls");
					break;
				}
				if (punktContin == 1)
				{
					contin = 1;
					system("cls");
					break;
				}
			} while (punktContin != -1);
		} while (contin == 0);
		cout << u.login << "\t" << u.progress << "\n";
		if (f != nullptr) fclose(f);
		err = fopen_s(&f, "user.txt", "w");
		if (f != nullptr)
		{
			cout << "FILE is CREATE\n";
			for (size_t i = 0; i < size; i++)
			{
				fwrite(&mas[i], sizeof(User), 1, f);
			}
			fclose(f);
		}
	}
}

