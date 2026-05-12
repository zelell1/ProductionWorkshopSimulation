#pragma once

#include <cstdint>

enum class ProductState : int8_t {
    kFinish = 0,
    kStart = 1,
    kWait = 2,
    kReady = 3
};

struct Event
{
    long long finish_time_;
    int product_id_;
    int machine_id_;
    int product_type_;
    ProductState state_;
    int size_of_incoming_box_;

    Event(
        long long finish_time,
        int product_id,
        int machine_id,
        int product_type,
        ProductState state,
        int size_of_incoming_box = 0
    );

    bool operator<(const Event& other) const;
};
