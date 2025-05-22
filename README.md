# lab_5
OpenCV, Multithreading, Mutex, Atomic

# Test 1
SequentialBlur
Core's size & Time
| size | Seq_Time, ms |
|------|--------------|
| 3x3  | 899.831      |
| 5x5  | 2248.87      |
| 7x7  | 3994.38      |

# Test 2
After writing `parallellBlur `function using std::thread i'm gonna compare results with basic `SequentialBlur`
| size | Seq_Time, ms | Par_time, ms | faster , % |
|------|--------------|--------------|------------|
| 3x3  | 899.831      | 208.732      | 430        |
| 5x5  | 2248.87      | 531.555      | 423        |
| 7x7  | 3994.38      | 1116.77      | 357        |

in average parallel blur faster than sequention in 4 times, that's cause laptons on which i run this code has only 4 cores

# Mutex and Atomic
This experimet tests the performance of atomic and mutex operations with a counter func example
| Counter   | Threads | Atomic, ms | Mutex, ms | faster, % |
|-----------|---------|------------|-----------|-----------|
| 2'000'000 | 4       | 121.394    | 374.76    | 309       |
| 2'000'000 | 8       | 238.641    | 1119.62   | 470       |
| 1'000'000 | 4       | 59.8509    | 157.522   | 266       |
| 1'000'000 | 8       | 134.113    | 519.948   | 387       |

In average atomic 3,58 times faster than mutex.
Also this sheet demonstates that dependency core's count to time is linear in atomic and non-linear in mutex
That is another disadvantage to use it in simple operations instead of atomic

### Difference between atomic and mutex
Use mutex, if required to share complex data like arrays, which can't be completed atomic like.
Atomic operation - operation what runs like a solid one

# Result
1. Multitreading can boost the same task in 4 times
2. atomic is more efficient in sharing resoures than mutex

Reading list:
https://habr.com/ru/articles/182610/
