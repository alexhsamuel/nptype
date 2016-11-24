import setuptools
from   numpy.distutils.misc_util import get_numpy_include_dirs

setuptools.setup(
    ext_modules=[
        setuptools.Extension(
            "fixed.ext",
            extra_compile_args=[],
            sources=[
                "fixed/ext.c",
                "fixed/fixed.c",
                "fixed/np_fixed.c",
            ],
            include_dirs=get_numpy_include_dirs(),
            library_dirs=[],
            libraries=[],
            depends=[],
        ),
    ]
)
