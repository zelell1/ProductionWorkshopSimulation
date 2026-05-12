#include "product.h"

Product::Product(int id, int start_type, int finish_type) {
    id_ = id;
    type_ = start_type;
    finish_type_ = finish_type;
}

bool Product::IsFinish() const {
    return type_ == finish_type_;
}

void Product::MoveToNextType() {
    type_ += IsFinish() ? 0 : 1;
}

int Product::GetId() const {
    return id_;
}

int Product::GetType() const {
    return type_;
}
