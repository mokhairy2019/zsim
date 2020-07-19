file(REMOVE_RECURSE
  "lib/libzsim.pdb"
  "lib/libzsim.a"
)

# Per-language clean rules from dependency scanning.
foreach(lang CXX)
  include(CMakeFiles/zsim_static.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
