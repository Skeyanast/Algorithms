#include <Windows.h>
#include <iostream>
#include <vector>
#include <string>
#include <conio.h>

using namespace std;

string encrypt(string& input) {
    vector<char> word(input.begin(), input.end());
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    string alphabet1 = "goydsipeluavcrjwxznhbqftmk";

    for (int i = 0; i < word.size(); i++) {
        for (int j = 0; j < (int)alphabet.length(); j++) {
            if (word[i] == alphabet[j]) {
                word[i] = alphabet1[j % 26];
                break;
            }
        }
    }

    string str(word.begin(), word.end());
    return str;
}

string decrypt(string& input) {
    vector<char> word(input.begin(), input.end());
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    string alphabet1 = "goydsipeluavcrjwxznhbqftmk";

    for (int i = 0; i < word.size(); i++) {
        for (int j = 0; j < (int)alphabet.length(); j++) {
            if (word[i] == alphabet1[j]) {
                word[i] = alphabet[j % 26];
                break;
            }
        }
    }

    string str(word.begin(), word.end());
    return str;
}

int main() {

    string text;
    getline(cin, text);

    text = encrypt(text);
    cout << text<< endl;

    text = decrypt(text);
    cout << text << endl;


    return 0;
}