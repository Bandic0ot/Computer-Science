package ai;

import java.util.*;

public class Problem {
    protected int locations;
    public void initialize() {

    }

    public boolean isGoal(ProblemState state) {
        for(int i = 0; i < state.getAllPkgs().length; i++) {
            if(state.allPkgs[i].location != state.allPkgs[i].source) {
                return false;
            }

            if(state.allCars[i].location != 0) {
                return false;
            } else if(state.allCars[i].pkg != null) {
                return false;
            }
        }

        return true;
    }

    public LinkedList<ProblemState> successors(ProblemState state) {
        LinkedList<ProblemState> states = new LinkedList<>();

        // Generate all the states where the vehicles do not remain in their current locations.
        for(int i = 0; i < state.allCars.length; i++) {
            for(int j = 0; j < locations; j++) {
                // Move all cars to different locations
                if(state.allCars[i].location != j) {
                    ProblemState generatedState = state;
                    generatedState.allCars[i].location = j;

                    // Move every package on the vehicle along with the vehicle itself.
                    if(!state.allCars[i].pkg.isEmpty()) {
                        for(int x = 0; x < state.allCars[i].pkg.size(); x++) {
                            generatedState.allPkgs[i].location = j;
                        }
                    }

                    states.add(generatedState);
                }
            }

            for(int j = 0; j < state.allPkgs.length; j++) {
                if(state.allCars[i].location == state.allPkgs[j].source && state.allPkgs[j].location == state.allPkgs[j].source) {
                    ProblemState generatedState = state;
                    generatedState.allCars[i].pkg.add(state.allPkgs[j]);
                    states.add(generatedState);
                }

                if(state.allCars[i].location == state.allPkgs[j].destination && state.allPkgs[j].location == state.allPkgs[j].destination) {
                    ProblemState generatedState = state;
                    generatedState.allCars[i].pkg.remove(state.allPkgs[j]);
                    states.add(generatedState);
                }
            }
        }


        return states;
    }
}