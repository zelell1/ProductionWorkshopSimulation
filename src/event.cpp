#include "event.h"

Event::Event(
    long long finish_time,
    int product_id,
    int machine_id,
    int product_type,
    ProductState state,
    int size_of_incoming_box
) {
    finish_time_ = finish_time;
    product_id_ = product_id;
    machine_id_ = machine_id;
    product_type_ = product_type;
    state_ = state;
    size_of_incoming_box_ = size_of_incoming_box;
}

bool Event::operator<(const Event& other) const {
    if (finish_time_ != other.finish_time_) {
        return finish_time_ > other.finish_time_;
    }

     if (state_ != other.state_) {
        return state_ > other.state_;
    }

    return machine_id_ > other.machine_id_;
}
