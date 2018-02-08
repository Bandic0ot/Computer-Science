package ai;

import java.util.*;

public class StateQueue {
    LinkedList<ProblemState> list;

    public void intialize() {
        list = new LinkedList<>();
    }

    public void add(ProblemState state) {
        if(!list.contains(state)) {
            list.addFirst(state);
        }
    }

    public ProblemState remove() {
        if(!list.isEmpty()) {
            return list.removeFirst();
        } else {
            return null;
        }
    }

    public void compareState(ProblemState state) {

    }
}
