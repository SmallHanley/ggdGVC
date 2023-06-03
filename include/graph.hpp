#pragma once

#include <list>
#include <unordered_map>

class graph
{
public:
    enum Method { GREEDY, BACKTRACKING };

    graph() : m_method(GREEDY) {}

    graph(Method method) : m_method(method) {}

    void add_vertex(int id)
    {
        if (m_adjList.find(id) == m_adjList.end()) {
            m_adjList[id] = std::list<int>();
            m_color[id] = -1;
            m_vertex.push_back(id);
            m_numV++;
        }
    }

    void add_edge(int id1, int id2)
    {
        if (m_adjList.find(id1) == m_adjList.end()) {
            m_adjList[id1] = std::list<int>();
            m_color[id1] = -1;
            m_vertex.push_back(id1);
            m_numV++;
        }
        if (m_adjList.find(id2) == m_adjList.end()) {
            m_adjList[id2] = std::list<int>();
            m_color[id2] = -1;
            m_vertex.push_back(id2);
            m_numV++;
        }
        m_adjList[id1].push_back(id2);
        m_adjList[id2].push_back(id1);
        m_edge.push_back(std::make_pair(id1, id2));
        m_numE++;
    }

    void set_vertex_color(int id, int color)
    {
        if (m_adjList.find(id) == m_adjList.end()) {
            m_adjList[id] = std::list<int>();
            m_color[id] = color;
            m_vertex.push_back(id);
            m_numV++;
        }
        m_color[id] = color;
    }

    int get_vertex_color(int id)
    {
        if (m_color.find(id) == m_color.end()) {
            return -1;
        }
        return m_color[id];
    }

    void set_method(Method method) { m_method = method; }

    std::unordered_map<int, int> load_color() { return m_color; }
    std::vector<int> load_vertex() { return m_vertex; }
    std::vector<std::pair<int, int>> load_edge() { return m_edge; }

    void color_graph()
    {
        switch (m_method) {
        case GREEDY:
            greedy_coloring();
            break;
        default:
            exit(1);
        }
    }
    void read_graph(char *file);

private:
    int m_numV;
    int m_numE;
    std::vector<int> m_vertex;
    std::vector<std::pair<int, int>> m_edge;
    std::unordered_map<int, std::list<int>> m_adjList;
    std::unordered_map<int, int> m_color;
    Method m_method;

    void greedy_coloring();
};
