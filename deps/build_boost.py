#! /usr/bin/env python3
# encoding: utf-8
import os
import subprocess
import sys
import shutil

root_path = None

def try_call(*args, **kwargs):
    try:
        subprocess.check_call(*args, **kwargs)
    except subprocess.CalledProcessError as e:
        print('Failed to build Allegro 5!')
        sys.exit(e.returncode)

boost_extracted = ""
def extract_boost():
    global boost_extracted
    os.chdir(root_path)
    os.chdir('deps')
    boost_version = "1_51_0"
    try_call(["tar", "-xvf", "boost_{0}.tar.gz".format(boost_version)])
    boost_extracted = "boost_" + boost_version
    shutil.move(boost_extracted, 'builds')


def build_boost():
    os.chdir(root_path)
    os.chdir('deps')
    os.chdir('builds')
    os.chdir(boost_extracted)
    try_call(["./bootstrap.sh", "--prefix=../../usr/local/", "--with-libraries=system,thread,timer"])
    try_call(["./b2"])
    try_call(["./b2", "install"])

root_path = os.getcwd()
extract_boost()
build_boost()
