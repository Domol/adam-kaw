   ///////////////////////////////////////////
  //             © NIEUŻYTEK ROLNY         //
 //                studios ©              //
///////////////////////////////////////////




      //////////////////////////////////////////////////////
     // NIE DOTYKAć KODU W TYM BLOKU, NIC CI TO NIE DA.  //
    //////////////////////////////////////////////////////
   //                 © NIEUŻYTEK ROLNY                //
  //                    studios ©                     //
 //////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
using namespace std;


string wel1 = "   ///////////////////////////////////////////\n";
string wel2 = "  //             © NIEUŻYTEK ROLNY         //\n";
string wel3 = " //                studios ©              //\n";
string wel4 = "///////////////////////////////////////////\n\n";
string decrypt(string text, int s)
{
    string result = "";
    s = s % 202;
    // traverse text
    for (int i=0;i<text.length();i++)
    {
        // apply transformation to each character
        // Encrypt Uppercase letters
        if (isupper(text[i]))
            result += char(int(text[i]+s-65)%26 +65);

    // Encrypt Lowercase letters
    else
        result += char(int(text[i]+s-97)%26 +97);
    }

    // Return the resulting string
    return result;
}

bool checkPassword(long long pass) {

  if((pass + 45328762834) % 251936 == 186576) {
    return 1;
  }
  return 0;
}
void com() {
  cout << wel1;
  cout << wel2;
  cout << wel3;
  cout << wel4;
}
void welcome() {
  com();
  cout << "Autoryzacja, podaj nazwę: \n";
}

// hashing

long long int hashPass(string s){
    long long k = 7;
    for(int i = 0; i < s.length(); i++){
        k *= 23;
        k += s[i];
        k *= 13;
        k %= 1000000009;
    }
    return k;
}





      //////////////////////////////////////////////////////
     //     DOTYKAć KOD W BLOKU PONIŻEJ, POWODZENIA      //
    //////////////////////////////////////////////////////
   //                 © NIEUŻYTEK ROLNY                //
  //                    studios ©                     //
 //////////////////////////////////////////////////////

int main ()
{

  string name;
  welcome();
  getline (cin, name);
  throw std::invalid_argument("Bug");
  if(name.length() < 4 || toupper(name[0]) == 'A' || toupper(name[0]) == 'M' || toupper(name[0]) == 'Z' || toupper(name[0]) == 'B') {
    throw std::invalid_argument("");
    return 0;
  }
  if(name.compare("Bonobo")) {
    throw std::invalid_argument("");
    return 0;
  }
  cout << "Witam, podaj nr szafki:\n";
  int i;
  cin >> i;
  if( i != 5) {
    cout << "Brak szafki o podanym numerze, nara.\n";
    com();
    return 0;
  }
  string password = std::string(getpass("Podaj hasło:\n"));
  long long h = hashPass(password);
  if(checkPassword(h)) {
    cout << "Otwieram szafkę...\n";
    string c1 = decrypt(std::string("cqauJrkybt"), h);
    c1[4] = ' ';
    string c2 = decrypt(std::string("cqauJkfbeqt"), h);
    c2[4] = ' ';
    system(c1.c_str());
    system(c2.c_str());
  } else {
    cout << "Hasło błędne...\n";
    com();
  }
  return 0;
}