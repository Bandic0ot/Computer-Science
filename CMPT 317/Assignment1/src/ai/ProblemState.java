package ai;

public class ProblemState {
    protected ProblemState previousState;
    protected Car[] allCars;
    protected Parcel[] allPkgs;

    public ProblemState getPreviousState() {
        return previousState;
    }

    public void setPreviousState(ProblemState previousState) {
        this.previousState = previousState;
    }

    public Car[] getAllCars() {
        return allCars;
    }

    public void setAllCars(Car[] allCars) {
        this.allCars = allCars;
    }

    public Parcel[] getAllPkgs() {
        return allPkgs;
    }

    public void setAllPkgs(Parcel[] allPkgs) {
        this.allPkgs = allPkgs;
    }
}
