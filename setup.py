import setuptools

setuptools.setup(
    ext_modules=[
        setuptools.Extension(
            "fixed.ext",
            extra_compile_args=[],
            sources=[
                "fixed/fixed.c",
            ],
            library_dirs=[],
            libraries=[],
            depends=[],
        ),
    ]
)
