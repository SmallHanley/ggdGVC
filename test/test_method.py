from ggdGVC import graph
import pytest

class Test_Method():
    def test_greedy(self):
        G = graph()

        G.add_edge(0, 1)
        G.add_edge(0, 2)
        G.add_edge(1, 2)
        G.add_edge(1, 3)
        G.add_edge(2, 3)
        G.add_edge(3, 4)
        G.color_graph()
        color = G.load_color()
        assert color[0] != color[1]
        assert color[0] != color[2]
        assert color[1] != color[2]
        assert color[1] != color[3]
        assert color[2] != color[3]
        assert color[3] != color[4]

if __name__ == '__main__':
    G = graph()

    G.add_edge(0, 1)
    G.add_edge(0, 2)
    G.add_edge(1, 2)
    G.add_edge(1, 4)
    G.add_edge(2, 4)
    G.add_edge(3, 4)
    color = G.load_color()
    print(color)
    G.color_graph()
    color = G.load_color()
    print(color)
