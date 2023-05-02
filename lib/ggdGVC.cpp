#include <pybind11/pybind11.h>
#include "graph.hpp"

namespace py = pybind11;

void graph::color_graph() {}

void graph::read_graph(char *file) {}

PYBIND11_MODULE(ggdGVC, m)
{
    m.doc() = "ggdGVC: A Simple Vertex Coloring Library";
    py::class_<graph>(m, "graph")
        .def("add_vertex", &graph::add_vertex)
        .def("add_edge", &graph::add_edge)
        .def("set_vertex_color", &graph::set_vertex_color)
        .def("get_vertex_color", &graph::get_vertex_color);
}
