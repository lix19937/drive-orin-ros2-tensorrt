由于lambda表达式可以方便的捕获作用域中的变量，故可以作为子线程的参数

```cpp
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <atomic>
 
int main() {
 
    std::atomic_uint num(0);//atomic_uint时原子操作类，在不同的线程中访问时，是线程安全的。
    // 无参数lambda表达式
    auto a = [&]() -> void {
        std::this_thread::sleep_for(std::chrono::milliseconds(num*20));//休眠i*2ms
        num += 100;
    };
    // 新建子线程
    std::thread t(a);
    t.join();
    int value = num;
    printf("%d\n",value);


    // 有参数lambda表达式
    auto b = [&](int i) -> void {
        std::this_thread::sleep_for(std::chrono::milliseconds(i));//休眠i*2ms
        num += i;
    };
    // 新建子线程
    std::thread t2(b,1000);
    t2.join();
 
    value = num;
    printf("%d\n",value);
 
 
    return 0;
}
```
