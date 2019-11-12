#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>

using namespace std;

pair<int, int> test(istringstream &ss, float &x)
{
    int z = 0;
    while (ss >> z)
    {
        if (z == 0)
        {
            return make_pair<int, int>(1, 1);
        }
        else
        {
            int maxAltura = 0;
            int total = 0;

            float achafament = 0;

            for (int i = 0; i < z; ++i)
            {
                //int j = 1;
                pair<int, int> res = test(ss, x);
                int act = res.first;

                maxAltura = max(maxAltura, act);

                //j += res.second;
                total += res.second;

                //cout << "[PARCIAL] (" << z << ") Altura: " << maxAltura+1 << ", nodos: " << total << endl;

                achafament = (float)(total) / (float)(maxAltura+1);

                if (achafament > x)
                    x = achafament;
            }

            ++total;

            //cout << "[RAIZ] (" << z << ") Altura: " << maxAltura+1 << ", nodos: " << total << endl;

            // TODO: TEST
            //int nodes = nodes(ss);

            //j = act + z + max + 2 + k + 1; //max + z + 1;

            achafament = (float)(total) / (float)(maxAltura + 1);

            if (achafament > x)
                x = achafament;

            return make_pair<int, int>(maxAltura + 1, total + 0);
        }
    }

    return make_pair<int, int>(1, 1);
}

int main()
{
    int n;

    // Get number of trees to iterate
    cin >> n;
    cin.ignore();

    for (int i = 0; i < n; ++i)
    {
        string line;

        while (i < n and getline(cin, line))
        {
            if (line != "")
            {
                istringstream ss(line);

                float y = 0;

                test(ss, y);

                cout << fixed;
                cout << std::setprecision(3);
                cout << y << endl;
            }
        }
    }
}