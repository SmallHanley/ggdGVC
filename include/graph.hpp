#pragma once

#include <list>
#include <unordered_map>

class graph
{
public:
    void add_vertex(int id)
    {
        if (m_adjList.find(id) == m_adjList.end()) {
            m_adjList[id] = std::list<int>();
            m_color[id] = -1;
            m_numV++;
        }
    }

    void add_edge(int id1, int id2)
    {
        if (m_adjList.find(id1) == m_adjList.end()) {
            m_adjList[id1] = std::list<int>();
            m_color[id1] = -1;
            m_numV++;
        }
        if (m_adjList.find(id2) == m_adjList.end()) {
            m_adjList[id2] = std::list<int>();
            m_color[id2] = -1;
            m_numV++;
        }
        m_adjList[id1].push_back(id2);
        m_adjList[id2].push_back(id1);
        m_numE++;
    }

    void set_vertex_color(int id, int color)
    {
        if (m_adjList.find(id) == m_adjList.end()) {
            m_adjList[id] = std::list<int>();
            m_color[id] = color;
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

    std::unordered_map<int, int> load_color() { return m_color; }

    void color_graph();
    void read_graph(char *file);

private:
    int m_numV;
    int m_numE;
    std::unordered_map<int, std::list<int>> m_adjList;
    std::unordered_map<int, int> m_color;
};
