project(
  'chipper',
  'c',
  meson_version : '>= 1.3.0',
  version : '0.0.1',
  default_options : ['warning_level=3'],
)

dependencies = [
]

sources = [
  'src/main.c',
  'src/chipper_daemon.c',
  'src/chipper_log.c',
  'src/chipper_common.c'
]

exe = executable(
  'chipper',
  sources,
  dependencies : dependencies,
  include_directories : 'include',
  install : true,
)

test('basic', exe)
