#pragma once

#include <string>
#include <vector>
#include <unordered_map>
using namespace std;
typedef pair<char, int> letter_freq;

namespace StringLibrary {
	vector<int> GetPIArray(const string& pattern);
	vector<int> SearchWordWithKMP(const string& text, const string& pattern);
	vector<int> SearchWordWithRabinCarp(const string& text, const string& pattern);
	vector<vector<int>> GetPalindromicSubsequenceMemo(const string& text);
	int GetLongestPalindromicSubsequenceLength(const string& text);
	string GetLongestPalindromicSubsequences(const string& text);
	string GetLongestCommonSubsequence(const string& s1, const string& s2);
	int GetMinimumEditDistance(const string& s1, const string& s2);
	
	class HuffmanEncoding {
	private:
		class Node {
		public:
			int freq_;
			char letter_;
			Node* left_;
			Node* right_;
			Node(char letter, int freq) {
				letter_ = letter;
				freq_ = freq;
				left_ = right_ = nullptr;
			}
			~Node() {
				delete left_;
				delete right_;
			}
		};

		string encoded_text_ = "";
		Node* encoding_tree_ = nullptr;

		unordered_map<char,int> MakeFreqList(const string& text);
		void MakeEncodingTree(const string& text);
		void MakeLetterTable(unordered_map<char, string>& table, Node* now,string code);
	public:
		struct freq_compare {
			bool operator()(const Node* lhs, const Node* rhs) {
				return lhs->freq_ > rhs->freq_;
			}
		};
		HuffmanEncoding() {}
		~HuffmanEncoding() {
			delete encoding_tree_;
		}
		void Encode(string text);
		string GetEncodedText() { return encoded_text_; }
		string Decode();
	};
}