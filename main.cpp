#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <mpi.h>
using namespace std;

struct {
    int value;
    int rank;
} randValue, maxValue;

int main(int argc, char *argv[])
{
    time_t now = time(NULL);
    tm *ltm = localtime(&now);

    int rank; // номер процесса
    int size; // число процессов
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    srand(time(NULL) + rank);
    int value = rand();

    randValue.value = value;
    randValue.rank = rank;
    cout << ltm->tm_hour << ":" << ltm->tm_min << ":" << ltm->tm_sec
         << ": Процесс[" << rank << "]"
         << ": " << value << endl;

    MPI_Reduce(&randValue, &maxValue, 1, MPI_2INT, MPI_MAXLOC, 0,
               MPI_COMM_WORLD);
    cout << "[OK] Выполнил MPI_Reduce" << endl;

    if (rank == 0) {
        cout << "[END] МАКСИМУМ: " << maxValue.value << " Процесс["
             << maxValue.rank << "]" << endl;
    }

    MPI_Finalize();
    return 0;
}
