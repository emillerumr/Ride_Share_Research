Assign
------

This assigns customer requests with GPS coordinates onto vertices in the road network system.
To run:
	java Assign /path/to/graph/vertices.out < gps_requests.dat > network_requests.dat

gps_requests.dat contains lines of five tab-delimited numbers in the following format:
	time	sx	sy	ex	ey

time is an integer, identifying the simulation second when the request was received.
(sx, sy) is the starting coordinates of the request.
(ex, ey) is the ending coordinates of the request.

The output to network_requests.dat will be tab-delimited lines of:
	time	svertex	evertex

time is the simulation second.
svertex is the starting vertex.
evertex is the ending vertex.

Complete
--------

Contains a few tools to make sure that the graph is valid.
The input is a .gra file, so you should run like:
	java Complete < /path/to/graph/graph.gra

Which tool is used is hardcoded and requires recompilation to change.
All output is to standard output.

graToEdges(): will output an edges.out file
detectEdgeProblems(): identifies loops and one-direction edges
	(.gra allows directed graphs, but it should be undirected)
floodfill(0): floodfill algorithm starting at vertex 0
	This will return an array containing a boolean for each vertex
		of whether the vertex was visited.
	This can be used to identify unconnected vertices, but you have
		to separately output the integers because the floodfill call
		will not do that for you.

Convert
-------

Converts from edges.out to .gra format:
	java Convert < /path/to/graph/edges.out > /path/to/graph/graph.gra

Filter
------

Used with Complete to remove unconnected vertices.
Probably not very useful anymore...

GraphUtil
---------

Some utilities on the graph.
Requires three arguments:
	java GraphUtil /path/to/graph/vertices.out /path/to/graph/edges.out action

action determines which utility/tool will be used.

bound: identifies the topmost, leftmost, bottommost, and rightmost vertices on the graph
grid, grid-est: first, divides rectangle defined by bound into grid cells
	then, calculates how much distance of edges are in each grid cell
	for road network graph, this is total road length in the cell
	grid-est just estimates, but grid returns the accurate amount
togra: convert to .gra

Order
-----

I think if you have a .gra where the vertices are out of order, this will order it.

Vertex
------

Simple graph libary used by GraphUtil.


coordinate_parser
-----------------
-compile with g++ coordinate_parser.cpp -o coordinate_parser
-run with ./coordinate_parser

Note:
-vertices.txt and edges.txt must be in the input directory
-generates vertices.out and edges.out that can be converted to a .gra file that can be used with the simulator


request_parser
-----------------
compile with g++ request_parser.cpp -o request_parser
run with ./request_parser arg1

Note:
-vertices.txt must be in working directory
-traffic_trajectories.txt must be in input directory
 if arg1 is equal to "traffic", otherwise arg1 should
 be the number of trajectories to randomly create



