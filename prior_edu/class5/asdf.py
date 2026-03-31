import math
import time
from contextlib import contextmanager

@contextmanager
def elapsed_time():
    t = time.time()
    yield
    print(time.time()-t)

large_lst = list(range(10000))
large_set = set(large_lst)


with elapsed_time():
    for _ in large_lst:
        if _ not in large_lst:
            pass

with elapsed_time():
    for _ in large_set:
        if _ not in large_set:
            pass





