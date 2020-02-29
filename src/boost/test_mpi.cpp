//#include <gtest/gtest.h>
//#include <iostream>
//#include <thread>
//#include <vector>
//#include <mpi.h>
//
//void processor() {
//    int argc;
//    const char* argv;
//    MPI_Init(nullptr, nullptr);
//
//    int rank;
//    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//
//    MPI_Finalize();
//}
//
//TEST(testMPI, case1) {
//    std::vector<std::thread> ps(10);
//
//    auto now = std::chrono::system_clock::now();
//    for (int i = 0; i < ps.size(); i++) {
//        ps[i] = std::thread(processor);
//    }
//}
