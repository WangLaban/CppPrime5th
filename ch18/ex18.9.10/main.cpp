#include "Sales_data.h"
using std::cout;
using std::cin;
using std::endl;

int main()
{
    Sales_data item1("book1", 10, 23.3), item2("book2", 6, 66.6), sum;
    cout<<item1 + item2;


    while (cin >> item1 >> item2)
    {
        try {
            sum = item1 + item2;
        }
        catch (const isbn_mismatch &e)
        {
            cout << e.what() << ": left isbn(" << e.left << ") right isbn(" << e.right << ")" << endl;
        }
        cout << "book:\n" << sum << endl;
    }

    return 0;
}
