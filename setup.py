from setuptools import setup, Extension
from pybind11.setup_helpers import Pybind11Extension, build_ext

ext_modules = [
    Pybind11Extension(
        "kmeans_manhattan",
        ["app/kmeans_manhattan.cpp"],
        extra_compile_args=["-std=c++17"],
    ),
]

setup(
    name="kmeans_manhattan",
    ext_modules=ext_modules,
    cmdclass={"build_ext": build_ext},
    zip_safe=False,
)
