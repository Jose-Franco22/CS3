#include "trendtracker.h"


        Trendtracker::Trendtracker(string filename){
            
            
            Entry x;
            ifstream file(filename);
            if (!file) {
                return;
            }

            string hashtag;
            while (getline(file, hashtag)) {

                x.hashtag = hashtag;
                x.pop = 0;
                E.push_back(x);
            }

            file.close();
        };


        int Trendtracker::size(){
            return E.size();
        };

		// Adds 1 to the total number times a hashtag has been tweeted.
		// If the hashtag does not exist in TrendTracker, does nothing.
		//
		// Must run in O(log(n)) time.

        void Trendtracker::tweeted(string ht){  
            int x = search(ht);
            E[x].pop += 1;
        };

        // Returns the number of times a hashtag has been tweeted.
		// If the hashtag does not exist in Trendtracker, returns -1.
		//
		// Must run in O(log(n)) time.

        int Trendtracker::popularity(string name){

            int x = search(name);

            if(x > 0)
            return E[x].pop;

            return -1;

        };


        string Trendtracker::top_trend(){
            return E[S[0]].hashtag;
        };



        void Trendtracker::top_three_trends(vector<string> &T){
            for(int i = 0;i<S.size();i++){
                T[i] = E[S[i]].hashtag;
            }
        };


		// Optional helper method.
		// Returns the index of E containing an Entry with hashtag ht.
		// If no such hashtag is found, returns -1.
		//
		// Should run in O(log(n)).


        int Trendtracker::search(string ht){


            int m;
            int start = 0;
            int end = E.size()-1;

            while(start <= end){
                m = start + (start + end) / 2;

                if(E[m].hashtag == ht){
                   return m;
                }

                else if( E[m].hashtag < ht){
                   start = m+1;
                }

                else    {
                    end = m-1;
                }
            
            };

            return -1;
        };