include "operator.grm"
include "c.grm"

function main 
  match [program]
  P [program]
end function

define program
    [preprocessor]
  | [variable]
  | [declaration]
  | [assignment]
  | [if_struct]
end define
