#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include <ctime>

using namespace std;

struct vertex
{
	long id;
	double x;
	double y;
};

struct trajectory
{
	long timestamp;
	vertex starting_point;
	vertex ending_point;
};

struct traffic_point
{
	long object_id;
	long timestamp;
	string type;
	double latitude;
	double longitude;
};

bool compare_trajectories(trajectory t1, trajectory t2)
{
	return(t1.timestamp < t2.timestamp);
}

int main(int argc, char* argv[])
{
	ifstream trajectory_fin("input/traffic_trajectories.txt");
	ifstream vertex_fin("input/vertices.txt");
	string first_line;
	getline(trajectory_fin,first_line);
	long object_id;
	long timestamp;
	string type;
	double longitude;
	double latitude;

	vector<trajectory> trajectories;
	map<long, vertex> disappearpoints_by_id;
	map<long, vertex> newpoints_by_id;


	vector<vertex> vertices;
	long vertex_id;
	char comma;
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
		// longitude = -longitude;
		
		currentVertex.id = vertex_id;
		currentVertex.x = longitude;
		currentVertex.y = latitude;
		vertices.push_back(currentVertex);
		vertices_by_id.insert(pair<long,vertex>(vertex_id,currentVertex));
		id_converter.insert(pair<long,long>(vertex_id,i));
		i++;
	}
	string arg1 = argv[1];
	if(argc > 1 && arg1 == "traffic")
	{
		vector<traffic_point> newpoints;
		vector<traffic_point> disappearpoints;
		while(!trajectory_fin.eof())
		{
			traffic_point current_traffic_point;

			trajectory_fin>>object_id;
			trajectory_fin>>timestamp;
			trajectory_fin>>type;
			trajectory_fin>>latitude;
			trajectory_fin>>longitude;
			// longitude = -longitude;

			if(type == "newpoint")
			{
				current_traffic_point.object_id = object_id;
				current_traffic_point.timestamp = timestamp;
				current_traffic_point.type = type;
				current_traffic_point.latitude = latitude;
				current_traffic_point.longitude = longitude;
				newpoints.push_back(current_traffic_point);
			}
			else if(type == "disappearpoint")
			{
				current_traffic_point.object_id = object_id;
				current_traffic_point.timestamp = timestamp;
				current_traffic_point.type = type;
				current_traffic_point.latitude = latitude;
				current_traffic_point.longitude = longitude;
				disappearpoints.push_back(current_traffic_point);
			}
		}

		for(vector<traffic_point>::iterator disappearpoints_itr = disappearpoints.begin(); disappearpoints_itr != disappearpoints.end(); disappearpoints_itr++)
		{
			trajectory curret_trajectory;
			for(vector<traffic_point>::iterator newpoints_itr = newpoints.begin(); newpoints_itr != newpoints.end(); newpoints_itr++)
			{
				if(disappearpoints_itr->object_id == newpoints_itr->object_id)
				{
					for(vector<vertex>::iterator vertex_itr = vertices.begin(); vertex_itr != vertices.end(); vertex_itr++)
					{
						if(abs(vertex_itr->x - newpoints_itr->longitude) < 0.000001 && abs(vertex_itr->y - newpoints_itr->latitude) < 0.000001)
						{
							// cout<<"found beginning vertex!"<<endl;
							curret_trajectory.starting_point = *vertex_itr;
							curret_trajectory.timestamp = newpoints_itr->timestamp;
						}
						else if(abs(vertex_itr->x - disappearpoints_itr->longitude) < 0.000001 && abs(vertex_itr->y - disappearpoints_itr->latitude) < 0.000001)
						{
							// cout<<"found ending vertex!"<<endl;
							curret_trajectory.ending_point = *vertex_itr;
						}
					}
				}
			}
			trajectories.push_back(curret_trajectory);
			// cout<<curret_trajectory.starting_point.x<<","<<curret_trajectory.starting_point.y<<endl
			// 	<<curret_trajectory.ending_point.x<<","<<curret_trajectory.ending_point.y<<endl;
		}
		sort(trajectories.begin(),trajectories.end(), compare_trajectories);

		ofstream trajectory_fout("output/newtaxi.dat");
		
		// cout<<trajectories.size()<<endl;
		// trajectory_fout<<trajectories.size()<<endl;
		for(vector<trajectory>::iterator itr = trajectories.begin(); itr != trajectories.end(); itr++)
		{
			// cout<<itr->timestamp + 25000<<" "<<id_converter.at(itr->starting_point.id)<<" "<<id_converter.at(itr->ending_point.id)<<endl;

			trajectory_fout<<itr->timestamp + 25200<<" "<<id_converter.at(itr->starting_point.id)<<" "<<id_converter.at(itr->ending_point.id)<<endl;
		}
	}
	else
	{
		srand(time(0));
		long timestamp = 25200;
		long num_trajectories;
		ofstream trajectory_fout("output/newtaxi.dat");
		if(argc > 1)
		{
			num_trajectories = atoi(argv[1]);
		}
		else
		{
			num_trajectories = 100;
		}
		for(int k = 0; k < num_trajectories; k++)
		{
			long starting_vertex_id = rand() % vertices.size();
			long ending_vertex_id = rand() % vertices.size();
			while(starting_vertex_id == ending_vertex_id)
			{
				ending_vertex_id = rand() % vertices.size();
			}
			timestamp++;
			// cout<<timestamp<<" "<<starting_vertex_id<<" "<<ending_vertex_id<<endl;
			trajectory_fout<<timestamp<<" "<<starting_vertex_id<<" "<<ending_vertex_id<<endl;
		} 
	}
	return 0;
}