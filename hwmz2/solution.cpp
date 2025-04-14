#ifndef SOLVE_H
#define SOLVE_H

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <sstream>
#include "minpriorityqueue.h"
#include "vertex.h"

using namespace std;

// Forward declaration
void find_path(Vertex* start);

string solve(string maze) {
    vector<vector<Vertex>> grid;
    unordered_map<char, vector<Vertex*>> portal_map;
    vector<Vertex*> exits;
    vector<string> maze_rows;

    // Parse maze into rows and build grid
    istringstream stream(maze);
    string line;
    int row_idx = 0;
    while (getline(stream, line)) {
        maze_rows.push_back(line);
        vector<Vertex> current_row;
        int col_idx = 0;
        for (char ch : line) {


            Vertex v(row_idx, col_idx);

            v.c = ch;


            v.iswall = (ch == '#');


            if (isdigit(ch)) {
                v.isportal = true;
                v.portal_len = ch - '0';
            }
            current_row.push_back(v);
            col_idx++;
        }
        grid.push_back(current_row);
        row_idx++;
    }

    // Collect portals and exits
    for (auto& row : grid) {
        for (auto& v : row) {
            if (v.isportal) {
                portal_map[v.c].push_back(&v);
            }
            // Check if it's a border cell (exit)
            if (!v.iswall && (v.row == 0 || v.row == grid.size()-1 || 
                v.col == 0 || v.col == grid[v.row].size()-1)) {
                exits.push_back(&v);
            }
        }
    }

    // Connect portal pairs
    for (auto& pair : portal_map) {
        if (pair.second.size() == 2) {
            Vertex* a = pair.second[0];
            Vertex* b = pair.second[1];
            a->neighs.push_back({b, a->portal_len});
            b->neighs.push_back({a, b->portal_len});
        }
    }

    // Build neighbor connections
    for (int r = 0; r < grid.size(); ++r) {
        for (int c = 0; c < grid[r].size(); ++c) {
            Vertex& v = grid[r][c];
            if (v.iswall) continue;

            // Up
            if (r > 0 && !grid[r-1][c].iswall) 
                v.neighs.push_back({&grid[r-1][c], 1});
            
            // Down
            if (r < grid.size()-1 && !grid[r+1][c].iswall) 
                v.neighs.push_back({&grid[r+1][c], 1});
            
            // Left
            if (c > 0 && !grid[r][c-1].iswall) 
                v.neighs.push_back({&grid[r][c-1], 1});
            
            // Right
            if (c < grid[r].size()-1 && !grid[r][c+1].iswall) 
                v.neighs.push_back({&grid[r][c+1], 1});
        }
    }

    // Find shortest path from first exit to closest other exit
    if (exits.empty()) return maze;
    find_path(exits[0]);

    cout << exits[0] << endl;

    cout << exits[1] << endl;


    // Find exit with minimal distance
    Vertex* end = nullptr;
    int min_dist = 100000;
    for (Vertex* exit : exits) {
        if (exit != exits[0] && exit->dist < min_dist) {
            min_dist = exit->dist;
            end = exit;
        }
    }

    // Reconstruct path
    if (!end) return maze;
    
    // Reconstruct path and mark with 'o'
    Vertex* curr = end;
    while (curr) {
        // Only mark non-wall cells (spaces AND portals)
        if (maze_rows[curr->row][curr->col] != '#') {
            maze_rows[curr->row][curr->col] = 'o';
        }
        curr = curr->bc;
    }

    // Rebuild solution string
// Rebuild solution string WITH trailing newline for each line
    string solution;
    for (const auto& row : maze_rows) {
        solution += row + '\n';
    }
    // Remove the last '\n' if original maze didn't have it (optional)
    if (!maze.empty() && maze.back() != '\n') {
        solution.pop_back();
    }

    return solution;
}

void find_path(Vertex* start) {
    MinPriorityQueue<Vertex*> Q;
    start->dist = 0;
    Q.push(start, start->dist);

    while (Q.size() > 0) {
        Vertex* curr = Q.front();
        Q.pop();

        if (curr->marked) continue;
        curr->marked = true;

        for (auto& [neighbor, weight] : curr->neighs) {
            int new_dist = curr->dist + weight;
            if (new_dist < neighbor->dist) {
                neighbor->dist = new_dist;
                neighbor->bc = curr;
                Q.push(neighbor, new_dist);
            }
        }
    }
}

#endif