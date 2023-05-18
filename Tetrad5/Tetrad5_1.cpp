#include <iostream>
#include <string>
#include <vector>

using namespace std;

string caesar_encryption(string& as, int key)
{
    if (key >= 26) {
        key %= 26;
    }

    vector<char> vec;

    for (int i = 0; i < as.size(); i++) {
        if (as[i] >= 'a' && as[i] <= 'z') {
            char temp = as[i] + key;
            if (temp >= 'a' && temp <= 'z') {
                vec.push_back(temp);
            }
            else {
                if (temp > 'z') {
                    temp -= 26;
                    vec.push_back(temp);
                }
                else if (temp < 'a') {
                    temp += 26;
                    vec.push_back(temp);
                }
            }
        }
        else if (as[i] >= 'A' && as[i] <= 'Z') {
            char temp = as[i] + key;
            if (temp >= 'A' && temp <= 'Z') {
                vec.push_back(temp);
            }
            else {
                if (temp > 'Z') {
                    temp -= 26;
                    vec.push_back(temp);
                }
                else if (temp < 'A') {
                    temp += 26;
                    vec.push_back(temp);
                }
            }
        }
        else {
            vec.push_back(as[i]);
        }
    }

    as.clear();

    for (int i = 0; i < vec.size(); i++) {
        as.push_back(vec[i]);
    }
    return as;
}

string caesar_decryption(string& as, int key)
{
    if (key >= 26) {
        key %= 26;
    }

    vector<char> vec;

    for (int i = 0; i < as.size(); i++) {
        if (as[i] >= 'a' && as[i] <= 'z') {
            char temp = as[i] - key;
            if (temp >= 'a' && temp <= 'z') {
                vec.push_back(temp);
            }
            else {
                if (temp > 'z') {
                    temp -= 26;
                    vec.push_back(temp);
                }
                else if (temp < 'a') {
                    temp += 26;
                    vec.push_back(temp);
                }
            }
        }
        else if (as[i] >= 'A' && as[i] <= 'Z') {
            char temp = as[i] - key;
            if (temp >= 'A' && temp <= 'Z') {
                vec.push_back(temp);
            }
            else {
                if (temp > 'Z') {
                    temp -= 26;
                    vec.push_back(temp);
                }
                else if (temp < 'A') {
                    temp += 26;
                    vec.push_back(temp);
                }
            }
        }
        else {
            vec.push_back(as[i]);
        }
    }

    as.clear();

    for (int i = 0; i < vec.size(); i++) {
        as.push_back(vec[i]);
    }
    return as;
}
/*
string replacement_encryption(string& as)
{

}

string replacement_decryption(string& as)
{

}
*/
int main()
{
    setlocale(LC_ALL, "Russian");

    cout << "Шифрование шифром Цезаря: " << endl;
    cout << "Enter the key: ";
    int key;
    cin >> key;
    cout << "Ключ = " << key << endl;

    cout << "Enter your text:" << endl;
    string as;
    cin.ignore();
    getline(cin, as);
    
    as = caesar_encryption(as, key);

    cout << "Текст зашифрован шифром Цезаря" << endl;
    cout << as << endl;

    as = caesar_decryption(as, key);

    cout << "Текст расшифрован" << endl;
    cout << as << endl;

    return 0;
}