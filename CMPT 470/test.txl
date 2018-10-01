include "preprocessor.grm"
include "operator.grm"
include "c.grm"

function main 
  match [program]
  P [program]
end function

define program
    [repeat code]
end define

define code
    [preprocessor]
  | [body]
  | [repeat func]
end code
