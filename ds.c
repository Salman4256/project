//write your code here..
#include <string.h>

// A Huffman tree node
struct MinHeapNode {
char data;
	unsigned freq;
	struct MinHeapNode *left, *right;
};

// A Min Heap: Collection of min-heap (or Huffman tree) nodes
struct MinHeap {
	unsigned size;
	unsigned capacity;
	struct MinHeapNode** array;
};

// A utility function to allocate a new min heap node with given character and frequency
struct MinHeapNode* newNode(char data, unsigned freq) {
	struct MinHeapNode* temp = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));
	temp->left = temp->right = NULL;
	temp->data = data;
	temp->freq = freq;
	return temp;
}

// A utility function to create a min heap of given capacity
struct MinHeap* createMinHeap(unsigned capacity) {
	struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
	minHeap->size = 0;
	minHeap->capacity = capacity;
	minHeap->array = (struct MinHeapNode**)malloc(minHeap->capacity * sizeof(struct MinHeapNode*));
	return minHeap;
}

// A utility function to swap two min heap nodes
void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b) {
	struct MinHeapNode* t = *a;
	*a = *b;
	*b = t;
}

// The standard minHeapify function.
void minHeapify(struct MinHeap* minHeap, int idx) {
	int smallest = idx;
	int left = 2 * idx + 1;
	int right = 2 * idx + 2;
	if (left < minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq)
		smallest = left;

	if (right < minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq)
		smallest = right;

	if (smallest != idx) {
		swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
		minHeapify(minHeap, smallest);
	}
}

// A utility function to check if the size of heap is one
int isSizeOne(struct MinHeap* minHeap) {
	return (minHeap->size == 1);
}

// A standard function to extract minimum value node from heap
struct MinHeapNode* extractMin(struct MinHeap* minHeap) {
	struct MinHeapNode* temp = minHeap->array[0];
	minHeap->array[0] = minHeap->array[minHeap->size - 1];
	--minHeap->size;
	minHeapify(minHeap, 0);
	return temp;
}

// A utility function to insert a new node to Min Heap
void insertMinHeap(struct MinHeap* minHeap, struct MinHeapNode* minHeapNode) {
	++minHeap->size;
	int i = minHeap->size - 1;

	while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq) {
		minHeap->array[i] = minHeap->array[(i - 1) / 2];
		i = (i - 1) / 2;
	}
	minHeap->array[i] = minHeapNode;
}

// A standard function to build min heap
void buildMinHeap(struct MinHeap* minHeap) {
	int n = minHeap->size - 1;
	int i;

	for (i = (n - 1) / 2; i >= 0; --i)
		minHeapify(minHeap, i);
}

// A utility function to print an array of size n
void printArr(int arr[], int n) {
	int i;
	for (i = 0; i < n; ++i)
// Utility function to check if this node is leaf
int isLeaf(struct MinHeapNode* root) {
	return !(root->left) && !(root->right);
}

// Creates a min heap of capacity equal to size and inserts all character of data[] in min heap. Initially size of min heap is equal to capacity
struct MinHeap* createAndBuildMinHeap(char data[], int freq[], int size) {
	struct MinHeap* minHeap = createMinHeap(size);

	for (int i = 0; i < size; ++i)
		minHeap->array[i] = newNode(data[i], freq[i]);

	minHeap->size = size;
	buildMinHeap(minHeap);
	return minHeap;
}

// The main function that builds Huffman tree
struct MinHeapNode* buildHuffmanTree(char data[], int freq[], int size) {
	struct MinHeapNode *left, *right, *top;
	struct MinHeap* minHeap = createAndBuildMinHeap(data, freq, size);

	while (!isSizeOne(minHeap)) {
		left = extractMin(minHeap);
		right = extractMin(minHeap);

		top = newNode('$', left->freq + right->freq);
		top->left = left;
		top->right = right;

		insertMinHeap(minHeap, top);
	}

	return extractMin(minHeap);
}

// Prints huffman codes from the root of Huffman Tree. It uses arr[] to store codes
void printCodes(struct MinHeapNode* root, int arr[], int top, char codes[][100]) {
	if (root->left) {
		arr[top] = 0;
		printCodes(root->left, arr, top + 1, codes);
	}

	if (root->right) {
		arr[top] = 1;
		printCodes(root->right, arr, top + 1, codes);
	}
}

// Decodes the encoded text using the Huffman tree
void decodeText(struct MinHeapNode* root, char* encodedText, char* decodedText) {
	struct MinHeapNode* current = root;
	int j = 0;
	for (int i = 0; i < strlen(encodedText); ++i) {
		if (encodedText[i] == '0')
			current = current->left;
		else
			current = current->right;

		if (isLeaf(current)) {
			decodedText[j++] = current->data;
			current = root;
		}
	}
	decodedText[j] = '\0';
}

int main() {
	char text[1000];
	printf("Enter the text to be encode: ");
	fgets(text, sizeof(text), stdin);
	text[strcspn(text, "\n")] = '\0';  // Remove the newline character

	int freq[256] = {0};
	for (int i = 0; text[i]; ++i) {
		freq[(int)text[i]]++;
	}

	char data[256];
	int frequencies[256];
	int size = 0;

	for (int i = 0; i < 256; ++i) {
		if (freq[i]) {
			data[size] = (char)i;
			frequencies[size] = freq[i];
			size++;
		}
	}

	struct MinHeapNode* root = buildHuffmanTree(data, frequencies, size);

	int arr[100], top = 0;
	char codes[256][100] = {0};
	printCodes(root, arr, top, codes);

	char encodedText[10000] = {0};
	encodeText(text, codes, encodedText);
	printf("Encoded text: %s\n", encodedText);

	char decodedText[1000];
	decodeText(root, encodedText, decodedText);
	printf("Decoded text: %s\n", decodedText);

	return 0;
}