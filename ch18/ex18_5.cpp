#include <iostream>
#include <cstdlib>
using namespace std;

int main()
{
    try {
        //
    }
    catch (overflow_error e)
    {
        cout << e.what();
        abort();
    }
    catch (underflow_error u)
    {
        cout << u.what();
        abort();
    }
    catch (range_error r)
    {
        cout << r.what();
        abort();
    }
    catch (domain_error d)
    {
        cout << d.what();
        abort();
    }
    catch (invalid_argument i)
    {
        cout << i.what();
        abort();
    }
    catch (out_of_range o)
    {
        cout << o.what();
        abort();
    }
    catch (length_error l)
    {
        cout << l.what();
        abort();
    }
    catch (runtime_error r)
    {
        cout << r.what();
        abort();
    }
    catch (logic_error l)
    {
        cout << l.what();
        abort();
    }
    catch (bad_alloc b)
    {
        cout << b.what();
        abort();
    }
    catch (exception e)
    {
        cout << e.what();
        abort();
    }

    return 0;
}
