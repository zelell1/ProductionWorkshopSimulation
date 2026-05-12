#include "machine.h"

Machine::Machine(int id) {
    id_ = id;
    curr_product_id_ = -1;
}

void Machine::AddProductToIncomingBox(int product_id) {
    incoming_box_.push(product_id);
}

int Machine::GetNextProduct() const {
    if (incoming_box_.empty()) {
        return -1;
    }
    return incoming_box_.front();
}

void Machine::RunProcess() {
    if (incoming_box_.empty()) return;
    curr_product_id_ = incoming_box_.front();
    incoming_box_.pop();
}

bool Machine::IsBusy() const {
    return curr_product_id_ != -1;
}

int Machine::GetIncomingBoxSize() const {
    return incoming_box_.size();
}

void Machine::FinishProcess() {
    curr_product_id_ = -1;
}
