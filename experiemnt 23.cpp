/* first_fit.cpp
   First-fit memory allocation simulation.
   Compile: g++ -std=c++11 first_fit.cpp -o first_fit
*/

#include <iostream>
#include <vector>
using namespace std;

int main() {
    int nBlocks, nProcs;
    cout << "Enter number of memory blocks: ";
    cin >> nBlocks;
    vector<int> blockSize(nBlocks);
    for (int i = 0; i < nBlocks; ++i) {
        cout << "Block " << i << " size: ";
        cin >> blockSize[i];
    }

    cout << "Enter number of processes: ";
    cin >> nProcs;
    vector<int> procSize(nProcs);
    for (int i = 0; i < nProcs; ++i) {
        cout << "Process " << i << " size: ";
        cin >> procSize[i];
    }

    vector<int> allocation(nProcs, -1);

    for (int i = 0; i < nProcs; ++i) {
        for (int j = 0; j < nBlocks; ++j) {
            if (blockSize[j] >= procSize[i]) {
                allocation[i] = j;
                blockSize[j] -= procSize[i];
                break;
            }
        }
    }

    cout << "\nProcess No.\tProcess Size\tBlock No.\n";
    for (int i = 0; i < nProcs; ++i) {
        cout << "   " << i << "\t\t" << procSize[i] << "\t\t";
        if (allocation[i] != -1) cout << allocation[i] << "\n";
        else cout << "Not Allocated\n";
    }

    return 0;
}

