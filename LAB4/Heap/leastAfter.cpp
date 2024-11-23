#include <queue>
#include <vector>

int leastAfter(std::vector<int>& nums, int k) {
    // Use a min-heap (priority queue)
    std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap(nums.begin(), nums.end());
    
    // Perform k operations
    for (int i = 0; i < k; ++i) {
        int smallest = minHeap.top(); // Get the smallest element
        minHeap.pop();               // Remove it from the heap
        minHeap.push(smallest * 2);  // Push the doubled value back into the heap
    }
    
    // The smallest element after k operations
    return minHeap.top();
}
