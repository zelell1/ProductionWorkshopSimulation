#pragma once

class Product {
private:
    int id_;
    int type_;
    int finish_type_;

public:
    Product(int id, int start_type, int finish_type);

    bool IsFinish() const;

    void MoveToNextType();

    int GetId() const;
    
    int GetType() const;
};
