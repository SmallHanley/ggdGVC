#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <unordered_map>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class graph
{
public:
    enum Method { GREEDY, BACKTRACKING };

    graph() : m_numV(0), m_numE(0), m_method(GREEDY) {}

    graph(Method method) : m_numV(0), m_numE(0), m_method(method) {}

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

    void write_graph(const std::string& filename) const
    {
        std::ofstream file(filename);
        if (file.is_open()) {
            json j = to_json();
            file << j.dump(4); // 寫入 JSON 字串到檔案（縮排為 4 個空格）
            file.close();
        }
    }

    void read_graph(const std::string& filename)
    {
        std::ifstream file(filename);
        if (file.is_open()) {
            json j;
            file >> j;
            from_json(j);
            file.close();
        }
    }

private:
    int m_numV;
    int m_numE;
    std::vector<int> m_vertex;
    std::vector<std::pair<int, int>> m_edge;
    std::unordered_map<int, std::list<int>> m_adjList;
    std::unordered_map<int, int> m_color;
    Method m_method;

    void greedy_coloring();

    json to_json() const
    {
        json j;

        j["numV"] = m_numV;
        j["numE"] = m_numE;
        j["vertex"] = m_vertex;
        j["edge"] = m_edge;
        j["color"] = m_color;

        return j;
    }

    void from_json(const json& j)
    {
        m_numV = j["numV"];
        m_numE = j["numE"];
        m_vertex = j["vertex"].get<std::vector<int>>();
        m_edge = j["edge"].get<std::vector<std::pair<int, int>>>();
        m_color = j["color"].get<std::unordered_map<int, int>>();
        m_adjList.clear();
        for (auto v : m_vertex) {
            m_adjList[v] = std::list<int>();
        }
        for (auto e : m_edge) {
            m_adjList[e.first].push_back(e.second);
            m_adjList[e.second].push_back(e.first);
        }
    }
};
