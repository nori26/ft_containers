template <typename T>
void f(...)
{}

// 仮引数の型が不明なので、実引数からTを推定できない
int main()
{
	// f(1); // エラー
	f<int>(); // OK
}
