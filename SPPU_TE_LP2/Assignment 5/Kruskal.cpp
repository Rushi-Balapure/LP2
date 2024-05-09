#include <iostream>
#include <vector>
using namespace std;
class DSU{
	vector<int> rank;
	vector<int> size;
	vector<int> parent;
public:
	DSU(int n){
		rank.resize(n+1, 0);
		size.resize(n+1, 1);

		parent.resize(n+1);
		for(int i=0; i<n; i++){
			parent[i] = i;
		}
	}

	int findUltimateParent(int num){
		if(num == parent[num]){
			return num;
		}
		return parent[num] = findUltimateParent(parent[num]);
	}

	void unionByRank(int u, int v){
		int uu = findUltimateParent(u);
		int uv = findUltimateParent(v);

		if(uu == uv){
			return;
		}

		if(rank[uu] > rank[uv]){
			parent[uv] = uu;
		}else if(rank[uv] > rank[uu]){
			parent[uu] = uv;
		}else{
			parent[uv] = uu;
			rank[uu]++;
		}
	}

	void unionBySize(int u, int v){
		int uu = findUltimateParent(u);
		int uv = findUltimateParent(v);

		if(uu == uv){
			return;;
		}

		if(size[uu] > size[uv]){
			parent[uv] = uu;
			size[uu] += size[uv];
		}else{
			parent[uu] = uv;
			size[uv] += size[uu];
		}
	}
};

int kruskalMST(int n, vector<vector<int>> &edges)
{
	vector<pair<int, pair<int,int>>> sortedEdges;
	for(auto edge : edges){
		int w = edge[2];
		int u = edge[0];
		int v = edge[1];
		sortedEdges.push_back({w,{u, v}});
	}
	
	sort(sortedEdges.begin(), sortedEdges.end());

	DSU MST(n);
	int result = 0;

	for(auto edge : sortedEdges){
		int w = edge.first;
		int u = edge.second.first;
		int v = edge.second.second;

		if(MST.findUltimateParent(u) != MST.findUltimateParent(v)){
			result += w;
			MST.unionBySize(u, v);
		}
	}

	return result;
}