struct Foo {
    void print(int* x) { // Some member function.
        std::cout << *x << std::endl;
    }
};

int main() {
    Foo foo; // Create instance of Foo.

    // Store member function and the instance using std::bind.
    Callback<void(int*)>::func = std::bind(&Foo::print, foo, std::placeholders::_1);

    // Convert callback-function to c-pointer.
    void (*c_func)(int*) = static_cast<decltype(c_func)>(Callback<void(int*)>::callback);

    // Use in any way you wish.
    std::unique_ptr<int> iptr{new int(5)};
    c_func(iptr.get());
}
