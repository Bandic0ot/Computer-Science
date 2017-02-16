import lib280.base.Dispenser280;
import lib280.base.Searchable280;
import lib280.exception.ContainerFull280Exception;
import lib280.exception.DuplicateItems280Exception;
import lib280.exception.NoCurrentItem280Exception;
import lib280.tree.OrderedSimpleTree280;

/**
 * Created by Matt on 2017-02-16.
 */
public class AVLTree280<I extends Comparable<? super I>> extends OrderedSimpleTree280 {
    // -------- Instance Variables --------
    /**
     * An integer to store the height of the current node.
     */
    protected int height;

    // -------- Constructor --------

    /**
     * Sets the inherited instance variable 'rootNode' to null.
     */
    public AVLTree280() {
        super();
    }

    // -------- Methods --------

    @Override
    public void insert(Object x) throws ContainerFull280Exception, DuplicateItems280Exception {

    }

    @Override
    public void deleteItem() throws NoCurrentItem280Exception {

    }

    public void restoreAVLProperty() {

    }

}
