#pragma once

#include "event.h"
#include "machine.h"
#include "product.h"

#include <queue>
#include <vector>

class Manufactory {
private:
    long long time_;
    std::vector<std::vector<long long>> exec_time_matrix_;
    std::vector<long long> machines_load_;
    std::vector<Machine> machines_;
    std::vector<Product> products_;
    std::priority_queue<Event> events_;

public:
    Manufactory();

    void AddMachine();

    void AddProduct(int machine_id, Product&& product);

    void SetTimeMatrixSize(int m, int n);

    void SetTimeInMatrix(int i, int j, long long time);

    void RunManufactoryWork();

private:

    void InitProcess();

    void PushToMachineBox(int machine_id, int product_id);

    void RunProcessOnMachine(int machine_id);

    void MoveToNextType(int product_id);

    int ChooseNextMachine();

    bool HandleStart(const Event& event);

    void HandleFinish(const Event& event);

    void PrintEventLog(const Event& event);
};
