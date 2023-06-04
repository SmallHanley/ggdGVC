#pragma once

#include <climits>
#include <fstream>
#include <iostream>
#include <list>
#include <nlohmann/json.hpp>
#include <string>
#include <unordered_map>

using json = nlohmann::json;

class graph
{
public:
    enum Method { GREEDY, BACKTRACKING, WELSH_POWELL };

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
        if (std::find(m_edge.begin(), m_edge.end(), std::make_pair(id1, id2)) ==
                m_edge.end() ||
            std::find(m_edge.begin(), m_edge.end(), std::make_pair(id2, id1)) ==
                m_edge.end()) {
            m_adjList[id1].push_back(id2);
            m_adjList[id2].push_back(id1);
            m_edge.push_back(std::make_pair(id1, id2));
            m_numE++;
        }
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
        case BACKTRACKING:
            backtracking_coloring();
            break;
        case WELSH_POWELL:
            welsh_powell_coloring();
            break;
        default:
            exit(1);
        }
    }

    void clear_color()
    {
        for (auto &it : m_color) {
            it.second = -1;
        }
    }

    void write_graph(const std::string &filename) const
    {
        std::ofstream file(filename);
        if (file.is_open()) {
            json j = to_json();
            file << j.dump(4);  // 寫入 JSON 字串到檔案（縮排為 4 個空格）
            file.close();
        }
    }

    void read_graph(const std::string &filename)
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

    void greedy_coloring()
    {
        std::vector<bool> available(m_numV, false);
        for (auto u = m_adjList.begin(); u != m_adjList.end(); u++) {
            for (auto i = u->second.begin(); i != u->second.end(); i++) {
                if (m_color[*i] != -1) {
                    available[m_color[*i]] = true;
                }
            }
            int cr;
            for (cr = 0; cr < m_numV; cr++) {
                if (available[cr] == false) {
                    break;
                }
            }
            m_color[u->first] = cr;
            for (auto i = u->second.begin(); i != u->second.end(); i++) {
                if (m_color[*i] != -1) {
                    available[m_color[*i]] = false;
                }
            }
        }
    }

    bool isValidColor(int id, int c, std::unordered_map<int, int> &color)
    {
        for (int neighbor : m_adjList[id]) {
            if (color[neighbor] == c) {
                return false;
            }
        }
        return true;
    }

    bool backtrack(int idx, std::unordered_map<int, int> &color)
    {
        int minC = INT_MAX;
        if (idx == m_numV) {
            auto numC =
                std::max_element(color.begin(), color.end(),
                                 [](const std::pair<int, int> &a,
                                    const std::pair<int, int> &b) -> bool {
                                     return a.second < b.second;
                                 })
                    ->second;
            if (numC < minC) {
                m_color = color;
                minC = numC;
            }
            return true;
        }

        for (int c = 0; c < m_numV; c++) {
            if (isValidColor(m_vertex[idx], c, color)) {
                color[m_vertex[idx]] = c;
                if (backtrack(idx + 1, color))
                    return true;
                color[m_vertex[idx]] = -1;
            }
        }

        return false;
    }

    void backtracking_coloring()
    {
        if (!m_numV)
            return;

        std::unordered_map<int, int> color(m_color);
        backtrack(0, color);
    }

    void welsh_powell_coloring()
    {
        std::list<int> vertex(m_vertex.begin(), m_vertex.end());

        vertex.sort([&](int id1, int id2) {
            return m_adjList[id1].size() > m_adjList[id2].size();
        });

        int numC = 0;

        while (!vertex.empty()) {
            for (auto it = vertex.begin(); it != vertex.end(); it++) {
                if (isValidColor(*it, numC, m_color)) {
                    m_color[*it] = numC;
                    it = vertex.erase(it);
                }
            }
            numC++;
        }
    }

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

    void from_json(const json &j)
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
