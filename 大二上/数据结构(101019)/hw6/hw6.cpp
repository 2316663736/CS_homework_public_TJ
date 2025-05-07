#include <unordered_map>
#include <vector>

class FreqStack {
private:
    // ��¼ÿ��Ԫ�ص�Ƶ��
    std::unordered_map<int, int> freq;
    // ��Ƶ�ʷ����ջ��group[i]�洢Ƶ��Ϊi��Ԫ��
    std::unordered_map<int, std::vector<int>> group;
    // ��ǰ���Ƶ��
    int maxFreq;

public:
    FreqStack() {
        maxFreq = 0;
    }

    void push(int val) {
        // ����Ƶ��
        freq[val]++;
        // �������Ƶ��
        maxFreq = max(maxFreq, freq[val]);
        // ��Ԫ�ؼ����ӦƵ�ʵ���
        group[freq[val]].push_back(val);
    }

    int pop() {
        // ��ȡ���Ƶ��������һ��Ԫ��
        int val = group[maxFreq].back();
        // �������Ƴ���Ԫ��
        group[maxFreq].pop_back();
        // ����Ƶ��
        freq[val]--;

        // �����ǰ���Ƶ����Ϊ�գ���СmaxFreq
        if (group[maxFreq].empty()) {
            maxFreq--;
        }

        return val;
    }
};