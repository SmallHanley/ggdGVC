import ggdGVC
import pytest

class Test_Graph():
    def test_basic(self):
        G = ggdGVC.graph()

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

    def test_load_color(self):
        G = ggdGVC.graph()

        color = G.load_color()
        print(color)

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
        print(color)

if __name__ == '__main__':
    G = ggdGVC.graph()

    color = G.load_color()
    print(color)

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
