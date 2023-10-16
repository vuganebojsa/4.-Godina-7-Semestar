import urllib.request
from functools import lru_cache


@lru_cache(maxsize=32)
def get_pep(num):
    resource = 'https://www.python.org/dev/peps/pep-%04d/' % num
    try:
        with urllib.request.urlopen(resource) as s:
            return s.read()
    except Exception as e:
        print(e)
        return '123'


for n in 8, 290, 308, 320, 8, 218, 320, 279, 289, 320, 9991:
    pep = get_pep(n)
    print(n, len(pep))
print(get_pep.cache_info())
