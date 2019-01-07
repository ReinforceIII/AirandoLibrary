//String Tokenizer
//void Tokenize : save in Parameter(tokenVector)
//vector<string> Tokenize : return tokenVector

#include <string>
#include <vector>

using namespace std;

void Tokenize(const string& str, vector<string>& tokenVector, const string& delimiter) {
   tokenVector.clear();
   //find_first_not_of -> return type : string::size_t
   auto start = str.find_first_not_of(delimiter, 0);
   auto last = str.find_first_of(delimiter, start);

   while (last != string::npos || start != std::string::npos) {
	tokenVector.push_back(str.substr(start, last - start));
	start = str.find_first_not_of(delimiter, last);
	last = str.find_first_of(delimiter, start);
   }
}

vector<string> Tokenize(const string& str, const string& delimiter) {
    vector<string> tokenVector;
    auto start = str.find_first_not_of(delimiter,0);
    auto last = str.find_first_of(delimiter,start);

    while (last != string::npos || start != std::string::npos) {
        tokenVector.push_back(str.substr(start, last - start));
	    start = str.find_first_not_of(delimiter, last);
	    last = str.find_first_of(delimiter, start);
    }
}