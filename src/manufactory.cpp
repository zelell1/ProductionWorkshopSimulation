#include "manufactory.h"
#include "logger.h"
#include <algorithm>
#include <utility>

Manufactory::Manufactory() {
    time_ = 0;
}

void Manufactory::AddMachine() {
    machines_.emplace_back(machines_.size());
    machines_load_.push_back(0);
}

void Manufactory::AddProduct(int machine_id, Product&& product) {
    machines_[machine_id].AddProductToIncomingBox(products_.size());
    machines_load_[machine_id] += exec_time_matrix_[product.GetType()][machine_id];
    products_.emplace_back(std::move(product));
}

void Manufactory::SetTimeMatrixSize(int m, int n) {
    exec_time_matrix_.assign(m - 1, std::vector<long long>(n));
}

void Manufactory::SetTimeInMatrix(int i, int j, long long time) {
    exec_time_matrix_[i][j] = time;
}

void Manufactory::InitProcess() {
    for (int i = 0; i < machines_.size(); ++i) {
        int product_id = machines_[i].GetNextProduct();
        if (product_id == -1) continue;

        events_.emplace(
            0, 
            product_id,
            i, 
            products_[product_id].GetType(),
            ProductState::kStart);
    }
}

void Manufactory::RunManufactoryWork() {
    InitProcess();

    while (!events_.empty()) {
        time_ = events_.top().finish_time_;
        std::vector<Event> events_buff;

        while (!events_.empty() && events_.top().finish_time_ == time_) {
            Event event = events_.top();
            events_.pop();

            bool should_print = true;

            if (event.state_ == ProductState::kFinish) {
                HandleFinish(event);
            } else if (event.state_ == ProductState::kStart) {
                should_print = HandleStart(event);
            }

            if (should_print) {
                events_buff.push_back(event);
            }
        }

        std::sort(
            events_buff.begin(),
            events_buff.end(),
            [](const auto& left, const auto& right) {
                if (left.state_ != right.state_) {
                    return left.state_ < right.state_;
                }

                return left.machine_id_ < right.machine_id_;
            }
        );

        for (const auto& event : events_buff) {
            PrintEventLog(event);
        }
    }

    Logger::LogStop(time_);
}

void Manufactory::PushToMachineBox(int machine_id, int product_id) {
    machines_[machine_id].AddProductToIncomingBox(product_id);
}

void Manufactory::RunProcessOnMachine(int machine_id) {
    int product_id = machines_[machine_id].GetNextProduct();
    if (product_id == -1) return;

    const Product& curr_product = products_[product_id];
    long long process_time = exec_time_matrix_[curr_product.GetType()][machine_id];

    events_.emplace(
            time_ + process_time,
            product_id,
            machine_id,
            curr_product.GetType(),
            ProductState::kFinish
    );

    machines_load_[machine_id] -= process_time;
    machines_[machine_id].RunProcess();
}

void Manufactory::MoveToNextType(int product_id) {
    int next_machine_id = ChooseNextMachine();
    const Machine& machine = machines_[next_machine_id];
    const Product& curr_product = products_[product_id];
    machines_load_[next_machine_id] += exec_time_matrix_[curr_product.GetType()][next_machine_id];
    int prev_incoming_box_size = machine.GetIncomingBoxSize();

    PushToMachineBox(next_machine_id, product_id);

    if (!machine.IsBusy() && prev_incoming_box_size == 0) {
        events_.emplace(
            time_,
            product_id,
            next_machine_id,
            curr_product.GetType(),
            ProductState::kStart
        );
    } else {
        events_.emplace(
            time_,
            product_id,
            next_machine_id,
            curr_product.GetType(),
            ProductState::kWait,
            prev_incoming_box_size
        );
    }
}

int Manufactory::ChooseNextMachine() {
    return std::distance(machines_load_.begin(), std::min_element(machines_load_.begin(), machines_load_.end()));
}

bool Manufactory::HandleStart(const Event& event) {
    if (!machines_[event.machine_id_].IsBusy()) {
        RunProcessOnMachine(event.machine_id_);
        return true;
    }
    return false;
}

void Manufactory::HandleFinish(const Event& event) {
    Product& product = products_[event.product_id_];
    Machine& machine = machines_[event.machine_id_];

    machine.FinishProcess();
    int next_product_id = machine.GetNextProduct();
    product.MoveToNextType();

    if (product.IsFinish()) {
        events_.emplace(
            time_,
            event.product_id_,
            event.machine_id_,
            product.GetType(),
            ProductState::kReady);
    } else {
        MoveToNextType(event.product_id_);
    }

    if (next_product_id != -1) {
        events_.emplace(
            time_,
            next_product_id,
            event.machine_id_,
            products_[next_product_id].GetType(),
            ProductState::kStart
        );
    }
}

void Manufactory::PrintEventLog(const Event& event) {
    switch (event.state_) {
        case ProductState::kFinish:
            Logger::LogFinish(
                event.finish_time_,
                event.product_id_,
                event.product_type_,
                event.machine_id_
            );
            break;

        case ProductState::kStart:
            Logger::LogStart(
                event.finish_time_,
                event.product_id_,
                event.product_type_,
                event.machine_id_
            );
            break;

        case ProductState::kWait:
            Logger::LogWait(
                event.finish_time_,
                event.product_id_,
                event.product_type_,
                event.machine_id_,
                event.size_of_incoming_box_
            );
            break;

        case ProductState::kReady:
            Logger::LogReady(event.finish_time_, event.product_id_, event.machine_id_);
            break;
    }
}
