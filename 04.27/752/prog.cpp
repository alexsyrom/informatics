#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>

template <class Class>
void Print(Class instance) {
    std::cout << instance << std::endl;
}

void Print() {
    std::cout << std::endl;
}


const int kMinValue = -1000 * 1000 * 1000 - 1;
const size_t kNullIndex = 1000 * 1000 * 1000;

struct QueryResponse {
    size_t index;
    int value;

    QueryResponse(size_t index=kNullIndex, int value=kMinValue) :
        index(index),
        value(value)
    {}

    bool operator < (const QueryResponse& other) const {
        return 
            std::tie(this->value, this->index) < 
            std::tie(other.value, other.index);

    }
};

const QueryResponse kNullResponse(kNullIndex, kMinValue);

size_t ComputeMinPowerOfTwo(size_t number) {
    size_t result = 1;
    while (result < number) {
        result *= 2;
    }
    return result;
}

class SegmentTree {
  public:
    /*
     * vector_ contains the segment tree itself, 
     * the numeration starts from one
     */

    SegmentTree(const std::vector<int>& elements) {
        min_power_ = ComputeMinPowerOfTwo(elements.size());
        vector_.resize(min_power_ * 2);
        for (size_t index = 0; index < elements.size(); ++index) {
            vector_[min_power_ + index].value = elements[index];
            vector_[min_power_ + index].index = index;
        }
        for (size_t index = min_power_ + elements.size(); index < vector_.size(); ++index) {
            vector_[index] = kNullResponse;
        }
        for (size_t index = min_power_ - 1; index > 0; --index) {
            vector_[index] = std::max(vector_[index * 2], vector_[index * 2 + 1]);
        }
    }

    QueryResponse GetMax(size_t left, size_t right) const {
       return InnerGetMax(left, right, 1, 0, min_power_);
    }
  
  private:
    size_t min_power_;
    std::vector<QueryResponse> vector_;

    QueryResponse InnerGetMax(
        size_t left, size_t right,
        size_t vertex, size_t vertex_left, size_t vertex_right) const 
    {
        if (vertex_right <= left || right <= vertex_left) {
            return kNullResponse;
        }
        if (left <= vertex_left && vertex_right <= right) {
            return vector_[vertex];
        }
        size_t median = (vertex_left + vertex_right) / 2;
        return std::max(
            InnerGetMax(
                left, right, 
                2 * vertex, vertex_left, median
            ),
            InnerGetMax(
                left, right, 
                2 * vertex + 1, median, vertex_right
            )
        );
    }
};

SegmentTree ReadInput(std::ifstream& input) {
    size_t element_count;
    input >> element_count;
    std::vector<int> elements(element_count);
    for (size_t index = 0; index < element_count; ++index) {
        input >> elements[index]; 
    }
    return SegmentTree(elements);
}


int main() {
    std::ios_base::sync_with_stdio(false);
    std::ifstream input("input.txt");
    std::ofstream output("output.txt");
    SegmentTree segment_tree = ReadInput(input);
    size_t k;
    input >> k;
    for (size_t index = 0; index < k; ++index) {
        size_t left, right;
        input >> left >> right;
        QueryResponse answer = segment_tree.GetMax(left - 1, right);
        output << answer.value << ' ' << answer.index + 1 << std::endl;
    }
    return 0;
}


