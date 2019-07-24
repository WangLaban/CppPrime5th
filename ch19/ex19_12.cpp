#include <iostream>
#include <string>
class Screen {
public:
	typedef std::string::size_type pos;
	static const pos Screen::*data() {
		return &Screen::cursor;
	}
	Screen() = default;
	Screen(pos ht, pos wd, char c) : height(ht), width(wd), contents(ht * wd, c) {}
	char get() const { return contents[cursor]; }
	char get_cursor() const { return contents[cursor]; }
	inline char get(pos ht, pos wd) const;
	Screen &move(pos r, pos c);
private:
	std::string contents;
	pos cursor = 0;
	pos height = 0, width = 0;
};
char Screen::get(pos r, pos c) const
{
	pos row = r * width;
	return contents[row + c];
}
Screen& Screen::move(pos r, pos c)
{
	pos row = r * width;
	cursor = row + c;
	return *this;
}

using std::string;
using std::cout;
int main()
{
	const Screen::pos Screen::*pc = Screen::data();
	Screen s(10,10,'-');
	s.move(5, 2);
	cout << s.*pc;

	return 0;
}
