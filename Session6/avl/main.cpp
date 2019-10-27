#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>

using namespace std;

pair<int, int> test(istringstream &ss, bool &es_avl)
{
    int z = 0;
    while (ss >> z)
    {
        if (z == 0 and es_avl)
        {
            return make_pair<int, int>(1, 1);
        }
        else
        {
            int maxAltura = 0;
            int total = 0;
            int diferencia = 0;

            for (int i = 0; i < z; ++i)
            {

                pair<int, int> res = test(ss, es_avl);
                int act = res.first;

                maxAltura = max(maxAltura, act);

                //j += res.second;
                total += res.second;

                //cout << "[PARCIAL] (" << z << ") Altura: " << maxAltura+1 << ", nodos: " << total << endl;

                if (z > 1)
                {
                    if (i == 0)
                        diferencia = res.first;
                    else
                        diferencia = max(diferencia, res.first) - min(diferencia, res.first);
                }

                if (res.second > 1 and diferencia > 1)
                    es_avl = false;
            }

            ++total;

            if (total > 1 and diferencia > 1)
                es_avl = false;

            //cout << "[RAIZ] (" << z << ") Altura: " << maxAltura+1 << ", nodos: " << total << ", DiffAltura " << diffAltura << endl;

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

                bool es_avl = true;
                pair<int, int> res = test(ss, es_avl);

                cout << "alcada " << res.first << ", " << ((es_avl) ? "es " : "no es ") << "avl" << endl;
            }
        }
    }
}