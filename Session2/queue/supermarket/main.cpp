#include "queue.hpp"
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

int main()
{
    string line;
    int n;
    unsigned int i = 0;
    vector<queue> v;

    cin >> n;

    if (n > 0)
    {
        vector<queue> v(n);
        cin.ignore();

        while (getline(cin, line) and i < n)
        {
            istringstream ss(line);

            string x;

            while (ss >> x)
            {
                v[i].push(x);
            }
            ++i;
        }

        cout << "SORTIDES" << endl
             << "--------" << endl;

        while (getline(cin, line))
        {
            istringstream ss(line);

            string x;

            while (ss >> x)
            {
                if (x == "ENTRA")
                {
                    string nombre;
                    int num;
                    ss >> nombre;
                    ss >> num;

                    if (num > 0 and num <= n)
                    {
                        v[num - 1].push(nombre);
                    }
                }
                else if (x == "SURT")
                {
                    int num;
                    ss >> num;

                    if (num > 0 and num <= n)
                    {
                        if (not v[num - 1].empty())
                        {
                            cout << v[num - 1].first() << endl;
                            v[num - 1].pop();
                        }
                    }
                }
            }
        }

        cout << endl
             << "CONTINGUTS FINALS" << endl
             << "-----------------" << endl;

        for (int i = 0; i < n; ++i)
        {
            cout << "cua " << (i + 1) << ":";
            if (not v[i].empty())
                cout << " ";

            while (not v[i].empty())
            {
                cout << v[i].first();
                v[i].pop();
                if (not v[i].empty())
                    cout << " ";
            }
            cout << endl;
        }
    }
}