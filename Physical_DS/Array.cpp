#include <iostream>

using namespace std;

/**
 * ============================================================================
 *                           ARRAY ADT - LEARNING GUIDE
 * ============================================================================
 *
 * This Array ADT uses a dynamically allocated array.
 *
 * It keeps two important values:
 *
 *       size   -> total capacity of the array
 *       length -> number of elements currently stored
 *
 * Example:
 *
 *       Capacity (size) = 8
 *       Length          = 5
 *
 *       [10 20 30 40 50 |     |     |     ]
 *        <--- length --->    unused space
 *        <----------- size ----------->
 *
 * Main Operations:
 *   - Fill
 *   - Display
 *   - Search
 *   - Append
 *   - Insert
 *   - Delete
 *   - Delete by value
 *   - Enlarge
 *   - Merge
 *
 * Common Time Complexities:
 *
 *   Access       : O(1)
 *   Search       : O(n)
 *   Append       : O(1)
 *   Insert       : O(n)
 *   Delete       : O(n)
 *
 * Space Complexity: O(size)
 *
 * ============================================================================
 */

class Array
{
private:
    int size;
    int length;
    int* arr;

public:
    // ==================== CONSTRUCTOR ====================

    /**
     * Creates an empty array with the given capacity.
     */
    Array(int arrSize)
    {
        size = arrSize;
        length = 0;

        arr = new int[size];
    }

    // ==================== ARRAY OPERATIONS ====================

    /**
     * FILL
     *
     * Takes values from the user and stores them in the array.
     */
    void fill()
    {
        int numberOfElements;

        cout << "Enter number of elements: ";
        cin >> numberOfElements;

        if (numberOfElements < 0 || numberOfElements > size)
        {
            cout << "Invalid number of elements.\n";
            return;
        }

        for (int i = 0; i < numberOfElements; i++)
        {
            cin >> arr[i];
        }

        length = numberOfElements;
    }

    /**
     * DISPLAY
     *
     * Prints the currently stored elements.
     */
    void display() const
    {
        cout << "Array: ";

        for (int i = 0; i < length; i++)
        {
            cout << arr[i] << " ";
        }

        cout << "\n";
    }

    /**
     * GET SIZE
     *
     * Returns the total capacity.
     */
    int getSize() const
    {
        return size;
    }

    /**
     * GET LENGTH
     *
     * Returns the number of stored elements.
     */
    int getLength() const
    {
        return length;
    }

    /**
     * SEARCH
     *
     * Returns the first index containing key.
     * Returns -1 if key is not found.
     */
    int search(int key) const
    {
        for (int i = 0; i < length; i++)
        {
            if (arr[i] == key)
                return i;
        }

        return -1;
    }

    /**
     * APPEND
     *
     * Adds an element at the end of the stored elements.
     *
     * Visualization:
     *
     *   Before:
     *   [10 20 30 |   |   ]
     *             ^
     *           length
     *
     *   After append(40):
     *   [10 20 30 40 |   ]
     */
    void append(int key)
    {
        if (length == size)
        {
            cout << "Array is full.\n";
            return;
        }

        arr[length] = key;
        length++;
    }

    /**
     * INSERT
     *
     * Inserts a value at the given index.
     *
     * Example:
     *
     *   Before:
     *   [10 20 30 40]
     *
     *   insert(1, 15)
     *
     *   Shift:
     *   [10 20 20 30 40]
     *
     *   Result:
     *   [10 15 20 30 40]
     */
    void insert(int index, int key)
    {
        if (index < 0 || index > length)
        {
            cout << "Invalid index.\n";
            return;
        }

        if (length == size)
        {
            cout << "Array is full.\n";
            return;
        }

        // Shift elements right to make space.
        for (int i = length; i > index; i--)
        {
            arr[i] = arr[i - 1];
        }

        arr[index] = key;
        length++;
    }

    /**
     * DELETE AT
     *
     * Deletes the element at a specific index.
     *
     * Elements after it are shifted left.
     */
    void deleteAt(int index)
    {
        if (index < 0 || index >= length)
        {
            cout << "Invalid index.\n";
            return;
        }

        // Shift elements left to fill the deleted position.
        for (int i = index; i < length - 1; i++)
        {
            arr[i] = arr[i + 1];
        }

        length--;
    }

    /**
     * DELETE BY VALUE
     *
     * Finds the first occurrence of key
     * and deletes it.
     */
    void deleteByValue(int key)
    {
        int index = search(key);

        if (index == -1)
        {
            cout << "Element not found.\n";
            return;
        }

        deleteAt(index);
    }

    /**
     * ENLARGE
     *
     * Creates a larger array and copies the elements into it.
     *
     * Visualization:
     *
     *   Old:
     *   [10 20 30 |   |   ]
     *
     *             ↓
     *
     *   New:
     *   [10 20 30 |   |   |   |   ]
     */
    void enlarge(int newSize)
    {
        if (newSize <= size)
        {
            cout << "New size must be greater than current size.\n";
            return;
        }

        int* newArr = new int[newSize];

        // Copy existing elements.
        for (int i = 0; i < length; i++)
        {
            newArr[i] = arr[i];
        }

        delete[] arr;

        arr = newArr;
        size = newSize;
    }

    /**
     * MERGE
     *
     * Adds the elements of another Array object
     * to the end of this array.
     *
     * The second array is passed by reference
     * to avoid copying an object that owns dynamic memory.
     */
    void merge(const Array& other)
    {
        int newSize = size + other.size;
        int* newArr = new int[newSize];

        // Copy this array.
        for (int i = 0; i < length; i++)
        {
            newArr[i] = arr[i];
        }

        // Copy the other array after it.
        for (int i = 0; i < other.length; i++)
        {
            newArr[length + i] = other.arr[i];
        }

        delete[] arr;

        arr = newArr;
        size = newSize;
        length += other.length;
    }

    // ==================== DESTRUCTOR ====================

    /**
     * Frees the dynamically allocated memory.
     */
    ~Array()
    {
        delete[] arr;
    }
};

// =========================== MAIN FUNCTION ===========================

int main()
{
    Array myArr(5);

    myArr.append(10);
    myArr.append(20);
    myArr.append(30);

    cout << "Initial array:\n";
    myArr.display();

    cout << "Index of 20: "
        << myArr.search(20) << "\n";

    myArr.insert(1, 15);

    cout << "\nAfter insert:\n";
    myArr.display();

    myArr.deleteAt(2);

    cout << "\nAfter delete:\n";
    myArr.display();

    myArr.enlarge(10);

    myArr.append(40);
    myArr.append(50);

    cout << "\nAfter enlarge and append:\n";
    myArr.display();

    Array other(3);

    other.append(100);
    other.append(200);

    myArr.merge(other);

    cout << "\nAfter merge:\n";
    myArr.display();

    return 0;
}