#ifndef MINPRIORITYQUEUE_H
#define MINPRIORITYQUEUE_H

#include <unordered_map>
#include <vector>
#include <utility> // Has pair and swap

using namespace std;

template <typename T>
class MinPriorityQueue
{
    public:
        // Creates an empty MinPriorityQueue
        MinPriorityQueue()
        {
            // No initialization needed as vectors and unordered_maps
            // initialize themselves to empty
        }

        // Returns the number of elements in the MinPriorityQueue.
        int size()
        {
            return H.size();
        }    

        // Pushes a new value x with priority p into the MinPriorityQueue.
        void push(T x, int p)
        {
            // Add to end of heap
            H.emplace_back(x, p);
            // Record its index in the map
            I[x] = H.size() - 1;
            // Bubble up to maintain heap property
            bubble_up(H.size() - 1);
        }

        // Returns the value at the front of the MinPriorityQueue.
        T front()
        {
            return H[0].first;
        }

        // Removes the value at the front of the MinPriorityQueue.
        void pop()
        {
            if (H.empty()) return;
            
            // Remove from index map
            I.erase(H[0].first);
            
            if (H.size() > 1) {
                // Move last element to root
                H[0] = H.back();
                I[H[0].first] = 0;
            }
            
            // Remove last element
            H.pop_back();
            
            if (!H.empty()) {
                // Bubble down the new root
                bubble_down(0);
            }
        }

        // Changes the priority of x to new_p if current priority is at least new_p
        void decrease_key(T x, int new_p)
        {
            // Check if x exists and its current priority is >= new_p
            if (I.find(x) == I.end() || H[I[x]].second <= new_p) {
                return; // or we could throw an exception
            }
            
            int index = I[x];
            // Update the priority
            H[index].second = new_p;
            // Bubble up to maintain heap property
            bubble_up(index);
        }

    private:
        vector< pair<T, int> > H; // The heap.
        unordered_map<T, int> I;  // Maps values to their indices in H.
        
        // Helper function to maintain heap property by bubbling up
        void bubble_up(int index)
        {
            while (index > 0) {
                int parent = (index - 1) / 2;
                if (H[index].second >= H[parent].second) {
                    break;
                }
                // Swap with parent
                swap(H[index], H[parent]);
                // Update indices in map
                I[H[index].first] = index;
                I[H[parent].first] = parent;
                // Move up
                index = parent;
            }
        }
        
        // Helper function to maintain heap property by bubbling down
        void bubble_down(int index)
        {
            int left, right, smallest;
            while (true) {
                left = 2 * index + 1;
                right = 2 * index + 2;
                smallest = index;
                
                if (left < H.size() && H[left].second < H[smallest].second) {
                    smallest = left;
                }
                if (right < H.size() && H[right].second < H[smallest].second) {
                    smallest = right;
                }
                
                if (smallest == index) {
                    break;
                }
                
                // Swap with smallest child
                swap(H[index], H[smallest]);
                // Update indices in map
                I[H[index].first] = index;
                I[H[smallest].first] = smallest;
                // Move down
                index = smallest;
            }
        }
};

#endif