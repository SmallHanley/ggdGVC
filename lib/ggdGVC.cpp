#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "graph.hpp"

namespace py = pybind11;

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
        .def("set_method", &graph::set_method)
        .def("load_vertex", &graph::load_vertex)
        .def("load_edge", &graph::load_edge)
        .def("load_color", &graph::load_color)
        .def("color_graph", &graph::color_graph)
        .def("write_graph", &graph::write_graph)
        .def("read_graph", &graph::read_graph);

    py::enum_<graph::Method>(clsGraph, "Method")
        .value("GREEDY", graph::Method::GREEDY)
        .value("BACKTRACKING", graph::Method::BACKTRACKING)
        .export_values();
}
