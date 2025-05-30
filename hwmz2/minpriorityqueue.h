
#ifndef MINPRIORITYQUEUE_H
#define MINPRIORITYQUEUE_H

// NOTE: You may not include any other libraries!
#include <unordered_map>
#include <vector>
#include <utility> // Has pair and swap

using namespace std;

template <typename T>
class MinPriorityQueue
{
	// For the mandatory running times below:
	//
	// n is the number of strings in the MinPriorityQueue.
	//
	// Assume the operations of map are O(1) time 
	// (they are average case, but not worst-case).

	public:
		// Creates an empty MinPriorityQueue
		MinPriorityQueue()
		{
			H.clear();
			I.clear();
		}

		// Returns the number of elements in the MinPriorityQueue.
		//
		// Must run in O(1) time.
		int size()
		{
			return H.size();
		}	

		// Pushes a new element x with priority p
		// into the MinPriorityQueue.
		//
		// Must run in O(log(n)) time. 
		void push(T x, int p)
		{
			H.emplace_back(x,p);
			I[x] = H.size() - 1;
			bubbleup(H.size()-1);
		}

		// Returns the string at the front of the MinPriorityQueue.
		// Undefined behavior if the MinPriorityQueue is empty.
		// 
		// Must run in O(1) time.
		T front()
		{
			return H[0].first;
		}

		// Removes the string at the front of the MinPriorityQueue.
		// Undefined behavior if the MinPriorityQueue is empty.
		//
		// Must run in O(log(n)) time. 
		void pop()
		{	
			if(H.empty()){
				return;
			}
			
			I.erase(H[0].first);

			if(H.size() > 1){
				swap(H[0],H.back());
				I[H[0].first] = 0;
			}

			H.pop_back();
			
			if(!H.empty()){
				bubbledown(0);
			}
		}

		// If x is in the MinPriorityQueue 
		// with current priority at least new_p,  
		// then changes the priority of x to new_p.
		// Undefined behavior otherwise.
		//
		// Must run in O(log(n)) time. 
		void decrease_key(T x, int new_p)
		{
			if(H[I[x]].second <= new_p){
				return;
			}

			H[I[x]].second = new_p;
			bubbleup(I[x]);
		}

	private:
		// You don't need any other instance variables,
		// but you can add some if you want to.
		unordered_map<T, int> I; // Maps elements to indices in H.
		vector< pair<T, int> > H;     // The array containing the heap.


		int left_c(int i){
			return (i*2)+1;
		}


		int right_c(int i){
			return left_c(i)+1;
		}


		int parent(int i){
			return (i - 1) / 2;
		}

		void swapper(int a, int b){
			swap(H[a], H[b]);
            I[H[a].first] = a;
            I[H[b].first] = b;
		}

		void bubbleup(int i){
			if(i == 0){
				return;
			}

			int par = parent(i);

			if(H[par].second > H[i].second){
				swapper(i,par);
				bubbleup(par);
			}

		}

		void bubbledown(int i){
			int l = left_c(i);
			int r = right_c(i);
			int smallest = i;

			if(l < H.size() && H[i].second > H[l].second){
				smallest = l;
			}

			if(r < H.size() && H[i].second > H[r].second){
				smallest = r;
			}	

			if (smallest != i){
                swapper(i, smallest);
                bubbledown(smallest);
            }
		}
};

#endif 

