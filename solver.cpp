/*  written by Lance Mendenhall   7/21/24  */

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>

std::map<char,int> mymap;
std::vector<std::string> myvec;

void print_remaining_words() {
	for(std::string x:myvec) {
		std::cout << x << std::endl;
	}
}

void countletters() {
	mymap.clear();
	// char mychar;
	for(std::string x:myvec) {
		for(char mychar:x) {
			// std::cout << mychar << std::endl; 
			if(mymap.count(mychar)) {
				mymap[mychar] += 1;
			}
			else {
				mymap[mychar] = 1;
			}
		}
	}
}

void removeLetter() {
	std::vector<std::string> temp_vec;
	char x;
	std::cout << "Enter the letter you want to remove" << std::endl;
	std::cin >> x;
	for (std::string mystr: myvec) {
		if(mystr.find(x) == std::string::npos) {
			temp_vec.push_back(mystr);
		}
	}
	myvec = temp_vec;
}

void keepLetter() {
	std::vector<std::string> temp_vec;
	char x;
	std::cout << "Enter the letter you want to keep" << std::endl;
	std::cin >> x;
	for (std::string mystr: myvec) {
		if(mystr.find(x) != std::string::npos) {
			temp_vec.push_back(mystr);
		}
	}
	myvec = temp_vec;
}

void keepLetterInPlace() {
	std::vector<std::string> temp_vec;
	char x;
	int i;
	std::cout << "Enter the letter you want to keep" << std::endl;
	std::cin >> x;
	std::cout << "What place should it be in?" << std::endl;
	std::cin >> i;
	for (std::string mystr: myvec) {
		if(mystr[i-1] == x) {
			temp_vec.push_back(mystr);
		}
	}
	myvec = temp_vec;
}

void removeLetterInPlace() {
	std::vector<std::string> temp_vec;
	char x;
	int i;
	std::cout << "Enter the letter you want to remove" << std::endl;
	std::cin >> x;
	std::cout << "What place should it be in?" << std::endl;
	std::cin >> i;
	for (std::string mystr: myvec) {
		if(mystr[i-1] != x) {
			temp_vec.push_back(mystr);
		}
	}
	myvec = temp_vec;
}

std::string findBestWord() {
	int biggestTotal = 0;
	std::string retval = "a";
	for(std::string word: myvec) {
		//std::string actual_word = word;
		std::string no_dups = "";
		int total = 0;
		for(char mychar: word) {
			if(no_dups.find(mychar) == std::string::npos) {
				no_dups += mychar;
				total += mymap[mychar];
			}
		}
		if(total > biggestTotal) {
			retval = word;
			biggestTotal = total;
		}
	}
	return retval;
}

void keepMultiples() {
	std::vector<std::string> temp_vec;
	int count;
	char mychar;
	std::cout << "Enter the letter you want to keep duplicates of" << std::endl;
	std::cin >> mychar;
	for(std::string word:myvec) {
		count = 0;
		for(int i = 0;i<word.length();i++) {
			if(word[i] == mychar) {
				count++;
			}
		}
		if(count > 1) {
			temp_vec.push_back(word);
		}
	}
	myvec = temp_vec;
}

int main() {

	std::string myline;

	std::ifstream words("wordlist.txt");

	if(words.is_open()) {
		while(words >> myline) {
			myvec.push_back(myline);
		}
	}
	words.close();

bool notFinished = true;
std::string input;
char inputChar;

while(notFinished) {
	countletters();
	std::string best_word = findBestWord();
	std::cout << "\nBest word: " << best_word << std::endl;

	std::cout << "There are " << myvec.size() << " words left." << std::endl;

	std::cout << "\nYou can:" << std::endl;
	std::cout << "r remove all words with a letter" << std::endl;
	std::cout << "s remove all words with a letter in a specific place" << std::endl;
	std::cout << "k keep words containing a certain letter" << std::endl;
	std::cout << "p keep words with a letter in a certain place" << std::endl;
	std::cout << "m keep words with a multiple of a letter" << std::endl;
	std::cout << "l list all remaining words" << std::endl;
	std::cout << "q quit" << std::endl;
	std::cout << "" << std::endl;

	std::cout << "What do you want to do?" << std::endl;
	std::cin >> input;
	inputChar = input[0];

	switch (inputChar)
		{
		case 'q':
			std::cout << "Thanks for playing!" << std::endl;
			notFinished = false;
			break;
		case 'l':
			print_remaining_words();
			break;
		case 'r':
			removeLetter();
			break;
		case 'k':
			keepLetter();
			break;
		case 'p':
			keepLetterInPlace();
			break;
		case 's':
			removeLetterInPlace();
			break;
		case 'm':
			keepMultiples();
			break;

		default:
			std::cout << "Enter a valid choice." << std::endl;
			break;
		}

	}
	return 0;
}