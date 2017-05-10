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

struct QueryResponse {
    int diff;
    int value;

    QueryResponse(int value=kMinValue, int diff=0) :
        diff(diff),
        value(value)
    {}

    bool operator < (const QueryResponse& other) const {
        return value < other.value;
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

    SegmentTree(const std::vector<int>& elements) {
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
            vector_[index] = std::max(vector_[index * 2], vector_[index * 2 + 1]);
        }
    }

    QueryResponse GetMax(size_t left, size_t right) {
       return InnerGetMax(left, right, 1, 0, min_power_);
    }

    void Add(size_t left, size_t right, int diff) {
        InnerAdd(left, right, diff, 1, 0, min_power_);
    }
  
  private:
    size_t min_power_;
    std::vector<QueryResponse> vector_;

    void Push(size_t vertex) {
        if (2 * vertex < vector_.size()) {
            for (size_t index = 0; index < 2; ++index) {
                vector_[2 * vertex + index].diff += vector_[vertex].diff;
                vector_[2 * vertex + index].value += vector_[vertex].diff;
            }
        }
        vector_[vertex].diff = 0;
    }

    void Update(size_t vertex) {
        if (2 * vertex < vector_.size()) {
            vector_[vertex].value = std::max(
                vector_[2 * vertex].value,
                vector_[2 * vertex + 1].value
            );
        }
    }

    QueryResponse InnerGetMax(
        size_t left, size_t right,
        size_t vertex, size_t vertex_left, size_t vertex_right) 
    {
        if (vertex_right <= left || right <= vertex_left) {
            return kNullResponse;
        }
        if (left <= vertex_left && vertex_right <= right) {
            return vector_[vertex];
        }
        Push(vertex);
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

    void InnerAdd(
        size_t left, size_t right, int diff,
        size_t vertex, size_t vertex_left, size_t vertex_right) 
    {
        if (vertex_right <= left || right <= vertex_left) {
            return;
        }
        if (left <= vertex_left && vertex_right <= right) {
            vector_[vertex].value += diff;
            vector_[vertex].diff += diff;
            return;
        }
        Push(vertex);
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
    size_t n, k, m;
    input >> n >> k >> m;
    SegmentTree segment_tree(std::move(std::vector<int>(n)));
    for (size_t index = 0; index < m; ++index) {
        size_t left, right;
        input >> left >> right;
        if (segment_tree.GetMax(left, right).value >= k) {
            output << 0 << std::endl;
            continue;
        }
        output << 1 << std::endl;
        segment_tree.Add(left, right, 1);
    }
    return 0;
}


