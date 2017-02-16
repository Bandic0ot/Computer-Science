import lib280.exception.ContainerFull280Exception;
import lib280.exception.DuplicateItems280Exception;
import lib280.tree.OrderedSimpleTree280;

/**
 * Created by Matt on 2017-02-16.
 */
public class AVLTree<I extends Comparable<? super I>> extends OrderedSimpleTree280 {
    @Override
    public boolean has(Object y) {
        return false;
    }

    @Override
    public void search(Object x) {

    }

    @Override
    public void insert(Object x) throws ContainerFull280Exception, DuplicateItems280Exception {

    }

    @Override
    public boolean membershipEquals(Object x, Object y) {
        return false;
    }
}
