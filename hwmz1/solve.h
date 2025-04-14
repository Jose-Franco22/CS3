#ifndef SOLVE_H
#define SOLVE_H

#include <vector>
#include <string>
#include <unordered_set>
#include <queue>
#include <unordered_map>

using namespace std;

// For the mandatory running time, assume that the time for
// operations of queue, unordered_set, and map are O(1). 
// (They are for average-case, but not worst-case).
//
// For the mandatory running time below, s is the length of 
// the input string representing the maze.
// 
// For a complete description of the maze string 
// and maze solution formats, see the assignment pdf.


// Returns a string representing a shortest solution to the maze.
// Has undefined behavior if the maze is not valid or has no solution.
//
// Must run in O(s) time.

string solve(string maze){
    vector<vector<char>> grid;
    vector<char> current_row;
    for (char c : maze) {
        if (c == '\n') {
            if (!current_row.empty()) {
                grid.push_back(current_row);
                current_row.clear();
            }
        } else {
            current_row.push_back(c);
        }
    }
    if (!current_row.empty()) {
        grid.push_back(current_row);
    }

    if (grid.empty()) return maze;

    int rows = grid.size();
    int cols = grid[0].size();

    vector<pair<int, int>> entrances;
    
    for (int c = 0; c < cols; c++) {
        if (grid[0][c] == ' ') entrances.emplace_back(0, c);
        if (rows > 1 && grid[rows-1][c] == ' ') entrances.emplace_back(rows-1, c);
    }
    
    for (int r = 1; r < rows-1; r++) {
        if (grid[r][0] == ' ') entrances.emplace_back(r, 0);
        if (cols > 1 && grid[r][cols-1] == ' ') entrances.emplace_back(r, cols-1);
    }

    if (entrances.empty()) return maze;

    for (auto [start_row, start_col] : entrances) {
        
        queue<pair<int, int>> q;
        unordered_map<int, unordered_map<int, bool>> visited;
        unordered_map<int, unordered_map<int, pair<int, int>>> parent;

        q.push({start_row, start_col});
        visited[start_row][start_col] = true;
        parent[start_row][start_col] = {-1, -1};

     
        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};

        bool exit_found = false;
        int exit_row = -1, exit_col = -1;

        while (!q.empty() && !exit_found) {
            auto current = q.front();
            q.pop();
            int r = current.first;
            int c = current.second;

        
            if ((r == 0 || r == rows-1 || c == 0 || c == cols-1) && 
                (r != start_row || c != start_col)) {
                exit_row = r;
                exit_col = c;
                exit_found = true;
                break;
            }

            for (int i = 0; i < 4; i++) {
                int nr = r + dr[i];
                int nc = c + dc[i];

                if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && 
                    grid[nr][nc] == ' ' && !visited[nr][nc]) {
                    visited[nr][nc] = true;
                    parent[nr][nc] = {r, c};
                    q.push({nr, nc});
                }
            }
        }

        if (exit_found) {

            vector<pair<int, int>> path;
            int r = exit_row, c = exit_col;
            while (r != -1 && c != -1) {
                path.push_back({r, c});
                auto p = parent[r][c];
                r = p.first;
                c = p.second;
            }

            string result = maze;
            int current_row = 0;
            int current_col = 0;
            for (int i = 0; i < result.size(); i++) {
                if (result[i] == '\n') {
                    current_row++;
                    current_col = 0;
                    continue;
                }

                for (auto pos : path) {
                    if (current_row == pos.first && current_col == pos.second) {
                        result[i] = 'o';
                        break;
                    }
                }
                current_col++;
            }
            return result;
        }
    }

    return maze;
}

#endif 