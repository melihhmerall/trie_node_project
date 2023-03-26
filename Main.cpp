
#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;
vector<string> split (const string &s, char delim) {
    vector<string> result;
    stringstream ss (s);
    string item;

    while (getline (ss, item, delim)) {
        result.push_back (item);
    }

    return result;
}
struct node
{
    int prefix_count;
    bool isEnd;
    struct node *child[26];
}*head;
void init()
{
    head = new node();
    head->isEnd = false;
    head->prefix_count = 0;
}
void insert_trie(string word)
{
    node *current = head;
    current->prefix_count++;

    for(int i = 0 ; i < word.length(); ++i)
    {
        int letter = (int)word[i] - (int)'a';
        if(current->child[letter] == NULL)
            current->child[letter] = new node();

        current->child[letter]->prefix_count++;
        current = current->child[letter];
    }
    current->isEnd = true;
}
void delete_trie(string word){
    node *current = head;
    for (int i = 0; i < word.length(); ++i) {
        int letter = (int)word[i] - (int)'a';
        if (current->child[letter] != NULL) {
            current = current->child[letter] ;
        }
    }
    current->isEnd = false;

}
bool search_trie(string word)
{
    node *current = head;
    for(int i = 0 ; i < word.length(); ++i)
    {
        int letter = (int)word[i] - (int)'a';
        if(current->child[letter] == NULL)
            return false;		//not found
        current = current->child[letter];
    }
    return current->isEnd;
}
int search_prefix(string word){
    node *current = head;
    for(int i = 0; i < word.length() ; ++i)
    {
        int letter = (int)word[i] - (int)'a';
        if(current->child[letter] == NULL)
            return 0;
        else
            current = current->child[letter];
    }
    return current->prefix_count;
}

int main(int argc, char* argv[]) {
    init();
    vector<string> vectors;
    vector<string> vectors2;
    vector<string> insert_vectors;
    vector<string> search_vectors;
    fstream input1;
    input1.open(argv[1], ios::in);
    string line;
    while (getline(input1, line)) {
        vectors.push_back(line);

    }
    input1.close();
    ofstream myfile;
    myfile.open(argv[2]);
    for (int i = 0; i < vectors.size(); ++i) {
        stringstream ss (vectors[i]);
        string item;
        while (getline (ss, item, '(')) {
            vectors2.push_back (item);
        }
    }
    for (int i = 0; i < vectors2.size(); ++i) {
        if (vectors2[i] == "insert") {
            vectors2[i + 1].pop_back();
            stringstream ss(vectors2[i + 1]);
            string item;
            while (getline(ss, item, ',')) {
                insert_vectors.push_back(item);
                char couter = '"';
                if (search_trie(item)==true){
                    myfile <<couter <<  item <<couter << " already exist"<< endl;
                }
            }
            for (int j = 0; j < insert_vectors.size(); j = j+2) {
                string melih = insert_vectors[j];


                char couter = '"';
                if (search_trie(melih)== false){
                    insert_trie(melih);
                    myfile << couter <<melih <<couter <<  " was added"<< endl;
                }
                else if (search_trie(melih)== true) {
                    for (int k = 0; k <insert_vectors.size() ; ++k) {
                         if (melih == insert_vectors[k]&& insert_vectors[j+1] != insert_vectors[k+1]){
                            insert_vectors[j+1] = insert_vectors[k+1];
                             myfile << couter <<melih <<couter <<  " was updated"<< endl;
                         }
                    }
                }
            }
        } else if (vectors2[i] == "search"){

            vectors2[i + 1].pop_back();
            stringstream ss(vectors2[i + 1]);
            string item;
            while (getline(ss, item)) {
                char couter = '"';
                search_vectors.push_back(item);
                if (search_trie(item)== true){
                    for (int j = 0; j < insert_vectors.size(); ++j) {
                        if (item == insert_vectors[j]){
                            myfile << couter << "The English equivalent is "<< insert_vectors[j+1] <<couter << endl;
                        }
                    }
                }
                 else if (search_prefix(item) == true)
                {
                    myfile << couter <<"not enough Dothraki word"<<couter << endl;
                }
                else if (search_trie(item) == false){
                    string prefix(1,item[0]);
                    if (search_prefix(prefix) == false) {
                        myfile << couter <<"no record"<<couter << endl;
                    }
                    else{
                        myfile << couter <<"incorrect Dothraki word"<<couter << endl;
                    }
                }
            }
            for (int k = 0; k < search_vectors.size(); ++k) {
                string melih = search_vectors[k];
                char couter = '"';
            }

        }
        else if (vectors2[i] == "delete"){
            vectors2[i + 1].pop_back();
            stringstream ss(vectors2[i + 1]);
            string item;
            char couter = '"';
            while (getline(ss, item)) {
                if (search_trie(item) == true){
                    delete_trie(item);
                    myfile << couter << item << couter << " deletion is successful" << endl;
                }  else if (search_prefix(item) == true){
                    myfile << couter <<"not enough Dothraki word"<<couter << endl;
                }else if (search_prefix(item)){
                    myfile << couter <<"not enough Dothraki word"<<couter << endl;
                }
                else if (search_trie(item) == false){
                    string prefix(1,item[0]);
                    if (search_prefix(prefix) == false) {
                        myfile << couter <<"no record"<<couter  << endl;
                    }
                    else{
                        myfile << couter <<"incorrect Dothraki word"<<couter << endl;
                    }
                }
            }
        }
    }
    return 0;
}
