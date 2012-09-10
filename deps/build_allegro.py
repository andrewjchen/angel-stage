#! /usr/bin/env python3
# encoding: utf-8
import os
import os.path as path
import shutil
import subprocess
import sys

def try_call(*args, **kwargs):
    try:
        subprocess.check_call(*args, **kwargs)
    except subprocess.CalledProcessError as e:
        print('Failed to build Allegro 5!')
        sys.exit(e.returncode)


def make_allegro_build_directory():
    os.chdir(root_path)
    os.chdir('deps')
    os.chdir('builds')
    if path.lexists('allegro_build'):
        i = 1
        while path.lexists('allegro_build ({0})'.format(i)):
            i += 1
        shutil.move('allegro_build', 'allegro_build ({0})'.format(i))
    os.mkdir('allegro_build')

allegro_path = None
def update_allegro_repo():
    global allegro_path
    os.chdir(root_path)
    try_call(['git', 'submodule', 'init', 'deps/allegro'])
    try_call(['git', 'submodule', 'update', 'deps/allegro'])
    os.chdir('deps')
    os.chdir('allegro')
    allegro_path = os.getcwd()
    try_call(['git', 'checkout', '5.0'])

def build_allegro():
    os.chdir(root_path)
    os.chdir('deps')
    os.chdir('builds')
    os.chdir('allegro_build')
    try_call(['cmake', allegro_path])
    try_call(['make', '-j', '8'])

def install_allegro_to_deps():
    os.chdir(root_path)
    os.chdir('deps')
    os.chdir('builds')
    os.chdir('allegro_build')
    try_call(['make', 'install', 'DESTDIR=' + path.join(root_path, 'deps')])

root_path = os.getcwd()
update_allegro_repo()
make_allegro_build_directory()
build_allegro()
install_allegro_to_deps()


