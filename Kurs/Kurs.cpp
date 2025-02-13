#include <iostream>
#include <fstream>
#include <windows.h>
#include <string> 
using namespace std;
double** create_matr(int size)
{
	double** M = new double* [size];
	for (int i = 0; i < size; i++)
		M[i] = new double[size];
	return M;
}
double** zapoln_matr(int size, string name)
{
	double** M = new double* [size];
	cout << "Введите элементы матрицы " << name << ":" << endl;
	for (int i = 0; i < size; i++)
	{
		M[i] = new double[size];
		for (int j = 0; j < size; j++)
			cin >> M[i][j];
	}
	return M;
}
void file_matr(double** M, int size, string name)
{
	ofstream F;
	F.open(name, ios::app);
	F << size << endl;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size - 1; j++)
			F << M[i][j] << " ";
		F << M[i][size - 1] << endl;
	}
	F << endl;
	F.close();
}
void vivod_matr(double** M, int size, string name)
{
	cout << "Матрица " << name << ":" << endl;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size - 1; j++)
			cout << M[i][j] << " ";
		cout << M[i][size - 1] << endl;
	}
}
void delete_mass(double** M, int kol)
{
	for (int i = 0; i < kol; i++)
		delete[] M[i];
	delete[] M;
}
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int kom = 1;
	int sizeA{}, sizeB{}, sizeC{};
	double** A{};
	double** B{};
	double** C{};
	while (kom != 0)
	{
		cout << "Введите команду:" << endl;
		cout << "1 - консольный ввод данных о матрицах A, B и C;" << endl;
		cout << "2 - файловый ввод данных о матрицах А, В и С;" << endl;
		cout << "3 - редактирование элементов матриц;" << endl;
		cout << "4 - замена элементов матрицы С нулями те элементы, равные максимумам столбцов в матрице А или строк в матрице В;" << endl;
		cout << "5 - консольный вывод матриц;" << endl;
		cout << "6 - файловый вывод матриц;" << endl;
		cout << "0 - выход из программы." << endl;
		cout << "Выбранная команда: ";
		cin >> kom;
		string name{};
		switch (kom)
		{
		case 1:
		{
			if (sizeA > 0)
				delete_mass(A, sizeA);
			if (sizeB > 0)
				delete_mass(B, sizeB);
			if (sizeC > 0)
				delete_mass(C, sizeC);
			cout << "Введите размер матрицы A: ";
			cin >> sizeA;
			A = zapoln_matr(sizeA, "A");
			cout << "Введите размер матрицы B: ";
			cin >> sizeB;
			B = zapoln_matr(sizeB, "B");
			cout << "Введите размер матрицы C: ";
			cin >> sizeC;
			C = zapoln_matr(sizeC, "C");
			break;
		}
		case 2:
		{
			cout << "Введите название файла (без формата): ";
			cin >> name;
			name += ".txt";
			ifstream file;
			file.open(name);
			file >> sizeA;
			A = create_matr(sizeA);
			for (int i = 0; i < sizeA; i++)
				for (int j = 0; j < sizeA; j++)
					file >> A[i][j];
			file >> sizeB;
			B = create_matr(sizeB);
			for (int i = 0; i < sizeB; i++)
				for (int j = 0; j < sizeB; j++)
					file >> B[i][j];
			file >> sizeC;
			C = create_matr(sizeC);
			for (int i = 0; i < sizeC; i++)
				for (int j = 0; j < sizeC; j++)
					file >> C[i][j];
			file.close();
			cout << "Файлы считаны!" << endl;
			break;
		}
		case 3:
		{
			int row{}, col{};
			double count{};
			cout << "Введите букву выбранной матрицы (A, B, C) для редактирования, либо запишите любую другую последовательность для прекращения редактирования: ";
			cin >> name;
			row = 1;
			cout << "Введите номер строки: ";
			cin >> row;
			cout << "Введите номер столбца: ";
			cin >> col;
			cout << "Введите новое значение изменяемого элемента: ";
			cin >> count;
			if (name == "A")
				A[row - 1][col - 1] = count;
			if (name == "B")
				B[row - 1][col - 1] = count;
			if (name == "C")
				C[row - 1][col - 1] = count;
		}
		case 4:
		{
			double* max = new double[sizeA + sizeB];
			for (int i = 0; i < sizeA; i++)
			{
				max[i] = A[0][i];
				for (int j = 1; j < sizeA; j++)
					if (A[j][i] > max[i])
						max[i] = A[j][i];
			}
			for (int i = 0; i < sizeB; i++)
			{
				max[sizeA + i] = B[i][0];
				for (int j = 1; j < sizeB; j++)
					if (B[i][j] > max[sizeA + i])
						max[sizeA + i] = B[i][j];
			}
			for (int i = 0; i < sizeC; i++)
				for (int j = 0; j < sizeC; j++)
					for (int x = 0; x < sizeA + sizeB; x++)
						if (C[i][j] == max[x])
						{
							C[i][j] = 0;
							continue;
						}
			break;
		}
		case 5:
		{
			vivod_matr(A, sizeA, "A");
			vivod_matr(B, sizeB, "B");
			vivod_matr(C, sizeC, "C");
			break;
		}
		case 6:
		{
			cout << "Введите название файла (без формата): ";
			cin >> name;
			name += ".txt";
			file_matr(A, sizeA, name);
			file_matr(B, sizeB, name);
			file_matr(C, sizeC, name);
			cout << "Файлы заполнены." << endl;
			break;
		}
		case 0:
		{
			cout << "Программа завершена." << endl;
			break;
		}
		default:
		{
			cout << "Неверный номер программы." << endl;
			break;
		}
		}
	}
	delete_mass(A, sizeA);
	delete_mass(B, sizeB);
	delete_mass(C, sizeC);
}