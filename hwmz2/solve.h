
    #ifndef SOLVE_H
    #define SOLVE_H

    #include <string>
    #include <unordered_set>
    #include "minpriorityqueue.h" // Includes <vector>, <unordered_map>, <utility>
    #include "vertex.h"
    #include <sstream>  


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
    //
    //
    // Returns a string representing a shortest solution to the maze.
    // Undefined behavior if the maze is not valid or has no solution.
    //
    // Must run in O(s*log(s)) time.


    void find_path(Vertex* start) {
        MinPriorityQueue<Vertex*> Q;
        start->dist = 0;
        Q.push(start, start->dist);
    
        while (Q.size() != 0) {
            Vertex* curr = Q.front();
            Q.pop();
    
            if (curr->marked) continue;
            curr->marked = true;
    
            for (size_t i = 0; i < curr->neighs.size(); i++) {
                Vertex* neighbor = curr->neighs[i].first;
                int weight = curr->neighs[i].second;
                int new_dist = curr->dist + weight;
    
                if (new_dist < neighbor->dist) {
                    neighbor->dist = new_dist;
                    neighbor->bc = curr;
                    Q.push(neighbor, new_dist);
                }
            }
        }
    }

string solve(string maze){
    vector<vector<Vertex>> grid;
    unordered_map <char, vector<Vertex*>> portal_map;
    vector<Vertex*> exits;
    vector<string> maze_rows;

    int row = 0;
    istringstream stream(maze);
    string line;
            
    while (getline(stream, line)) {
        maze_rows.push_back(line);
        vector<Vertex> current_row;
        int col = 0;
            
        for (char ch : line) {
            Vertex v(row, col);
            v.c = ch;
                    
            if (ch == '#') {
                v.iswall = true;
            }
                    
            if (isdigit(ch)) {
                v.isportal = true;
                v.portal_len = ch - '0';
            }

            current_row.push_back(v);
            col++;
        }
                
        grid.push_back(current_row);
        row++;
    }

    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[i].size(); ++j) {
            Vertex& v = grid[i][j];
            if (v.isportal) {
                portal_map[v.c].push_back(&v);
            }
                    
            if (!v.iswall && (v.row == 0 || v.row == grid.size()-1 || v.col == 0 || v.col == grid[i].size()-1)) {
                exits.push_back(&v);
            }
        }
    }

    if(!portal_map.empty()){
        for (auto& [ch, vec] : portal_map) {
            Vertex* a = vec[0];
            Vertex* b = vec[1];
        
            a->neighs.push_back({b,b->portal_len});
            b->neighs.push_back({a,a->portal_len});
        }
    }

    for (int r = 0; r < grid.size(); r++) {
        for (int c = 0; c < grid[r].size(); c++) {
            Vertex& v = grid[r][c];
            if (v.iswall) continue;

            if (r > 0 && !grid[r-1][c].iswall) 
                v.neighs.push_back({&grid[r-1][c], 1});
            
            if (r < grid.size()-1 && !grid[r+1][c].iswall) 
                v.neighs.push_back({&grid[r+1][c], 1});
            
            if (c > 0 && !grid[r][c-1].iswall) 
                v.neighs.push_back({&grid[r][c-1], 1});
            
            if (c < grid[r].size()-1 && !grid[r][c+1].iswall) 
                v.neighs.push_back({&grid[r][c+1], 1});
        }
    }

    if(exits.empty()){
        return maze;
    }
        
    find_path(exits[0]);

    Vertex* end = nullptr;
    int min_dist = 100000;

    for(int i=0; i<exits.size(); i++){
        if(exits[i] != exits[0] && exits[i]->dist < min_dist){
            min_dist = exits[i]->dist;
            end = exits[i];
        }
    }

    Vertex* curr = end;
    while (curr) {
        if (maze_rows[curr->row][curr->col] != '#') {
            maze_rows[curr->row][curr->col] = 'o';
        }
        curr = curr->bc;
    }

    string solution;
    for (const auto& row : maze_rows) {
        solution += row + "\n";
    }
    if (!maze.empty() && maze.back() != '\n') {
        solution.pop_back();
    }

    return solution;
}

#endif

