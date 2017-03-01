import lib280.base.Dispenser280;
import lib280.base.Searchable280;
import lib280.exception.ContainerEmpty280Exception;
import lib280.exception.ContainerFull280Exception;
import lib280.exception.DuplicateItems280Exception;
import lib280.exception.NoCurrentItem280Exception;
import lib280.tree.BinaryNode280;
import lib280.tree.LinkedSimpleTree280;
import lib280.tree.OrderedSimpleTree280;

/**
 * Created by Matt on 2017-02-16.
 */
public class AVLTree280<I extends Comparable<? super I>> extends OrderedSimpleTree280<I> {
    // -------- Instance Variables --------
    /**
     * An integer to store the height of the current node.
     */

    // -------- Constructor --------

    /**
     * Sets the inherited instance variable 'rootNode' to null.
     * And set the initial heights of the trees.
     */

    public AVLTree280() {
        super();
    }

    // -------- Methods --------
    public void insert(AVLNode280<I> n, I x) {
        if(isEmpty()) {
            rootNode = createNewNode(x);
        } else if(x.compareTo(rootItem()) < 0) {
            AVLTree280<I> leftTree = (AVLTree280<I>) rootLeftSubtree();
            leftTree.insert(x);
            setRootLeftSubtree(leftTree);

            // Recompute the subtree height
            n.height = Integer.max(height((AVLNode280<I>) n.leftNode()), height((AVLNode280<I>) n.rightNode())) + 1;

        } else {
            AVLTree280<I> rightTree = (AVLTree280<I>) rootRightSubtree();
            rightTree.insert(x);
            setRootRightSubtree(rightTree);

            // Recompute the subtree height
           n.height = Integer.max(height((AVLNode280<I>) n.leftNode()), height((AVLNode280<I>) n.rightNode())) + 1;
        }

        //restoreAVLProperty();
    }

    @Override
    public void deleteItem() throws NoCurrentItem280Exception {

    }

    public void restoreAVLProperty() {
//        // Left Rotation (Uses recursion)
//        if(rightSubtreeHeight - leftSubtreeHeight == 2) {
//            rotateLeft();
//            //restoreAVLProperty();
//        }
        // Right Rotation

        // Double Left Rotation

        // Double Right Rotation
    }

    private void rotateLeft() {
        AVLNode280<I> tempRight = (AVLNode280<I>) rootNode.rightNode();
        AVLNode280<I> tempLeft = (AVLNode280<I>) tempRight.leftNode();

        tempRight.setLeftNode(rootNode);
        rootNode.setRightNode(tempLeft);
    }

    private void rotateRight() {

    }

    @Override
    protected AVLNode280<I> createNewNode(I item) {
        return new AVLNode280<I>(item);
    }

    protected int height(AVLNode280<I> node) {
        return node.height;
    }

    @SuppressWarnings("unchecked")
    public static void main(String args[]) {
        AVLTree280<Integer> T = new AVLTree280<>();

        T.insert((AVLNode280)T.rootNode, 8);
        T.insert((AVLNode280)T.rootNode, 10);
        T.insert((AVLNode280)T.rootNode, 11);

        System.out.println(T.toStringByLevel());
        //System.out.println("Left: " + T.leftSubtreeHeight + " Right: " + T.rightSubtreeHeight);
    }
}
