public class mkny {
    public void successor() {
        struct pkg {
            int location;
            int source;
            int destination;
            bool delivered = false;
        }
        
        struct car {
            pkg payload;
            int location;
        }
        
        int destination;
        int home = 0;
        
        // Pickup the package.
        while(!car.payload) {
            if(car.location == pkg.location) {
                car.payload = pkg;
            } else {
                car.location++;
            }
        }
        
        // Deliver the package.
        while(car.payload) {
            if(car.payload.destination > car.location) {
                car.location++;
            } else if(car.payload.destination < car.location) {
                car.location--;
            } else {
                pkg.delivered = true;
                car.payload = nil;
            }
        }

        // Return home.
        while(car.location != home) {
            car.location--;
        }
    }

    public static void main(String[] args) {

    }
}

