#pragma once

#include <queue>

class Machine {
private:
    int id_;
    int curr_product_id_;
    std::queue<int> incoming_box_;

public:
    explicit Machine(int id);

    void AddProductToIncomingBox(int product_id);

    int GetNextProduct() const;

    void RunProcess();

    bool IsBusy() const;

    int GetIncomingBoxSize() const;
    
    void FinishProcess();
};
