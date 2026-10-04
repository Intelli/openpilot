import os
import subprocess
import sys
import sysconfig
import platform
import shlex
import importlib
import numpy as np

import SCons.Errors
from SCons.Defaults import _stripixes

SCons.Warnings.warningAsException(True)

Decider('MD5-timestamp')

SetOption('num_jobs', max(1, int(os.cpu_count()/2)))

AddOption('--ccflags', action='store', type='string', default='', help='pass arbitrary flags over the command line')
AddOption('--verbose', action='store_true', default=False, help='show full build commands')
AddOption('--minimal',
          action='store_false',
          dest='extras',
          default=os.path.exists(File('#.gitattributes').abspath), # minimal by default on release branch (where there's no LFS)
          help='the minimum build to run openpilot. no tests, tools, etc.')

# Detect platform
real_arch = subprocess.check_output(["uname", "-m"], encoding='utf8').rstrip()
arch = real_arch
if os.environ.get('SP_FORCE_ARCH'):
  arch = os.environ['SP_FORCE_ARCH']
elif platform.system() == "Darwin":
  arch = "Darwin"
elif arch == "aarch64" and (os.path.isfile('/TICI') or os.environ.get('SP_FORCE_TICI') == '1'):
  arch = "larch64"
assert arch in [
  "larch64",  # linux tici arm64
  "aarch64",  # linux pc arm64
  "x86_64",   # linux pc x64
  "Darwin",   # macOS arm64 (x86 not supported)
]

pkg_names = ['bzip2', 'capnproto', 'eigen', 'ffmpeg', 'libjpeg', 'libyuv', 'ncurses', 'zeromq', 'zstd']
pkgs = [importlib.import_module(name) for name in pkg_names]

# Use the tools distributed with the pinned dependency packages, including
# capnpc and the panda ARM firmware compiler, rather than host versions.
firmware_compiler = importlib.import_module('gcc_arm_none_eabi')
dependency_bins = [x.BIN_DIR for x in pkgs if hasattr(x, 'BIN_DIR')]
dependency_bins.append(os.path.join(firmware_compiler.TOOLCHAIN_DIR, 'bin'))
os.environ['PATH'] = os.pathsep.join([*dependency_bins, os.environ['PATH']])

sysroot = os.environ.get('SP_TICI_SYSROOT', '').rstrip('/')
if arch == 'larch64' and sysroot and real_arch not in ('aarch64', 'arm64'):
  raise SCons.Errors.UserError('Device builds require an ARM64 container and Python runtime')

def tici_path(path):
  return os.path.join(sysroot, path.lstrip('/')) if sysroot else path


# ***** enforce a whitelist of system libraries *****
# this prevents silently relying on a 3rd party package,
# e.g. apt-installed libusb. all libraries should either
# be distributed with all Linux distros and macOS, or
# vendored in commaai/dependencies.
allowed_system_libs = {
  "EGL", "GLESv2", "GL",
  "Qt5Charts", "Qt5Core", "Qt5Gui", "Qt5Widgets",
  "dl", "drm", "gbm", "m", "pthread",
}

def _resolve_lib(env, name):
  for d in env.Flatten(env.get('LIBPATH', [])):
    p = Dir(str(d)).abspath
    for ext in ('.a', '.so', '.dylib'):
      f = File(os.path.join(p, f'lib{name}{ext}'))
      if f.exists() or f.has_builder():
        return name
  if name in allowed_system_libs:
    return name
  raise SCons.Errors.UserError(f"Unexpected non-vendored library '{name}'")

def _libflags(target, source, env, for_signature):
  libs = []
  lp = env.subst('$LIBLITERALPREFIX')
  for lib in env.Flatten(env.get('LIBS', [])):
    if isinstance(lib, str):
      if os.sep in lib or lib.startswith('#'):
        libs.append(File(lib))
      elif lib.startswith('-') or (lp and lib.startswith(lp)):
        libs.append(lib)
      else:
        libs.append(_resolve_lib(env, lib))
    else:
      libs.append(lib)
  return _stripixes(env['LIBLINKPREFIX'], libs, env['LIBLINKSUFFIX'],
                    env['LIBPREFIXES'], env['LIBSUFFIXES'], env, env['LIBLITERALPREFIX'])

env = Environment(
  ENV={
    "PATH": os.environ['PATH'],
    "PYTHONPATH": ':'.join([Dir("#").abspath, Dir("#third_party/acados").abspath, Dir("#opendbc_repo").abspath]),
    "ACADOS_SOURCE_DIR": Dir("#third_party/acados").abspath,
    "ACADOS_PYTHON_INTERFACE_PATH": Dir("#third_party/acados/acados_template").abspath,
    "TERA_PATH": Dir("#").abspath + f"/third_party/acados/{arch}/t_renderer"
  },
  CCFLAGS=[
    "-g",
    "-fPIC",
    "-O2",
    "-Wunused",
    "-Werror",
    "-Wshadow" if arch in ("Darwin", "larch64") else "-Wshadow=local",
    "-Wno-unknown-warning-option",
    "-Wno-inconsistent-missing-override",
    "-Wno-c99-designator",
    "-Wno-reorder-init-list",
    "-Wno-vla-cxx-extension",
  ],
  CFLAGS=["-std=gnu11"],
  CXXFLAGS=["-std=c++1z"],
  CPPPATH=[
    "#",
    "#msgq",
    "#third_party",
    "#third_party/json11",
    "#third_party/linux/include",
    "#third_party/acados/include",
    "#third_party/acados/include/blasfeo/include",
    "#third_party/acados/include/hpipm/include",
    "#third_party/catch2/include",
    [x.INCLUDE_DIR for x in pkgs],
  ],
  LIBPATH=[
    "#common",
    "#msgq_repo",
    "#third_party",
    "#selfdrive/pandad",
    "#rednose/helpers",
    f"#third_party/acados/{arch}/lib",
    [x.LIB_DIR for x in pkgs],
  ],
  RPATH=[],
  CYTHONCFILESUFFIX=".cpp",
  COMPILATIONDB_USE_ABSPATH=True,
  REDNOSE_ROOT="#",
  tools=["default", "cython", "compilation_db", "rednose_filter"],
  toolpath=["#site_scons/site_tools", "#rednose_repo/site_scons/site_tools"],
)
for key in ('TMPDIR', 'PARAMS_ROOT', 'SP_USE_PINNED_MODELS'):
  if key in os.environ:
    env['ENV'][key] = os.environ[key]
if arch != "larch64":
  env['_LIBFLAGS'] = _libflags

# Arch-specific flags and paths
if arch == "larch64":
  env["CC"] = "clang"
  env["CXX"] = "clang++"
  if sysroot:
    env.Append(CCFLAGS=[f'--sysroot={sysroot}'])
    env.Append(LINKFLAGS=[f'--sysroot={sysroot}'])
  env.Append(CPPPATH=[tici_path('/usr/include/aarch64-linux-gnu'), tici_path('/usr/include')])
  env.Append(LIBPATH=[
    tici_path('/usr/local/lib'),
    tici_path('/usr/lib/aarch64-linux-gnu'),
    tici_path('/lib/aarch64-linux-gnu'),
    tici_path('/system/vendor/lib64'),
  ])
  env.Append(LINKFLAGS=[f'-Wl,-rpath-link,{tici_path(p)}' for p in
                       ('/usr/local/lib', '/usr/lib/aarch64-linux-gnu', '/lib/aarch64-linux-gnu', '/system/vendor/lib64')])
  env.Append(RPATH=['/usr/local/lib'])
  arch_flags = ["-D__TICI__", "-mcpu=cortex-a57", "-DQCOM2"]
  env.Append(CCFLAGS=arch_flags)
  env.Append(CXXFLAGS=arch_flags)
elif arch == "Darwin":
  env.Append(LIBPATH=[
    "/System/Library/Frameworks/OpenGL.framework/Libraries",
  ])
  env.Append(CCFLAGS=["-DGL_SILENCE_DEPRECATION"])
  env.Append(CXXFLAGS=["-DGL_SILENCE_DEPRECATION"])

_extra_cc = shlex.split(GetOption('ccflags') or '')
if _extra_cc:
  env.Append(CCFLAGS=_extra_cc)

# no --as-needed on mac linker
if arch != "Darwin":
  env.Append(LINKFLAGS=["-Wl,--as-needed", "-Wl,--no-undefined"])

# Shorter build output: show brief descriptions instead of full commands.
# Full command lines are still printed on failure by scons.
if not GetOption('verbose'):
  for action, short in (
    ("CC",     "CC"),
    ("CXX",    "CXX"),
    ("LINK",   "LINK"),
    ("SHCC",   "CC"),
    ("SHCXX",  "CXX"),
    ("SHLINK", "LINK"),
    ("AR",     "AR"),
    ("RANLIB", "RANLIB"),
    ("AS",     "AS"),
  ):
    env[f"{action}COMSTR"] = f"  [{short}] $TARGET"

# progress output
node_interval = 5
node_count = 0
def progress_function(node):
  global node_count
  node_count += node_interval
  sys.stderr.write("progress: %d\n" % node_count)
if os.environ.get('SCONS_PROGRESS'):
  Progress(progress_function, interval=node_interval)

# ********** Cython build environment **********
envCython = env.Clone()
envCython["CPPPATH"] += [sysconfig.get_paths()['include'], np.get_include()]
envCython["CCFLAGS"] += ["-Wno-#warnings", "-Wno-cpp", "-Wno-shadow", "-Wno-deprecated-declarations"]
envCython["CCFLAGS"].remove("-Werror")

envCython["LIBS"] = []
if arch == "Darwin":
  envCython["LINKFLAGS"] = env["LINKFLAGS"] + ["-bundle", "-undefined", "dynamic_lookup"]
else:
  # Python extension symbols are resolved by the interpreter at load time.
  envCython["LINKFLAGS"] = [f for f in env['LINKFLAGS'] if f != '-Wl,--no-undefined'] + ["-pthread", "-shared"]

np_version = SCons.Script.Value(np.__version__)
Export('envCython', 'np_version')

Export('env', 'arch')

# Setup cache dir
default_cache_dir = '/data/scons_cache' if arch == "larch64" else '/tmp/scons_cache'
cache_dir = ARGUMENTS.get('cache_dir', default_cache_dir)
CacheDir(cache_dir)
Clean(["."], cache_dir)

# ********** start building stuff **********

# Build common module
SConscript(['common/SConscript'])
Import('_common')
common = [_common, 'json11', 'zmq']
Export('common')

# Build messaging (cereal + msgq + socketmaster + their dependencies)
# Enable swaglog include in submodules
env_swaglog = env.Clone()
env_swaglog['CXXFLAGS'].append('-DSWAGLOG="\\"common/swaglog.h\\""')
SConscript(['msgq_repo/SConscript'], exports={'env': env_swaglog})

SConscript(['cereal/SConscript'])

Import('socketmaster', 'msgq')
messaging = [socketmaster, msgq, 'capnp', 'kj',]
Export('messaging')


# Build other submodules
SConscript(['panda/SConscript'])

# Build rednose library
SConscript(['rednose/SConscript'])

# Build system services
SConscript([
  'system/loggerd/SConscript',
])

if arch == "larch64":
  SConscript(['system/camerad/SConscript'])

# Build openpilot
SConscript(['third_party/SConscript'])

# Build selfdrive
SConscript([
  'selfdrive/pandad/SConscript',
  'selfdrive/controls/lib/lateral_mpc_lib/SConscript',
  'selfdrive/controls/lib/longitudinal_mpc_lib/SConscript',
  'selfdrive/locationd/SConscript',
  'selfdrive/modeld/SConscript',
  'selfdrive/ui/SConscript',
])

SConscript(['sunnypilot/SConscript'])

# Build tools
if arch != "larch64":
  SConscript([
    'tools/replay/SConscript',
    'tools/cabana/SConscript',
    'tools/jotpluggler/SConscript',
  ])


env.CompilationDatabase('compile_commands.json')
