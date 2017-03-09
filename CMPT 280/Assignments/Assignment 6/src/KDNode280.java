import lib280.tree.BinaryNode280;

/**
 * Created by Matt on 2017-03-07.
 */
public class KDNode280<I extends Comparable<? super I>> extends BinaryNode280<I> {
    protected int dimension;

    public KDNode280(I x) {
        super(x);
        dimension = 1;
    }

    public int getDimension() {
        return dimension;
    }

    public void setDimension(int dimension) {
        this.dimension = dimension;
    }

    @Override
    public KDNode280<I> leftNode() {
        return (KDNode280<I>) super.leftNode();
    }

    @Override
    public KDNode280<I> rightNode() {
        return (KDNode280<I>) super.rightNode();
    }
}
