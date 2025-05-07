#include <iostream>
#include <string>
#include <vector>
using namespace std;

// �ж��Ƿ�Ϊ����
bool isPrime(int n) {
    if (n < 2) return false;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

// ��ȡ���ڵ���n����С����
int getNextPrime(int n) {
    if (n <= 2) return 2;
    if (n % 2 == 0) n++; // �����ż�����ȼ�1�������
    while (!isPrime(n)) n += 2; // ֻ�������
    return n;
}

unsigned long long int getHash(const string& key) {
    unsigned long long int hash = 0;
    for (char c : key) {
        hash = hash * 37ULL + (unsigned long long int)c;
    }
    return hash;
}

// ƽ��̽��
int findPosition(vector<bool>& used, unsigned long long int hash, int tableSize) {
    int base = hash % tableSize;

    // i��1��ʼ����Ϊi=0���������baseλ��
    // �ȼ��baseλ��
    if (!used[base]) return base;

    // Ȼ��ʹ��ƽ��̽��: base �� i^2
    for (int i = 1; i <= tableSize; i++) {
        // ����̽��: base + i^2
        long long offset = ((long long)i * i) % tableSize;
        int pos = (base + offset) % tableSize;
        if (!used[pos]) return pos;

        // ����̽��: base - i^2
        pos = ((base - offset) % tableSize + tableSize) % tableSize;
        if (!used[pos]) return pos;
    }
    return -1;
}

int main() {
    int N, P;
    cin >> N >> P;

    // ��ȡ��
    int tableSize = P;
    if (!isPrime(P)) {
        tableSize = getNextPrime(P);
    }

    vector<bool> used(tableSize, false);

    for (int i = 0; i < N; i++) {
        string key;
        cin >> key;

        if (i > 0) cout << " ";

        unsigned long long int hash = getHash(key);
        int pos = findPosition(used, hash, tableSize);

        if (pos == -1) {
            cout << "-";
        }
        else {
            cout << pos;
            used[pos] = true;
        }
    }
    cout << endl;

    return 0;
}