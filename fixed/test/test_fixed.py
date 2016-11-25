from   fixed import Fixed

#-------------------------------------------------------------------------------

def test_basic():
    f = Fixed(2, 1 << 29)
    assert repr(f) == "Fixed(2, 536870912)"
    assert str(f) == "2.12500000000"


