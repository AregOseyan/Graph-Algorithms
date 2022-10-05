#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <string>
#include <unordered_set>
#include <queue>

void addEdge(std::unordered_map<int, std::vector<int>>& graph, int p, int q)
{
  if (graph.find(p) == graph.end()) { graph[p] = {}; }
  if (graph.find(q) == graph.end()) { graph[q] = {}; }
  graph[p].push_back(q);
  graph[q].push_back(p);
}

void buildGraph(std::string address, std::unordered_map<int, std::vector<int>>& graph)
{
  std::ifstream file;
  file.open(address);

  file.ignore(10000, '\n');
  file.ignore(10000, '\n');
  std::string n;
  std::string m;
  if (file)
  {
    while(file >> n >> m)
    {
      try
      {
        int num1 = std::stoi(n);
        int num2 = std::stoi(m);
        addEdge(graph, num1, num2);
      }
      catch (std::invalid_argument const &e)
      {
        std::cout << "invalid_argument thrown!!!" << std::endl;
      }
      catch (std::out_of_range const &e)
      {
        std::cout << "out_of_range thrown!!!" << std::endl;
      }
    }
  }
  else { std::cout << "File not find!\n"; }
}

void printGraph(const std::unordered_map<int, std::vector<int>>& graph)
{
  for (auto x : graph)
  {
    std::cout << x.first;
    for (int i = 0; i < x.second.size(); ++i)
    {
      std::cout << " <-> " << x.second[i];
    }
    std::cout << std::endl;
  }
}

void BFS(std::unordered_map<int, std::vector<int>>& graph, int s, std::unordered_set<int>& exp)
{
  exp.insert(s);
  std::queue<int> qu;
  qu.push(s);
  while (!qu.empty())
  {
    int u = qu.front();
    qu.pop();
    for (int i = 0; i < graph[u].size(); ++i)
    {
      if (exp.find(graph[u][i]) == exp.end())
      {
        exp.insert(graph[u][i]);
        qu.push(graph[u][i]);
      }
    }
  }
}

int BFSLoop(std::unordered_map<int, std::vector<int>>& graph)
{
  std::unordered_set<int> exp;
  int res = 0;
  for (auto x : graph)
  {
    if (exp.find(x.first) == exp.end())
    {
      res++;
      BFS(graph, x.first, exp);
    }
  }
  return res;
}

int main()
{
  std::unordered_map<int, std::vector<int>> graph1;
  buildGraph("tinyG.txt", graph1);
  //printGraph(graph); 
  std::cout << "Number of connectivity components (tinyG.txt) " << BFSLoop(graph1) << std::endl;
  std::unordered_map<int, std::vector<int>> graph2;
  buildGraph("input.txt", graph2); 
  std::cout << "Number of connectivity components (input.txt) " << BFSLoop(graph2) << std::endl;

  return {};
}
