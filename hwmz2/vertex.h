
#include <vector>

using namespace std;

// A helper class implementing a vertex in 
// an adjacency-list-based graph.
class Vertex
{
        public:
                Vertex(int r, int c)
                {
                        row = r;
                        col = c;
                        portal_len = 1000;
                        marked = false;
                        bc = nullptr;
                        dist = 100000; 
                        isportal = false;
                        iswall = false;
                }

                // Corresponding row and column location in maze
                int row;
                int col;
                bool marked;
                Vertex* bc;
                char c;
                int portal_len;
                int dist;
                bool isportal;
                bool iswall;



                // List of neighboring vertices
                vector< pair<Vertex*, int> > neighs;
};

