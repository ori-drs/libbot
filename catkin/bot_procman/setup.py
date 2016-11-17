from distutils.core import setup
from catkin_pkg.python_setup import generate_distutils_setup

d = generate_distutils_setup(
    packages=['bot_procman'],
    package_dir={'': '../../bot2-procman/python/src'}
)

setup(**d)
