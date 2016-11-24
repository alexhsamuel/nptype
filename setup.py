import setuptools

setuptools.setup(
    ext_modules=[
        setuptools.Extension(
            "fixed.ext",
            extra_compile_args=[],
            sources=[
                "fixed/ext.c",
                "fixed/fixed.c",
            ],
            library_dirs=[],
            libraries=[],
            depends=[],
        ),
    ]
)
