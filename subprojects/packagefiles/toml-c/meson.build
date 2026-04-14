project('toml-c', 'c', version: '1.0.0')

toml_lib = static_library('toml',
    'toml.c',
    include_directories: include_directories('.')
)

toml_dep = declare_dependency(
  include_directories: include_directories('.'),
  link_with: toml_lib
)