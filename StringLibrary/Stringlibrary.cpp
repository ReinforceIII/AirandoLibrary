#include "Stringlibrary.h"
#include <algorithm>
#include <stack>
#include <queue>
constexpr int MOD = 987654323;
constexpr int CNT = 26;
constexpr int mod(long n) {
	if (n >= 0) return n % MOD;
	else return ((-n / MOD + 1)*MOD + n) % MOD;
}

vector<int> StringLibrary::GetPIArray(const string & pattern) {
	int size = pattern.length();
	int following_index = 0;
	vector<int> pi(size, 0);
	for (int i = 1; i < size; i++) {
		while (following_index > 0 && pattern[i] != pattern[following_index]) following_index = pi[following_index - 1];
		if (pattern[i] == pattern[following_index]) pi[i] = ++following_index;
	}
	return pi;
}

vector<int> StringLibrary::SearchWordWithKMP(const string & text, const string & pattern) {
	vector<int> answer;
	vector<int> pi = StringLibrary::GetPIArray(pattern);
	int text_size = text.length();
	int pattern_size = pattern.length();
	int pattern_index = 0;
	for (int i = 0; i < text_size; i++) {
		while (pattern_index > 0 && text[i] != pattern[pattern_index]) pattern_index = pi[pattern_index - 1];
		if (text[i] == pattern[pattern_index]) {
			if (pattern_index == pattern_size - 1) {		//pattern all match
				answer.push_back(i - pattern_size + 1);
				pattern_index = pi[pattern_index - 1];
			}
			else pattern_index++;							//not yet
		}
	}
	return answer;
}

vector<int> StringLibrary::SearchWordWithRabinCarp(const string & text, const string & pattern) {
	vector<int> answer;
	int text_size = text.length();
	int pattern_size = pattern.length();
	if (text_size < pattern_size) return answer;

	long pattern_hash = 0;
	long text_hash = 0;	
	long power = 1;
	for (int i = 0; i <= text_size - pattern_size; i++) {
		if (i == 0) {
			for (int j = 0; j < pattern_size; j++) {
				pattern_hash = mod(pattern_hash + (long)pattern[pattern_size - 1 - j] * power);
				text_hash = mod(text_hash + (long)text[pattern_size - 1 - j] * power);
				if (j < pattern_size - 1) power = mod(power * CNT);
			}
		}
		else text_hash = mod(CNT*(text_hash - (long)text[i-1]*power) + (long)text[i+pattern_size-1]);

		if (text_hash == pattern_hash) {
			string subtext = text.substr(i, pattern_size);
			if (subtext == pattern) answer.push_back(i);
		}
	}
	return answer;
}

vector<vector<int>> StringLibrary::GetPalindromicSubsequenceMemo(const string & text) {
	int size = text.length();
	vector<vector<int>> memo(size, vector<int>(size,0));
	for (int i = 0; i < size; i++) memo[i][i] = 1;
	for (int interval = 1; interval <= size; interval++) {
		for (int start = 0; start < size - interval; start++) {
			int end = start + interval;
			if (text[start] == text[end]) memo[start][end] = memo[start + 1][end - 1] + 2;
			else memo[start][end] = max(memo[start + 1][end], memo[start][end - 1]);
		}
	}
	return memo;
}

int StringLibrary::GetLongestPalindromicSubsequenceLength(const string & text) {
	vector<vector<int>> memo = StringLibrary::GetPalindromicSubsequenceMemo(text);
	return memo[0][text.length()-1];
}

string StringLibrary::GetLongestPalindromicSubsequences(const string & text) {
	vector<vector<int>> memo = StringLibrary::GetPalindromicSubsequenceMemo(text);
	string front = "";
	string back = "";
	int start = 0;
	int end = text.length() - 1;
	while (start <= end) {
		if (text[start] == text[end]) {
			front += text[start];
			if (memo[start][end] != 1) back += text[end];
			start++;
			end--;
		}
		else {
			if (memo[start + 1][end] >= memo[start][end - 1]) start++;
			else end--;
		}
	}
	reverse(back.begin(), back.end());
	string answer = front+back;
	return answer;
}

string StringLibrary::GetLongestCommonSubsequence(const string & s1, const string & s2) {
	const string str1 = '0' + s1;
	const string str2 = '0' + s2;
	vector<vector<int>> memo(str1.size(), vector<int>(str2.size(), 0));
	for (size_t i = 1; i < str1.length(); i++) {
		for (size_t j = 1; j < str2.length(); j++) {
			if (str1[i] == str2[j]) memo[i][j] = memo[i - 1][j - 1] + 1;
			else memo[i][j] = max(memo[i - 1][j], memo[i][j - 1]);
		}
	}
	stack<int> wordstack;
	int one_index = str1.length() - 1;
	int two_index = str2.length() - 1;
	while (memo[one_index][two_index] != 0) {
		if (memo[one_index][two_index] == memo[one_index][two_index-1]) two_index--;
		else if (memo[one_index][two_index] == memo[one_index-1][two_index]) one_index--;
		else if (memo[one_index][two_index] - 1 == memo[one_index - 1][two_index - 1]) {
			wordstack.push(one_index);
			one_index--;
			two_index--;
		}
	}
	string answer = "";
	while (!wordstack.empty()) {
		answer += str1[wordstack.top()];
		wordstack.pop();
	}
	return answer;
}

int StringLibrary::GetMinimumEditDistance(const string & s1, const string & s2) {
	const string str1 = '0' + s1;
	const string str2 = '0' + s2;
	vector<vector<int>> memo(str1.length(), vector<int>(str2.length(), 0));
	for (size_t i = 1; i < str1.length(); i++) memo[i][0] = i;
	for (size_t i = 1; i < str2.length(); i++) memo[0][i] = i;

	for (size_t i = 1; i < str1.length(); i++) {
		for (size_t j = 1; j < str2.length(); j++) {
			if (str1[i] == str2[j]) memo[i][j] = memo[i - 1][j - 1];
			else memo[i][j] = min(min(memo[i][j - 1], memo[i - 1][j]), memo[i - 1][j - 1]) + 1;
		}
	}
	return memo[str1.length()-1][str2.length()-1];
}

unordered_map<char, int> StringLibrary::HuffmanEncoding::MakeFreqList(const string& text) {
	unordered_map<char, int> freq;
	for (int i = 0; i < text.size(); i++) freq[text[i]]++;
	return freq;
}

void StringLibrary::HuffmanEncoding::MakeEncodingTree(const string& text) {
	//make freq_list & priority_queue
	unordered_map<char, int> freq_list = MakeFreqList(text);
	if (freq_list.empty()) return;
	priority_queue<Node*, vector<Node*>, StringLibrary::HuffmanEncoding::freq_compare> pq;
	for (auto iter = freq_list.begin(); iter != freq_list.end(); iter++) {
		Node* temp = new Node(iter->first, iter->second);
		pq.push(temp);
	}

	//construct tree
	while (true) {
		Node* left_node = pq.top(); pq.pop();
		Node* right_node = pq.top(); pq.pop();
		encoding_tree_ = new Node('.', left_node->freq_ + right_node->freq_);
		encoding_tree_->left_ = left_node;
		encoding_tree_->right_ = right_node;

		if (pq.empty()) return;
		pq.push(encoding_tree_);
	}
}

void StringLibrary::HuffmanEncoding::MakeLetterTable(unordered_map<char, string>& table, Node * now, string code) {
	if (now->left_ != nullptr) {
		code += '0';
		MakeLetterTable(table, now->left_, code);
		code.erase(code.length() - 1);
	}
	if (now->right_ != nullptr) {
		code += '1';
		MakeLetterTable(table, now->right_, code);
		code.erase(code.length() - 1);
	}
	if (now->left_ == nullptr && now->right_ == nullptr) {
		table[now->letter_] = code;
	}
}

void StringLibrary::HuffmanEncoding::Encode(string text) {
	MakeEncodingTree(text);
	unordered_map<char, string> letter_table;
	string code = "";
	MakeLetterTable(letter_table, encoding_tree_, code);
	for (int i = 0; i < text.length(); i++) {
		encoded_text_ += letter_table.find(text[i])->second;
	}
}

string StringLibrary::HuffmanEncoding::Decode() {
	string answer = "";
	Node* root = encoding_tree_;
	Node* tracking = encoding_tree_;
	for (int i = 0; i < encoded_text_.length(); i++) {
		if (encoded_text_[i] == '0') {
			tracking = tracking->left_;
		}
		else if (encoded_text_[i] == '1') {
			tracking = tracking->right_;
		}
		if (tracking->left_ == nullptr && tracking->right_ == nullptr) {
			answer += tracking->letter_;
			tracking = root;
		}
	}
	return answer;
}
