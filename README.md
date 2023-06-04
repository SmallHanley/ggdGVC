# ggdGVC: A Simple Vertex Coloring Library

Graph coloring is a popular research topics in graph theory. Vertex coloring is one of the coloring problems that involves assigning colors to the vertices of a graph such that no two adjacent vertices have the same color.

## Prospective Users

The prospective users of ggdGVC include computer science students and researchers. The library can be used in various applications, including scheduling, register allocation, and frequency allocation in wireless communication.

## Prerequisites

Install [nlohmann/json](https://github.com/nlohmann/json) for serialization and deserialization.

```
$ sudo apt install nlohmann-json3-dev
```

You also have to install [matplotlib](https://matplotlib.org/) and [networkx](https://networkx.org/) for visualization.

```
$ pip install matplotlib
$ pip install networkx
```

## System Architecture

ggdGVC will be developed in C++, and create Python bindings of the C++ code.

The system architecture of the library will consist of the following components:

* Graph data structures
* Vertex coloring algorithm
* API

ggdGVC will provide python code for visualization and testing (see [visual_sample.py](test/visual_sample.py)).

## Build

```
cd lib
make
```

Run the test.

```
cd test
make test
```

## API Description

The following API will be provided in both C++ and Python.

* `graph(Method method=GREEDY)`
    * Create a graph.
    * Method includes `GREEDY`, `BACKTRACKING`, and `WELSH_POWELL`, default setting is `GREEDY`.
* `void add_vertex(int id)`
    * Add vertex to the graph.
* `void add_edge(int id1, int id2)`
    * Add edge to the graph.
    * The edge connects vertex `id1` and `id2`. If vertex does not exist, add the new vertex to the graph.
* `void set_vertex_color(int id, int color)`
    * Color the specific vertex `id` with `color`.
* `int get_vertex_color(int id)`
    * Get the color of vertex `id`.
* `void set_method(Method method)`
    * Set method.
* `std::unordered_map<int, int> load_color()`
    * In C++, return unordered_map of color. In each mapping, the first element is vertex id, and the second element is the color of the vertex.
    * In Python, return dictionary of color.
* `std::vector<int> load_vertex()`
    * In C++, return vector of vertices.
    * In Python, return list of vertex id.
* `std::vector<std::pair<int, int>>`
    * In C++, return vector of edges, and each edge is a pair of vertices.
    * In Python, return list of tuple.
* `void color_graph()`
    * Color the graph.
* `int get_color_num()`
    * Get the number of colors used in `color_graph()`.
* `void clear_color()`
    * Clear all the colors int the graph.
* `void write_graph(const std::string &filename)`
    * Write to a JSON file with `filename`.
* `void read_graph(const std::string &filename)`
    * Read from a JSON file with `filename`.

## JSON File Format

* `color`: The first element is vertex id, and the second element is the color of the vertex.
* `edge`: The two elements represent the two vertices id connected to each other.
* `numE`: The number of edges.
* `numV`: The number of vertices.
* `vertex`: The list of vertices id.

```json
{
    "color": [
        [
            0,
            -1
        ],
        [
            1,
            -1
        ],
        [
            2,
            -1
        ]
    ],
    "edge": [
        [
            0,
            1
        ],
        [
            1,
            2
        ],
        [
            0,
            2
        ]
    ],
    "numE": 3,
    "numV": 3,
    "vertex": [
        0,
        1,
        2
    ]
}
```

If you would like to refer to more examples, please refer to the `graph/` directory.

## Visualization Result

* Complete graph
[](image/complete_graph.png)

* Bipartite graph
[](image/bipartite_graph.png)

* Petersen graph
[](image/petersen_graph.png)

## Timing Result

|                                      |  greedy  | backtracking | welsh_powell |
|:------------------------------------:|:--------:|:------------:|:------------:|
|              $K_{1000}$              | 0.039789 |   0.735179   |   1.227832   |
|               # colors               |   1000   |     1000     |     1000     |
| bipartite graph V(500, 500), E(5000) | 0.000179 |   0.000104   |   0.000289   |
|               # colors               |    8     |      2       |      11      |
|   random graph V(5000), E(100000)    | 0.006608 |   0.006476   |   0.014120   |
|               # colors               |    17    |      17      |      18      |
