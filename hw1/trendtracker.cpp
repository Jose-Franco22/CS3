#include "trendtracker.h"

Trendtracker::Trendtracker(){
			vector<Entry> E; //O(1)
		};

		// Inserts a hashtag (tweeted 0 times) into the Trendtracker.
		// If the hashtag already is in Trendtracker, does nothing.
		//
		// Must run in O(n) time.

		//Time Complexity
		//O(1) + O(n) + O(1) + O(1) + O(1) --> O(n)

		void Trendtracker::insert(string ht){ 				 //O(1)

			//O(n)*( O(1) + O(1) ) --> O(n)*( O(1) ) --> O(n)

			for(int i = 0; i < E.size(); i++){ //O(n), n being E.size()
				if(E[i].hashtag == ht){			 //O(1)
					return;    					 //O(1)
				}
			}

			E.push_back({ht,0});				//O(1)

		};

		// Return the number of hashtags in the Trendtracker.
		//
		// Must run in O(1) time.

		//Time Complexity
		//O(1)

		int Trendtracker::size(){
			return E.size(); //O(1)
		};

		// Adds 1 to the total number times a hashtag has been tweeted.
		// If the hashtag does not exist in TrendTracker, does nothing.
		//
		// Must run in O(n) time.

		//Time Complexity
		//O(n)
		
		void Trendtracker::tweeted(string ht){

			//O(n)*( O(1) + O(1) + O(1) ) --> O(n)*( O(1) ) --> O(n)

			for (int i = 0; i < E.size(); i++) //O(n) 
			{
				if(E[i].hashtag == ht){ //O(1)
					E[i].pop++;			//O(1)
					return;				//O(1)
				}
			}
			
		};

		// Returns the number of times a hashtag has been tweeted.
		// If the hashtag does not exist in Trendtracker, returns -1.
		//
		// Must run in O(n) time.

		//Time Complexity
		//O(1) + O(n) * ( O(1) + O(1) )  + O(1) = O(n)

        int Trendtracker::popularity(string name) {
            for (int i = 0; i < E.size(); i++) { //O(n), n being E.size()
                
                if (E[i].hashtag == name) { //O(1)
                    return E[i].pop;		//O(1)
                }
            }
            return -1;						//O(1)
        }

		// Returns a most-tweeted hashtag.
		// If the Trendtracker has no hashtags, returns "".
		//
		// Must run in O(n) time.


		//Time Complexity
		//O(1) + O(1) + O(1) + O(n) * ( O(1) + O(1) )  + O(1) = O(n)

		string Trendtracker::top_trend(){

            if (E.empty()){ //O(1)
				return "";  //O(1)
			}; 

            Entry top = E[0];	//O(1)
            
            for (int i = 0;i<E.size(); i++) {	//O(n), n being E.size()
                if (E[i].pop > top.pop) {		//O(1)
                    top = E[i];					//O(1)
                }
            }
            
            return top.hashtag;					//O(1)
        };

        // Fills the provided vector with the 3 most-tweeted hashtags,
        // in order from most-tweeted to least-tweeted.
        //
        // If there are fewer than 3 hashtags, then the vector is filled
        // with all hashtags (in most-tweeted to least-tweeted order).
        //
        // Must run in O(n) time.

		//Time Complexity
		//O(n)

		void Trendtracker::top_three_trends(vector<string> &T){
    				
			T.clear();		//O(1)

    		if (E.empty()) {		//O(1)
        	return;					//O(1)
    		}

  
    		Entry first = {"", -1};		//O(1)
        	Entry second = {"", -1};	//O(1)
    		Entry third = {"", -1};		//O(1)

 
    		for (size_t i = 0; i < E.size(); ++i) {		//O(n)
        		if (E[i].pop > first.pop) {				//O(1)
            		third = second;						//O(1)
            		second = first;						//O(1)
            		first = E[i];						//O(1)
        		} 
				else if (E[i].pop > second.pop) {		//O(1)
            		third = second;						//O(1)
            		second = E[i];						//O(1)
        		} 
				else if (E[i].pop > third.pop) {		//O(1)
            		third = E[i];						//O(1)
        		}
    		}


    		if (first.pop != -1) T.push_back(first.hashtag);		//O(1)
    		if (second.pop != -1) T.push_back(second.hashtag);		//O(1)
    		if (third.pop != -1) T.push_back(third.hashtag);		//O(1)
		};


        // Remove the given hashtag from the trendtracker.
        //
        // Must run in O(n) time.

		//Time Complexity
		//O(n)

        void Trendtracker::remove(string ht) {
    		for (int i = 0; i < E.size(); ++i) {	//O(n)
        		if (E[i].hashtag == ht) {			//O(1)
            		E.erase(E.begin() + i);			//O(1)
            		return;							//O(1)
        		}	
    		}
		};
        
        // Fills the provided vector with the k most-tweeted hashtags,
        // in order from most-tweeted to least-tweeted.
        //
        // If there are fewer than k hashtags, then the vector is filled
        // with all hashtags (in most-tweeted to least-tweeted order).
        //
        // Must run in O(nk) time.

		//Time Complexity
		//O(nk)

	void Trendtracker::top_k_trends(vector<string> &T, int k) {
    
        T.clear();	//O(1)
        
    	if (E.empty()) {	//O(1)
        	return;	//O(1)
    	}

    	vector<Entry> temp = E; //O(1)

    	for (int i = 0; i < k && !temp.empty(); ++i) { //O(n)
     		int maxIndex = 0; //O(1)


        	for (int j = 1; j < temp.size(); ++j) {	//O(k)
            	if (temp[j].pop > temp[maxIndex].pop) { //O(1)

                	maxIndex = j; //O(1)
            	}
        	}

        	T.push_back(temp[maxIndex].hashtag);	//O(1) 
        	temp.erase(temp.begin() + maxIndex);	//O(1)
    	}
	};