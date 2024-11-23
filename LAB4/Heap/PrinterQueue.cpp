#include <iostream>
#include <map>
#include <queue>
#include <string>

class PrinterQueue {
private:
    // Map để lưu độ ưu tiên và các file theo thứ tự FIFO
    std::map<int, std::queue<std::string>, std::greater<int>> priorityQueue;

public:
    // Thêm một file vào hàng đợi
    void addNewRequest(int priority, std::string fileName) {
        priorityQueue[priority].push(fileName);
    }

    // In file theo độ ưu tiên
    void print() {
        // Nếu hàng đợi trống
        if (priorityQueue.empty()) {
            std::cout << "No file to print\n";
            return;
        }

        // Duyệt từ độ ưu tiên cao nhất
        auto it = priorityQueue.begin();
        std::string fileName = it->second.front(); // Lấy file đầu tiên trong hàng đợi
        it->second.pop(); // Xóa file vừa in khỏi hàng đợi

        // Nếu không còn file nào trong queue của độ ưu tiên đó, xóa hẳn entry trong map
        if (it->second.empty()) {
            priorityQueue.erase(it);
        }

        // In tên file
        std::cout << fileName << '\n';
    }
};
