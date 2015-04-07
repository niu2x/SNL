# -*- coding:utf-8 -*-
from distutils.core import setup
import glob
import py2exe
setup(windows=["run2.pyw"], data_files=[('icon', ['icon/han.ico']), ('bin',['bin/first.exe', 'bin/dgxj.exe', 'bin/ll1.exe', 'bin/yuyi.exe'])])