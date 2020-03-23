// Number_6.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
/*
Сушков Андрей 5 группа

Написать функцию, которая найдёт и напечатает все вершины в неориентированном графе,

удаление которых приводит к увеличению компонент связности в графе (удаляются и все

смежные рёбра). Во входном потоке в первой строке задаётся количество вершин и

количество рёбер, а далее в каждой строке - пара номеров вершин, которые соединены

ребром.
*/

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

void findSmallGraph(int countVertex, bool **graph, int pos, bool *visited)
{
	visited[pos] = 1;
	for (int i = 0; i < countVertex; i++)
	{
		if (graph[pos][i] == 1 && visited[i] == 0)
		{
			findSmallGraph(countVertex, graph, i, visited);
		}
	}
}

int countSmallGraph(int countVertex, bool **graph, bool *visited)
{
	int count = 0;
	for (int i = 0; i < countVertex; i++)
	{
		if (visited[i] == 0)
		{
			count++;
			findSmallGraph(countVertex, graph, i, visited);
		}
	}
	return count;
}

void findDeletedVertex(int mainCount, int countVertex, bool **graph, bool *visited)
{
	bool *deletedVertex = new bool[countVertex];
	for (int i = 0; i < countVertex; i++)
		deletedVertex[i] = 0;

	bool find = false;

	for (int i = 0; i < countVertex; i++)
	{
		for (int i = 0; i < countVertex; i++)
			visited[i] = 0;
		visited[i] = 1;
		int temp = countSmallGraph(countVertex, graph, visited);
		if (temp > mainCount)
		{
			deletedVertex[i] = 1;
			find = true;
		}
		visited[i] = 0;
	}

	if (find == true)
	{
		cout << "Вершины: ";
		for (int i = 0; i < countVertex; i++)
			if (deletedVertex[i] == 1)
				cout << i << " ";
	}
	else
		cout << "Таких вершин нет!\n";
}

int main()
{
	setlocale(LC_ALL, "Russian");
	int countVertex = 0;
	int countEdge = 0;
	ifstream fin("graph2.txt");
	string symbol = "2";

	fin >> symbol;
	countVertex = atoi(symbol.c_str());

	bool **graph = new bool*[countVertex];
	for (int i = 0; i < countVertex; i++)
		graph[i] = new bool[countVertex];

	for (int i = 0; i < countVertex; i++)
	{
		for (int j = 0; j < countVertex; j++)
		{
			graph[i][j] = 0;
		}
	}

	fin >> symbol;
	countEdge = atoi(symbol.c_str());

	int first = 0;
	int second = 0;
	for (int i = 0; i < countEdge; i++)
	{
		fin >> symbol;
		first = atoi(symbol.c_str());

		fin >> symbol;
		second = atoi(symbol.c_str());

		graph[first][second] = 1;
		graph[second][first] = 1;
	}

	for (int i = 0; i < countVertex; i++)
	{
		for (int j = 0; j < countVertex; j++)
		{
			cout << graph[i][j] << " ";
		}
		cout << "\n";
	}

	int pos = 0;
	bool *visited = new bool[countVertex];
	for (int i = 0; i < countVertex; i++)
		visited[i] = 0;
	int mainCount = countSmallGraph(countVertex, graph, visited);
	findDeletedVertex(mainCount, countVertex, graph, visited);
}
