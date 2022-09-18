#include <bits.h>

using namespace std;
const int maxNode = 444444;
const int INF = 0x3f3f3f3f;

struct Treap {
    int root, treapCnt, key[maxNode], priority[maxNode],
     childs[maxNode][2], cnt[maxNode], size[maxNode];

    Treap() {
        root = 0;
        treapCnt = 1;
        priority[0] = INF;
        size[0] = 0;
    }
    void update(int x) {
        size[x] = size[childs[x][0]] + cnt[x] + size[childs[x][1]];
    }
    void rotate(int &x, int t) {
        int y = childs[x][t];
        childs[x][t] = childs[y][1 - t];
        childs[y][1 - t] = x;
        update(x);
        update(y);
        x = y;
    }
    void __insert(int &x, int k) {
        if(x) {
            if(key[x] == k) {
                cnt[x]++;
            } else {
                int t = key[x] < k;
                __insert(childs[x][t], k);
                if(priority[childs[x][t]] < priority[x]) {
                    rotate(x, t);
                }
            }
        } else {
            x = treapCnt++;
            key[x] = k;
            cnt[x] = 1;
            priority[x] = rand();
            childs[x][0] = childs[x][1] = 0;
        }
        update(x);
    }

    void __erase(int &x, int k) {
        if(key[x] == k) {
            if(cnt[x] > 1) {
                cnt[x]--;
            } else {
                if(childs[x][0] == 0 && childs[x][1] == 0) {
                    x = 0;
                    return;
                }
                int t = priority[childs[x][0]] > priority[childs[x][1]];
                rotate(x, t);
                __erase(x, k);
            }
        } else {
            __erase(childs[x][key[x] < k], k);
        }
        update(x);
    }
    int __getKth(int &x, int k) {
        if(k <= size[childs[x][0]]) {
            return __getKth(childs[x][0], k);
        }
        k -= size[childs[x][0]] + cnt[x];
        if(k <= 0) {
            return key[x];
        }
        return __getKth(childs[x][1], k);
    }

    void insert(int k) {
        __insert(root, k);
    }

    void erase(int k) {
        __erase(root, k);
    }

    int getKth(int k) {
        return __getKth(root, k);
    }
};

int main() {

    return 0;
}