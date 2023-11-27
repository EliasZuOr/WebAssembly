#include <iostream>
using namespace std;

struct node {
    int data;
    struct node *left, *right;
};

struct node* New_Node(int data) {
    struct node* temp = new struct node;
    temp->data = data;
    temp->left = temp->right = NULL;
    return temp;
}

void In_Order(struct node* node, int* elements, int& index) {
    if (node == NULL)
        return;
    In_Order(node->left, elements, index);
    elements[index++] = node->data;
    In_Order(node->right, elements, index);
}

void Pre_Order(struct node* node, int* elements, int& index) {
    if (node == NULL)
        return;
    elements[index++] = node->data;
    Pre_Order(node->left, elements, index);
    Pre_Order(node->right, elements, index);
}

void Post_Order(struct node* node, int* elements, int& index) {
    if (node == NULL)
        return;
    Post_Order(node->left, elements, index);
    Post_Order(node->right, elements, index);
    elements[index++] = node->data;
}

void merge(int* arr, int left, int middle, int right) {
    int n1 = middle - left + 1;
    int n2 = right - middle;

    int* leftArr = new int[n1];
    int* rightArr = new int[n2];

    for (int i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        rightArr[j] = arr[middle + 1 + j];

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }

    delete[] leftArr;
    delete[] rightArr;
}


void mergeSort(int* arr, int left, int right) {
    if (left < right) {
        int middle = left + (right - left) / 2;

        mergeSort(arr, left, middle);
        mergeSort(arr, middle + 1, right);

        merge(arr, left, middle, right);
    }
}

int main() {
    struct node* root = New_Node(18);
    root->left = New_Node(30);
    root->right = New_Node(23);
    root->left->left = New_Node(9);
    root->left->right = New_Node(45);

    int elementCount = 5 * 3; // Tres recorridos: In Order, Pre Order, Post Order
    int* elements = new int[elementCount];
    int index = 0;

    In_Order(root, elements, index);
    Pre_Order(root, elements, index);
    Post_Order(root, elements, index);


   cout << "In Order, Pre Order, and Post Order (Before Mergesort): ";
    for (int i = 0; i < elementCount; i++) {
        cout << elements[i] << " ";
    }
      cout << endl;

    mergeSort(elements, 0, elementCount - 1);

       cout << "In Order, Pre Order, and Post Order (After Mergesort): ";
    for (int i = 0; i < elementCount; i++) {
        cout << elements[i] << " ";
    }
        cout << endl;

    delete[] elements;

    return 0;
}