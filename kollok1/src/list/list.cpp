#include <memory>
#include <iostream>  // Для printList (если печать нужна)

template<typename T>
struct ListNode {
    T data;
    std::shared_ptr<ListNode<T>> next;
    ListNode(T val) : data(val), next(nullptr) {}
};

// Объявления функций шаблонов
template<typename T>
std::shared_ptr<ListNode<T>> reverseListRecursive(std::shared_ptr<ListNode<T>> head);

template<typename T>
void printList(std::shared_ptr<ListNode<T>> head);

// ------------------------------
// Реализации шаблонных функций

template<typename T>
std::shared_ptr<ListNode<T>> reverseListRecursive(std::shared_ptr<ListNode<T>> head) {
    if (!head || !head->next) return head;

    auto newHead = reverseListRecursive(head->next);
    head->next->next = head;
    head->next = nullptr;
    return newHead;
}

template<typename T>
void printList(std::shared_ptr<ListNode<T>> head) {
    while (head) {
        std::cout << head->data << " ";
        head = head->next;
    }
    std::cout << "\n";
}
