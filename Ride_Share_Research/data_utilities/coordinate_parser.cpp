#include <iostream>
#include <fstream>
#include <map>
#include <iomanip>
#include <vector>
#include <math.h>

using namespace std;

struct vertex
{
	long id;
	double x;
	double y;
};

struct edge
{
	long v1;
	long v2;
};

double getDistance(vector<vertex> vertices, long index_1, long index_2)
{
	double x_difference = vertices[index_1].x - vertices[index_2].x;
	double y_difference = vertices[index_1].y - vertices[index_2].y;
	return(sqrt(x_difference*x_difference + y_difference*y_difference));
}

int main()
{
	// long file_length = 0;
	// string data;
	// ifstream file_length_fin("vertices.txt");
	// while(!file_length_fin.eof())
	// {
	// 	file_length++;
	// 	getline(file_length_fin,data);
	// }
	// file_length_fin.close();


	cout.precision(6);
	ifstream vertex_fin("input/vertices.txt");
	ifstream edge_fin("input/edges.txt");
	ofstream vertex_fout("output/vertices.out");
	ofstream edge_fout("output/edges.out");
	long vertex_id;
	char comma;
	double latitude;
	double longitude;
	vector<vertex> vertices;

	map<long,vertex> vertices_by_id;
	// vertex_fout<<file_length<<endl;
	map<long,long> id_converter;
	long i = 0;
	while(!vertex_fin.eof())
	{
		vertex currentVertex;
		vertex_fin>>vertex_id;
		vertex_fin>>comma;
		vertex_fin>>latitude;
		vertex_fin>>comma;
		vertex_fin>>longitude;
		if(longitude < 0)
		{
			longitude = -longitude;
		}
		currentVertex.id = vertex_id;
		currentVertex.x = longitude;
		currentVertex.y = latitude;
		vertices.push_back(currentVertex);
		vertices_by_id.insert(pair<long,vertex>(vertex_id,currentVertex));
		id_converter.insert(pair<long,long>(vertex_id,i));
		i++;
	}
	cout<<vertices.size()<<endl;
	vertex_fout<<vertices.size()<<endl;
	for(int k = 0; k < vertices.size(); k++)
	{
		vertex_fout<<setprecision(6)<<fixed<<vertices[k].y<<" ";
		vertex_fout<<setprecision(6)<<fixed<<vertices[k].x<<endl;
	}

	long edge_id;
	long vertex_id_1,vertex_id_2;
	string extra;
	vector<edge> edges;
	while(!edge_fin.eof())
	{
		edge currentEdge;
		edge_fin>>edge_id;
		edge_fin>>comma;
		edge_fin>>vertex_id_1;
		edge_fin>>comma;
		edge_fin>>vertex_id_2;
		getline(edge_fin,extra);

		currentEdge.v1 = vertex_id_1;
		currentEdge.v2 = vertex_id_2;
		edges.push_back(currentEdge);
	}
	cout<<edges.size()<<endl;
	edge_fout<<edges.size()<<endl;
	for(int k = 0; k < edges.size(); k++)
	{
		edge_fout<<setprecision(6)<<fixed<<id_converter[edges[k].v1]<<" ";
		edge_fout<<setprecision(6)<<fixed<<id_converter[edges[k].v2]<<" ";
		edge_fout<<getDistance(vertices,id_converter[edges[k].v1],id_converter[edges[k].v2])<<endl;
	}
	// cout<<vertices.size()<<endl;
	// vertex_fout<<vertices.size()<<endl;
	// for(int k = 0; k < vertices.size(); k++)
	// {
	// 	vertex_fout<<setprecision(6)<<fixed<<vertices[k].x<<" ";
	// 	vertex_fout<<setprecision(6)<<fixed<<vertices[k].y<<endl;
	// }
	return 1;
}