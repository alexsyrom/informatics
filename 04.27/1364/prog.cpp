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


const long long kMinValue = 0;

struct QueryResponse {
    long long diff;
    long long value;

    QueryResponse(long long value=kMinValue, long long diff=0) :
        diff(diff),
        value(value)
    {}

    QueryResponse operator + (const QueryResponse& other) const {
        return QueryResponse(value + other.value);
    }
};

const QueryResponse kNullResponse(kMinValue);

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

    SegmentTree(const std::vector<long long>& elements) {
        min_power_ = ComputeMinPowerOfTwo(elements.size());
        vector_.resize(min_power_ * 2);
        for (size_t index = 0; index < elements.size(); ++index) {
            QueryResponse& element = vector_[min_power_ + index];
            element.value = elements[index];
            element.diff = 0;
        }
        for (size_t index = min_power_ + elements.size(); index < vector_.size(); ++index) {
            vector_[index] = kNullResponse;
        }
        for (size_t index = min_power_ - 1; index > 0; --index) {
            vector_[index] = vector_[index * 2] + vector_[index * 2 + 1];
        }
    }

    long long GetSum(size_t left, size_t right) {
       return InnerGetSum(left, right, 1, 0, min_power_).value;
    }

    void Add(size_t left, size_t right, long long diff) {
        InnerAdd(left, right, diff, 1, 0, min_power_);
    }
  
  private:
    size_t min_power_;
    std::vector<QueryResponse> vector_;

    void Push(size_t vertex, size_t vertex_left, size_t vertex_right) {
        if (2 * vertex < vector_.size()) {
            for (size_t index = 0; index < 2; ++index) {
                vector_[2 * vertex + index].diff += vector_[vertex].diff;
                vector_[2 * vertex + index].value += 
                    vector_[vertex].diff * (vertex_right - vertex_left) / 2;
            }
        }
        vector_[vertex].diff = 0;
    }

    void Update(size_t vertex) {
        if (2 * vertex < vector_.size()) {
            vector_[vertex].value = vector_[2 * vertex].value + vector_[2 * vertex + 1].value;
        }
    }

    QueryResponse InnerGetSum(
        size_t left, size_t right,
        size_t vertex, size_t vertex_left, size_t vertex_right) 
    {
        if (vertex_right <= left || right <= vertex_left) {
            return kNullResponse;
        }
        if (left <= vertex_left && vertex_right <= right) {
            return vector_[vertex];
        }
        Push(vertex, vertex_left, vertex_right);
        size_t median = (vertex_left + vertex_right) / 2;
        return 
            InnerGetSum(
                left, right, 
                2 * vertex, vertex_left, median
            ) + 
            InnerGetSum(
                left, right, 
                2 * vertex + 1, median, vertex_right
            );
    }

    void InnerAdd(
        size_t left, size_t right, long long diff,
        size_t vertex, size_t vertex_left, size_t vertex_right) 
    {
        if (vertex_right <= left || right <= vertex_left) {
            return;
        }
        if (left <= vertex_left && vertex_right <= right) {
            vector_[vertex].value += diff * (vertex_right - vertex_left);
            vector_[vertex].diff += diff;
            return;
        }
        Push(vertex, vertex_left, vertex_right);
        size_t median = (vertex_left + vertex_right) / 2;
        InnerAdd(
            left, right, diff,
            2 * vertex, vertex_left, median
        );
        InnerAdd(
            left, right, diff,
            2 * vertex + 1, median, vertex_right
        );
        Update(vertex);
    }
};


int main() {
    std::ios_base::sync_with_stdio(false);
    std::ifstream input("input.txt");
    std::ofstream output("output.txt");
    size_t n, m;
    input >> n >> m;
    SegmentTree segment_tree(std::move(std::vector<long long>(n)));
    for (size_t index = 0; index < m; ++index) {
        size_t type;
        input >> type;
        if (type == 1) {
            size_t left, right;
            long long diff;
            input >> left >> right >> diff;
            segment_tree.Add(left, right, diff);
        } else {
            size_t left, right;
            input >> left >> right;
            output << segment_tree.GetSum(left, right) << std::endl;
        }
    }
    return 0;
}
