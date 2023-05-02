#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "graph.hpp"

namespace py = pybind11;

void graph::color_graph() {}

void graph::read_graph(char *file) {}

PYBIND11_MODULE(ggdGVC, m)
{
    m.doc() = "ggdGVC: A Simple Vertex Coloring Library";

    py::class_<graph> clsGraph(m, "graph");

    clsGraph.def(py::init<>())
        .def(py::init<graph::Method>())
        .def("add_vertex", &graph::add_vertex)
        .def("add_edge", &graph::add_edge)
        .def("set_vertex_color", &graph::set_vertex_color)
        .def("get_vertex_color", &graph::get_vertex_color)
        .def("load_color", &graph::load_color);

    py::enum_<graph::Method>(clsGraph, "Method")
        .value("GREEDY", graph::Method::GREEDY)
        .value("BACKTRACKING", graph::Method::BACKTRACKING)
        .export_values();
}
