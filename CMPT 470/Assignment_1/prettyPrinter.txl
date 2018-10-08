% Matthew Mulenga
% mam558
% 11144528

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
    [preprocessor] [NL]
  | [body] [NL]
  | [func_struct] [NL]
end define
