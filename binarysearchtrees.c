// A C program that I made that helps in finding the median of two sorted arrays using binary search trees.

#include <stdio.h>
#include <stdlib.h>

// Define a structure for a binary search tree node
typedef struct TreeNode {
    int value;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// Function to insert a value into a binary search tree
TreeNode* insert(TreeNode* root, int value) {
    if (root == NULL) {
        TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
        newNode->value = value;
        newNode->left = newNode->right = NULL;
        return newNode;
    }

    if (value < root->value) {
        root->left = insert(root->left, value);
    } else {
        root->right = insert(root->right, value);
    }

    return root;
}

// Function to traverse a binary search tree in-order and store the values in an array
void inOrderTraversal(TreeNode* root, int* array, int* index) {
    if (root != NULL) {
        inOrderTraversal(root->left, array, index);
        array[(*index)++] = root->value;
        inOrderTraversal(root->right, array, index);
    }
}

// Function to find the median of two sorted arrays
double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    // Combine the elements of both arrays into a single sorted array
    int* combinedArray = (int*)malloc((nums1Size + nums2Size) * sizeof(int));

    int index = 0;
    for (int i = 0; i < nums1Size; i++) {
        combinedArray[index++] = nums1[i];
    }

    for (int i = 0; i < nums2Size; i++) {
        combinedArray[index++] = nums2[i];
    }

    // Construct a balanced binary search tree from the combined array
    TreeNode* root = NULL;
    for (int i = 0; i < nums1Size + nums2Size; i++) {
        root = insert(root, combinedArray[i]);
    }

    // Traverse the binary search tree in-order to get the sorted values
    int* sortedArray = (int*)malloc((nums1Size + nums2Size) * sizeof(int));
    index = 0;
    inOrderTraversal(root, sortedArray, &index);

    // Calculate the median
    double median;
    if ((nums1Size + nums2Size) % 2 == 0) {
        int middle1 = (nums1Size + nums2Size) / 2 - 1;
        int middle2 = (nums1Size + nums2Size) / 2;
        median = (sortedArray[middle1] + sortedArray[middle2]) / 2.0;
    } else {
        int middle = (nums1Size + nums2Size) / 2;
        median = sortedArray[middle];
    }

    // Free allocated memory
    free(combinedArray);
    free(sortedArray);

    return median;
}

int main() {
    int nums1[] = {1, 3};
    int nums1Size = sizeof(nums1) / sizeof(nums1[0]);

    int nums2[] = {2};
    int nums2Size = sizeof(nums2) / sizeof(nums2[0]);

    double median = findMedianSortedArrays(nums1, nums1Size, nums2, nums2Size);

    printf("Median of the two sorted arrays: %.2lf\n", median);

    return 0;
}
