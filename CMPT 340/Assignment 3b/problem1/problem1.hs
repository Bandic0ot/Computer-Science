-- Start with outer comprehension, iterate through each instance of x
-- using the x as the root for the tuple.
-- Process the inner comprehension next, using y as the second part of 
-- the tuple, this gives us a list of tuples.
-- Finally concatenate these lists of tuples to give us a single list
-- of tuples.
comprehension :: [(Integer, Integer)]
comprehension = concat [[(x, y) | y <- [4, 5, 6]] | x <- [1, 2, 3]]