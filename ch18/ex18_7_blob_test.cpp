#include "ex18_7_blob.h"
#include <string>
using std::string;

int main()
{
    Blob<string> sb1{"a", "b", "c"};
    Blob<string> sb2 = sb1;

    sb2[2] = "b";

    if (sb1 > sb2) {
        for (auto iter = sb2.cbegin(); iter != sb2.cend(); ++iter) {
            cout << *iter << " ";
        }
        cout << endl;
    }

    ConstBlobPtr<string> iter(sb2);
    cout << iter->size() << endl;

    vector<string> vec{"good", "for", "you"};
    Blob<string> sb3(vec.begin(), vec.end());

    for (auto&& s : sb3) {
        cout << s << " ";
    }
    cout << "\n";
}
