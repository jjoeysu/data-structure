#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string>
#include <malloc.h>
#include<vector>
#include<iostream>
#include <cstdio>
using namespace std;

#define type int
#define maxsize 100

class vertex //�����
{
public:
	type data;
	int degree, indegree, outdegree;
};

class edge//����
{
public:
	type data;
	int weight;
};

class graphmatrix//ͼ��
{
public:
	vector<vertex> V;
	vector<vector<edge*>> E;

	int vn, en;//�����������

	//����
	int degree(int i) {
		return V[i].degree;
	}

	//���
	int indegree(int i) {
		return V[i].indegree;
	}

	//����
	int outdegree(int i) {
		return V[i].outdegree;
	}


	//�жϽ���Ƿ����
	bool exists(int i, int j) {
		return E[i][j] != NULL;
	}

	//�������ڽ��
	int nextneighbor(int i, int j) {
		while (!exists(i, ++j) && i < vn);
		return j;
	}

	//�ӱ�
	void insertedge(edge ed, int i, int j) {
		if (!exists(i, j)) {
			E[i][j] = new edge(ed);
			en++;
			V[i].outdegree++;
			V[j].indegree++;
		}
	}

	//ɾ����
	void removeedge(edge edge, int i, int j)
	{
		if (exists(i, j)) {
			delete E[i][j];
			E[i][j] = NULL;
			en--;
			V[i].outdegree--;
			V[j].indegree--;
		}
	}

	//�ӽ��
	void insertvertex(vertex ve) {
		for (int i = 0; i < vn; ++i)
			E[i].push_back(NULL);
		vn++;
		E.push_back(E[vn]);
		V.push_back(ve);
	}

	//ɾ�����
	void removevertex(int i) {
		for (int j = 0; j < vn; ++j) {
			if (exists(i, j)) {
				delete E[i][j];
				V[j].indegree--
					;
			}
			E.erase(E.begin() + i); vn--;
			for (int j = 0; j < vn; ++j) {
				if (exists(j, i)) {
					delete E[j][i];
					E[j].erase(E[j].begin() + i);
					V[j].outdegree--;
				}
				V.erase(V.begin() + i);
			}
		}

	}



};

//dijkstra�㷨
void dijkstra(graphmatrix g, int v)
{
	int dist[maxsize], path[maxsize], s[maxsize];
	int mindis, i, j, u;
	for (i = 0; i < g.vn; i++)
	{
		dist[i] = g.E[v][i]->weight;
		s[i] = 0;
		if (g.E[v][i]->weight < INFINITY)
			path[i] = v;
		else path[i] = -1;
	}
	s[v] = 1; path[v] = 0;
	for (i = 0; i < g.vn - 1; i++) {
		mindis = INFINITY;
		for(j=0;j<g.vn;j++)
			if (s[j] == 0 && dist[j] < mindis)
			{
				u = j;
				mindis = dist[j];
			}
		s[u] = 1;
		for(j=0;j<g.vn;j++)
			if(s[j]==0)
				if (g.E[u][j]->weight < INFINITY && dist[u] + g.E[u][j]->weight < dist[j])
				{
					dist[j] = dist[u] + g.E[u][j]->weight;
					path[j] = u;
				}
	}
	dispath(g, dist, path, s, v);
}

//����ӽ��v�������������·��
void dispath(graphmatrix g, int dist[], int path[], int s[], int v)
{
	int i, j, k;
	int apath[maxsize], d;
	for(i=0;i<g.vn;i++)
		if (s[i] == 1 && i != v)
		{
			printf("�Ӷ���%d������%d��·������Ϊ��%d\t·��Ϊ��", v, i, dist[i]);
			d = 0; apath[d] = i;
			k = path[i];
			if (k == -1)
				printf("��·��\n");
			else
			{
				while (k != v)
				{
					d++; apath[d] = k;
					k = path[k];
				}
				d++; apath[d] = v;
				printf("%d", apath[d]);
				for (j = d - 1; j >= 0; j--)
					printf(",%d", apath[j]);
				printf("\n");
			}
		}
}

//prim�㷨������Խ��vΪ�������С��������
void prim(graphmatrix g, int v)
{
	int lowcost[maxsize];
	int min;
	int closest[maxsize], i, j, k;
	for (i = 0; i < g.vn; i++)
	{
		lowcost[i] = g.E[v][i]->weight;
		closest[i] = v;
	}
	for (i = 0; i < g.vn; i++)
	{
		min = INFINITY;
		for(j=0;j<g.vn;j++)
			if (lowcost[j] != 0 && lowcost[j] < min)
			{
				min = lowcost[j];
				k = j;
			}
		printf("�ߣ�%d,%d��ȨΪ��%d\n", closest[k], k, min);
		lowcost[k] = 0;
		for(j=0;j<g.vn;j++)
			if (lowcost[j] != 0 && g.E[k][j]->weight < lowcost[j])
			{
				lowcost[j] = g.E[k][j]->weight;
				closest[j] = k;
			}
	}
}

//���Ե�������
int main(void)
{
	graphmatrix g; g.vn = 9;
}



























