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
After writing `parallellBlur `function using std::thread i'm gonna copare results with basic `SequentialBlur`
| size | Seq_Time, ms | Par_time, ms | faster , % |
|------|--------------|--------------|------------|
| 3x3  | 899.831      | 208.732      | 430        |
| 5x5  | 2248.87      | 531.555      | 423        |
| 7x7  | 3994.38      | 1116.77      | 357        |
in average parallel blur faster than sequention in 4 times, that's cause laptons on which i run this code has only 4 cores

Reading list:
https://habr.com/ru/articles/182610/