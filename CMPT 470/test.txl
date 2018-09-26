function main 
  match [program]
  P [program]
end function

keys
  main auto double int struct break else long switch
  case enum register typedef char extern return union
  continue for signed void do if static while
  default goto sizeof volatile const float short unsigned
end keys

compounds
  '== '!= '<= '>= '|| '&&
end compounds

define expr
    [id]
  | [number]
  | [expr] [op] [expr]
end define

define op
    '+
  | '-
  | '*
  | '/
end define

rule program
  [expr]
end rule
