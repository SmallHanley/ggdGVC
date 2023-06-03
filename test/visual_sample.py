import networkx as nx
import matplotlib.pyplot as plt
from ggdGVC import graph

# Contruct graph
G = graph()
G.add_edge(0, 1)
G.add_edge(0, 2)
G.add_edge(1, 2)
G.add_edge(1, 4)
G.add_edge(2, 4)
G.add_edge(3, 4)
G.add_vertex(17)

# Set coloring method
G.set_method(graph.GREEDY)

# Color graph
G.color_graph()

# Load graph information
vertex = G.load_vertex()
edge = G.load_edge()
color = G.load_color()

# Visualization
G = nx.Graph()
G.add_nodes_from(vertex)
G.add_edges_from(edge)
color_map = []
for node in G:
    color_map.append(color[node])
nx.draw(G, node_color=color_map, with_labels=True)
plt.show()