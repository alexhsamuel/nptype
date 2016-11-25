import numpy as np
from   fixed import Fixed

#-------------------------------------------------------------------------------

def test_create_array():
    f0 = Fixed(10, 1 << 31)
    f1 = Fixed(12, 1 << 29)
    arr = np.array([f0, f1, f0], dtype=Fixed.dtype)
    assert str(arr[0]) == '10.50000000000'  # FIXME


def test_compare0():
    a = np.array([
        Fixed( 9, 1 << 31),
        Fixed(10, 0),
        Fixed(10, 1 << 29)
    ], dtype=Fixed.dtype)
    assert list(a <  Fixed(10, 0)) == [ True, False, False]
    assert list(a <= Fixed(10, 0)) == [ True,  True, False]


