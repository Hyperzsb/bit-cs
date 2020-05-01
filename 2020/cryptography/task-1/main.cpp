#include <iostream>
#include <string>

using namespace std;

int main() {
    cout << "Please input your cipher text: " << endl;
    string cipher_text, plain_text;
    getline(cin, cipher_text);
    plain_text.assign(cipher_text);
    int length = cipher_text.length();
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < length; j++)
            if (cipher_text[j] >= 'A' && cipher_text[j] <= 'Z')
                plain_text[j] = char((cipher_text[j] - 65 + i) % 26 + 65);
            else if (cipher_text[j] >= 'a' && cipher_text[j] <= 'b')
                plain_text[j] = char((cipher_text[j] - 97 + i) % 26 + 97);
            else
                plain_text[j] = cipher_text[j];
        cout << "Plain text when k = " << i << " is:" << endl;
        cout << plain_text << endl;
    }

    cout << "Please check the plain texts manually." << endl;
    return 0;
}