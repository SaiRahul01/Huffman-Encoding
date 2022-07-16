#include <bits/stdc++.h>
using namespace std;

string unencodedmessage = "";

map<char, string> dict;

class Node
{
public:
    char alphabet;
    unsigned f;
    Node *left, *right;
    Node(char alphabet, unsigned freq)
    {
        this->alphabet = alphabet;
        this->f = freq;
        left = NULL;
        right = NULL;
    }
};
struct cmp
{
    bool operator()(Node *a, Node *b)
    {
        return a->f > b->f;
    }
};
Node *mainroot;

void display(Node *root, string s)
{
    if (!root)
        return;
    if (root->alphabet != '~')
    {
        cout << root->alphabet << ":" << s << endl;

        dict[root->alphabet] = s;
        cout << dict[root->alphabet] << " ";
    }
    display(root->left, s + "0");
    display(root->right, s + "1");
}

void compress(vector<char> &a, vector<int> &b, int len)
{
    Node *l, *r, *root;
    priority_queue<Node *, vector<Node *>, cmp> pq;
    for (int i = 0; i < len; ++i)
        pq.push(new Node(a[i], b[i]));
    while (pq.size() != 1)
    {
        l = pq.top();
        pq.pop();
        r = pq.top();
        pq.pop();
        root = new Node('~', l->f + r->f);
        root->left = l;
        root->right = r;
        pq.push(root);
    }
    mainroot = root;
    cout << "Main Root\n";
    cout << mainroot->alphabet << " " << mainroot->f << endl;
    cout << "Main Root\n";
}

void decToBinary(int n)
{

    int binaryNum[32];

    int i = 0;
    while (n)
    {

        binaryNum[i] = n % 2;
        n = n / 2;
        i++;
    }

    string ans = "";
    for (int j = i - 1; j >= 0; j--)
        ans += to_string(binaryNum[j]);
    int rem = 8 - ans.size();
    while (rem--)
    {
        ans = "0" + ans;
    }
    unencodedmessage += ans;
}

void helper(string s)
{

    for (char p : s)
    {
        int val = p;
        decToBinary(val);
    }
}
double savedspace(int a, int b)
{

    double ans = (double)(a - b);
    ans /= (1.0) * a;

    return ans * 100;
}

int main()
{
    string s;
    cout << "Enter the Message: ";
    cin >> s;
    map<char, int> frequency;
    vector<char> charvector;
    vector<int> freqvector;
    for (char x : s)
    {
        frequency[x]++;
    }
    // cout<<"Printing Map:\n";
    for (auto x : frequency)
    {
        charvector.push_back(x.first);
        freqvector.push_back(x.second);
    }

    compress(charvector, freqvector, charvector.size());
    helper(s);

    string compressedval = "";
    cout << "Printing dict\n";
    for (char x : s)
    {
        cout << dict[x] << "";
        compressedval += dict[x];
    }
    cout << "Dict ended\n";

    double gg = savedspace(8 * s.size(), 2 * compressedval.size() + 8 * charvector.size());

    if (gg < 0)
    {
        cout << "Huffmann Encoding is not preferred for these type of messages\n";
        return 0;
    }
    else
    {
        cout << "\nThe Encoding Chart \n";
        display(mainroot, "");
        cout << endl;
        cout << "Before Compression\n";
        cout << s << " -> " << unencodedmessage << endl;
        cout << "After Compression\n";
        cout << s << " -> ";
        cout << compressedval << endl;
        cout << "\nSpace Saved: " << gg << "%";
    }
}