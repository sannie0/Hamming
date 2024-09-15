#include <iostream>
#include <string>
#include <bitset>
#include <vector>
#include <cstdlib> 
#include <ctime> 
#include <string> 

using namespace std;

#define N 20
vector <int> DegreeOfTwo;
vector <string> MatrixBits;
vector <int> Ind;

void FillVectorDegree(vector<int>& DegreeOfTwo) {
    for (int i = 0; i < N; i++) {
        DegreeOfTwo.push_back(pow(2, i));
        ///return DegreeOfTwo;
    }
}

int RandomNumber(string& CalculateBits) {
    return rand() % CalculateBits.length() + 1;
}

string SetControlBits(vector<int>& DegreeOfTwo, vector<string>& MatrixBits, string ConvertString) {
    MatrixBits.clear();
    
    int strlen = ConvertString.length();
    string ControlBit;
    string ConvertStringChange = ConvertString;
    ControlBit.resize(strlen, '_');

    int sum = 0;

    for (int i = 0; i < strlen; i++) {
        if (i + 1 == DegreeOfTwo[log2(i + 1)]) {
            int degree = i + 1;
            string ControlBit(strlen, '_'); // Инициализируем строку символами '_'
            int sum = 0;
            // Проход по битам строки
            for (int k = degree - 1; k < strlen; k += 2 * degree) {
                for (int n = k; n < k + degree && n < strlen; n++) {
                    ControlBit[n] = 'x'; // Чередование символов 'x' и '_'
                    if (ConvertStringChange[n] == '1') {
                        sum++; // Подсчет единиц
                    }
                }
            }
        
        if (sum % 2 != 0) {
            ConvertStringChange[i] = '1';
            ControlBit += " " + to_string(sum);
  
        }
        else {
            ConvertStringChange[i] = '0';
        }
            MatrixBits.push_back(ControlBit);
        }
    }
    return ConvertStringChange;
}

void Print(vector<int>& DegreeOfTwo, vector<string>& MatrixBits, string ConvertString) {
    cout << endl;
    for (int i = 0; i < ConvertString.length(); i++) {
        if (i + 1 == DegreeOfTwo[log2(i + 1)]) {
            cout << "*";
        }
        else {
            cout << "_";
        }  
    }

    cout << endl;
    for (int i = 0; i < ConvertString.length(); i++) {
        cout << ConvertString[i];
    }

    cout << endl;
    for (int i = 0; i < MatrixBits.size(); i++) {
        cout << MatrixBits[i] << endl;
    }
}

void ControlBit(string& BinaryString, string& ConvertString, int count) {
    int j = 0;
    for (int i = 0; i < BinaryString.length() + count; i++) {
        if (i + 1 == DegreeOfTwo[log2(i + 1)]) {
            ConvertString[i] = '0';
        }
        else {
            ConvertString[i] = BinaryString[j];
            j++;
        }
    }
}

void PositionBit(string& BinaryString, int count) {
    string PositionString;
    PositionString.resize(BinaryString.length(), '_');
    for (int i = 0; i < BinaryString.length() + count; i++) {
        if (i + 1 == DegreeOfTwo[log2(i + 1)]) {
            PositionString[i] = '*';
        }
    }
    cout << PositionString << endl;
}

void CompareStrings(vector<int>& Ind, string& CalculateBits, string& CompareString, int ind) {
    for (int i = 0; i < ind - 1; i++) {
        if (CalculateBits[i] != CompareString[i]) {
            Ind.push_back(i);  
        }
    }
}


void ZeroBit(string &TempString) {
    for (int i = 0; i < TempString.length(); i++) {
        if (i + 1 == DegreeOfTwo[log2(i + 1)]) {
            TempString[i] = '0';
        }
    }
    cout << TempString << endl;
}



int main() {
    system("chcp 1251");

    string BinaryString, ConvertString, CompareString;
    FillVectorDegree(DegreeOfTwo);

    cout << "\t\tВведите значение:" << endl;
    cin >> BinaryString;

    int PowerOfTwo = 1, count = 0;
    while (PowerOfTwo <= BinaryString.length()) {
        count++;
        PowerOfTwo *= 2;
    }

    PositionBit(BinaryString, count);

    ConvertString.resize(BinaryString.length() + count, '0');
    ControlBit(BinaryString, ConvertString, count);

    cout << "\n\t\tРасстановка контрольных битов" << endl;
    cout << ConvertString << endl;

    string CalculateBits = SetControlBits(DegreeOfTwo, MatrixBits, ConvertString);
    Print(DegreeOfTwo, MatrixBits, ConvertString);

    cout << CalculateBits << endl;

    int ind;
    cout << "\n\nСмоделируем ситуацию ошибки полученного сообщения. Пусть это будет бит - ";
    cin >> ind;


    while (ind < 1 || ind > ConvertString.length()) {
        cout << "Введите значение от 1 до " << ConvertString.length() << endl;
        cin >> ind;
    }

    string PositionString(CalculateBits.length(), '_');
    PositionString[ind - 1] = '*';
    cout << PositionString << endl;
    cout << CalculateBits << endl;

    string TempString = CalculateBits;
    TempString[ind - 1] = (TempString[ind - 1] == '0') ? '1' : '0';

    cout << "\n\t\tОпределение ошибки\n";
    PositionBit(TempString, 0);
    ZeroBit(TempString);

    CompareString = SetControlBits(DegreeOfTwo, MatrixBits, TempString);
    Print(DegreeOfTwo, MatrixBits, TempString);
    cout << CompareString << endl;

    CompareStrings(Ind, CalculateBits, CompareString, ind);
    string bits;
    int bit = 0;
    for (int i = 0; i < Ind.size(); i++) {
        bits += to_string(Ind[i] + 1) + " ";
        bit += Ind[i] + 1;
    }

    cout << "\nКак видно из сравнения, индексы - " << bits << " не совпадают с полученным сообщением\n";
    cout << "Вывод: ошибка находится в " << bit << " бите" << endl;

    return 0;
}

