#include <memory>
#include <functional>
#include <vector>
#include <stdexcept>

template <typename T>
class PQueue {
private:
    using function = std::function<bool(T, T)>;

    std::shared_ptr<function> function_ptr;
    std::vector<T> list;

    void swap(int firstIndex, int secondIndex) noexcept {
        T buffer = list[firstIndex];
        list[firstIndex] = list[secondIndex];
        list[secondIndex] = buffer;
    }

    using descendants = std::pair<std::shared_ptr<T>, std::shared_ptr<T>>;

    std::shared_ptr<int> getCorrectIndex(int index) noexcept {
        if (index < list.size()) {
            return std::make_shared<int>(index);
        }

        return nullptr;
    }

    descendants getDescendants(int index) noexcept {
        return {getCorrectIndex(2 * index + 1), getCorrectIndex(2 * index + 2)};
    }

    int best(int firstIndex, int secondIndex) noexcept {
        if ((*function_ptr)(list[firstIndex], list[secondIndex])) {
            return firstIndex;
        }

        return secondIndex;
    }

    int chooseBest(int baseIndex, int anotherIndex) noexcept {
        if (best(baseIndex, anotherIndex) == baseIndex) {
            return -1;
        }

        return anotherIndex;
    }

    int getBestDescendant(int index) noexcept {
        descendants _descendants = getDescendants(index);
        
        bool isFirstEmpty = _descendants.first == nullptr;
        bool isSecondEmpty = _descendants.second == nullptr;
        
        if (isFirstEmpty == isSecondEmpty) {
            if (isFirstEmpty) {
                return -1;
            }

            int indexBestDescendant = best(*_descendants.first, *_descendants.second);

            return chooseBest(index, indexBestDescendant);
        }

        if (isFirstEmpty) {
            return chooseBest(index, *_descendants.second);
        }

        return chooseBest(index, *_descendants.first);
    }

    void up(int index) {
        while (index != 0) {
            int parentIndex = (index - 1) / 2;

            if ((*function_ptr)(list[index], list[parentIndex])) {
                swap(index, parentIndex);
                index = parentIndex;
                continue;
            }

            break;
        }
    }

    void down(int index) {
        while (true) {
            int bestIndex = getBestDescendant(index);

            if (bestIndex == -1) {
                break;
            }

            swap(index, bestIndex);
            index = bestIndex;
        }
    }
public:
    PQueue(std::shared_ptr<function> _function_ptr) noexcept {
        function_ptr = _function_ptr;
    }

    void fromVector(std::vector<T>& data) {
        if (list.size() != 0) {
            throw std::runtime_error("pqueue is not empty");
        }

        list = std::move(data); 
        for (int index = list.size() / 2; index >= 0; index--) {
            down(index);
        }
    }

    void push(T value) noexcept {
        int currentIndex = list.size();
        list.push_back(value);
        up(currentIndex);
    }

    T pop() {
        int size = list.size();
        if (size == 0) {
            throw std::runtime_error("pqueue is empty");
        }

        T result = list[0];

        if (size == 1) {
            list.clear();
            return result;
        }

        int currentIndex = 0;
        list[currentIndex] = list[size - 1];
        list.pop_back();

        down(currentIndex);

        return result;
    }

    bool empty() noexcept {
        return list.size() == 0;
    }
};
