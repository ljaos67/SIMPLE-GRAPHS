/*
Programmer: Leonart Jaos
Assignment 11
z911688


*/
#include "simplegraph.h"

#include <fstream>
#include <iostream>
#include <list>
#include <vector>

using namespace std;


vector<int> visited;
vector<int> paths;
int ci;
Graph::Graph(const char* filename)
{
	int a, s, num;
	char c;
	ifstream ins;
	ins.open(filename);
	list<int> li;
	if(!ins)
	{
		cerr<< "Could not open input file: " << filename << " Exiting program..." << endl;
	}
	ins >> a;
	num = a + 1;
	for(int i = 0; i < num; i++)
	{
		for(int j = 0; j < num; j++)
		{
			if(i == 0)
			{
				if(j == (num - 1))
				{
					adj_list.push_back(li);
				}
				else
				{
					ins >> c;		
					labels.push_back(c);
					adj_list.push_back(li);
				}
			}
			else if(j == 0)
			{
				ins >> c;
				cout << "value for nodes " << c << "\n\n";
			}
			else
			{
				ins >> a;
				if(a == 1)
				{
					adj_list[i-1].push_back(j-1);
				}
			}

		}
	}
	// size = # of edges
	for(int i = 0; i < adj_list.size(); i++)
	{
		auto it = adj_list[i].begin();
		while(it != adj_list[i].end())
		{
			if((*it) > i)
			{
				s++;
			}
			++it;
		}
	}
	size = s;
	ins.close();
}

Graph::~Graph()
{
	visited.clear();
	paths.clear();
	for(int i =0; i < adj_list.size(); i++)
	{
		adj_list[i].clear();
	}
	adj_list.clear();
	labels.clear();
}

int Graph::Getsize() const
{
	return size;
}
bool inVisited(vector<int> v, int val)
{
	for(int ind =0; ind < v.size(); ind++)
	{
		if(v[ind] == val)
			return true;
	}
	return false;
}
bool inList(int index, vector< list<int>> v, int val)
{
	for(auto it = v[index].begin(); it != v[index].end(); ++it)
	{
		if(((*it)== val)&&(!inVisited(visited,(val))))
			return true;
	}
	return false;
}
void Graph::Depthfirst(int v)
{
	bool check = false;
	visited.push_back(v);
	paths.push_back(v);
	for(auto it = adj_list[v].begin(); it != adj_list[v].end(); ++it)
	{
		int w = *it;
		if(!inVisited(visited,w))
		{ 
			paths.push_back(w);
			Depthfirst(w);
		}

	}
}

void Graph::Traverse()
{
	int f = 0;
	bool found, r;
	for(int j = 0; j < labels.size(); j++)
	{
		if(!inVisited(visited,j))
		{
			ci = j;
			Depthfirst(j);
		}
	}
	cout << "------- traverse of graph ------\n";
	for(int i = 0; i <visited.size(); i++)
	{
		cout << labels[visited[i]] << " ";
	}
	cout << "\n";
	for(int i = 0; i < paths.size(); i++)
	{
		if(f == 0)
		{
			cout << "(" << labels[paths[i]] << ", ";
			f++;
		}
		else
		{
			cout << labels[paths[i]] << ") ";
			f = 0;
		}
	}
	cout << "\n--------- end of traverse -------\n\n";
}

void Graph::Print() const
{
	cout << "Number of vertices in the graph: " << labels.size() << "\n\n";
	cout << "-------- graph --------\n";
	for(int i = 0; i < labels.size(); i++)
	{
		cout << labels[i] << ":";
		for(auto it = adj_list[i].begin(); it != adj_list[i].end(); ++it)
		{
			cout << " " << labels[(*it)] << ",";
		}
		cout << "\n";
	}
	cout << "------- end of graph ------\n\n";
}

int main(int argc, char** argv) {
  if (argc < 2) {
    cerr << "args: input-file-name\n";
    return 1;
  }

  Graph g(argv[1]);

  g.Print();

  g.Traverse();

  return 0;
}
