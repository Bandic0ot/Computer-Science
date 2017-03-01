import lib280.tree.BinaryNode280;

/**
 * Created by Matt on 2017-02-28.
 */
public class AVLNode280<I extends Comparable<? super I>> extends BinaryNode280<I> {
    // -------- Instance Variables --------
    /**
     * An integer to store the height of the current node.
     */
    protected int height;

    public AVLNode280(I x) {
        super(x);
        height = 1;
    }

}
