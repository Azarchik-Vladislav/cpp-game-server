#pragma once

#include <chrono>
#include <memory>
#include <string>
#include <vector>

namespace model {
const static double DEFAULT_SPEED = 1.;
const static size_t DEFAULT_BAG_CAPACITY = 3;

struct SpeedUnit {
    double horizontal;
    double vertical;

    // Оператор равенства
    bool operator==(const SpeedUnit& other) const {
        return horizontal == other.horizontal &&
               vertical == other.vertical;
    }

    // Оператор неравенства
    bool operator!=(const SpeedUnit& other) const {
        return !(*this == other);
    }

    // Оператор меньше
    bool operator<(const SpeedUnit& other) const {
        if (horizontal != other.horizontal) {
            return horizontal < other.horizontal;
        }
        return vertical < other.vertical;
    }

    // Оператор меньше или равно
    bool operator<=(const SpeedUnit& other) const {
        return !(*this > other);
    }

    // Оператор больше
    bool operator>(const SpeedUnit& other) const {
        return other < *this;
    }

    // Оператор больше или равно
    bool operator>=(const SpeedUnit& other) const {
        return !(*this < other);
    }
}; 

struct CoordObject {
    double x; 
    double y;

    // Оператор равенства
    bool operator==(const CoordObject& other) const {
        return x == other.x && y == other.y;
    }

    // Оператор неравенства
    bool operator!=(const CoordObject& other) const {
        return !(*this == other);
    }

    // Оператор меньше
    bool operator<(const CoordObject& other) const {
        if (x != other.x) {
            return x < other.x;
        }
        return y < other.y;
    }

    // Оператор меньше или равно
    bool operator<=(const CoordObject& other) const {
        return !(*this > other);
    }

    // Оператор больше
    bool operator>(const CoordObject& other) const {
        return other < *this;
    }

    // Оператор больше или равно
    bool operator>=(const CoordObject& other) const {
        return !(*this < other);
    }
};

enum class Direction {
    U,
    D,
    R,
    L,
    STOP
};

class Loot {
public:
    Loot() = default;
    Loot(size_t id, size_t type, size_t cost, CoordObject position, bool is_picked_up = false);

    void MarkPikedUp() const;

    size_t GetId() const;
    size_t GetType() const;
    size_t GetCost() const;
    CoordObject GetPosition() const;

    bool IsPickedUp() const;

    // Операторы сравнения
    bool operator==(const Loot& other) const {
        return id_ == other.id_ &&
               type_ == other.type_ &&
               cost_ == other.cost_ &&
               position_ == other.position_ &&
               is_picked_up_ == other.is_picked_up_;
    }

    bool operator!=(const Loot& other) const {
        return !(*this == other);
    }

    bool operator<(const Loot& other) const {
        if (id_ != other.id_) {
            return id_ < other.id_;
        }
        if (type_ != other.type_) {
            return type_ < other.type_;
        }
        if (cost_ != other.cost_) {
            return cost_ < other.cost_;
        }
        if (position_ != other.position_) {
            return position_ < other.position_;
        }
        return is_picked_up_ < other.is_picked_up_;
    }

    bool operator<=(const Loot& other) const {
        return !(*this > other);
    }

    bool operator>(const Loot& other) const {
        return other < *this;
    }

    bool operator>=(const Loot& other) const {
        return !(*this < other);
    }
    
private:
    size_t id_;
    size_t type_;
    size_t cost_;
    CoordObject position_;
    mutable bool is_picked_up_;
};

class Dog {
public:
    using Bag = std::vector<Loot>;
    Dog() = default;
    explicit Dog(CoordObject coord, const std::string& name, size_t id, size_t bag_capacity);

    void AddScore(size_t score);
    bool AddLoot(const Loot& loot);

    void UpdateState(SpeedUnit speed, Direction dir);
    void Move(CoordObject coord);
    void LayOutLoot();
    void TryPickUpLoot(const Loot& loot);

    void SetTimeInGame(const std::chrono::milliseconds& time);
    void SetInactiveTime(const std::chrono::milliseconds& time);

    const std::string& GetName() const;
    const std::vector<Loot>& GetBag() const;
    size_t GetId() const;
    CoordObject GetCoord() const;
    CoordObject GetPrevCoord() const;
    SpeedUnit GetSpeed() const;
    Direction GetDirection() const;
    size_t GetBagCapacity() const;
    size_t GetScore() const;
    std::string GetDirectionToString() const;
    std::chrono::milliseconds GetTimeInGame() const;
    std::chrono::milliseconds GetInactiveTime() const;
private:
    CoordObject coord_ {0.0, 0.0};
    CoordObject prev_coord_ {0.0, 0.0};
    SpeedUnit speed_ {0.0, 0.0};
    Direction dir_ = Direction::U;
    Bag bag_;
    std::string name_= "";
    size_t score_ = 0;
    size_t id_ = 0;

    std::chrono::milliseconds time_in_game_{0};
    std::chrono::milliseconds inactive_time_{0};

    bool IsFullBag() const;
};

using DogPtr = std::shared_ptr<Dog>;
using ConstDogPtr = std::shared_ptr<const Dog>;
}//namespace model