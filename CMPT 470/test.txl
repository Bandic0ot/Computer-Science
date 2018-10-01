include "operator.grm"
include "c.grm"

function main 
  match [program]
  P [program]
end function

define program
    [preprocessor]
  | [body]
  | [repeat func]
end define
