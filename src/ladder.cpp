#include <iostream>
#include <fstream>
#include <queue>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <cmath>
#include "ladder.h"
#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}

using namespace std;

void error(string word1, string word2, string msg){
    cout << word1 << word2 << msg << endl;
}
bool edit_distance_within(const string& str1, const std::string& str2, int d){
    int len1 = str1.size();
    int len2 = str2.size();
    if(abs(len2 - len1) > d) { return false; }
    vector<vector<int>> table(len1 + 1, vector<int>(len2 + 1));
    
    if(len1 == len2){
        int distance = 0;
        for(int i = 0; i < len1; ++i){
            if(str1[i] != str2[i]){
                ++distance;
                if(distance > d){
                    return false;
                }
            }
        }
        return distance <= d;
    }

    else if(abs(len1 - len2) == 1){
        const string& longer_word = len1 > len2 ? str1 : str2;
        const string& shorter_word = len1 < len2 ? str1 : str2;

        int shorter_size = shorter_word.size();
        int longer_size = longer_word.size();
        int distance = 0;
        int i = 0;
        int j = 0;
        while(i < shorter_size && j < longer_size){
            if(shorter_word[i] != longer_word[j]){
                ++distance;
                if(distance > d){ return false; }
                ++j; //move to next char in longer str only
            }
            else{ ++i; ++j; }
        }
        return distance <= d;
    }

    return false;
}
bool is_adjacent(const string& word1, const string& word2){
    return edit_distance_within(word1, word2, 1);
}
vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list){
    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});
    set<string> visited;
    visited.insert(begin_word);
    if(word_list.find(end_word) == word_list.end()){ return {}; }
    else if(end_word == begin_word) { return {}; }
    while(!ladder_queue.empty()){
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = ladder.back();
        for(string word : word_list){
            if(is_adjacent(last_word, word)){
                if(visited.find(word) == visited.end()){
                    visited.insert(word);
                    vector<string> new_ladder = ladder;
                    new_ladder.push_back(word);
                    if(word == end_word){
                        return new_ladder;
                    }
                    ladder_queue.push(new_ladder);
                }
            }
        }
    }
    return {};
}
void load_words(set<string> & word_list, const string& file_name){
    ifstream in(file_name);
    if (!in) {
        throw runtime_error("Can't open input file");
    }
    string word;
    while(in >> word){ word_list.insert(word); }
    in.close();
}
void print_word_ladder(const vector<string>& ladder){
    if(!ladder.empty()){
        cout << "Word ladder found: ";
        for(string word : ladder){
            cout << word << " ";
        }
        cout << endl;
    }
    else{
        cout << "No word ladder found." << endl;
    }
}
void verify_word_ladder(){
    set<string> word_list;
    load_words(word_list, "words.txt");
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}