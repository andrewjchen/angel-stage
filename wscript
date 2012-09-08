#! /usr/bin/env python3
# encoding: utf-8
APPNAME = 'angel-stage'
VERSION = '0.1'
top = '.'
out = 'wbuild'

from waf_extensions import declare_variants

declare_variants('debug', 'release')

def options(opt):
    opt.add_option('--cc', action='store', default='clang', help='The C Compiler to use.')
    opt.add_option('--ccxx', action='store', default='clang++', help='The C++ Compiler to use.')
    opt.load('compiler_c')
    opt.load('compiler_cxx')
    opt.recurse('deps')
    opt.recurse('src')
    opt.recurse('tests')

def common_configure(conf):
    if conf.find_program(conf.options.cc):
        conf.env['CC'] = conf.options.cc
        conf.env['CCXX'] = conf.options.cc
    conf.load('compiler_c')
    conf.load('compiler_cxx')
    conf.check(feature='c cprogram cstlib cshlib', cflags=['-Wall', '-std=c99'])
    conf.check(feature='cxx cxxprogram cxxstlib cxxshlib', cxxflags=['-Wall', '-std=c++11'])
    conf.env.append_value('CFLAGS', ['-Wall', '-std=c99'])
    conf.env.append_value('CXXFLAGS', ['-Wall', '-std=c++11'])

def configure_debug(conf):
    conf.setenv('debug')
    common_configure(conf)
    conf.check(cflags=['-g'])
    conf.env.append_value('CFLAGS', ['-g'])
    conf.check(cxxflags=['-g'])
    conf.env.append_value('CXXFLAGS', ['-g'])

def configure_release(conf):
    conf.setenv('release')
    common_configure(conf)
    conf.check(cflags=['-DNDEBUG'])
    conf.env.append_value('CFLAGS', ['-DNDEBUG'])
    conf.check(cxxflags=['-DNDEBUG'])
    conf.env.append_value('CXXFLAGS', ['-DNDEBUG'])
    try:
        conf.check(cflags=['-O4'])
    except Exception as e:
        conf.check(cflags=['-O3'])
        conf.env.append_value('CFLAGS', ['-O3'])
    else:
        conf.env.append_value('CFLAGS', ['-O4'])
    try:
        conf.check(cxxflags=['-O4'])
    except Exception as e:
        conf.check(cxxflags=['-O3'])
        conf.env.append_value('CXXFLAGS', ['-O3'])
    else:
        conf.env.append_value('CXXFLAGS', ['-O4'])

def configure(conf):
    configure_debug(conf)
    configure_release(conf)
    conf.recurse('deps')
    conf.recurse('src')
    conf.recurse('tests')

def build(bld):
    if not bld.variant:
        print('Building all variants.')
        from waflib.Scripting import run_command
        run_command('build_debug')
        run_command('build_release')
    else:
        bld.recurse('deps')
        bld.recurse('src')
        bld.recurse('tests')

def test(context):
    context.recurse('tests')
