file(REMOVE_RECURSE
  "DuckGame"
  "DuckGame.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/DuckGame.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
