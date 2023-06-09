from ggdGVC import graph
import pytest

class Test_Graph():
    def test_basic(self):
        G = graph()

        G.add_vertex(1)
        color = G.get_vertex_color(1)
        assert color == -1
        G.set_vertex_color(1, 3)
        color = G.get_vertex_color(1)
        assert color == 3
        G.set_vertex_color(1, 4)
        color = G.get_vertex_color(1)
        assert color == 4
        color = G.get_vertex_color(2)
        assert color == -1
        G.clear_color()
        color = G.get_vertex_color(1)
        assert color == -1

    def test_load_color(self):
        G = graph()

        color = G.load_color()
        assert len(color) == 0

        G.add_vertex(1)
        color = G.get_vertex_color(1)
        assert color == -1
        G.set_vertex_color(1, 3)
        color = G.get_vertex_color(1)
        assert color == 3
        G.set_vertex_color(1, 4)
        color = G.get_vertex_color(1)
        assert color == 4
        color = G.get_vertex_color(2)
        assert color == -1

        color = G.load_color()
        assert len(color) == 1

        G.set_vertex_color(4, 22)
        G.add_edge(5, 6)

        color = G.load_color()
        assert len(color) == 4
        assert color[4] == 22

    def test_read_graph(self):
        G = graph()
        G.read_graph('../graph/complete_graph.json')
        G.color_graph()
        num = G.get_color_num()
        assert num == 10

if __name__ == '__main__':
    G = graph(graph.BACKTRACKING)

    color = G.load_color()
    print(len(color))

    G.add_vertex(1)
    G.add_vertex(3)
    color = G.get_vertex_color(1)
    assert color == -1
    G.set_vertex_color(1, 3)
    color = G.get_vertex_color(1)
    assert color == 3
    G.set_vertex_color(1, 4)
    color = G.get_vertex_color(1)
    assert color == 4
    color = G.get_vertex_color(2)
    assert color == -1

    color = G.load_color()
    print(color)
